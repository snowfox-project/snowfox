/**
 * Snowfox is a modular RTOS with extensive IO support.
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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/N25Q256A/util/N25Q256A_Util.h>

#include <snowfox/driver/memory/N25Q256A/N25Q256A_Capabilities.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace N25Q256A
{

namespace util
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

bool isValidSector(uint32_t const sector_num)
{
  if  (sector_num < CAPABILITIES.sector_num) return true; 
  else                                       return false;
}

uint32_t toSectorBaseAddr(uint32_t const sector_num)
{
  uint32_t const sector_base_addr = sector_num * CAPABILITIES.sector_size;
  return sector_base_addr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* util */

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */
