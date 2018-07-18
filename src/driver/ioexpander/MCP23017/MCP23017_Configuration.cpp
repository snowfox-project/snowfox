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

bool MCP23017_Configuration::configAsInput(interface::Port const port, interface::Pin const pin, interface::PullUpMode const pull_up_mode)
{
  if(!setDirection (port, pin, Direction::Input)) return false;
  if(!setPullUpMode(port, pin, pull_up_mode    )) return false;

  return true;
}

bool MCP23017_Configuration::configAsOutput(interface::Port const port, interface::Pin const pin)
{
  return setDirection(port, pin, Direction::Output);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

bool MCP23017_Configuration::setDirection(interface::Port const port, interface::Pin const pin, Direction const direction)
{
  interface::Register const reg_iodir_addr    = interface::toReg_IODIR(port);
  uint8_t                   reg_iodir_content = 0;

  if(!_io.readRegister(reg_iodir_addr, &reg_iodir_content)) return false;

  switch(direction)
  {
  case Direction::Input : reg_iodir_content |=  static_cast<uint8_t>(pin); break;
  case Direction::Output: reg_iodir_content &= ~static_cast<uint8_t>(pin); break;
  }

  if(!_io.writeRegister(reg_iodir_addr, reg_iodir_content)) return false;

  return true;
}

bool MCP23017_Configuration::setPullUpMode(interface::Port const port, interface::Pin const pin, interface::PullUpMode const pull_up_mode)
{
  interface::Register const reg_gppu_addr    = interface::toReg_GPPU(port);
  uint8_t                   reg_gppu_content = 0;

  if(!_io.readRegister(reg_gppu_addr, &reg_gppu_content)) return false;

  switch(pull_up_mode)
  {
  case interface::PullUpMode::Enabled : reg_gppu_content |=  static_cast<uint8_t>(pin); break;
  case interface::PullUpMode::Disabled: reg_gppu_content &= ~static_cast<uint8_t>(pin); break;
  }

  if(!_io.writeRegister(reg_gppu_addr, reg_gppu_content)) return false;

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */
