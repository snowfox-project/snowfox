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

#include <stdio.h>

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/Delay.h>
#include <spectre/hal/avr/ATMEGA328P/I2CMaster.h>
#include <spectre/hal/avr/common/ATxxxx/i2c/I2CMasterBase.h>

#include <spectre/driver/sensor/AD7151/AD7151.h>
#include <spectre/driver/sensor/AD7151/AD7151_IoI2c.h>
#include <spectre/driver/sensor/AD7151/AD7151_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t  const AD7151_I2C_ADDR  = (0x48 << 1);
static uint32_t const LOOP_DELAY_ms    = 1000; /* 1 s */

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::I2CMaster i2c_master_atmega328p(&TWCR, &TWDR, &TWSR, &TWBR);
  ATxxxx::I2CMasterBase i2c_master           (i2c_master_atmega328p);

  i2c_master.setI2CClock(hal::interface::I2CMasterConfiguration::F_100_kHz);

  ATMEGA328P::Delay     delay;

  /* DRIVER ***************************************************************************/

  sensor::AD7151::AD7151_IoI2c      ad7151_io_i2c (AD7151_I2C_ADDR, i2c_master);
  sensor::AD7151::AD7151_Control    ad7151_control(ad7151_io_i2c              );
  sensor::AD7151::AD7151            ad7151        (ad7151_control             );

  /* APPLICATION **********************************************************************/

  uint8_t capacitive_input_range = static_cast<uint8_t>(sensor::AD7151::interface::CapacitiveInputRange::RANGE_1_0_pF);

  ad7151.open();

  ad7151.ioctl(sensor::AD7151::IOCTL_SET_CAPACITIVE_INPUT_RANGE, static_cast<void *>(&capacitive_input_range));

  for(;;)
  {
    uint16_t capacity_raw = 0;

    ad7151.read(reinterpret_cast<uint8_t *>(&capacity_raw), sizeof(capacity_raw));

    char msg[16];
    sprintf(msg, "Capacity / RAW = %04X\n", capacity_raw);

    delay.delay_ms(LOOP_DELAY_ms);
  }

  ad7151.close();

  return 0;
}
