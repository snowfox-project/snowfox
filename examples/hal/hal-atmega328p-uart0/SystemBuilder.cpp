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

#include "SystemBuilder.h"

#include <avr/io.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SystemBuilder::SystemBuilder()
: _interrupt_controller (&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ADCSRA, &EECR, &ACSR, &TWCR, &SPMCSR),
  _uart0                (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, _interrupt_controller)

{
  /* Configure UART0 */

  _uart0.setBaudRate                  (interface::UartBaudRate::B115200, F_CPU);
  _uart0.setParity                    (interface::UartParity::None            );
  _uart0.setStopBit                   (interface::UartStopBit::_1             );

  _uart0.registerUARTCallbackInterface(&_uart_task_input_handler              );


  _interrupt_controller.registerISR   (ATMEGA328P::USART_UART_DATA_REGISTER_EMPTY,
                                       ATMEGA328P::UART0::ISR_onTransmitRegisterEmpty,
                                       &_uart0);

  _interrupt_controller.registerISR   (ATMEGA328P::USART_RECEIVE_COMPLETE,
                                       ATMEGA328P::UART0::ISR_onReceiveComplete,
                                       &_uart0);

  _interrupt_controller.enableInterrupt(ATMEGA328P::USART_UART_DATA_REGISTER_EMPTY);
  _interrupt_controller.enableInterrupt(ATMEGA328P::USART_RECEIVE_COMPLETE        );

  /* Configure Interrupt Controller */


  _interrupt_controller.enableInterrupt(ATMEGA328P::GLOBAL);
}
