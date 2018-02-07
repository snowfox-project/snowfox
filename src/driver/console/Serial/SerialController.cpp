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

#include <spectre/driver/console/Serial/SerialController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace console
{

namespace serial
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SerialController::SerialController(hal::interface::UART & uart, hal::interface::UARTConfiguration & uart_config, SerialQueue & rx_queue, SerialQueue & tx_queue)
: _uart       (uart       ),
  _uart_config(uart_config),
  _rx_queue   (rx_queue   ),
  _tx_queue   (tx_queue   )
{

}

SerialController::~SerialController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void SerialController::enable()
{
  _uart_config.enableInterrupt(hal::interface::UartInt::RxComplete);
}

void SerialController::setBaudRate(interface::SerialBaudRate const baud_rate)
{
  switch(baud_rate)
  {
  case interface::SerialBaudRate::B115200: _uart_config.setBaudRate(hal::interface::UartBaudRate::B115200); break;
  }
}

void SerialController::setParity(interface::SerialParity const parity)
{
  switch(parity)
  {
  case interface::SerialParity::None: _uart_config.setParity(hal::interface::UartParity::None); break;
  case interface::SerialParity::Even: _uart_config.setParity(hal::interface::UartParity::Even); break;
  case interface::SerialParity::Odd : _uart_config.setParity(hal::interface::UartParity::Odd ); break;
  }
}

void SerialController::setStopBit(interface::SerialStopBit const stop_bit)
{
  switch(stop_bit)
  {
  case interface::SerialStopBit::_1: _uart_config.setStopBit(hal::interface::UartStopBit::_1); break;
  case interface::SerialStopBit::_2: _uart_config.setStopBit(hal::interface::UartStopBit::_2); break;
  }
}

bool SerialController::isRxBufferEmpty()
{
  bool const is_rx_buffer_empty = (_rx_queue.size() == 0);
  return is_rx_buffer_empty;
}

uint8_t SerialController::getRxBufferData()
{
  uint8_t data = 0;
  _rx_queue.pop(&data);
  return data;
}

bool SerialController::isTxBufferFull()
{
  bool const is_tx_buffer_full = (_tx_queue.size() == _tx_queue.capacity());
  return is_tx_buffer_full;
}

void SerialController::putDataTxBuffer(uint8_t const data)
{
  _tx_queue.push(data);
  _uart_config.enableInterrupt(hal::interface::UartInt::TxComplete);
}

void SerialController::onTransmitComplete()
{
  bool const is_tx_data_available = _tx_queue.size() > 0;

  if(is_tx_data_available)
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

void SerialController::onReceiveComplete()
{
  uint8_t data = 0;

  _uart.receive (data);
  _rx_queue.push(data);
}

void SerialController::disable()
{
  _uart_config.disableInterrupt(hal::interface::UartInt::RxComplete);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* serial */

} /* console */

} /* driver */

} /* spectre */
