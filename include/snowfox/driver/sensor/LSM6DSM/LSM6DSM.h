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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/sensor/LSM6DSM/interface/LSM6DSM_Control.h>
#include <snowfox/driver/sensor/LSM6DSM/interface/LSM6DSM_Configuration.h>

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

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LSM6DSM final : public driver::interface::Driver
{

public:

           LSM6DSM(interface::LSM6DSM_Configuration & config,
                   interface::LSM6DSM_Control       & control);
  virtual ~LSM6DSM();


  virtual bool    open (                                                  ) override final;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override final;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override final;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override final;
  virtual void    close(                                                  ) override final;

private:

  interface::LSM6DSM_Configuration & _config;
  interface::LSM6DSM_Control       & _control;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LSM6DSM */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_H_ */