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

#include <spectre/driver/memory/AT45DBx/AT45DBx_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * DEFINE
 **************************************************************************************/

#define AT45DBx_RDDEVID (0x9F)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AT45DBx_Configuration::AT45DBx_Configuration(interface::AT45DBx_Io & io)
: _io(io)
{

}

AT45DBx_Configuration::~AT45DBx_Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

util::jedec::JedecCode AT45DBx_Configuration::readDeviceId()
{
  uint8_t const buf_cmd_in [interface::AT45DBx_Io::COMMAND_BUFFER_SIZE] = {AT45DBx_RDDEVID, 0, 0, 0};
  uint8_t       buf_cmd_out[interface::AT45DBx_Io::COMMAND_BUFFER_SIZE] = {0,               0, 0, 0};

  _io.exchange(buf_cmd_in, buf_cmd_out);

  util::jedec::JedecCode const jedec_code(buf_cmd_out + 1);

  return jedec_code;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* spectre */
