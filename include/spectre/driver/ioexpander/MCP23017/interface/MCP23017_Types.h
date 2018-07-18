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

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_TYPES_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_TYPES_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <spectre/driver/ioexpander/MCP23017/interface/MCP23017_Io.h>

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

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Port
{
  A, B
};

enum class Pin : uint8_t
{
  IO0 = 0,
  IO1 = 1,
  IO2 = 2,
  IO3 = 3,
  IO4 = 4,
  IO5 = 5,
  IO6 = 6,
  IO7 = 7
};

/**************************************************************************************
 * FUNCTION PROTOTYPES
 **************************************************************************************/

Register toReg_GPPU (Port const port);
Register toReg_GPIO (Port const port);
Register toReg_IODIR(Port const port);


/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_TYPES_H_ */
