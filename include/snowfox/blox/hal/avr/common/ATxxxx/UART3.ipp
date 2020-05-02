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
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::blox::ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <uint8_t UART_DATA_REGISTER_EMPTY_INTERRUPT_NUMBER,
          uint8_t UART_RECEIVE_COMPLETE_INTERRUPT_NUMBER>
UART3<UART_DATA_REGISTER_EMPTY_INTERRUPT_NUMBER, UART_RECEIVE_COMPLETE_INTERRUPT_NUMBER>::UART3(
             volatile uint8_t                                  * udr3,
             volatile uint8_t                                  * ucsr3a,
             volatile uint8_t                                  * ucsr3b,
             volatile uint8_t                                  * ucsr3c,
             volatile uint16_t                                 * ubrr3,
             hal::interface::InterruptController               & int_ctrl,
             uint32_t                                    const   f_cpu)
: _uart3                                  (udr3, ucsr3a, ucsr3b, ucsr3c, ubrr3, int_ctrl, f_cpu),
  _uart3_uart_data_register_empty_callback(_uart3),
  _uart3_receive_complete_callback        (_uart3)
{
  int_ctrl.registerInterruptCallback(UART_DATA_REGISTER_EMPTY_INTERRUPT_NUMBER, &_uart3_uart_data_register_empty_callback);
  int_ctrl.registerInterruptCallback(UART_RECEIVE_COMPLETE_INTERRUPT_NUMBER,    &_uart3_receive_complete_callback        );
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::blox::ATxxxx */
