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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/BMG160/interface/BMG160_Interface.h>
#include <snowfox/driver/sensor/BMG160/interface/BMG160_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMG160
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMG160_Control : public BMG160_Interface,
                       public BMG160_Configuration
{

public:

           BMG160_Control() { }
  virtual ~BMG160_Control() { }


  /* BMG160 Interface */

  virtual bool readXYZAxis    (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) = 0;
  virtual bool readXAxis      (int16_t * raw_x                                  ) = 0;
  virtual bool readYAxis      (int16_t * raw_y                                  ) = 0;
  virtual bool readZAxis      (int16_t * raw_z                                  ) = 0;
  virtual bool readTemperature(int8_t  * raw_temp                               ) = 0;


  /* BMG160 Configuration Interface */

  virtual bool setOutputDataRateAndBandwith (OutputDataRateAndBandwith const output_data_rate_and_bandwidth) = 0;
  virtual bool setFullScaleRange            (FullScaleRange            const full_scale_range              ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* BMG160 */

} /* sensor */

} /* driver */

} /* snowfox */



#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONTROL_H_ */
