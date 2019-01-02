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
 * This example programm is tailored for usage with Arduino Uno
 * and Dragino LoRa Shield V1.4
 *
 * Electrical interface:
 *   CS   = D10 = PB2
 *   SCK  = D13 = PB5
 *   MISO = D12 = PB4
 *   MOSI = D11 = PB3
 *   DIO0 = D2  = PD2 = INT0
 *   DIO1 = D3  = PD3 = INT1 (Connect Pin #2 / DIO1 of connector SV1 with D3/INT1)
 *
 * Upload via avrdude
 *   avrdude -p atmega328p -c avrisp2 -e -U flash:w:driver-rfm9x-spi-atmega328p-transmitter-dragino-lora-shield-v1.4
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdio.h>
#include <string.h>

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/Delay.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA328P/UART0.h>
#include <spectre/blox/hal/avr/ATMEGA328P/SpiMaster.h>
#include <spectre/blox/hal/avr/ATMEGA328P/ExternalInterruptController.h>

#include <spectre/blox/driver/lora/RFM9x.h>
#include <spectre/blox/driver/serial/SerialUart.h>

#include <spectre/driver/lora/RFM9x/RFM9x_IoSpi.h>

#include <spectre/trace/Trace.h>
#include <spectre/trace/SerialTraceOutput.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint16_t                    const UART_RX_BUFFER_SIZE         = 0;
static uint16_t                    const UART_TX_BUFFER_SIZE         = 64;

static hal::interface::SpiMode     const RFM9x_SPI_MODE              = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const RFM9x_SPI_BIT_ORDER         = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const RFM9x_SPI_PRESCALER         = 16;       /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz */

static uint32_t                    const RFM9x_F_XOSC_Hz             = 32000000; /* 32 MHz                                      */
static hal::interface::TriggerMode const RFM9x_DIO0_INT_TRIGGER_MODE = hal::interface::TriggerMode::RisingEdge;
static hal::interface::TriggerMode const RFM9x_DIO1_INT_TRIGGER_MODE = hal::interface::TriggerMode::RisingEdge;
static uint32_t                    const RFM9x_FREQUENCY_Hz          = 433775000; /* 433.775 Mhz - Dedicated for digital communication channels in the 70 cm band */
static uint16_t                    const RFM9x_PREAMBLE_LENGTH       = 8;
static uint16_t                    const RFM9x_TX_FIFO_FIZE          = 128;
static uint16_t                    const RFM9x_RX_FIFO_FIZE          = 128;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /************************************************************************************
   * HAL
   ************************************************************************************/

  ATMEGA328P::Delay               delay;

  ATMEGA328P::InterruptController int_ctrl  (&EIMSK, &PCICR, &WDTCSR, &TIMSK0, &TIMSK1, &TIMSK2, &UCSR0B, &SPCR, &TWCR, &EECR, &SPMCSR, &ACSR, &ADCSRA);
  ATMEGA328P::CriticalSection     crit_sec  (&SREG);

  /* As the datasheet state: 'If SS is configured as an input and is driven low
   * while MSTR is set, MSTR will be cleared.'. This means that in this special
   * case where the CS pin is equal with SS pin we need to set it before configuring
   * the SPI interface.
   */
  ATMEGA328P::DigitalOutPin       rfm9x_cs  (&DDRB, &PORTB,        2); /* CS   = D10 = PB2 */
  ATMEGA328P::DigitalOutPin       rfm9x_sck (&DDRB, &PORTB,        5); /* SCK  = D13 = PB5 */
  ATMEGA328P::DigitalInPin        rfm9x_miso(&DDRB, &PORTB, &PINB, 4); /* MISO = D12 = PB4 */
  ATMEGA328P::DigitalOutPin       rfm9x_mosi(&DDRB, &PORTB,        3); /* MOSI = D11 = PB3 */

  rfm9x_cs.set();
  rfm9x_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  blox::ATMEGA328P::UART0                       uart0       (&UDR0,
                                                             &UCSR0A,
                                                             &UCSR0B,
                                                             &UCSR0C,
                                                             &UBRR0,
                                                             int_ctrl,
                                                             F_CPU);

  blox::ATMEGA328P::SpiMaster                   spi_master  (&SPCR,
                                                             &SPSR,
                                                             &SPDR,
                                                             crit_sec,
                                                             int_ctrl,
                                                             RFM9x_SPI_MODE,
                                                             RFM9x_SPI_BIT_ORDER,
                                                             RFM9x_SPI_PRESCALER);

  blox::ATMEGA328P::ExternalInterruptController ext_int_ctrl(&EICRA,
                                                             &PCMSK0,
                                                             &PCMSK1,
                                                             &PCMSK2,
                                                             int_ctrl);

  /* EXT INT #0 for DIO0 notifications by RFM9x ***************************************/
  ATMEGA328P::DigitalInPin rfm9x_dio0_int_pin              (&DDRD, &PORTD, &PIND, 2); /* D2 = PD2 = INT0 */
                           rfm9x_dio0_int_pin.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  ext_int_ctrl().setTriggerMode(ATMEGA328P::toExtIntNum(ATMEGA328P::ExternalInterrupt::EXTERNAL_INT0), RFM9x_DIO0_INT_TRIGGER_MODE);
  ext_int_ctrl().enable        (ATMEGA328P::toExtIntNum(ATMEGA328P::ExternalInterrupt::EXTERNAL_INT0)                             );

  /* EXT INT #1 for DIO1 notifications by RFM9x ***************************************/
  ATMEGA328P::DigitalInPin rfm9x_dio1_int_pin              (&DDRD, &PORTD, &PIND, 3); /* D3 = PD3 = INT1 */
                           rfm9x_dio1_int_pin.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  ext_int_ctrl().setTriggerMode(ATMEGA328P::toExtIntNum(ATMEGA328P::ExternalInterrupt::EXTERNAL_INT1), RFM9x_DIO1_INT_TRIGGER_MODE);
  ext_int_ctrl().enable        (ATMEGA328P::toExtIntNum(ATMEGA328P::ExternalInterrupt::EXTERNAL_INT1)                             );

  /* GLOBAL INTERRUPT *****************************************************************/
  int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::GLOBAL));


  /************************************************************************************
   * DRIVER
   ************************************************************************************/

  /* SERIAL ***************************************************************************/
  blox::SerialUart serial(crit_sec,
                          uart0(),
                          UART_RX_BUFFER_SIZE,
                          UART_TX_BUFFER_SIZE,
                          serial::interface::SerialBaudRate::B115200,
                          serial::interface::SerialParity::None,
                          serial::interface::SerialStopBit::_1);

  trace::SerialTraceOutput serial_trace_output(serial());
  trace::Trace             trace              (serial_trace_output,trace::Level::Debug);

  /* RFM95 ****************************************************************************/
  lora::RFM9x::RFM9x_IoSpi rfm9x_spi(spi_master(), rfm9x_cs);

  blox::RFM9x rfm9x(crit_sec,
                    ext_int_ctrl(),
                    ATMEGA328P::toExtIntNum(ATMEGA328P::ExternalInterrupt::EXTERNAL_INT0),
                    ATMEGA328P::toExtIntNum(ATMEGA328P::ExternalInterrupt::EXTERNAL_INT1),
                    rfm9x_spi,
                    RFM9x_F_XOSC_Hz,
                    RFM9x_FREQUENCY_Hz,
                    lora::RFM9x::interface::SignalBandwidth::BW_250_kHz,
                    lora::RFM9x::interface::CodingRate::CR_4_5,
                    lora::RFM9x::interface::SpreadingFactor::SF_128,
                    RFM9x_PREAMBLE_LENGTH,
                    RFM9x_TX_FIFO_FIZE,
                    RFM9x_RX_FIFO_FIZE);


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  for(uint16_t msg_cnt = 0;; msg_cnt++)
  {
    uint8_t msg[64] = {0};

    uint16_t const msg_len = snprintf(reinterpret_cast<char *>(msg), 64, "[Spectre RTOS (c) LXRobotics] [lora::RFM9x] Message %d\r\n", msg_cnt);

    ssize_t const ret_code = rfm9x().write(msg, msg_len);

    if     (ret_code == static_cast<ssize_t>(lora::RFM9x::RetCodeWrite::ParameterError      )) trace.print(trace::Level::Debug, "ERROR   - ParameterError\r\n");
    else if(ret_code == static_cast<ssize_t>(lora::RFM9x::RetCodeWrite::TxFifoSizeExceeded  )) trace.print(trace::Level::Debug, "ERROR   - TxFifoSizeExceeded\r\n");
    else if(ret_code == static_cast<ssize_t>(lora::RFM9x::RetCodeWrite::ModemBusy_NotSleep  )) trace.print(trace::Level::Debug, "ERROR   - ModemBusy_NotSleep\r\n");
    else if(ret_code == static_cast<ssize_t>(lora::RFM9x::RetCodeWrite::ModemBusy_NotStandby)) trace.print(trace::Level::Debug, "ERROR   - ModemBusy_NotStandby\r\n");
    else                                                                                       trace.print(trace::Level::Debug, "SUCCESS - %s", msg);

    delay.delay_ms(1000);
  }


  /* CLEANUP **************************************************************************/

  return 0;
}
