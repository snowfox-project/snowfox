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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART_ONRXDONECALLBACK_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART_ONRXDONECALLBACK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/uart/events/UART_onRxDoneCallback.h>

#include <spectre/hal/interface/uart/UartControl.h>
#include <spectre/hal/interface/locking/CriticalSection.h>

#include <spectre/util/container/Queue.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace serial
{

namespace UART
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART_onRxDoneCallback : public hal::interface::UART_onRxDoneCallback
{

public:

           UART_onRxDoneCallback(hal::interface::CriticalSection   & crit_sec,
                                 util::container::Queue<uint8_t> & rx_queue,
                                 hal::interface::UartControl       & uart_ctrl);
  virtual ~UART_onRxDoneCallback();


  virtual void onRxDone() override;


private:

  hal::interface::CriticalSection   & _crit_sec;
  util::container::Queue<uint8_t> & _rx_queue;
  hal::interface::UartControl       & _uart_ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART_ONRXDONECALLBACK_H_ */
