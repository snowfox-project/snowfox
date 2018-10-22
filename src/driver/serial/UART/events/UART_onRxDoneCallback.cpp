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

#include <spectre/driver/serial/UART/events/UART_onRxDoneCallback.h>

#include <spectre/hal/interface/locking/LockGuard.hpp>

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
 * CTOR/DTOR
 **************************************************************************************/

UART_onRxDoneCallback::UART_onRxDoneCallback(hal::interface::CriticalSection & crit_sec, util::container::Queue<uint8_t> & rx_queue, hal::interface::UartControl & uart_ctrl)
: _crit_sec (crit_sec ),
  _rx_queue (rx_queue ),
  _uart_ctrl(uart_ctrl)
{

}

UART_onRxDoneCallback::~UART_onRxDoneCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART_onRxDoneCallback::onRxDone()
{
  hal::interface::LockGuard<hal::interface::CriticalSection> lock(_crit_sec);

  uint8_t data = 0;
  _uart_ctrl.receive(data);

  if(!_rx_queue.isFull())
  {
    _rx_queue.push(data);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */
