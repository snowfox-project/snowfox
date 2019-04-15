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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_INTERFACE_LSM6DSM_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_INTERFACE_LSM6DSM_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/LSM6DSM/interface/LSM6DSM_RegisterBits.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace LSM6DSM
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LSM6DSM_Control
{

public:

           LSM6DSM_Control() { }
  virtual ~LSM6DSM_Control() { }


  virtual bool reset() = 0;
  
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* LSM6DSM */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_INTERFACE_LSM6DSM_CONTROL_H_ */