/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDE_SPECTRE_UTIL_BITMANIP_H_
#define INCLUDE_SPECTRE_UTIL_BITMANIP_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <assert.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace util
{

/**************************************************************************************
 * FUNCTIONS
 **************************************************************************************/

inline void setBit(volatile uint8_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 8);
  *reg |= (1<<bit_pos);
}

inline void setBit(volatile uint16_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 16);
  *reg |= (1<<bit_pos);
}

inline void setBit (volatile uint32_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 32);
  *reg |= (1<<bit_pos);
}

inline void clrBit(volatile uint8_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 8);
  *reg &= ~(1<<bit_pos);
}

inline void clrBit(volatile uint16_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 16);
  *reg &= ~(1<<bit_pos);
}

inline void clrBit(volatile uint32_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 32);
  *reg &= ~(1<<bit_pos);
}

inline void toogleBit(volatile uint8_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 8);
  *reg ^= (1<<bit_pos);
}

inline void toogleBit(volatile uint16_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 16);
  *reg ^= (1<<bit_pos);
}

inline void toogleBit(volatile uint32_t * reg, uint8_t const bit_pos)
{
  assert(bit_pos < 32);
  *reg ^= (1<<bit_pos);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* type*/

} /* spectre */

#endif /* INCLUDE_SPECTRE_UTIL_BITMANIP_H_ */
