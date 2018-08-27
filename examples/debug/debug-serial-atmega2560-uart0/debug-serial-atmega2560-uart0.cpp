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
 * This example program is tailored for usage with Arduino Mega
 *
 * Upload via avrdude
 *   avrdude -p atmega328p -c avrisp2 -e -U flash:w:debug-serial-atmega2560-uart0
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA2560/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA2560/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA2560/UART0.h>

#include <spectre/blox/driver/serial/SerialUart.h>

#include <spectre/debug/serial/DebugSerial.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint16_t const UART_RX_BUFFER_SIZE =  0;
static uint16_t const UART_TX_BUFFER_SIZE = 16;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA2560::InterruptController int_ctrl(&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ACSR, &ADCSRA, &EECR, &TIMSK3, &UCSR1B, &TWCR, &SPMCSR, &TIMSK4, &TIMSK5, &UCSR2B, &UCSR3B);
  ATMEGA2560::CriticalSection     crit_sec(&SREG);

  blox::ATMEGA2560::UART0         uart0   (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);


  /* DRIVER ***************************************************************************/

  blox::SerialUart serial(crit_sec,
                          uart0(),
                          UART_RX_BUFFER_SIZE,
                          UART_TX_BUFFER_SIZE,
                          serial::interface::SerialBaudRate::B115200,
                          serial::interface::SerialParity::None,
                          serial::interface::SerialStopBit::_1);


  /* GLOBAL INTERRUPT *****************************************************************/

  int_ctrl.enableInterrupt(ATMEGA640_1280_2560::toIntNum(ATMEGA2560::Interrupt::GLOBAL));


  /* APPLICATION **********************************************************************/

  debug::DebugSerial debug_serial(serial());

  for(uint32_t cnt = 0;; cnt++)
  {
    debug_serial.print("( %08X ) Hello ATMEGA2560\r\n", cnt);
  }

  return 0;
}
