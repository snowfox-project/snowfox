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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_INTERFACE_AT45DBX_IO_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_INTERFACE_AT45DBX_IO_H_

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

namespace AT45DBx
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AT45DBx_Io
{

public:

           AT45DBx_Io() { }
  virtual ~AT45DBx_Io() { }


  virtual void exchange(uint8_t const * buf_cmd_in                                                                ) = 0;
  virtual void exchange(uint8_t const * buf_cmd_in, uint8_t       * buf_cmd_out                                   ) = 0;
  virtual void exchange(uint8_t const * buf_cmd_in, uint8_t const * buf_data_in,  uint16_t const buf_data_in_size ) = 0;
  virtual void exchange(uint8_t const * buf_cmd_in, uint8_t       * buf_data_out, uint16_t const buf_data_out_size) = 0;


  static constexpr uint16_t COMMAND_BUFFER_SIZE = 4;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* AT45DBx */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_INTERFACE_AT45DBX_IO_H_ */
