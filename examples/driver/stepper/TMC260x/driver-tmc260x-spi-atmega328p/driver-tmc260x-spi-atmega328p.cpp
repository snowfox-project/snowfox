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
 * This example program is tailored for usage with Arduino Uno and Trinamic
 * TOS-100 Stepper Motor Driver Shield (https://github.com/trinamic/TOS-100)
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA328P/SpiMaster.h>

#include <spectre/driver/stepper/TMC26x/TMC26x.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static hal::interface::SpiMode     const TMC26x_SPI_MODE         = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const TMC26x_SPI_BIT_ORDER    = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const TMC26x_SPI_PRESCALER    = 16; /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz                     */

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::InterruptController int_ctrl      (&EIMSK, &PCICR, &WDTCSR, &TIMSK0, &TIMSK1, &TIMSK2, &UCSR0B, &SPCR, &TWCR, &EECR, &SPMCSR, &ACSR, &ADCSRA);
  ATMEGA328P::CriticalSection     crit_sec      (&SREG);

  ATMEGA328P::DigitalOutPin       tmc26x_cs     (&DDRB, &PORTB,        2); /* CS      = D10 = PB2 */
  ATMEGA328P::DigitalOutPin       tmc26x_sck    (&DDRB, &PORTB,        5); /* SCK     = D13 = PB5 */
  ATMEGA328P::DigitalInPin        tmc26x_miso   (&DDRB, &PORTB, &PINB, 4); /* MISO    = D12 = PB4 */
  ATMEGA328P::DigitalOutPin       tmc26x_mosi   (&DDRB, &PORTB,        3); /* MOSI    = D11 = PB3 */

  ATMEGA328P::DigitalOutPin       tmc26x_step   (&DDRD, &PORTD,        7); /* STEP    = D7  = PD7 */
  ATMEGA328P::DigitalOutPin       tmc26x_dir    (&DDRD, &PORTD,        6); /* DIR     = D6  = PD6 */
  ATMEGA328P::DigitalOutPin       tmc26x_nEnable(&DDRD, &PORTD,        5); /* nENABLE = D5  = PD5 */
  ATMEGA328P::DigitalOutPin       tmc26x_sg     (&DDRD, &PORTD,        4); /* SG      = D4  = PD4 */

  tmc26x_cs.set();
  tmc26x_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  blox::ATMEGA328P::SpiMaster     spi_master    (&SPCR,
                                                 &SPSR,
                                                 &SPDR,
                                                 crit_sec,
                                                 int_ctrl,
                                                 TMC26x_SPI_MODE,
                                                 TMC26x_SPI_BIT_ORDER,
                                                 TMC26x_SPI_PRESCALER);

  /* GLOBAL INTERRUPT *****************************************************************/
  int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::GLOBAL));


  /* DRIVER ***************************************************************************/

  /* TMC26x ***************************************************************************/
  stepper::TMC26x::TMC26x tmc26x;


  /* APPLICATION **********************************************************************/


  tmc26x.open();

  for(;;)
  {
    /* TODO */
  }

  tmc26x.close();

  return 0;
}
