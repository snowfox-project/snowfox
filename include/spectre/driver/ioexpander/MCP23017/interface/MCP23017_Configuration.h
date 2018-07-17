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

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_CONFIGURATION_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

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
 * DEFINES
 **************************************************************************************/

#define MCP23017_REG_IODIR_IO7_bm (1<<7)
#define MCP23017_REG_IODIR_IO6_bm (1<<6)
#define MCP23017_REG_IODIR_IO5_bm (1<<5)
#define MCP23017_REG_IODIR_IO4_bm (1<<4)
#define MCP23017_REG_IODIR_IO3_bm (1<<3)
#define MCP23017_REG_IODIR_IO2_bm (1<<2)
#define MCP23017_REG_IODIR_IO1_bm (1<<1)
#define MCP23017_REG_IODIR_IO0_bm (1<<0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Port : uint8_t
{
  A, B
};

enum class Pin : uint8_t
{
  IO0 = MCP23017_REG_IODIR_IO0_bm,
  IO1 = MCP23017_REG_IODIR_IO1_bm,
  IO2 = MCP23017_REG_IODIR_IO2_bm,
  IO3 = MCP23017_REG_IODIR_IO3_bm,
  IO4 = MCP23017_REG_IODIR_IO4_bm,
  IO5 = MCP23017_REG_IODIR_IO5_bm,
  IO6 = MCP23017_REG_IODIR_IO5_bm,
  IO7 = MCP23017_REG_IODIR_IO7_bm
};

enum class Direction : uint8_t
{
  Input, Output
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP23017_Configuration
{

public:

           MCP23017_Configuration() { }
  virtual ~MCP23017_Configuration() { }


  virtual bool setDirection(Port const port, Pin const pin, Direction const direction) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_INTERFACE_MCP23017_CONFIGURATION_H_ */
