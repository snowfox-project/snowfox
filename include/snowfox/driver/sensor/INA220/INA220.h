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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_INA220_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_INA220_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/INA220/interface/INA220_Control.h>

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

namespace INA220
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_BUS_VOLTAGE_RANGE    = 0; /* Arg: interface::BusVoltageRangeSelect *    -> uint16_t *  */
static uint32_t constexpr IOCTL_SET_SHUNT_PGA_GAIN       = 1; /* Arg: interface::ShuntPGAGainSelect *       -> uint16_t *  */
static uint32_t constexpr IOCTL_SET_BUS_ADC_RESOLUTION   = 2; /* Arg: interface::BusADCResolutionSelect *   -> uint16_t *  */
static uint32_t constexpr IOCTL_SET_SHUNT_ADC_RESOLUTION = 3; /* Arg: interface::ShuntADCResolutionSelect * -> uint16_t *  */
static uint32_t constexpr IOCTL_SET_OPERATING_MODE       = 4; /* Arg: interface::OperatingModeSelect *      -> uint16_t *  */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class INA220 final : public driver::interface::Driver
{

public:

           INA220(interface::INA220_Control & ctrl);
  virtual ~INA220();


  virtual bool    open (                                                  ) override final;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override final;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override final;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override final;
  virtual void    close(                                                  ) override final;

private:

  interface::INA220_Control & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* INA220 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_INA220_H_ */
