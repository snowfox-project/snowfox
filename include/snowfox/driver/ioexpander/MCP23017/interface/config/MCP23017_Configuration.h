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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_CONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdbool.h>

#include <snowfox/driver/ioexpander/MCP23017/interface/MCP23017_Types.h>

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
 * TYPEDEFS
 **************************************************************************************/

enum class PullUpMode
{
  Enabled, Disabled
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP23017_Configuration
{

public:

           MCP23017_Configuration() { }
  virtual ~MCP23017_Configuration() { }


  virtual bool configAsInput (Port const port, Pin const pin, PullUpMode const pull_up_mode) = 0;
  virtual bool configAsOutput(Port const port, Pin const pin                               ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_CONFIGURATION_H_ */
