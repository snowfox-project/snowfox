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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_NORFLASHINFO_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_NORFLASHINFO_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef struct
{
  /* Different NOR flash types support different API's. Some may support chip/sector/
   * subsector-level erase, others might only support chip/sector-level erase. It's
   * the same with write and read access. Viewed from the point-of-view of using this
   * generic NOR driver as interface for an overlying embedded flash filesystem there
   * are actually only 6 parameter that count:
   * - What's the smallest read block size?
   * - What's the smallest program block size?
   * - What's the smallest erase block size and how many erase blocks are available?
   * If one multiplies the erase_size with the block_count the result should be
   * the total NOR flash memory size.
   */
  uint32_t read_size;
  uint32_t prog_size;
  uint32_t erase_size;
  uint32_t block_count; /* Number of erasable blocks in the flash */
} NorFlashInfo;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_NORFLASHINFO_H_ */
