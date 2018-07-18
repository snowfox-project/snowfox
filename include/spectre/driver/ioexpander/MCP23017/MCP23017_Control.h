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

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/ioexpander/MCP23017/interface/control/MCP23017_Control.h>

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

class MCP23017_Control : public interface::MCP23017_Control
{

public:

           MCP23017_Control(interface::MCP23017_Io & io);
  virtual ~MCP23017_Control();


  virtual bool set  (interface::Port const port, interface::Pin const pin               ) override;
  virtual bool clr  (interface::Port const port, interface::Pin const pin               ) override;
  virtual bool isSet(interface::Port const port, interface::Pin const pin, bool & is_set) override;
  virtual bool isClr(interface::Port const port, interface::Pin const pin, bool & is_clr) override;


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

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_CONTROL_H_ */
