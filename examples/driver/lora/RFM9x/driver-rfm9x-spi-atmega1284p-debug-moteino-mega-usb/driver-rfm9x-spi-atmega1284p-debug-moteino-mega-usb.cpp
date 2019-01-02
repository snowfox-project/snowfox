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
 * This example program is tailored for usage with Moteino-Mega-USB
 *
 * Electrical interface:
 *   CS   = D4 = PB4
 *   SCK  = D7 = PB7
 *   MISO = D6 = PB6
 *   MOSI = D5 = PB5
 *
 * Upload via avrdude (and the USB connection of the Moteino-Mega-USB)
 *   avrdude -p atmega1284p -c arduino -P /dev/ttyUSB0 -e -U flash:w:driver-rfm9x-spi-atmega1284p-debug-moteino-mega-usb
 *
 * Upload via avrdude (and eHajo uISP-Stick)
 *   avrdude -p atmega1284p -c usbtiny -P usb -e -U flash:w:driver-rfm9x-spi-atmega1284p-debug-moteino-mega-usb
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA1284P/Flash.h>
#include <spectre/hal/avr/ATMEGA1284P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA1284P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA1284P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA1284P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA1284P/UART0.h>
#include <spectre/blox/hal/avr/ATMEGA1284P/SpiMaster.h>

#include <spectre/blox/driver/serial/SerialUart.h>

#include <spectre/driver/lora/RFM9x/RFM9x_Debug.h>
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

static uint16_t                    const UART_RX_BUFFER_SIZE =  0;
static uint16_t                    const UART_TX_BUFFER_SIZE = 16;

static hal::interface::SpiMode     const RFM9x_SPI_MODE              = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const RFM9x_SPI_BIT_ORDER         = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const RFM9x_SPI_PRESCALER         = 16; /* Moteino Mega USB CLK = 16 MHz -> SPI Clk = 1 MHz */

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /************************************************************************************
   * HAL
   ************************************************************************************/

  ATMEGA1284P::Flash               flash;

  ATMEGA1284P::InterruptController int_ctrl  (&EIMSK, &PCICR, &WDTCSR, &TIMSK0, &TIMSK1, &TIMSK2, &UCSR0B, &UCSR1B, &SPCR, &TWCR, &EECR, &SPMCSR, &ACSR, &ADCSRA);
  ATMEGA1284P::CriticalSection     crit_sec  (&SREG);

  ATMEGA1284P::DigitalOutPin       rfm9x_cs  (&DDRB, &PORTB,        4); /* CS   = D4 = PB4 */
  ATMEGA1284P::DigitalOutPin       rfm9x_sck (&DDRB, &PORTB,        7); /* SCK  = D7 = PB7 */
  ATMEGA1284P::DigitalInPin        rfm9x_miso(&DDRB, &PORTB, &PINB, 6); /* MISO = D6 = PB6 */
  ATMEGA1284P::DigitalOutPin       rfm9x_mosi(&DDRB, &PORTB,        5); /* MOSI = D5 = PB5 */

  rfm9x_cs.set();
  rfm9x_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  blox::ATMEGA1284P::UART0         uart0     (&UDR0,
                                              &UCSR0A,
                                              &UCSR0B,
                                              &UCSR0C,
                                              &UBRR0,
                                              int_ctrl,
                                              F_CPU);

  blox::ATMEGA1284P::SpiMaster     spi_master(&SPCR,
                                              &SPSR,
                                              &SPDR,
                                              crit_sec,
                                              int_ctrl,
                                              RFM9x_SPI_MODE,
                                              RFM9x_SPI_BIT_ORDER,
                                              RFM9x_SPI_PRESCALER);

  /* GLOBAL INTERRUPT *****************************************************************/
  int_ctrl.enableInterrupt(ATMEGA164P_324P_644P_1284P::toIntNum(ATMEGA1284P::Interrupt::GLOBAL));


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


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  lora::RFM9x::RFM9x_Debug::debug_dumpAllRegs(trace, flash, rfm9x_spi);

  for(;;)
  {

  }

  return 0;
}
