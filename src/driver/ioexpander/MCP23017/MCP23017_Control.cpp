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

#include <spectre/driver/ioexpander/MCP23017/MCP23017_Control.h>

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
  /* TODO */ return false;
}

bool MCP23017_Control::clr(interface::Port const port, interface::Pin const pin)
{
  /* TODO */ return false;
}

bool MCP23017_Control::isSet(interface::Port const port, interface::Pin const pin)
{
  /* TODO */ return false;
}

bool MCP23017_Control::isClr(interface::Port const port, interface::Pin const pin)
{
  /* TODO */ return false;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */
