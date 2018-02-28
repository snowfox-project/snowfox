/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/TPA81/interface/TPA81_Interface.h>
#include <spectre/driver/sensor/TPA81/interface/TPA81_IO_Interface.h>

#include <spectre/debug/interface/Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace TPA81
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TPA81 : public TPA81_Interface
{

public:

           TPA81(TPA81_IO_Interface & io);
  virtual ~TPA81();


  /* TPA81 Interface */

  virtual bool readSoftwareRevision   (uint8_t         * software_revision  ) override;
  virtual bool readAmbientTemperature (uint8_t         * ambient_temperature) override;
  virtual bool readThermophileArray   (ThermophileData * thermo_data        ) override;


          void debug_dumpAllRegs      (debug::interface::Debug & debug_interface);

private:

  TPA81_IO_Interface & _io;

  bool readSingleRegister   (RegisterSelect const reg_sel, uint8_t        * data);
  bool writeSingleRegister  (RegisterSelect const reg_sel, uint8_t const    data);

  void debug_dumpSingleReg  (debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* TPA81 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_H_ */
