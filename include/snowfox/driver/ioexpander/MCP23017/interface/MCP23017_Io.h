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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_IO_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_IO_H_

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

namespace ioexpander
{

namespace MCP23017
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

/* The address values in the enum class 'Register' assume that
 * the registers for Port A and Port B are in the same bank =>
 * IOCON.BANK = '0'.
 */
enum class Register : uint8_t
{
  IODIR_A    = 0x00,
  IODIR_B    = 0x01,
  IPOL_A     = 0x02,
  IPOL_B     = 0x03,
  GPINTEN_A  = 0x04,
  GPINTEN_B  = 0x05,
  DEFVAL_A   = 0x06,
  DEFVAL_B   = 0x07,
  INTCON_A   = 0x08,
  INTCON_B   = 0x09,
  IOCON_A    = 0x0A,
  IOCON_B    = 0x0B,
  GPPU_A     = 0x0C,
  GPPU_B     = 0x0D,
  INTF_A     = 0x0E,
  INTF_B     = 0x0F,
  INTCAP_A   = 0x10,
  INTCAP_B   = 0x11,
  GPIO_A     = 0x12,
  GPIO_B     = 0x13,
  OLAT_A     = 0x14,
  OLAT_B     = 0x15
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP23017_Io
{

public:

           MCP23017_Io() { }
  virtual ~MCP23017_Io() { }


  virtual bool readRegister (Register const reg, uint8_t       * data) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const   data) = 0;

};

/**************************************************************************************
 * PUBLIC PROTOTYPES
 **************************************************************************************/

bool setBit(MCP23017_Io & io, Register const reg, uint8_t const bit_pos);
bool clrBit(MCP23017_Io & io, Register const reg, uint8_t const bit_pos);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_IO_H_ */
