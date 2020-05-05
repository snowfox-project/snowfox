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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/INA220/interface/INA220_Control.h>

#include <snowfox/driver/sensor/INA220/interface/INA220_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::INA220
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class INA220_Control final : public interface::INA220_Control
{

public:

           INA220_Control(interface::INA220_Io & io);
  virtual ~INA220_Control();


  virtual bool readShuntVoltage     (int16_t * shunt_voltage) override;
  virtual bool readBusVoltage       (int16_t * bus_voltage  ) override;


  virtual bool setBusVoltageRange   (interface::BusVoltageRange    const bus_voltage_range   ) override;
  virtual bool setShuntPgaGain      (interface::ShuntPgaGain       const shunt_pga_gain      ) override;
  virtual bool setBusAdcResolution  (interface::BusAdcResolution   const bus_adc_resolution  ) override;
  virtual bool setShuntAdcResolution(interface::ShuntAdcResolution const shunt_adc_resolution) override;
  virtual bool setOperatingMode     (interface::OperatingMode      const operating_mode      ) override;


private:

  interface::INA220_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::INA220 */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_H_ */
