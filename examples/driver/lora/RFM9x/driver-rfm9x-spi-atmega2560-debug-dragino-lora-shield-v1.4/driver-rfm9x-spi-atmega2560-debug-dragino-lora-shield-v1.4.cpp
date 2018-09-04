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
 * This example program is tailored for usage with Arduino Mega (ATMEGA2560)
 *
 * Electrical interface:
 *   CS   = D10       = PB4
 *   SCK  = ICSP SCK  = PB1
 *   MISO = ICSP MISO = PB3
 *   MOSI = ICSP MOSI = PB2
 *
 * Upload via avrdude
 *   avrdude -p atmega2560 -c avrisp2 -e -U flash:w:driver-rfm9x-spi-atmega2560-debug-dragino-lora-shield-v1.4
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA2560/Flash.h>
#include <spectre/hal/avr/ATMEGA2560/SpiMaster.h>
#include <spectre/hal/avr/ATMEGA2560/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA2560/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA2560/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA2560/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA2560/UART0.h>

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

  ATMEGA2560::Flash               flash;
  ATMEGA2560::InterruptController int_ctrl(&EIMSK, &PCICR, &WDTCSR, &TIMSK0, &TIMSK1, &TIMSK2, &TIMSK3, &TIMSK4, &TIMSK5, &UCSR0B, &UCSR1B, &UCSR2B, &UCSR3B, &SPCR, &TWCR, &EECR, &SPMCSR, &ACSR, &ADCSRA);
  ATMEGA2560::CriticalSection     crit_sec(&SREG);
  blox::ATMEGA2560::UART0         uart0   (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);

  /* SPI/CS for RFM95 *****************************************************************/
  ATMEGA2560::DigitalOutPin rfm9x_cs     (&DDRB, &PORTB,        4);     /* CS   = D10          = PB4 */
  ATMEGA2560::DigitalOutPin rfm9x_sck    (&DDRB, &PORTB,        1);     /* SCK  = ICSP SCK     = PB1 */
  ATMEGA2560::DigitalInPin  rfm9x_miso   (&DDRB, &PORTB, &PINB, 3);     /* MISO = ICSP MISO    = PB3 */
  ATMEGA2560::DigitalOutPin rfm9x_mosi   (&DDRB, &PORTB,        2);     /* MOSI = ICSP MOSI    = PB2 */
  ATMEGA2560::DigitalOutPin atmega2560_ss(&DDRB, &PORTB,        0);     /* SS   = Slave Select = PB0 */

  atmega2560_ss.set(); /* Must be set in order to correctly configure SPI master when instantiating ATMEGA2560::SpiMaster */
  rfm9x_cs.set();
  rfm9x_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  ATMEGA2560::SpiMaster     spi_master(&SPCR, &SPSR, &SPDR);

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
  int_ctrl.enableInterrupt(ATMEGA640_1280_2560::toIntNum(ATMEGA2560::Interrupt::GLOBAL));


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  lora::RFM9x::RFM9x_Debug::debug_dumpAllRegs(debug_serial, flash, rfm9x_spi);

  for(;;)
  {

  }

  return 0;
}
