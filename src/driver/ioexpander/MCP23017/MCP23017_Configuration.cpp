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

#include <spectre/driver/ioexpander/MCP23017/MCP23017_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace ioexpander
{

namespace MCP23017
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MCP23017_Configuration::MCP23017_Configuration(interface::MCP23017_Io & io)
: _io(io)
{

}

MCP23017_Configuration::~MCP23017_Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool MCP23017_Configuration::setDirection(interface::Port const port, interface::Pin const pin, interface::Direction const direction)
{
  uint8_t reg_iodir_content = 0;

  if(!_io.readRegister(toReg_IODIR(port), &reg_iodir_content)) return false;

  switch(direction)
  {
  case interface::Direction::Input : reg_iodir_content |=  static_cast<uint8_t>(pin); break;
  case interface::Direction::Output: reg_iodir_content &= ~static_cast<uint8_t>(pin); break;
  }

  if(!_io.writeRegister(toReg_IODIR(port), reg_iodir_content)) return false;

  return true;
}

bool MCP23017_Configuration::enablePullUp(interface::Port const port, interface::Pin const pin)
{
  uint8_t reg_gppu_content = 0;

  if(!_io.readRegister(toReg_GPPU(port), &reg_gppu_content)) return false;

  reg_gppu_content |= static_cast<uint8_t>(pin);

  if(!_io.writeRegister(toReg_GPPU(port), reg_gppu_content)) return false;

  return true;
}

bool MCP23017_Configuration::disablePullUp(interface::Port const port, interface::Pin const pin)
{
  uint8_t reg_gppu_content = 0;

  if(!_io.readRegister(toReg_GPPU(port), &reg_gppu_content)) return false;

  reg_gppu_content &= ~static_cast<uint8_t>(pin);

  if(!_io.writeRegister(toReg_GPPU(port), reg_gppu_content)) return false;

  return true;
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

interface::Register MCP23017_Configuration::toReg_IODIR(interface::Port const port)
{
  if  (port == interface::Port::A) return interface::Register::IODIR_A;
  else                             return interface::Register::IODIR_B;
}

interface::Register MCP23017_Configuration::toReg_GPPU(interface::Port const port)
{
  if  (port == interface::Port::A) return interface::Register::GPPU_A;
  else                             return interface::Register::GPPU_B;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */
