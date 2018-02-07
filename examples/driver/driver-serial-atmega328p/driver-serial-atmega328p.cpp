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

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/UART0.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/driver/console/Serial/Serial.h>
#include <spectre/driver/console/Serial/SerialQueue.h>
#include <spectre/driver/console/Serial/SerialController.h>
#include <spectre/driver/console/Serial/SerialCallbackHandler.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint16_t const RX_QUEUE_SIZE = 16;
static uint16_t const TX_QUEUE_SIZE = 16;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::InterruptController int_ctrl  (&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ADCSRA, &EECR, &ACSR, &TWCR, &SPMCSR);
  ATMEGA328P::CriticalSection     crit_sec  (&SREG);
  ATMEGA328P::UART0               uart0     (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl);

  uart0.setBaudRate   (hal::interface::UartBaudRate::B115200, F_CPU);
  uart0.setParity     (hal::interface::UartParity::None            );
  uart0.setStopBit    (hal::interface::UartStopBit::_1             );

  int_ctrl.registerISR(ATMEGA328P::USART_UART_DATA_REGISTER_EMPTY, ATMEGA328P::UART0::ISR_onTransmitComplete, &uart0);
  int_ctrl.registerISR(ATMEGA328P::USART_RECEIVE_COMPLETE,         ATMEGA328P::UART0::ISR_onReceiveComplete,  &uart0);

  /* DRIVER ***************************************************************************/

  console::serial::SerialQueue            rx_queue        (crit_sec, RX_QUEUE_SIZE),
                                          tx_queue        (crit_sec, TX_QUEUE_SIZE);

  console::serial::SerialController       serial_ctrl     (uart0, uart0, rx_queue, tx_queue, F_CPU);
  console::serial::SerialCallbackHandler  serial_callback (serial_ctrl);
  console::serial::Serial                 serial          (serial_ctrl);

  uart0.registerUARTCallbackInterface (&serial_callback);

  int_ctrl.enableInterrupt            (ATMEGA328P::GLOBAL);

  /* APPLICATION **********************************************************************/

  serial.open();

  uint8_t buf[5] = {0};
  for(;;)
  {
    ssize_t const bytes_received = serial.read(buf, 5);

    if(bytes_received > 0) serial.write(buf, bytes_received);
  }

  serial.close();

  return 0;
}
