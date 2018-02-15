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

#ifndef INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_SERIALCONTROLLER_H_
#define INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_SERIALCONTROLLER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/serial/interface/SerialController.h>

#include <spectre/hal/interface/uart/UART.h>
#include <spectre/hal/interface/uart/UARTConfiguration.h>
#include <spectre/hal/interface/locking/CriticalSection.h>

#include <spectre/driver/serial/SerialQueue.h>

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

class UART_SerialController : public interface::SerialController
{

public:


           UART_SerialController(hal::interface::UART & uart, hal::interface::UARTConfiguration & uart_config, hal::interface::CriticalSection & crit_sec, SerialQueue & tx_queue);
  virtual ~UART_SerialController();


  virtual void enable            () override;

  virtual void setBaudRate       (interface::SerialBaudRate const baud_rate) override;
  virtual void setParity         (interface::SerialParity   const parity   ) override;
  virtual void setStopBit        (interface::SerialStopBit  const stop_bit ) override;

  virtual bool isTxBufferFull    (                    ) override;
  virtual void putDataTxBuffer   (uint8_t const   data) override;


  virtual void onTransmitComplete() override;
  virtual void onReceiveComplete () override;

  virtual void disable           () override;

private:

  hal::interface::UART              & _uart;
  hal::interface::UARTConfiguration & _uart_config;
  hal::interface::CriticalSection   & _crit_sec;
  SerialQueue                       & _tx_queue;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_SERIALCONTROLLER_H_ */
