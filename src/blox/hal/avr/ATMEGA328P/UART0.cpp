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

#include <spectre/blox/hal/avr/ATMEGA328P/UART0.h>

#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA328P
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART0::UART0(ParamIn & in)
: _uart0                                  (in._udr0, in._ucsr0a, in._ucsr0b, in._ucsr0c, in._ubrr0, in._int_ctrl, in._f_cpu),
  _uart0_uart_data_register_empty_callback(_uart0),
  _uart0_receive_complete_callback        (_uart0)

{
  in._int_ctrl_assembly.registerInterruptCallback(hal::ATMEGA328P::toIsrNum(hal::ATMEGA328P::InterruptServiceRoutine::USART_UART_DATA_REGISTER_EMPTY), &_uart0_uart_data_register_empty_callback);
  in._int_ctrl_assembly.registerInterruptCallback(hal::ATMEGA328P::toIsrNum(hal::ATMEGA328P::InterruptServiceRoutine::USART_RECEIVE_COMPLETE        ), &_uart0_receive_complete_callback        );
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* blox */

} /* spectre */
