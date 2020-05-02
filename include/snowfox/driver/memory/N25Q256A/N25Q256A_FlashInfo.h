/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_FLASHINFO_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_FLASHINFO_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/NorFlashInfo.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::N25Q256A
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

/* Designed initializes currently trigger an error due to not being allowed
 * within ISO C++ and '-Werror=pedantic' being enabled as a compile flag. There
 * are currently efforts underway to reinclude designed initializer lists with
 * C++20: For further information take a look at the following link:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0329r4.pdf
 */
static NorFlashInfo constexpr FLASH_INFO = 
{
  /* .read_size   = */    1, /* The N25Q256A allows byte-wise read access */
  /* .prog_size   = */  256, /* The N25Q256A can be programmed in 256 byte sized chunks */
  /* .erase_size  = */ 4096, /* The smallest erase size on the N25Q256A is a subsector erase */
  /* .block_count = */ 8192,
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::N25Q256A */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_FLASHINFO_H_ */
