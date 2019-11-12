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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/ioexpander/MCP23017/interface/control/MCP23017_Control.h>

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

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP23017_Control final : public interface::MCP23017_Control
{

public:

           MCP23017_Control(interface::MCP23017_Io & io);
  virtual ~MCP23017_Control();


  virtual bool set  (interface::Port const port, interface::Pin const   pin               ) override final;
  virtual bool clr  (interface::Port const port, interface::Pin const   pin               ) override final;
  virtual bool write(interface::Port const port, uint8_t        const   port_val          ) override final;

  virtual bool isSet(interface::Port const port, interface::Pin const   pin, bool * is_set) override final;
  virtual bool read (interface::Port const port, uint8_t              * port_val          ) override final;


private:

  interface::MCP23017_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONTROL_H_ */
