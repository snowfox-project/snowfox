/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_BLOX_DRIVER_SERIAL_SERIALUART_H_
#define INCLUDE_SNOWFOX_BLOX_DRIVER_SERIAL_SERIALUART_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/uart/Uart.h>
#include <snowfox/hal/interface/locking/CriticalSection.h>

#include <snowfox/driver/serial/Serial.h>
#include <snowfox/driver/serial/UART/UART_SerialControl.h>
#include <snowfox/driver/serial/UART/UART_SerialConfiguration.h>
#include <snowfox/driver/serial/UART/events/UART_onRxDoneCallback.h>
#include <snowfox/driver/serial/UART/events/UART_onTxDoneCallback.h>

#include <snowfox/util/container/Queue.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace blox
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SerialUart
{

public:

  SerialUart(hal::interface::CriticalSection       & crit_sec,
             hal::interface::Uart                  & uart,
             uint16_t                        const   uart_rx_buffer_size,
             uint16_t                        const   uart_tx_buffer_size);

  SerialUart(hal::interface::CriticalSection                  & crit_sec,
             hal::interface::Uart                            & uart,
             uint16_t                                  const   uart_rx_buffer_size,
             uint16_t                                  const   uart_tx_buffer_size,
             driver::serial::interface::SerialBaudRate const   baud_rate,
             driver::serial::interface::SerialParity   const   parity,
             driver::serial::interface::SerialStopBit  const   stop_bit);


  driver::serial::Serial & operator () () { return _serial; }


private:

  util::container::Queue<uint8_t>                _serial_rx_queue,
                                                 _serial_tx_queue;
  driver::serial::UART::UART_onRxDoneCallback    _serial_on_rx_done_callback;
  driver::serial::UART::UART_onTxDoneCallback    _serial_on_tx_done_callback;
  driver::serial::UART::UART_SerialConfiguration _serial_config;
  driver::serial::UART::UART_SerialControl       _serial_control;
  driver::serial::Serial                         _serial;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* blox */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_BLOX_DRIVER_SERIAL_SERIALUART_H_ */
