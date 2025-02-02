/*
  Digimatic USB
  Copyright (C) 2024 Axel Pirek

  This program is free software: you can redistribute it and/or modify it under the terms of the
  GNU General Public License version 3 as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program.
  If not, see <https://www.gnu.org/licenses/>.
*/

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
