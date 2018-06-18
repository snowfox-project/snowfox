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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_L3GD20_DEBUG_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_L3GD20_DEBUG_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/debug/interface/Debug.h>

#include <spectre/hal/interface/flash/Flash.h>

#include <spectre/driver/sensor/L3GD20/interface/L3GD20_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace L3GD20
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class L3GD20_Debug
{

public:

  static void debug_dumpAllRegs(debug::interface::Debug & debug_interface,
                                hal::interface::Flash   & flash,
                                interface::L3GD20_Io    & io);

private:

  L3GD20_Debug() { }
  L3GD20_Debug(L3GD20_Debug const & other) { }


  static void debug_dumpSingleReg(debug::interface::Debug   & debug_interface,
                                  hal::interface::Flash     & flash,
                                  interface::L3GD20_Io      & io,
                                  char                const * msg,
                                  interface::Register const   reg);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* L3GD20 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_L3GD20_DEBUG_H_ */
