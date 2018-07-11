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
 * This example programm is tailored for usage with Arduino Uno
 * and Seedstudio CAN Bus Shield V2.0
 *
 * Electrical interface:
 *   CS   = D10 = PB2
 *   SCK  = D13 = PB5
 *   MISO = D12 = PB4
 *   MOSI = D11 = PB3
 *   INT  = D2  = PD2 = INT0
 *
 * Upload via avrdude
 *   avrdude -p atmega328p -c avrisp2 -e -U flash:w:bin/driver-mcp2515-spi-atmega328p-transmitter
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/EINT0.h>
#include <spectre/hal/avr/ATMEGA328P/UART0.h>
#include <spectre/hal/avr/ATMEGA328P/Flash.h>
#include <spectre/hal/avr/ATMEGA328P/Delay.h>
#include <spectre/hal/avr/ATMEGA328P/SpiMaster.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/driver/serial/Serial.h>
#include <spectre/driver/serial/UART/UART_SerialConfig.h>
#include <spectre/driver/serial/UART/UART_SerialControl.h>
#include <spectre/driver/serial/UART/events/UART_onRxDoneCallback.h>
#include <spectre/driver/serial/UART/events/UART_onTxDoneCallback.h>

#include <spectre/driver/can/Can.h>

#include <spectre/driver/can/interface/CanFrameBuffer.h>

#include <spectre/driver/can/MCP2515/MCP2515_IoSpi.h>
#include <spectre/driver/can/MCP2515/MCP2515_Debug.h>
#include <spectre/driver/can/MCP2515/MCP2515_Control.h>
#include <spectre/driver/can/MCP2515/MCP2515_CanControl.h>
#include <spectre/driver/can/MCP2515/MCP2515_CanConfiguration.h>

#include <spectre/driver/can/MCP2515/events/MCP2515_EventCallback.h>
#include <spectre/driver/can/MCP2515/events/MCP2515_onWakeup.h>
#include <spectre/driver/can/MCP2515/events/MCP2515_onMessageError.h>
#include <spectre/driver/can/MCP2515/events/MCP2515_onReceiveBufferFull.h>
#include <spectre/driver/can/MCP2515/events/MCP2515_onTransmitBufferEmpty.h>

#include <spectre/debug/serial/DebugSerial.h>

#include <spectre/memory/container/Queue.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint16_t                    const UART_RX_BUFFER_SIZE      = 0;
static uint16_t                    const UART_TX_BUFFER_SIZE      = 64;

static hal::interface::SpiMode     const MCP2515_SPI_MODE         = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const MCP2515_SPI_BIT_ORDER    = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const MCP2515_SPI_PRESCALER    = 16; /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz                     */
static hal::interface::TriggerMode const MCP2515_INT_TRIGGER_MODE = hal::interface::TriggerMode::FallingEdge;

