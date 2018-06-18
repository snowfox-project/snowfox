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
 * INCLUDE
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

UART_SerialController::UART_SerialController(hal::interface::UARTConfiguration & uart_config)
: _uart_config(uart_config)
{

}

UART_SerialController::~UART_SerialController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

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

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */
