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
