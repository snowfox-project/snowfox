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
#include <spectre/hal/avr/ATxxxx/i2c/I2CMasterBase.h>

#include <spectre/driver/sensor/LIS3MDL/LIS3MDL.h>
#include <spectre/driver/sensor/LIS3MDL/LIS3MDL_IoI2c.h>
#include <spectre/driver/sensor/LIS3MDL/LIS3MDL_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t  const LIS3MDL_I2C_ADDR  = (0x1C << 1); /* SA1 pulled down to GND */
static uint32_t const LOOP_DELAY_ms     = 1000; /* 1 s */

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

  sensor::LIS3MDL::LIS3MDL_IoI2c      lis3mdl_io_i2c (LIS3MDL_I2C_ADDR, i2c_master);
  sensor::LIS3MDL::LIS3MDL_Control    lis3mdl_control(lis3mdl_io_i2c              );
  sensor::LIS3MDL::LIS3MDL            lis3mdl        (lis3mdl_control             );

  /* APPLICATION **********************************************************************/

  uint8_t operation_mode_xy = static_cast<uint8_t>(sensor::LIS3MDL::interface::OperationMode_XY::UHP                );
  uint8_t operation_mode_z  = static_cast<uint8_t>(sensor::LIS3MDL::interface::OperationMode_Z::UHP                 );
  uint8_t output_data_rate  = static_cast<uint8_t>(sensor::LIS3MDL::interface::OutputDataRate::ODR_10_Hz            );
  uint8_t full_scale_range  = static_cast<uint8_t>(sensor::LIS3MDL::interface::FullScaleRange::FS_plus_minus_4_Gauss);
  uint8_t conversion_mode   = static_cast<uint8_t>(sensor::LIS3MDL::interface::ConversionMode::CONTINOUS            );

  lis3mdl.open();

  lis3mdl.ioctl(sensor::LIS3MDL::IOCTL_SET_OPERATION_MODE_XY, static_cast<void *>(&operation_mode_xy));
  lis3mdl.ioctl(sensor::LIS3MDL::IOCTL_SET_OPERATION_MODE_Z,  static_cast<void *>(&operation_mode_z ));
  lis3mdl.ioctl(sensor::LIS3MDL::IOCTL_SET_OUTPUT_DATA_RATE,  static_cast<void *>(&output_data_rate ));
  lis3mdl.ioctl(sensor::LIS3MDL::IOCTL_SET_FULL_SCALE_RANGE,  static_cast<void *>(&full_scale_range ));
  lis3mdl.ioctl(sensor::LIS3MDL::IOCTL_SET_CONVERSION_MODE,   static_cast<void *>(&conversion_mode  ));

  for(;;)
  {
    /* TODO Read from sensor and write to serial debug interface */

    delay.delay_ms(LOOP_DELAY_ms);
  }

  lis3mdl.close();

  return 0;
}
