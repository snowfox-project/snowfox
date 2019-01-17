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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/LIS3MDL/interface/LIS3MDL_Interface.h>
#include <snowfox/driver/sensor/LIS3MDL/interface/LIS3MDL_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace LIS3MDL
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3MDL_Control : public LIS3MDL_Interface,
                        public LIS3MDL_Configuration
{

public:

           LIS3MDL_Control() { }
  virtual ~LIS3MDL_Control() { }


  /* LIS3MDL Interface */

  virtual bool checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz) = 0;
  virtual bool checkIfNewDataIsAvailable_X  (bool * is_new_data_available_x  ) = 0;
  virtual bool checkIfNewDataIsAvailable_Y  (bool * is_new_data_available_y  ) = 0;
  virtual bool checkIfNewDataIsAvailable_Z  (bool * is_new_data_available_z  ) = 0;

  virtual bool checkIfDataOverrun_XYZ       (bool * is_data_overrun_xyz      ) = 0;
  virtual bool checkIfDataOverrun_X         (bool * is_data_overrun_x        ) = 0;
  virtual bool checkIfDataOverrun_Y         (bool * is_data_overrun_y        ) = 0;
  virtual bool checkIfDataOverrun_Z         (bool * is_data_overrun_z        ) = 0;

  virtual bool readXYZAxis                  (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) = 0;
  virtual bool readXAxis                    (int16_t * raw_x                                  ) = 0;
  virtual bool readYAxis                    (int16_t * raw_y                                  ) = 0;
  virtual bool readZAxis                    (int16_t * raw_z                                  ) = 0;
  virtual bool readTemperature              (int16_t * raw_temp                               ) = 0;


  /* LIS3MDL Configuration */

  virtual bool setOperationMode_XY    (OperationMode_XY const operation_mode_xy) = 0;
  virtual bool setOperationMode_Z     (OperationMode_Z  const operation_mode_z ) = 0;
  virtual bool setOutputDataRate      (OutputDataRate   const output_data_rate ) = 0;
  virtual bool setFullScaleRange      (FullScaleRange   const full_scale_range ) = 0;
  virtual bool setConversionMode      (ConversionMode   const conversion_mode  ) = 0;
  virtual bool enableTemperatureSensor(                                        ) = 0;
  virtual bool enableBlockDataUpdate  (                                        ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_CONTROL_H_ */
