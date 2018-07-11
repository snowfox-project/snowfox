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

#include <avr/io.h>

#include <spectre/hal/avr/AT90CAN128/UART0.h>
#include <spectre/hal/avr/AT90CAN128/CriticalSection.h>
#include <spectre/hal/avr/AT90CAN128/InterruptController.h>

#include <spectre/driver/serial/Serial.h>
#include <spectre/driver/serial/UART/UART_SerialConfig.h>
#include <spectre/driver/serial/UART/UART_SerialControl.h>
#include <spectre/driver/serial/UART/events/UART_onRxDoneCallback.h>
#include <spectre/driver/serial/UART/events/UART_onTxDoneCallback.h>

#include <spectre/memory/container/Queue.h>

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

  AT90CAN128::InterruptController                 int_ctrl                               (&EIMSK, &TIMSK2, &TIMSK1, &TIMSK0, &CANGIE, &SPCR, &UCSR0B, &ACSR, &ADCSRA, &EECR, &TIMSK3, &UCSR1B, &TWCR, &SPMCSR);
  AT90CAN128::CriticalSection                     crit_sec                               (&SREG);

  AT90CAN128::UART0                               uart0                                  (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);
  AT90CAN128::UART0_TransmitRegisterEmptyCallback uart0_uart_data_register_empty_callback(uart0);
  AT90CAN128::UART0_ReceiveCompleteCallback       uart0_receive_complete_callback        (uart0);

  int_ctrl.registerInterruptCallback(AT90CAN32_64_128::toIsrNum(AT90CAN128::InterruptServiceRoutine::USART0_UART_DATA_REGISTER_EMPTY), &uart0_uart_data_register_empty_callback);
  int_ctrl.registerInterruptCallback(AT90CAN32_64_128::toIsrNum(AT90CAN128::InterruptServiceRoutine::USART0_RECEIVE_COMPLETE        ), &uart0_receive_complete_callback        );


  /* DRIVER ***************************************************************************/

  memory::container::Queue<uint8_t>   serial_rx_queue           (UART_RX_BUFFER_SIZE),
                                      serial_tx_queue           (UART_TX_BUFFER_SIZE);
  serial::UART::UART_onRxDoneCallback serial_on_rx_done_callback(crit_sec, serial_rx_queue);
  serial::UART::UART_onTxDoneCallback serial_on_tx_done_callback(crit_sec, serial_tx_queue, uart0);
  serial::UART::UART_SerialConfig     serial_config             (uart0);
  serial::UART::UART_SerialControl    serial_control            (crit_sec, serial_rx_queue, serial_tx_queue, uart0);
  serial::Serial                      serial                    (serial_config, serial_control);

  uart0.register_onRxDoneCallback(&serial_on_rx_done_callback);
  uart0.register_onTxDoneCallback(&serial_on_tx_done_callback);

  uint8_t baud_rate = static_cast<uint8_t>(serial::interface::SerialBaudRate::B115200);
  uint8_t parity    = static_cast<uint8_t>(serial::interface::SerialParity::None     );
  uint8_t stop_bit  = static_cast<uint8_t>(serial::interface::SerialStopBit::_1      );

  serial.open();
  serial.ioctl(serial::IOCTL_SET_BAUDRATE, static_cast<void *>(&baud_rate));
  serial.ioctl(serial::IOCTL_SET_PARITY,   static_cast<void *>(&parity   ));
  serial.ioctl(serial::IOCTL_SET_STOPBIT,  static_cast<void *>(&stop_bit ));


  /* GLOBAL INTERRUPT *****************************************************************/

  int_ctrl.enableInterrupt(AT90CAN32_64_128::toIntNum(AT90CAN128::Interrupt::GLOBAL));


  /* APPLICATION **********************************************************************/

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
