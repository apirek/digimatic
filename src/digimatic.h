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
 * Unit of measurement.
 */
enum digimatic_unit {
  /** Millimetre */
  DIGIMATIC_UNIT_MM = 0,
  /** Inch */
  DIGIMATIC_UNIT_IN = 1,
};

/**
 * Driver private data.
 */
struct digimatic_data {
  uint pin_ck, pin_data, pin_req;
  // One readout of ABS DIGIMATIC ID-SX2 is 13 nibbles.
  uint8_t buffer[13];
  size_t len;
};

/**
 * Initialize Digimatic driver and set up GPIOs.
 *
 * @param data Driver private data.
 * @param pin_ck Pin for CK signal.
 * @param pin_data Pin for DATA signal.
 * @param pin_req Pin for REQ signal.
 */
void digimatic_init(struct digimatic_data* data, const uint pin_ck, const uint pin_data, const uint pin_req);

/**
 * Read value from instrument.
 *
 * The value is read and returned in the unit of measurement of the instrument.
 *
 * @param data Driver private data.
 * @param value Pointer to write value to.
 * @returns 0 on success, < 0 on error.
 */
int digimatic_read(struct digimatic_data* data, double* value);

/**
 * Read 1 bit from DATA on CK.
 *
 * Read DATA on falling edge of CK or time out if there is no falling edge during the maximum duration a clock period might take.
 *
 * @param data Driver private data.
 * @param value Pointer to write value to.
 * @returns 0 on success, -1 on timeout.
 */
int digimatic_read_bit(struct digimatic_data* data, uint8_t* value);

/**
 * Parse data from instrument.
 *
 * @param buffer Data.
 * @param len Size of buffer.
 * @param value Pointer to write value to.
 * @param unit Pointer to write unit to.
 * @return 0 on success, < 0 on error.
 */
int digimatic_parse_buffer(const uint8_t* buffer, const size_t len, double* value, enum digimatic_unit* unit);
