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

#pragma once

/**
 * Driver private data.
 */
struct led_data {
  uint pin;
};

/**
 * Initialize LED driver and set up GPIOs.
 *
 * @param data Driver private data.
 * @param pin Pin for LED.
 */
void led_init(struct led_data* data, const uint pin);

/**
 * Turn LED on or off.
 * 
 * @param data Driver private data.
 * @param enable On if true, else off.
 */
void led_enable(struct led_data* data, const bool enable);
