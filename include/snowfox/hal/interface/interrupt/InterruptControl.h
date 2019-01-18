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

#ifndef INCLUDE_SNOWFOX_HAL_INTERFACE_INTERRUPT_INTERRUPTCONTROL_H_
#define INCLUDE_SNOWFOX_HAL_INTERFACE_INTERRUPT_INTERRUPTCONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <limits.h>

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

class InterruptControl
{

public:

           InterruptControl() { }
  virtual ~InterruptControl() { }


  static uint8_t constexpr GLOBAL_INT_NUM  = UCHAR_MAX - 1;
  static uint8_t constexpr INVALID_INT_NUM = UCHAR_MAX;


  virtual void enableInterrupt (uint8_t const int_num) = 0;
  virtual void disableInterrupt(uint8_t const int_num) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface*/

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_INTERFACE_INTERRUPT_INTERRUPTCONTROL_H_ */
