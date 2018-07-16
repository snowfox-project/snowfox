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
 * This example program is tailored for usage with Moteino-Mega-USB
 *
 * Upload via avrdude
 *   avrdude -p atmega1284p -c arduino -e -U flash:w:bin/debug-serial-atmega1284p-uart0
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA1284P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA1284P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA1284P/UART0.h>

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

static uint16_t const UART_RX_BUFFER_SIZE = 16;
static uint16_t const UART_TX_BUFFER_SIZE = 16;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/
  ATMEGA1284P::InterruptController int_ctrl(&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ACSR, &ADCSRA, &EECR, &TWCR, &SPMCSR, &UCSR1B);
  ATMEGA1284P::CriticalSection     crit_sec(&SREG);

  blox::ATMEGA1284P::UART0         uart0   (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, int_ctrl, F_CPU);


  /* DRIVER ***************************************************************************/
  blox::SerialUart serial(crit_sec, uart0(), UART_RX_BUFFER_SIZE, UART_TX_BUFFER_SIZE);

  uint8_t baud_rate = static_cast<uint8_t>(serial::interface::SerialBaudRate::B115200);
  uint8_t parity    = static_cast<uint8_t>(serial::interface::SerialParity::None     );
  uint8_t stop_bit  = static_cast<uint8_t>(serial::interface::SerialStopBit::_1      );

  serial().open();
  serial().ioctl(serial::IOCTL_SET_BAUDRATE, static_cast<void *>(&baud_rate));
  serial().ioctl(serial::IOCTL_SET_PARITY,   static_cast<void *>(&parity   ));
  serial().ioctl(serial::IOCTL_SET_STOPBIT,  static_cast<void *>(&stop_bit ));


  /* GLOBAL INTERRUPT *****************************************************************/
  debug::DebugSerial debug_serial(serial());


  /* GLOBAL INTERRUPT *****************************************************************/
  int_ctrl.enableInterrupt(ATMEGA164P_324P_644P_1284P::toIntNum(ATMEGA1284P::Interrupt::GLOBAL));


  /* APPLICATION **********************************************************************/
  for(uint32_t cnt = 0;; cnt++)
  {
    debug_serial.print("( %08X ) Hello ATMEGA1284P\n", cnt);
  }

  return 0;
}
