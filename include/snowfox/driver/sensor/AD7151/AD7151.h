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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_AD7151_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_AD7151_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/AD7151/interface/AD7151_Control.h>

#include <snowfox/driver/interface/Driver.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace AD7151
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_CAPACITIVE_INPUT_RANGE      = 0; /* Arg: interface::CapacitiveInputRangeSelect * -> uint8_t *  */
static uint32_t constexpr IOCTL_START_CONVERSION                = 1; /* Arg: none                                                  */
static uint32_t constexpr IOCTL_CHECK_IF_CONVERSION_IS_COMPLETE = 2; /* Arg: bool *                                                */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AD7151 final : public driver::interface::Driver
{

public:

           AD7151(interface::AD7151_Control & ctrl);
  virtual ~AD7151();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;

private:

  interface::AD7151_Control & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_AD7151_H_ */
