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

#include <spectre/driver/console/Serial/interface/SerialController.h>

#include <spectre/hal/interface/uart/UART.h>
#include <spectre/hal/interface/uart/UARTConfiguration.h>

#include <spectre/driver/console/Serial/SerialQueue.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class SerialController : public interface::SerialController
{

public:


           SerialController(hal::interface::UART & uart, hal::interface::UARTConfiguration & uart_config, SerialQueue & rx_queue, SerialQueue & tx_queue, uint32_t const f_cpu);
  virtual ~SerialController();


  virtual void    enable            () override;

  virtual void    setBaudRate       (interface::SerialBaudRate const baud_rate) override;
  virtual void    setParity         (interface::SerialParity   const parity   ) override;
  virtual void    setStopBit        (interface::SerialStopBit  const stop_bit ) override;

  virtual bool    isRxBufferEmpty   (                  ) override;
  virtual uint8_t getRxBufferData   (                  ) override;
  virtual bool    isTxBufferFull    (                  ) override;
  virtual void    putDataTxBuffer   (uint8_t const data) override;

  virtual void    onTransmitComplete() override;
  virtual void    onReceiveComplete () override;

  virtual void    disable           () override;

private:

  hal::interface::UART              & _uart;
  hal::interface::UARTConfiguration & _uart_config;
  SerialQueue                       & _rx_queue,
                                    & _tx_queue;
  uint32_t                            _f_cpu;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* serial */

} /* console */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_SERIALCONTROLLER_H_ */
