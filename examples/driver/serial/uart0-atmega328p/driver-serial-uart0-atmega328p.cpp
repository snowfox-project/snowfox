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

#include <spectre/driver/serial/Serial.h>
#include <spectre/driver/serial/UART/UART_ReceiveBuffer.h>
#include <spectre/driver/serial/UART/UART_TransmitBuffer.h>
#include <spectre/driver/serial/UART/UART_CallbackHandler.h>
#include <spectre/driver/serial/UART/UART_SerialController.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint16_t const RX_BUFFER_SIZE = 16;
static uint16_t const TX_BUFFER_SIZE = 16;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::InterruptController                 int_ctrl                               (&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ADCSRA, &EECR, &ACSR, &TWCR, &SPMCSR);
  ATMEGA328P::CriticalSection                     crit_sec                               (&SREG);

  ATMEGA328P::UART0                               uart0                                  (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);
  ATMEGA328P::UART0_TransmitRegisterEmptyCallback uart0_uart_data_register_empty_callback(uart0);
  ATMEGA328P::UART0_ReceiveCompleteCallback       uart0_receive_complete_callback        (uart0);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::USART_UART_DATA_REGISTER_EMPTY), &uart0_uart_data_register_empty_callback);
  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::USART_RECEIVE_COMPLETE        ), &uart0_receive_complete_callback        );

  /* DRIVER ***************************************************************************/

  serial::UART::UART_TransmitBuffer   serial_tx_buffer  (TX_BUFFER_SIZE, crit_sec, uart0);
  serial::UART::UART_ReceiveBuffer    serial_rx_buffer  (RX_BUFFER_SIZE, crit_sec, uart0);
  serial::UART::UART_CallbackHandler  serial_callback   (serial_tx_buffer, serial_rx_buffer);
  serial::UART::UART_SerialController serial_ctrl       (uart0);
  serial::Serial                      serial            (serial_ctrl, serial_tx_buffer, serial_rx_buffer);

  uart0.registerUARTCallback(&serial_callback);

  int_ctrl.enableInterrupt            (ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::GLOBAL));

  /* APPLICATION **********************************************************************/

  uint8_t baud_rate = static_cast<uint8_t>(serial::interface::SerialBaudRate::B115200);
  uint8_t parity    = static_cast<uint8_t>(serial::interface::SerialParity::None     );
  uint8_t stop_bit  = static_cast<uint8_t>(serial::interface::SerialStopBit::_1      );

  serial.open();
  serial.ioctl(serial::IOCTL_SET_BAUDRATE, static_cast<void *>(&baud_rate));
  serial.ioctl(serial::IOCTL_SET_PARITY,   static_cast<void *>(&parity   ));
  serial.ioctl(serial::IOCTL_SET_STOPBIT,  static_cast<void *>(&stop_bit ));

  uint8_t buf[5] = {0};
  for(;;)
  {
    ssize_t const bytes_received = serial.read(buf, 5);

    for(ssize_t bytes_written = 0; bytes_written != bytes_received; )
    {
      bytes_written += serial.write(buf + bytes_written, bytes_received - bytes_written);
    }
  }

  serial.close();

  return 0;
}
