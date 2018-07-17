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

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONFIGURATION_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/ioexpander/MCP23017/interface/config/MCP23017_Configuration.h>

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

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP23017_Configuration : public interface::MCP23017_Configuration
{

public:

           MCP23017_Configuration(interface::MCP23017_Io & io);
  virtual ~MCP23017_Configuration();


  virtual bool setDirection (interface::Port const port, interface::Pin const pin, interface::Direction const direction) override;
  virtual bool enablePullUp (interface::Port const port, interface::Pin const pin                                      ) override;
  virtual bool disablePullUp(interface::Port const port, interface::Pin const pin                                      ) override;


private:

  interface::MCP23017_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONFIGURATION_H_ */
