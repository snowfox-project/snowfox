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

#ifndef INCLUDE_SNOWFOX_BLOX_DRIVER_HAPTIC_DRV2605_H_
#define INCLUDE_SNOWFOX_BLOX_DRIVER_HAPTIC_DRV2605_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/delay/Delay.h>

#include <snowfox/driver/haptic/DRV2605/interface/DRV2605_Io.h>

#include <snowfox/driver/haptic/DRV2605/DRV2605.h>
#include <snowfox/driver/haptic/DRV2605/DRV2605_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::blox
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DRV2605
{

public:

   DRV2605(hal::interface::Delay                          & delay,
           driver::haptic::DRV2605::interface::DRV2605_Io & drv2605_io);

   DRV2605(hal::interface::Delay                                     & delay,
           driver::haptic::DRV2605::interface::DRV2605_Io            & drv2605_io,
           driver::haptic::DRV2605::interface::Mode            const   mode,
           driver::haptic::DRV2605::interface::Actuator        const   actuator,
           driver::haptic::DRV2605::interface::WaveformLibrary const   library);

   ~DRV2605();


  driver::haptic::DRV2605::DRV2605 & operator () () { return _drv2605; }


private:

  driver::haptic::DRV2605::DRV2605_Control _drv2605_control;

  driver::haptic::DRV2605::DRV2605         _drv2605;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::blox */

#endif /* INCLUDE_SNOWFOX_BLOX_DRIVER_HAPTIC_DRV2605_H_ */
