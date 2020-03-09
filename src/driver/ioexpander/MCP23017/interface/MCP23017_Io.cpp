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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/ioexpander/MCP23017/interface/MCP23017_Io.h>

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
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool setBit(MCP23017_Io & io, Register const reg, uint8_t const bit_pos)
{
  uint8_t reg_content = 0;

  if(!io.readRegister(reg, &reg_content)) return false;

  reg_content |= (1<<bit_pos);

  return io.writeRegister(reg, reg_content);
}

bool clrBit(MCP23017_Io & io, Register const reg, uint8_t const bit_pos)
{
  uint8_t reg_content = 0;

  if(!io.readRegister(reg, &reg_content)) return false;

  reg_content &= ~(1<<bit_pos);

  return io.writeRegister(reg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* snowfox */
