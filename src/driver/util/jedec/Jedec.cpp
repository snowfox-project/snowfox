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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/util/jedec/Jedec.h>

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
 * DEFINE
 **************************************************************************************/

#define JEDEC_DENSITY_CODE_MASK (0x1F)

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

ManufacturerId toManufacturerId(uint8_t const dev_id_byte_0, uint8_t const dev_id_byte_1, uint8_t const dev_id_byte_2)
{
  return static_cast<ManufacturerId>(dev_id_byte_0);
}

DensityCode toDensityCode(uint8_t const dev_id_byte_0, uint8_t const dev_id_byte_1, uint8_t const dev_id_byte_2)
{
  return static_cast<DensityCode>(dev_id_byte_1 & JEDEC_DENSITY_CODE_MASK);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* jedec */

} /* util */

} /* driver */

} /* spectre */
