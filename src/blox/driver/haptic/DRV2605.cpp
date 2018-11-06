/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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
 * INCLUDE
 **************************************************************************************/

#include <spectre/blox/driver/haptic/DRV2605.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DRV2605::DRV2605(hal::interface::Delay                          & delay,
                 driver::haptic::DRV2605::interface::DRV2605_Io & drv2605_io)
: _drv2605_control(drv2605_io, delay),
  _drv2605        (_drv2605_control )
{
  _drv2605.open();
}

DRV2605::DRV2605(hal::interface::Delay                                     & delay,
                 driver::haptic::DRV2605::interface::DRV2605_Io            & drv2605_io,
                 driver::haptic::DRV2605::interface::Mode            const   mode,
                 driver::haptic::DRV2605::interface::Actuator        const   actuator,
                 driver::haptic::DRV2605::interface::WaveformLibrary const   library)
: DRV2605(delay, drv2605_io)
{
  uint8_t mode_arg         = static_cast<uint8_t>(mode    );
  uint8_t actuator_arg     = static_cast<uint8_t>(actuator);
  uint8_t waveform_lib_arg = static_cast<uint8_t>(library );

  _drv2605.ioctl(driver::haptic::DRV2605::IOCTL_SET_MODE,             static_cast<void *>(&mode_arg        ));
  _drv2605.ioctl(driver::haptic::DRV2605::IOCTL_SET_ACTUATOR,         static_cast<void *>(&actuator_arg    ));
  _drv2605.ioctl(driver::haptic::DRV2605::IOCTL_SET_WAVEFORM_LIBRARY, static_cast<void *>(&waveform_lib_arg));
}

DRV2605::~DRV2605()
{
  _drv2605.close();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* blox */

} /* spectre */
