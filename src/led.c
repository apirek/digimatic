#include "hardware/gpio.h"

#include "led.h"

void led_init(struct led_data* data, const uint pin) {
  data->pin = pin;

  gpio_init(data->pin);
  gpio_set_dir(data->pin, GPIO_OUT);
}

void led_enable(struct led_data* data, const bool enable) {
  gpio_put(data->pin, enable);
}
