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

#include <spectre/driver/serial/UART/UART_SerialControl.h>

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

UART_SerialControl::UART_SerialControl(hal::interface::CriticalSection   & crit_sec,
                                       util::container::Queue<uint8_t> & rx_queue,
                                       util::container::Queue<uint8_t> & tx_queue,
                                       hal::interface::UartControl       & uart_ctrl)
: _crit_sec (crit_sec ),
  _rx_queue (rx_queue ),
  _tx_queue (tx_queue ),
  _uart_ctrl(uart_ctrl)
{
  _uart_ctrl.enableRx();
}

UART_SerialControl::~UART_SerialControl()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint16_t UART_SerialControl::receive(uint8_t * data, uint16_t const num_bytes)
{
  hal::interface::LockGuard<hal::interface::CriticalSection> lock(_crit_sec);

  uint16_t bytes_read = 0;
  for(;
      (bytes_read < num_bytes) && !_rx_queue.isEmpty();
      bytes_read++)
  {
    _rx_queue.pop(data + bytes_read);
  }

  return bytes_read;
}

uint16_t UART_SerialControl::transmit(uint8_t const * data, uint16_t const num_bytes)
{
  hal::interface::LockGuard<hal::interface::CriticalSection> lock(_crit_sec);

  uint16_t bytes_written = 0;
  for(;
      (bytes_written < num_bytes) && !_tx_queue.isFull();
      bytes_written++)
  {
    _tx_queue.push(data[bytes_written]);
  }

  if(bytes_written > 0)
  {
    _uart_ctrl.enableTx();
  }

  return bytes_written;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */
