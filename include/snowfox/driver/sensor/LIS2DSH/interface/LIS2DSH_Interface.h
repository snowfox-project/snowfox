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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::LIS2DSH::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS2DSH_Interface
{

public:

           LIS2DSH_Interface() { }
  virtual ~LIS2DSH_Interface() { }


  virtual bool checkIfNewDataIsAvailable_XYZ        (bool * is_new_data_available_xyz ) = 0;
  virtual bool checkIfNewDataIsAvailable_X          (bool * is_new_data_available_x   ) = 0;
  virtual bool checkIfNewDataIsAvailable_Y          (bool * is_new_data_available_y   ) = 0;
  virtual bool checkIfNewDataIsAvailable_Z          (bool * is_new_data_available_z   ) = 0;
  virtual bool checkIfNewDataIsAvailable_Temperature(bool * is_new_data_available_temp) = 0;

  virtual bool checkIfDataOverrun_XYZ               (bool * is_data_overrun_xyz       ) = 0;
  virtual bool checkIfDataOverrun_X                 (bool * is_data_overrun_x         ) = 0;
  virtual bool checkIfDataOverrun_Y                 (bool * is_data_overrun_y         ) = 0;
  virtual bool checkIfDataOverrun_Z                 (bool * is_data_overrun_z         ) = 0;
  virtual bool checkIfDataOverrun_Temperature       (bool * is_data_overrun_temp      ) = 0;

  virtual bool readXYZAxis                          (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) = 0;
  virtual bool readXAxis                            (int16_t * raw_x                                  ) = 0;
  virtual bool readYAxis                            (int16_t * raw_y                                  ) = 0;
  virtual bool readZAxis                            (int16_t * raw_z                                  ) = 0;
  virtual bool readTemperature                      (int16_t * raw_temp                               ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::LIS2DSH::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_INTERFACE_H_ */
