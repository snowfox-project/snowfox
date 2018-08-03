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
 *   avrdude -p atmega1284p -c arduino -P /dev/ttyUSB0 -e -U flash:w:driver-rfm9x-spi-atmega1284p-debug-moteino-mega-usb
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA1284P/Flash.h>
#include <spectre/hal/avr/ATMEGA1284P/SpiMaster.h>
#include <spectre/hal/avr/ATMEGA1284P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA1284P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA1284P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA1284P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA1284P/UART0.h>

#include <spectre/blox/driver/serial/SerialUart.h>

#include <spectre/driver/lora/RFM9x/RFM9x_Debug.h>
#include <spectre/driver/lora/RFM9x/RFM9x_IoSpi.h>

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
  ATMEGA1284P::InterruptController int_ctrl(&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ACSR, &ADCSRA, &EECR, &TWCR, &SPMCSR, &UCSR1B);
  ATMEGA1284P::CriticalSection     crit_sec(&SREG);
  blox::ATMEGA1284P::UART0         uart0   (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);

  /* SPI/CS for RFM95 *****************************************************************/
  ATMEGA1284P::DigitalOutPin rfm9x_cs  (&DDRB, &PORTB,        4);     /* CS   = D4 = PB4 */
  ATMEGA1284P::DigitalOutPin rfm9x_sck (&DDRB, &PORTB,        7);     /* SCK  = D7 = PB7 */
  ATMEGA1284P::DigitalInPin  rfm9x_miso(&DDRB, &PORTB, &PINB, 6);     /* MISO = D6 = PB6 */
  ATMEGA1284P::DigitalOutPin rfm9x_mosi(&DDRB, &PORTB,        5);     /* MOSI = D5 = PB5 */

  rfm9x_cs.set();
  rfm9x_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  ATMEGA1284P::SpiMaster     spi_master(&SPCR, &SPSR, &SPDR);

  spi_master.setSpiMode     (RFM9x_SPI_MODE     );
  spi_master.setSpiBitOrder (RFM9x_SPI_BIT_ORDER);
  spi_master.setSpiPrescaler(RFM9x_SPI_PRESCALER);


  /************************************************************************************
   * DRIVER
   ************************************************************************************/

  /* SERIAL ***************************************************************************/
  blox::SerialUart serial(crit_sec, uart0(), UART_RX_BUFFER_SIZE, UART_TX_BUFFER_SIZE);

  uint8_t baud_rate = static_cast<uint8_t>(serial::interface::SerialBaudRate::B115200);
  uint8_t parity    = static_cast<uint8_t>(serial::interface::SerialParity::None     );
  uint8_t stop_bit  = static_cast<uint8_t>(serial::interface::SerialStopBit::_1      );

  serial().ioctl(serial::IOCTL_SET_BAUDRATE, static_cast<void *>(&baud_rate));
  serial().ioctl(serial::IOCTL_SET_PARITY,   static_cast<void *>(&parity   ));
  serial().ioctl(serial::IOCTL_SET_STOPBIT,  static_cast<void *>(&stop_bit ));

  debug::DebugSerial debug_serial(serial());

  /* RFM95 ****************************************************************************/
  lora::RFM9x::RFM9x_IoSpi rfm9x_spi(spi_master, rfm9x_cs);


  /* GLOBAL INTERRUPT *****************************************************************/
  int_ctrl.enableInterrupt(ATMEGA164P_324P_644P_1284P::toIntNum(ATMEGA1284P::Interrupt::GLOBAL));


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  lora::RFM9x::RFM9x_Debug::debug_dumpAllRegs(debug_serial, flash, rfm9x_spi);

  for(;;)
  {

  }

  return 0;
}
