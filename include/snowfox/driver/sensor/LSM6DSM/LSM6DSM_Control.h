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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/LSM6DSM/interface/LSM6DSM_Control.h>

#include <snowfox/hal/interface/delay/Delay.h>

#include <snowfox/driver/sensor/LSM6DSM/interface/LSM6DSM_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::LSM6DSM
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LSM6DSM_Control final : public interface::LSM6DSM_Control
{

public:

           LSM6DSM_Control(interface::LSM6DSM_Io & io,
                           hal::interface::Delay & delay);
  virtual ~LSM6DSM_Control();


  virtual bool reset() override;

private:

  interface::LSM6DSM_Io & _io;
  hal::interface::Delay & _delay;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::LSM6DSM */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_CONTROL_H_ */