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

#include <spectre/blox/driver/serial/SerialUart.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SerialUart::SerialUart(hal::interface::CriticalSection       & crit_sec,
                       hal::interface::UartConfiguration     & uart_config,
                       hal::interface::UartControl           & uart_ctrl,
                       hal::interface::UartAssembly          & uart_assembly,
                       uint16_t                        const   uart_rx_buffer_size,
                       uint16_t                        const   uart_tx_buffer_size)
: _serial_rx_queue           (uart_rx_buffer_size                                    ),
  _serial_tx_queue           (uart_tx_buffer_size                                    ),
  _serial_on_rx_done_callback(crit_sec, _serial_rx_queue, uart_ctrl                  ),
  _serial_on_tx_done_callback(crit_sec, _serial_tx_queue, uart_ctrl                  ),
  _serial_config             (uart_config                                            ),
  _serial_control            (crit_sec, _serial_rx_queue, _serial_tx_queue, uart_ctrl),
  _serial                    (_serial_config, _serial_control                        )
{
  uart_assembly.register_onRxDoneCallback(&_serial_on_rx_done_callback);
  uart_assembly.register_onTxDoneCallback(&_serial_on_tx_done_callback);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* blox */

} /* spectre */
