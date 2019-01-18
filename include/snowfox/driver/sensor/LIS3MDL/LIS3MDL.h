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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/sensor/LIS3MDL/interface/LIS3MDL_Control.h>

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

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_OPERATION_MODE_XY  = 0; /* Arg: interface::OperationMode_XY     * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_OPERATION_MODE_Z   = 1; /* Arg: interface::OperationMode_Z      * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_OUTPUT_DATA_RATE   = 2; /* Arg: interface::OutputDataRateSelect * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_FULL_SCALE_RANGE   = 3; /* Arg: interface::FullScaleRangeSelect * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_CONVERSION_MODE    = 4; /* Arg: interface::ConversionMode       * -> uint8_t *  */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3MDL : public driver::interface::Driver
{

public:

           LIS3MDL(interface::LIS3MDL_Control & ctrl);
  virtual ~LIS3MDL();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;

private:

  interface::LIS3MDL_Control & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_ */
