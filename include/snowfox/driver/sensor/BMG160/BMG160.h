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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_BMG160_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_BMG160_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/sensor/BMG160/interface/BMG160_Control.h>

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

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_OUTPUT_DATA_RATE_AND_BANDWIDTH = 0; /* Arg: interface::OutputDataRateAndBandwithSelect * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_FULL_SCALE_RANGE               = 1; /* Arg: interface::FullScaleSelect                 * -> uint8_t *  */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMG160 final : public driver::interface::Driver
{

public:

           BMG160(interface::BMG160_Control & ctrl);
  virtual ~BMG160();


  virtual bool    open (                                                  ) override final;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override final;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override final;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override final;
  virtual void    close(                                                  ) override final;

private:

  interface::BMG160_Control & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMG160 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_BMG160_H_ */
