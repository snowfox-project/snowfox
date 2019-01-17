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

#include <snowfox/driver/ioexpander/MCP23017/MCP23017_Control.h>

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

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MCP23017_Control::MCP23017_Control(interface::MCP23017_Io & io)
: _io(io)
{

}

MCP23017_Control::~MCP23017_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool MCP23017_Control::set(interface::Port const port, interface::Pin const pin)
{
  return interface::setBit(_io, interface::toReg_GPIO(port), static_cast<uint8_t>(pin));
}

bool MCP23017_Control::clr(interface::Port const port, interface::Pin const pin)
{
  return interface::clrBit(_io, interface::toReg_GPIO(port), static_cast<uint8_t>(pin));
}

bool MCP23017_Control::write(interface::Port const port, uint8_t const port_val)
{
  return _io.writeRegister(interface::toReg_GPIO(port), port_val);
}

bool MCP23017_Control::isSet(interface::Port const port, interface::Pin const pin, bool * is_set)
{
  uint8_t reg_gpio_val = 0;

  if(_io.readRegister(interface::toReg_GPIO(port), &reg_gpio_val))
  {
    uint8_t const bit_pos  = static_cast<uint8_t>(pin);
    uint8_t const bit_mask = (1<<bit_pos);

    *is_set = (reg_gpio_val & bit_mask) == bit_mask;

    return true;
  }
  else
  {
    return false;
  }
}

bool MCP23017_Control::read(interface::Port const port, uint8_t * port_val)
{
  return _io.readRegister(interface::toReg_GPIO(port), port_val);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* snowfox */
