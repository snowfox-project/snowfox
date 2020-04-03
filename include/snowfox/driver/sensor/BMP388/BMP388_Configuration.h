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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_BMP388_CONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_BMP388_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/BMP388/interface/BMP388_Configuration.h>

#include <snowfox/driver/sensor/BMP388/interface/BMP388_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMP388_Configuration : public interface::BMP388_Configuration
{

public:

           BMP388_Configuration(interface::BMP388_Io & io);
  virtual ~BMP388_Configuration();


  virtual void readCalibData                (interface::CalibrationData & calib_data)                override;
  virtual void configPressureOversampling   (interface::PressureOversampling const over_sampling)    override;
  virtual void configTemperatureOversampling(interface::TemperatureOversampling const over_sampling) override;
  virtual void configOutputDataRate         (interface::OutputDataRate const odr)                    override;
  virtual void setIntPinOutputType          (interface::IntPinOutputType const type)                 override;
  virtual void enableInterrupt              (interface::Interrupt const interrupt)                   override;
  virtual void disableInterrupt             (interface::Interrupt const interrupt)                   override;
  virtual void configPowerMode              (interface::PowerMode const mode)                        override;


private:

  interface::BMP388_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_BMP388_CONFIGURATION_H_ */
