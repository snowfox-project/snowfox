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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_INTERFACE_N25Q256A_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_INTERFACE_N25Q256A_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

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

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class N25Q256A_Control
{

public:

  virtual ~N25Q256A_Control() { }

  virtual bool isEraseInProgress    (bool * is_erase_in_progress)  = 0;

  virtual bool read (uint32_t const read_addr,  uint8_t       * buffer, uint32_t const num_bytes) = 0;
  virtual bool write(uint32_t const write_addr, uint8_t const * buffer, uint32_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_INTERFACE_N25Q256A_CONTROL_H_ */
