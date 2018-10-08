/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_UTIL_JEDEC_DENSITYCODE_H_
#define INCLUDE_SPECTRE_DRIVER_UTIL_JEDEC_DENSITYCODE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace util
{

namespace jedec
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class DensityCode : uint8_t
{
  D_1MBit  = 0x02,
  D_2MBit  = 0x03,
  D_4MBit  = 0x04,
  D_8MBit  = 0x05,
  D_16MBit = 0x06,
  D_32MBit = 0x07,
  D_64MBit = 0x08
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* jedec */

} /* util */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_UTIL_JEDEC_DENSITYCODE_H_ */
