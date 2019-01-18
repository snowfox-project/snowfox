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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_AS5600_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_AS5600_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/sensor/AS5600/interface/AS5600_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace AS5600
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_POWER_MODE              =  0; /* Arg: interface::PowerModeSelect     * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_HYSTERESIS              =  1; /* Arg: interface::HysteresisSelect    * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_OUTPUT_STAGE            =  2; /* Arg: interface::OutputStageSelect   * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_PWM_FREQUENCY           =  3; /* Arg: interface::PWMFrequencySelect  * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_SLOW_FILTER             =  4; /* Arg: interface::SlowFilterSelect    * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_FAST_FILTER_THRESHOLD   =  5; /* Arg: interface::FastFilterThreshold * -> uint8_t *  */
static uint32_t constexpr IOCTL_ENABLE_WATCHDOG             =  6; /* Arg: none                                           */
static uint32_t constexpr IOCTL_DISABLE_WATCHDOG            =  7; /* Arg: none                                           */
static uint32_t constexpr IOCTL_SET_ANGULAR_START_POSITION  =  8; /* Arg: uint16_t *                                     */
static uint32_t constexpr IOCTL_SET_ANGULAR_STOP_POSITION   =  9; /* Arg: uint16_t *                                     */
static uint32_t constexpr IOCTL_SET_MAX_ANGLE               = 10; /* Arg: uint16_t *                                     */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AS5600 : public driver::interface::Driver
{

public:

           AS5600(interface::AS5600_Control & ctrl);
  virtual ~AS5600();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;

private:

  interface::AS5600_Control & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_AS5600_H_ */
