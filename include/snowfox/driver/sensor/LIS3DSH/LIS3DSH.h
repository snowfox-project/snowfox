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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3DSH_LIS3DSH_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3DSH_LIS3DSH_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/sensor/LIS3DSH/interface/LIS3DSH_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace LIS3DSH
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_OUTPUT_DATA_RATE  = 0; /* Arg: interface::OutputDataRateSelect * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_FULL_SCALE_RANGE  = 1; /* Arg: interface::FullScaleRangeSelect * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_FILTER_BANDWIDTH  = 2; /* Arg: interface::FilterBandwidth      * -> uint8_t *  */
static uint32_t constexpr IOCTL_ENABLE_XYZ            = 3; /* Arg: none                                            */
static uint32_t constexpr IOCTL_ENABLE_X              = 4; /* Arg: none                                            */
static uint32_t constexpr IOCTL_ENABLE_Y              = 5; /* Arg: none                                            */
static uint32_t constexpr IOCTL_ENABLE_Z              = 6; /* Arg: none                                            */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3DSH final : public driver::interface::Driver
{

public:

           LIS3DSH(interface::LIS3DSH_Control & ctrl);
  virtual ~LIS3DSH();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;

private:

  interface::LIS3DSH_Control & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3DSH_LIS3DSH_H_ */
