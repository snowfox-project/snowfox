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

#include <spectre/driver/serial/UART/UART_TransmitBuffer.h>

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

UART_TransmitBuffer::UART_TransmitBuffer(hal::interface::CriticalSection   & crit_sec,
                                         memory::container::Queue<uint8_t> & tx_queue,
                                         hal::interface::UARTControl       & uart_ctrl)
: _crit_sec (crit_sec ),
  _tx_queue (tx_queue ),
  _uart_ctrl(uart_ctrl)
{

}

UART_TransmitBuffer::~UART_TransmitBuffer()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool UART_TransmitBuffer::isFull()
{
  hal::interface::LockGuard lock(_crit_sec);

  return _tx_queue.isFull();
}

void UART_TransmitBuffer::putData(uint8_t const data)
{
  hal::interface::LockGuard lock(_crit_sec);

  if(!_tx_queue.isFull())
  {
    _tx_queue.push(data);
    _uart_ctrl.enableTx();
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */
