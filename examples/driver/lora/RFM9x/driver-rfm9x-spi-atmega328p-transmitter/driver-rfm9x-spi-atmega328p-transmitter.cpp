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

#include <string.h>

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/EINT0.h>
#include <spectre/hal/avr/ATMEGA328P/EINT1.h>
#include <spectre/hal/avr/ATMEGA328P/UART0.h>
#include <spectre/hal/avr/ATMEGA328P/Flash.h>
#include <spectre/hal/avr/ATMEGA328P/SpiMaster.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/driver/serial/Serial.h>
#include <spectre/driver/serial/UART/UART_ReceiveBuffer.h>
#include <spectre/driver/serial/UART/UART_TransmitBuffer.h>
#include <spectre/driver/serial/UART/UART_CallbackHandler.h>
#include <spectre/driver/serial/UART/UART_SerialController.h>

#include <spectre/driver/lora/RFM9x/RFM9x.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Debug.h>
#include <spectre/driver/lora/RFM9x/RFM9x_IoSpi.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Status.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Control.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Configuration.h>

#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_Dio0EventCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_onTxDoneCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_onRxDoneCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_onCadDoneCallback.h>

#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_Dio1EventCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_onRxTimeoutCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_onCadDetectedCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_onFhssChangeChannelCallback.h>

#include <spectre/os/Event.h>

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

static uint16_t                    const RX_BUFFER_SIZE              = 0;
static uint16_t                    const TX_BUFFER_SIZE              = 64;

static hal::interface::SpiMode     const RFM9x_SPI_MODE              = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const RFM9x_SPI_BIT_ORDER         = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const RFM9x_SPI_PRESCALER         = 16;       /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz */

static uint32_t                    const RFM9x_F_XOSC_Hz             = 32000000; /* 32 MHz                                      */
static hal::interface::TriggerMode const RFM9x_DIO0_INT_TRIGGER_MODE = hal::interface::TriggerMode::RisingEdge;
static hal::interface::TriggerMode const RFM9x_DIO1_INT_TRIGGER_MODE = hal::interface::TriggerMode::RisingEdge;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /************************************************************************************
   * HAL
   ************************************************************************************/

  ATMEGA328P::Flash                               flash;
  ATMEGA328P::InterruptController                 int_ctrl                               (&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ADCSRA, &EECR, &ACSR, &TWCR, &SPMCSR);
  ATMEGA328P::CriticalSection                     crit_sec                               (&SREG);

  /* UART0 ****************************************************************************/
  ATMEGA328P::UART0                               uart0                                  (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);
  ATMEGA328P::UART0_TransmitRegisterEmptyCallback uart0_uart_data_register_empty_callback(uart0);
  ATMEGA328P::UART0_ReceiveCompleteCallback       uart0_receive_complete_callback        (uart0);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::USART_UART_DATA_REGISTER_EMPTY), &uart0_uart_data_register_empty_callback);
  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::USART_RECEIVE_COMPLETE        ), &uart0_receive_complete_callback        );

  /* SPI/CS for RFM95 *****************************************************************/
  /* As the datasheet state: 'If SS is configured as an input and is driven low
   * while MSTR is set, MSTR will be cleared.'. This means that in this special
   * case where the CS pin is equal with SS pin we need to set it before configuring
   * the SPI interface.
   */
  ATMEGA328P::DigitalOutPin rfm9x_cs  (&DDRB, &PORTB,        2);     /* CS   = D10 = PB2 */
  ATMEGA328P::DigitalOutPin rfm9x_sck (&DDRB, &PORTB,        5);     /* SCK  = D13 = PB5 */
  ATMEGA328P::DigitalInPin  rfm9x_miso(&DDRB, &PORTB, &PINB, 4);     /* MOSI = D12 = PB4 */
  ATMEGA328P::DigitalOutPin rfm9x_mosi(&DDRB, &PORTB,        3);     /* MOSI = D11 = PB3 */

  rfm9x_cs.set();
  rfm9x_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  ATMEGA328P::SpiMaster     spi_master(&SPCR, &SPSR, &SPDR);

  spi_master.setSpiMode     (RFM9x_SPI_MODE     );
  spi_master.setSpiBitOrder (RFM9x_SPI_BIT_ORDER);
  spi_master.setSpiPrescaler(RFM9x_SPI_PRESCALER);

  /* EXT INT #0 for DIO0 notifications by RFM9x ***************************************/
  ATMEGA328P::DigitalInPin                          rfm9x_dio0_int_pin        (&DDRD, &PORTD, &PIND, 2); /* D2 = PD2 = INT0 */
  ATMEGA328P::EINT0                                 rfm9x_dio0_eint0          (&EICRA, int_ctrl);
  ATMEGA328P::EINT0_ExternalInterruptEventCallback  rfm9x_dio0_eint0_callback (rfm9x_dio0_eint0);

  rfm9x_dio0_int_pin.setPullUpMode (hal::interface::PullUpMode::PULL_UP);

  rfm9x_dio0_eint0.setTriggerMode  (RFM9x_DIO0_INT_TRIGGER_MODE);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::EXTERNAL_INT0), &rfm9x_dio0_eint0_callback);

  /* EXT INT #1 for DIO1 notifications by RFM9x ***************************************/
  ATMEGA328P::DigitalInPin                          rfm9x_dio1_int_pin        (&DDRD, &PORTD, &PIND, 3); /* D3 = PD3 = INT1 */
  ATMEGA328P::EINT1                                 rfm9x_dio1_eint1          (&EICRA, int_ctrl);
  ATMEGA328P::EINT1_ExternalInterruptEventCallback  rfm9x_dio1_eint1_callback (rfm9x_dio1_eint1);

  rfm9x_dio1_int_pin.setPullUpMode (hal::interface::PullUpMode::PULL_UP);

  rfm9x_dio1_eint1.setTriggerMode  (RFM9x_DIO1_INT_TRIGGER_MODE);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::EXTERNAL_INT1), &rfm9x_dio1_eint1_callback);



  /************************************************************************************
   * DRIVER
   ************************************************************************************/

  /* SERIAL ***************************************************************************/
  serial::UART::UART_TransmitBuffer   serial_tx_buffer  (TX_BUFFER_SIZE, crit_sec, uart0);
  serial::UART::UART_ReceiveBuffer    serial_rx_buffer  (RX_BUFFER_SIZE, crit_sec, uart0);
  serial::UART::UART_CallbackHandler  serial_callback   (serial_tx_buffer, serial_rx_buffer);
  serial::UART::UART_SerialController serial_ctrl       (uart0);
  serial::Serial                      serial            (serial_ctrl, serial_tx_buffer, serial_rx_buffer);

  uart0.registerUARTCallback(&serial_callback);

  uint8_t baud_rate = static_cast<uint8_t>(serial::interface::SerialBaudRate::B115200);
  uint8_t parity    = static_cast<uint8_t>(serial::interface::SerialParity::None     );
  uint8_t stop_bit  = static_cast<uint8_t>(serial::interface::SerialStopBit::_1      );

  serial.open();
  serial.ioctl(serial::IOCTL_SET_BAUDRATE, static_cast<void *>(&baud_rate));
  serial.ioctl(serial::IOCTL_SET_PARITY,   static_cast<void *>(&parity   ));
  serial.ioctl(serial::IOCTL_SET_STOPBIT,  static_cast<void *>(&stop_bit ));

  debug::DebugSerial debug_serial(serial);

  /* RFM95 ****************************************************************************/
  lora::RFM9x::RFM9x_IoSpi                        rfm9x_spi                             (spi_master, rfm9x_cs      );
  lora::RFM9x::RFM9x_Configuration                rfm9x_config                          (rfm9x_spi, RFM9x_F_XOSC_Hz);
  lora::RFM9x::RFM9x_Control                      rfm9x_control                         (rfm9x_spi                 );
  lora::RFM9x::RFM9x_Status                       rfm9x_status                          (rfm9x_spi                 );

  os::Event                                       rfm9x_tx_done_event                   (crit_sec);

  lora::RFM9x::RFM9x_onTxDoneCallback             rfm9x_on_tx_done_callback             (rfm9x_tx_done_event);
  lora::RFM9x::RFM9x_onRxDoneCallback             rfm9x_on_rx_done_callback;
  lora::RFM9x::RFM9x_onCadDoneCallback            rfm9x_on_cad_done_callback;
  lora::RFM9x::RFM9x_Dio0EventCallback            rfm9x_dio0_event_callback             (rfm9x_control, rfm9x_on_tx_done_callback, rfm9x_on_rx_done_callback, rfm9x_on_cad_done_callback);

  lora::RFM9x::RFM9x_onRxTimeoutCallback          rfm9x_on_rx_timeout_callback;
  lora::RFM9x::RFM9x_onFhssChangeChannelCallback  rfm9x_on_fhss_change_channel_callback;
  lora::RFM9x::RFM9x_onCadDetectedCallback        rfm9x_on_cad_detected_callback;
  lora::RFM9x::RFM9x_Dio1EventCallback            rfm9x_dio1_event_callback             (rfm9x_control, rfm9x_on_rx_timeout_callback, rfm9x_on_fhss_change_channel_callback, rfm9x_on_cad_detected_callback);

  lora::RFM9x::RFM9x                              rfm9x                                 (rfm9x_config, rfm9x_control, rfm9x_status, rfm9x_tx_done_event);


  rfm9x_dio0_eint0.registerExternalInterruptCallback(&rfm9x_dio0_event_callback);
  rfm9x_dio1_eint1.registerExternalInterruptCallback(&rfm9x_dio1_event_callback);


  uint32_t frequenzy_Hz     = 433775000; /* 433.775 Mhz - Dedicated for digital communication channels in the 70 cm band */
  uint8_t  signal_bandwidth = static_cast<uint8_t>(lora::RFM9x::interface::SignalBandwidth::BW_250_kHz);
  uint8_t  coding_rate      = static_cast<uint8_t>(lora::RFM9x::interface::CodingRate::CR_4_5         );
  uint8_t  spreading_factor = static_cast<uint8_t>(lora::RFM9x::interface::SpreadingFactor::SF_128    );
  uint16_t preamble_length  = 8;
  uint16_t tx_fifo_size     = 128;
  uint16_t rx_fifo_size     = 128;

  rfm9x.open();
  rfm9x.ioctl(lora::RFM9x::IOCTL_SET_FREQUENCY_HZ,      static_cast<void *>(&frequenzy_Hz    ));
  rfm9x.ioctl(lora::RFM9x::IOCTL_SET_SIGNAL_BANDWIDTH,  static_cast<void *>(&signal_bandwidth));
  rfm9x.ioctl(lora::RFM9x::IOCTL_SET_CODING_RATE,       static_cast<void *>(&coding_rate     ));
  rfm9x.ioctl(lora::RFM9x::IOCTL_SET_SPREADING_FACTOR,  static_cast<void *>(&spreading_factor));
  rfm9x.ioctl(lora::RFM9x::IOCTL_SET_PREAMBLE_LENGTH,   static_cast<void *>(&preamble_length ));
  rfm9x.ioctl(lora::RFM9x::IOCTL_SET_TX_FIFO_SIZE,      static_cast<void *>(&tx_fifo_size    ));
  rfm9x.ioctl(lora::RFM9x::IOCTL_SET_RX_FIFO_SIZE,      static_cast<void *>(&rx_fifo_size    ));

  /* ALL ******************************************************************************/
  int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::GLOBAL));



  /* APPLICATION **********************************************************************/

  lora::RFM9x::RFM9x_Debug::debug_dumpAllRegs(debug_serial, flash, rfm9x_spi);

  for(;;)
  {

  }


  /* CLEANUP **************************************************************************/

  serial.close();
  rfm9x.close ();

  return 0;
}
