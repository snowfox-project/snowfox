/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/sensor/AS5600/AS5600.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace AS5600
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AS5600::AS5600(interface::AS5600_Control & ctrl)
: _ctrl(ctrl)
{

}

AS5600::~AS5600()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool AS5600::open()
{
  /* TODO */
  return false;
}

ssize_t AS5600::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

ssize_t AS5600::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

bool AS5600::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_POWER_MODE *************************************************************/
  case IOCTL_SET_POWER_MODE:
  {
    uint8_t                    const * arg_ptr    = static_cast<uint8_t *>                 (arg     );
    interface::PowerModeSelect const   power_mode = static_cast<interface::PowerModeSelect>(*arg_ptr);
    return _ctrl.setPowerMode(power_mode);
  }
  break;
  /* IOCTL_SET_HYSTERESIS *************************************************************/
  case IOCTL_SET_HYSTERESIS:
  {
    uint8_t                     const * arg_ptr    = static_cast<uint8_t *>                  (arg     );
    interface::HysteresisSelect const   hysteresis = static_cast<interface::HysteresisSelect>(*arg_ptr);
    return _ctrl.setHysteresis(hysteresis);
  }
  break;
  /* IOCTL_SET_OUTPUT_STAGE ***********************************************************/
  case IOCTL_SET_OUTPUT_STAGE:
  {
    uint8_t                      const * arg_ptr      = static_cast<uint8_t *>                   (arg     );
    interface::OutputStageSelect const   output_stage = static_cast<interface::OutputStageSelect>(*arg_ptr);
    return _ctrl.setOutputStage(output_stage);
  }
  break;
  /* IOCTL_SET_PWM_FREQUENCY **********************************************************/
  case IOCTL_SET_PWM_FREQUENCY:
  {
    uint8_t                       const * arg_ptr       = static_cast<uint8_t *>                    (arg     );
    interface::PWMFrequencySelect const   pwm_frequency = static_cast<interface::PWMFrequencySelect>(*arg_ptr);
    return _ctrl.setPWMFrequency(pwm_frequency);
  }
  break;
  /* IOCTL_SET_SLOW_FILTER ************************************************************/
  case IOCTL_SET_SLOW_FILTER:
  {
    uint8_t                     const * arg_ptr     = static_cast<uint8_t *>                  (arg     );
    interface::SlowFilterSelect const   slow_filter = static_cast<interface::SlowFilterSelect>(*arg_ptr);
    return _ctrl.setSlowFilter(slow_filter);
  }
  break;
  /* IOCTL_SET_FAST_FILTER_THRESHOLD *************************************************/
  case IOCTL_SET_FAST_FILTER_THRESHOLD:
  {
    uint8_t                        const * arg_ptr               = static_cast<uint8_t *>                     (arg     );
    interface::FastFilterThreshold const   fast_filter_threshold = static_cast<interface::FastFilterThreshold>(*arg_ptr);
    return _ctrl.setFastFilterThreshold(fast_filter_threshold);
  }
  break;
  /* IOCTL_ENABLE_WATCHDOG ***********************************************************/
  case IOCTL_ENABLE_WATCHDOG:
  {
    return _ctrl.enableWatchog();
  }
  break;
  /* IOCTL_DISABLE_WATCHDOG **********************************************************/
  case IOCTL_DISABLE_WATCHDOG:
  {
    return _ctrl.disableWatchog();
  }
  break;
  /* IOCTL_SET_ANGULAR_START_POSITION ************************************************/
  case IOCTL_SET_ANGULAR_START_POSITION:
  {
    uint16_t const * arg_ptr = static_cast<uint16_t const *>(arg);
    return _ctrl.setAngularStartPosition(*arg_ptr);
  }
  break;
  /* IOCTL_SET_ANGULAR_STOP_POSITION *************************************************/
  case IOCTL_SET_ANGULAR_STOP_POSITION:
  {
    uint16_t const * arg_ptr = static_cast<uint16_t const *>(arg);
    return _ctrl.setAngularStopPosition(*arg_ptr);
  }
  break;
  /* IOCTL_SET_MAX_ANGLE *************************************************************/
  case IOCTL_SET_MAX_ANGLE:
  {
    uint16_t const * arg_ptr = static_cast<uint16_t const *>(arg);
    return _ctrl.setMaximumAngle(*arg_ptr);
  }
  break;
  }

  return false;
}

void AS5600::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* spectre */
