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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/INA220/interface/INA220_Interface.h>
#include <spectre/driver/sensor/INA220/interface/INA220_ConfigurationInterface.h>
#include <spectre/driver/sensor/INA220/interface/INA220_IO_Interface.h>

#include <spectre/driver/interface/Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace INA220
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class INA220_Control : public INA220_Interface,
                       public INA220_ConfigurationInterface
{

public:

           INA220_Control(INA220_IO_Interface & io);
  virtual ~INA220_Control();


  /* INA220 Interface */

  virtual bool readShuntVoltage(int16_t * shunt_voltage) override;
  virtual bool readBusVoltage  (int16_t * bus_voltage  ) override;


  /* INA220 Configuration Interface */

  virtual bool setBusVoltageRange   (BusVoltageRangeSelect     const sel) override;
  virtual bool setShuntPGAGain      (ShuntPGAGainSelect        const sel) override;
  virtual bool setBusADCResolution  (BusADCResolutionSelect    const sel) override;
  virtual bool setShuntADCResolution(ShuntADCResolutionSelect  const sel) override;
  virtual bool setOperatingMode     (OperatingModeSelect       const sel) override;


          void debug_dumpAllRegs    (driver::interface::Debug & debug_interface);

private:

  INA220_IO_Interface & _io;

  void debug_dumpSingleReg  (driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* INA220 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_H_ */
