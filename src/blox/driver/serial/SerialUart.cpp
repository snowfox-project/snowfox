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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/blox/driver/serial/SerialUart.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace blox
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SerialUart::SerialUart(hal::interface::CriticalSection       & crit_sec,
                       hal::interface::Uart                  & uart,
                       uint16_t                        const   uart_rx_buffer_size,
                       uint16_t                        const   uart_tx_buffer_size)
: _serial_rx_queue           (uart_rx_buffer_size                               ),
  _serial_tx_queue           (uart_tx_buffer_size                               ),
  _serial_on_rx_done_callback(crit_sec, _serial_rx_queue, uart                  ),
  _serial_on_tx_done_callback(crit_sec, _serial_tx_queue, uart                  ),
  _serial_config             (uart                                              ),
  _serial_control            (crit_sec, _serial_rx_queue, _serial_tx_queue, uart),
  _serial                    (_serial_config, _serial_control                   )
{
  uart.register_onRxDoneCallback(&_serial_on_rx_done_callback);
  uart.register_onTxDoneCallback(&_serial_on_tx_done_callback);
}

SerialUart::SerialUart(hal::interface::CriticalSection      & crit_sec,
            hal::interface::Uart                            & uart,
            uint16_t                                  const   uart_rx_buffer_size,
            uint16_t                                  const   uart_tx_buffer_size,
            driver::serial::interface::SerialBaudRate const   baud_rate,
            driver::serial::interface::SerialParity   const   parity,
            driver::serial::interface::SerialStopBit  const   stop_bit)
: SerialUart(crit_sec, uart, uart_rx_buffer_size, uart_tx_buffer_size)
{
  uint8_t ioctl_baud_rate = static_cast<uint8_t>(baud_rate);
  uint8_t ioctl_parity    = static_cast<uint8_t>(parity   );
  uint8_t ioctl_stop_bit  = static_cast<uint8_t>(stop_bit );

  _serial.ioctl(driver::serial::IOCTL_SET_BAUDRATE, static_cast<void *>(&ioctl_baud_rate));
  _serial.ioctl(driver::serial::IOCTL_SET_PARITY,   static_cast<void *>(&ioctl_parity   ));
  _serial.ioctl(driver::serial::IOCTL_SET_STOPBIT,  static_cast<void *>(&ioctl_stop_bit ));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* blox */

} /* snowfox */
