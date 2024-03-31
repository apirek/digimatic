#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"

#include "digimatic.h"
#include "led.h"

#define DIGIMATIC_PIN_DATA 3
#define DIGIMATIC_PIN_CK 4
#define DIGIMATIC_PIN_REQ 5

#define LED_PIN 25

int main() {
  stdio_init_all();

#ifdef LED_PIN
  struct led_data act_led;
  led_init(&act_led, LED_PIN);
  led_enable(&act_led, true);
#endif

  struct digimatic_data digimatic;
  digimatic_init(&digimatic, DIGIMATIC_PIN_CK, DIGIMATIC_PIN_DATA, DIGIMATIC_PIN_REQ);

  double value;
  int c, r;
  while (true) {
    // Trigger on any input.
    if ((c = getchar_timeout_us(-1)) != PICO_ERROR_TIMEOUT) {
#ifdef LED_PIN
      led_enable(&act_led, false);
#endif

      if ((r = digimatic_read(&digimatic, &value)) < 0) {
        printf("# Error reading from instrument: %d\n", r);
      } else {
        printf("%f\n", value);
      }

#ifdef LED_PIN
      led_enable(&act_led, true);
#endif
    }
  }
}
