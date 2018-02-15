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

UART_CallbackHandler::UART_CallbackHandler(interface::SerialController & serial_ctrl)
: _serial_ctrl(serial_ctrl)
{

}

UART_CallbackHandler::~UART_CallbackHandler()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART_CallbackHandler::onTransmitCompleteCallback()
{
  _serial_ctrl.onTransmitComplete();
}

void UART_CallbackHandler::onReceiveCompleteCallback(uint8_t const data)
{
  _serial_ctrl.onReceiveComplete();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */
