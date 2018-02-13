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

#include <spectre/driver/serial/UART/UART_SerialController.h>

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

UART_SerialController::UART_SerialController(hal::interface::UART & uart, hal::interface::UARTConfiguration & uart_config, hal::interface::CriticalSection & crit_sec, SerialQueue & rx_queue, SerialQueue & tx_queue)
: _uart       (uart       ),
  _uart_config(uart_config),
  _crit_sec   (crit_sec   ),
  _rx_queue   (rx_queue   ),
  _tx_queue   (tx_queue   )
{

}

UART_SerialController::~UART_SerialController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART_SerialController::enable()
{
  _uart_config.enableInterrupt(hal::interface::UartInt::RxComplete);
}

void UART_SerialController::setBaudRate(interface::SerialBaudRate const baud_rate)
{
  switch(baud_rate)
  {
  case interface::SerialBaudRate::B115200: _uart_config.setBaudRate(hal::interface::UartBaudRate::B115200); break;
  }
}

void UART_SerialController::setParity(interface::SerialParity const parity)
{
  switch(parity)
  {
  case interface::SerialParity::None: _uart_config.setParity(hal::interface::UartParity::None); break;
  case interface::SerialParity::Even: _uart_config.setParity(hal::interface::UartParity::Even); break;
  case interface::SerialParity::Odd : _uart_config.setParity(hal::interface::UartParity::Odd ); break;
  }
}

void UART_SerialController::setStopBit(interface::SerialStopBit const stop_bit)
{
  switch(stop_bit)
  {
  case interface::SerialStopBit::_1: _uart_config.setStopBit(hal::interface::UartStopBit::_1); break;
  case interface::SerialStopBit::_2: _uart_config.setStopBit(hal::interface::UartStopBit::_2); break;
  }
}

bool UART_SerialController::isRxBufferEmpty()
{
  hal::interface::LockGuard lock(_crit_sec);

  return _rx_queue.isEmpty();
}

void UART_SerialController::getRxBufferData(uint8_t * data)
{
  hal::interface::LockGuard lock(_crit_sec);

  _rx_queue.pop(data);
}

bool UART_SerialController::isTxBufferFull()
{
  hal::interface::LockGuard lock(_crit_sec);

  return _tx_queue.isFull();
}

void UART_SerialController::putDataTxBuffer(uint8_t const data)
{
  hal::interface::LockGuard lock(_crit_sec);

  _tx_queue.push(data);
  _uart_config.enableInterrupt(hal::interface::UartInt::TxComplete);
}

void UART_SerialController::onTransmitComplete()
{
  hal::interface::LockGuard lock(_crit_sec);

  if(!_tx_queue.isEmpty())
  {
    uint8_t data = 0;
    _tx_queue.pop(&data);
    _uart.transmit(data);
  }
  else
  {
    _uart_config.disableInterrupt(hal::interface::UartInt::TxComplete);
  }
}

void UART_SerialController::onReceiveComplete()
{
  hal::interface::LockGuard lock(_crit_sec);

  if(!_rx_queue.isFull())
  {
    uint8_t data = 0;

    _uart.receive (data);
    _rx_queue.push(data);
  }
}

void UART_SerialController::disable()
{
  _uart_config.disableInterrupt(hal::interface::UartInt::RxComplete);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */