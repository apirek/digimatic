#include <string.h>

#include "hardware/gpio.h"
#include "pico/time.h"

#include "digimatic.h"

void digimatic_init(struct digimatic_data* data, const uint pin_ck, const uint pin_data, const uint pin_req) {
  data->pin_ck = pin_ck;
  data->pin_data = pin_data;
  data->pin_req = pin_req;
  memset(data->buffer, 0, sizeof(data->buffer));
  data->len = 0;

  gpio_init(data->pin_ck);
  gpio_pull_up(data->pin_ck);

  gpio_init(data->pin_data);
  gpio_pull_up(data->pin_data);

  gpio_init(data->pin_req);
  gpio_set_dir(data->pin_req, GPIO_OUT);
  gpio_put(data->pin_req, 1);
  // Invert if REQ is connected via transistor.
  gpio_set_outover(data->pin_req, GPIO_OVERRIDE_INVERT);
}

int digimatic_parse_buffer(const uint8_t* buffer, const size_t len, double* value, enum digimatic_unit* unit) {
  // Check buffer length.
  if (len < 13) {
    return -1;
  }
  // First 4 nibbles are 0xF, ignore.
  // Parse sign.
  int sign = 0;
  switch (buffer[4]) {
    case 0x00:
      sign = 1;
      break;
    case 0x08:
      sign = -1;
      break;
    default:
      // Bad sign.
      return -1;
  }
  // Parse decimal point.
  int div = 0;
  switch (buffer[11]) {
    case 0x02:
      div = 100;
      break;
    case 0x03:
      div = 1000;
      break;
    case 0x04:
      div = 10000;
      break;
    case 0x05:
      div = 100000;
      break;
    default:
      // Bad decimal point.
      return -1;
  }
  // Parse value.
  if (value != NULL) {
    *value = (double) ((uint32_t) buffer[5] * 100000
        + buffer[6] * 10000
        + buffer[7] * 1000
        + buffer[8] * 100
        + buffer[9] * 10
        + buffer[10]
      ) / div * sign;
  }
  // Parse unit.
  if (unit != NULL) {
    switch (buffer[12]) {
      case 0x00:
        *unit = DIGIMATIC_UNIT_MM;
        break;
      case 0x01:
        *unit = DIGIMATIC_UNIT_IN;
        break;
      default:
        // Bad value for unit.
        return -1;
    }
  }
  return 0;
}

int digimatic_read_bit(struct digimatic_data* data, uint8_t* value) {
  // Timeout when no clock after (T2 + T3 + T4) seconds.
  const uint64_t now = time_us_64();
  const uint64_t timeout = now + 540;
  // Wait for CK to be high.
  while (time_us_64() <= timeout) {
    if (gpio_get(data->pin_ck)) {
      break;
    }
  }
  // Wait for CK to go low.
  while (time_us_64() <= timeout) {
    if (!gpio_get(data->pin_ck)) {
      *value = gpio_get(data->pin_data);
      return 0;
    }
  }
  return -1;
}

int digimatic_read(struct digimatic_data* data, double* value) {
  // Clear buffer.
  memset(data->buffer, 0, sizeof(data->buffer));
  data->len = 0;

  // Pull down REQ.
  gpio_put(data->pin_req, 0);

  // Read data.
  size_t i = 0;
  uint8_t bit = 0;
  // Timeout when no data after T1 seconds.
  const uint64_t now = time_us_64();
  const uint64_t timeout = now + 937500;
  while (!i && time_us_64() <= timeout) {
    // Read until clock timeout.
    while (digimatic_read_bit(data, &bit) >= 0) {
      // Release REQ.
      gpio_put(data->pin_req, 1);
      // Check bounds.
      if (i >= sizeof(data->buffer) * 8) {
        return -2;
      }
      data->buffer[i / 4] |= (bit << (i % 4));
      ++i;
    }
  }
  // Timeout, no data.
  if (!i) {
    return -1;
  }
  // Parse data.
  data->len = i / 4 + (i % 4 != 0);
  return digimatic_parse_buffer(data->buffer, data->len, value, NULL);
}