static uint8_t                     const F_MCP2515_MHz            = 16; /* Seedstudio CAN Bus Shield V2.0 is clocked with a 16 MHz crystal */
static uint16_t                    const CAN_TX_BUFFER_SIZE       = 8;
static uint16_t                    const CAN_RX_BUFFER_SIZE       = 8;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::Flash               flash;
  ATMEGA328P::Delay               delay;
  ATMEGA328P::InterruptController int_ctrl(&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ADCSRA, &EECR, &ACSR, &TWCR, &SPMCSR);
  ATMEGA328P::CriticalSection     crit_sec(&SREG);

  /* UART0 ****************************************************************************/
  ATMEGA328P::UART0                               uart0                                  (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);
  ATMEGA328P::UART0_TransmitRegisterEmptyCallback uart0_uart_data_register_empty_callback(uart0);
  ATMEGA328P::UART0_ReceiveCompleteCallback       uart0_receive_complete_callback        (uart0);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::USART_UART_DATA_REGISTER_EMPTY), &uart0_uart_data_register_empty_callback);
  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::USART_RECEIVE_COMPLETE        ), &uart0_receive_complete_callback        );

  /* SPI/CS for MCP2515 ***************************************************************/
  ATMEGA328P::DigitalOutPin mcp2515_cs  (&DDRB, &PORTB,        2); /* CS   = D10 = PB2 */
  ATMEGA328P::DigitalOutPin mcp2515_sck (&DDRB, &PORTB,        5); /* SCK  = D13 = PB5 */
  ATMEGA328P::DigitalInPin  mcp2515_miso(&DDRB, &PORTB, &PINB, 4); /* MISO = D12 = PB4 */
  ATMEGA328P::DigitalOutPin mcp2515_mosi(&DDRB, &PORTB,        3); /* MOSI = D11 = PB3 */

  mcp2515_cs.set();
  mcp2515_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  ATMEGA328P::SpiMaster     spi_master(&SPCR, &SPSR, &SPDR);

  spi_master.setSpiMode     (MCP2515_SPI_MODE     );
  spi_master.setSpiBitOrder (MCP2515_SPI_BIT_ORDER);
  spi_master.setSpiPrescaler(MCP2515_SPI_PRESCALER);

  /* EXT INT #0 for notifications by MCP2515 ******************************************/
  ATMEGA328P::DigitalInPin                         mcp2515_int_pin        (&DDRD, &PORTD, &PIND, 2); /* D2 = PD2 = INT0 */
  ATMEGA328P::EINT0                                mcp2515_eint0          (&EICRA, int_ctrl       );
  ATMEGA328P::EINT0_ExternalInterruptEventCallback mcp2515_eint0_callback (mcp2515_eint0          );

  mcp2515_int_pin.setPullUpMode (hal::interface::PullUpMode::PULL_UP);

  mcp2515_eint0.setTriggerMode  (MCP2515_INT_TRIGGER_MODE);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::EXTERNAL_INT0), &mcp2515_eint0_callback);



  /* DRIVER ***************************************************************************/

  /* SERIAL ***************************************************************************/
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

  debug::DebugSerial debug_serial(serial);

  /* MCP2515 **************************************************************************/
  can::interface::CanFrameBuffer              mcp2515_can_tx_buf                (CAN_TX_BUFFER_SIZE);
  can::interface::CanFrameBuffer              mcp2515_can_rx_buf                (CAN_RX_BUFFER_SIZE);

  can::MCP2515::MCP2515_IoSpi                 mcp2515_io_spi                    (spi_master, mcp2515_cs          );
  can::MCP2515::MCP2515_Control               mcp2515_ctrl                      (mcp2515_io_spi                  );
  can::MCP2515::MCP2515_CanConfiguration      mcp2515_can_config                (mcp2515_io_spi, F_MCP2515_MHz   );
  can::MCP2515::MCP2515_CanControl            mcp2515_can_control               (mcp2515_can_tx_buf, mcp2515_can_rx_buf, mcp2515_ctrl);

  can::MCP2515::MCP2515_onMessageError        mcp2515_on_message_error;
  can::MCP2515::MCP2515_onWakeup              mcp2515_on_wakeup;
  can::MCP2515::MCP2515_onTransmitBufferEmpty mcp2515_on_transmit_buffer_2_empty(mcp2515_can_tx_buf, mcp2515_ctrl);
  can::MCP2515::MCP2515_onTransmitBufferEmpty mcp2515_on_transmit_buffer_1_empty(mcp2515_can_tx_buf, mcp2515_ctrl);
  can::MCP2515::MCP2515_onTransmitBufferEmpty mcp2515_on_transmit_buffer_0_empty(mcp2515_can_tx_buf, mcp2515_ctrl);
  can::MCP2515::MCP2515_onReceiveBufferFull   mcp2515_on_receive_buffer_1_full  (mcp2515_can_rx_buf, mcp2515_ctrl);
  can::MCP2515::MCP2515_onReceiveBufferFull   mcp2515_on_receive_buffer_0_full  (mcp2515_can_rx_buf, mcp2515_ctrl);
  can::MCP2515::MCP2515_EventCallback         mcp2515_event_callback            (mcp2515_ctrl, mcp2515_on_message_error, mcp2515_on_wakeup, mcp2515_on_transmit_buffer_2_empty, mcp2515_on_transmit_buffer_1_empty, mcp2515_on_transmit_buffer_0_empty, mcp2515_on_receive_buffer_1_full, mcp2515_on_receive_buffer_0_full);

  can::Can                                    can                               (mcp2515_can_config, mcp2515_can_control);


  mcp2515_eint0.registerExternalInterruptCallback(&mcp2515_event_callback);


  uint8_t bitrate = static_cast<uint8_t>(can::interface::CanBitRate::BR_250kBPS);

  can.open();

  can.ioctl(can::IOCTL_SET_BITRATE, static_cast<void *>(&bitrate));

  /* ALL ******************************************************************************/
  int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::GLOBAL));


  /* APPLICATION **********************************************************************/

  can::MCP2515::MCP2515_Debug::debug_dumpAllRegs(debug_serial, flash, mcp2515_io_spi);

  for(;;)
  {
    hal::interface::CanFrame frame;

    /* This is how a Heartbeat frame looks like in CANOpen for
     * node id = 1, node state = preoperational
     */
    frame.id      = 0x701;
    frame.dlc     = 1;
    frame.data[0] = 0x7F;

    can.write(reinterpret_cast<uint8_t* >(&frame), sizeof(frame));

    delay.delay_ms(1000);
  }

  can.close();

  return 0;
}
