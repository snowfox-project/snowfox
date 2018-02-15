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

#ifndef INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_UARTCALLBACKHANDLER_H_
#define INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_UARTCALLBACKHANDLER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/uart/UARTCallback.h>

#include <spectre/driver/serial/interface/SerialController.h>

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

class UART_CallbackHandler : public spectre::hal::interface::UARTCallback
{

public:

           UART_CallbackHandler(interface::SerialController & serial_ctrl);
  virtual ~UART_CallbackHandler();


  virtual void onTransmitCompleteCallback(                  ) override;
  virtual void onReceiveCompleteCallback (uint8_t const data) override;


private:

  interface::SerialController & _serial_ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_UARTCALLBACKHANDLER_H_ */
