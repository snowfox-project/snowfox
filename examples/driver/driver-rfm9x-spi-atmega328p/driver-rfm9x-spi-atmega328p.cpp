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
 * This example program is tailored for usage with Arduino Uno and Dragino
 * LoRa Shield (https://github.com/dragino/Lora)
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/SPIMaster.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>

#include <spectre/driver/lora/RFM9x/RFM9x.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static hal::interface::SpiMode     const RFM9x_SPI_MODE         = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const RFM9x_SPI_BIT_ORDER    = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const RFM9x_SPI_PRESCALER    = 16; /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz                     */

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::SPIMaster     spi_master             (&SPCR, &SPSR, &SPDR);
  ATMEGA328P::DigitalOutPin rfm9x_cs               (&DDRB, &PORTB, 2); /* CS = D10 = PB2 */

  spi_master.setSpiMode         (RFM9x_SPI_MODE     );
  spi_master.setSpiBitOrder     (RFM9x_SPI_BIT_ORDER);
  spi_master.setSpiPrescaler    (RFM9x_SPI_PRESCALER);

  /* DRIVER ***************************************************************************/

  lora::RFM9x::RFM9x       rfm9x;

  /* APPLICATION **********************************************************************/


  rfm9x.open();

  for(;;)
  {
    /* TODO */
  }

  rfm9x.close();

  return 0;
}
