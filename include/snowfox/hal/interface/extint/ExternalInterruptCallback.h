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

#ifndef INCLUDE_SNOWFOX_HAL_INTERFACE_EXTINT_EXTERNALINTERRUPTCALLBACK_H_
#define INCLUDE_SNOWFOX_HAL_INTERFACE_EXTINT_EXTERNALINTERRUPTCALLBACK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/interrupt/InterruptCallback.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ExternalInterruptCallback : public InterruptCallback
{

public:

           ExternalInterruptCallback() { }
  virtual ~ExternalInterruptCallback() { }


  virtual void onExternalInterrupt() = 0;

  virtual void onInterrupt() override { onExternalInterrupt(); }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface*/

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_INTERFACE_EXTINT_EXTERNALINTERRUPTCALLBACK_H_ */
