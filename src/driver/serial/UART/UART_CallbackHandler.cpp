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

#include <spectre/driver/serial/UART/UART_CallbackHandler.h>

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

UART_CallbackHandler::UART_CallbackHandler(interface::SerialTransmitBuffer & serial_tx_buf, interface::SerialReceiveBuffer & serial_rx_buf)
: _serial_tx_buf(serial_tx_buf),
  _serial_rx_buf(serial_rx_buf)
{

}

UART_CallbackHandler::~UART_CallbackHandler()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool UART_CallbackHandler::onTransmitRegisterEmptyCallback(uint8_t * tx_data)
{
  return _serial_tx_buf.onTransmitRegisterEmpty(tx_data);
}

void UART_CallbackHandler::onReceiveCompleteCallback(uint8_t const data)
{
  _serial_rx_buf.onReceiveComplete(data);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */
