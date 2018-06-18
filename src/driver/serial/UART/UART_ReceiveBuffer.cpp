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

#include <spectre/driver/serial/UART/UART_ReceiveBuffer.h>

#include <spectre/hal/interface/locking/LockGuard.h>

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

UART_ReceiveBuffer::UART_ReceiveBuffer(uint16_t const size, hal::interface::CriticalSection & crit_sec, hal::interface::UARTConfiguration & uart_config)
: _rx_queue   (size    ),
  _crit_sec   (crit_sec),
  _uart_config(uart_config)
{
  _uart_config.enableRx();
}

UART_ReceiveBuffer::~UART_ReceiveBuffer()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool UART_ReceiveBuffer::isEmpty()
{
  hal::interface::LockGuard lock(_crit_sec);

  return _rx_queue.isEmpty();
}

void UART_ReceiveBuffer::getData(uint8_t * data)
{
  hal::interface::LockGuard lock(_crit_sec);

  _rx_queue.pop(data);
}

void UART_ReceiveBuffer::onReceiveComplete(uint8_t const rx_data)
{
  hal::interface::LockGuard lock(_crit_sec);

  if(!_rx_queue.isFull())
  {
    _rx_queue.push(rx_data);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */
