/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/hal/avr/AT90CAN128/CriticalSection.h>
#include <spectre/hal/avr/AT90CAN128/InterruptController.h>

#include <spectre/blox/hal/avr/AT90CAN128/UART0.h>

#include <spectre/blox/driver/serial/SerialUart.h>

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

  AT90CAN128::InterruptController int_ctrl(&EIMSK, &TIMSK2, &TIMSK1, &TIMSK0, &CANGIE, &SPCR, &UCSR0B, &ACSR, &ADCSRA, &EECR, &TIMSK3, &UCSR1B, &TWCR, &SPMCSR);
  AT90CAN128::CriticalSection     crit_sec(&SREG);

  blox::AT90CAN128::UART0         uart0   (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);


  /* DRIVER ***************************************************************************/

  blox::SerialUart serial(crit_sec,
                          uart0(),
                          UART_RX_BUFFER_SIZE,
                          UART_TX_BUFFER_SIZE,
                          serial::interface::SerialBaudRate::B115200,
                          serial::interface::SerialParity::None,
                          serial::interface::SerialStopBit::_1);


  /* GLOBAL INTERRUPT *****************************************************************/

  int_ctrl.enableInterrupt(AT90CAN32_64_128::toIntNum(AT90CAN128::Interrupt::GLOBAL));


  /* APPLICATION **********************************************************************/

  uint8_t buf[5] = {0};
  for(;;)
  {
    ssize_t const bytes_received = serial().read(buf, 5);

    for(ssize_t bytes_written = 0; bytes_written != bytes_received; )
    {
      bytes_written += serial().write(buf + bytes_written, bytes_received - bytes_written);
    }
  }

  return 0;
}
