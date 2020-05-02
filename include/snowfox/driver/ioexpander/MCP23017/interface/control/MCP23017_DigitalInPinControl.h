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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_CONTROL_MCP23017_DIGITALINPINCONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_CONTROL_MCP23017_DIGITALINPINCONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdbool.h>

#include <snowfox/driver/ioexpander/MCP23017/interface/MCP23017_Types.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::ioexpander::MCP23017::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP23017_DigitalInPinControl
{

public:

           MCP23017_DigitalInPinControl() { }
  virtual ~MCP23017_DigitalInPinControl() { }


  virtual bool isSet(Port const port, Pin const pin, bool * is_set) = 0;
  virtual bool read (Port const port, uint8_t * port_val          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::ioexpander::MCP23017::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_CONTROL_MCP23017_DIGITALINPINCONTROL_H_ */
