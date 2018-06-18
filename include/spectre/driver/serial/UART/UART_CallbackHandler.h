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

#ifndef INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_UARTCALLBACKHANDLER_H_
#define INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_UARTCALLBACKHANDLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/uart/UARTCallback.h>

#include <spectre/driver/serial/interface/SerialTransmitBuffer.h>
#include <spectre/driver/serial/interface/SerialReceiveBuffer.h>

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

           UART_CallbackHandler(interface::SerialTransmitBuffer & serial_tx_buf, interface::SerialReceiveBuffer & serial_rx_buf);
  virtual ~UART_CallbackHandler();


  virtual bool onTransmitRegisterEmptyCallback(uint8_t       * tx_data) override;
  virtual void onReceiveCompleteCallback      (uint8_t const   rx_data) override;


private:

  interface::SerialTransmitBuffer & _serial_tx_buf;
  interface::SerialReceiveBuffer  & _serial_rx_buf;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_UARTCALLBACKHANDLER_H_ */
