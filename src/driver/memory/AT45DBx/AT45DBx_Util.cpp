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

#include <snowfox/driver/memory/AT45DBx/AT45DBx_Util.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

uint32_t getNumPages(util::jedec::DensityCode const density_code)
{
  switch(density_code)
  {
  case util::jedec::DensityCode::D_1MBit : return  512; break;
  case util::jedec::DensityCode::D_2MBit : return 1024; break;
  case util::jedec::DensityCode::D_4MBit : return 2048; break;
  case util::jedec::DensityCode::D_8MBit : return 4096; break;
  case util::jedec::DensityCode::D_16MBit: return 4096; break;
  case util::jedec::DensityCode::D_32MBit: return 8192; break;
  case util::jedec::DensityCode::D_64MBit: return 8192; break;
  default                                : return    0; break;
  }
}

uint32_t getPageShift(util::jedec::DensityCode const density_code)
{
  switch(density_code)
  {
  case util::jedec::DensityCode::D_1MBit : return  8; break;
  case util::jedec::DensityCode::D_2MBit : return  8; break;
  case util::jedec::DensityCode::D_4MBit : return  8; break;
  case util::jedec::DensityCode::D_8MBit : return  8; break;
  case util::jedec::DensityCode::D_16MBit: return  9; break;
  case util::jedec::DensityCode::D_32MBit: return  9; break;
  case util::jedec::DensityCode::D_64MBit: return 10; break;
  default                                : return  0; break;
  }
}

uint32_t getPageSize(uint32_t const page_shift)
{
  uint32_t const page_size = (1 << page_shift);
  return page_size;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* snowfox */
