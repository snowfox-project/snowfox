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
 * INCLUDE
 **************************************************************************************/

#include <stdio.h>

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/Delay.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA328P/I2cMaster.h>

#include <spectre/driver/sensor/LIS3DSH/LIS3DSH.h>
#include <spectre/driver/sensor/LIS3DSH/LIS3DSH_IoI2c.h>
#include <spectre/driver/sensor/LIS3DSH/LIS3DSH_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t  const LIS3DSH_I2C_ADDR  = (0x1D << 1); /* SEL/SDO pulled up to VCC */
static uint32_t const LOOP_DELAY_ms     = 1000; /* 1 s */

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /************************************************************************************
   * HAL
   ************************************************************************************/

  ATMEGA328P::Delay               delay;

  ATMEGA328P::InterruptController int_ctrl    (&EIMSK, &PCICR, &WDTCSR, &TIMSK0, &TIMSK1, &TIMSK2, &UCSR0B, &SPCR, &TWCR, &EECR, &SPMCSR, &ACSR, &ADCSRA);
  ATMEGA328P::CriticalSection     crit_sec    (&SREG);

  blox::ATMEGA328P::I2cMaster     i2c_master  (&TWCR,
                                               &TWDR,
                                               &TWSR,
                                               &TWBR,
                                               crit_sec,
                                               int_ctrl,
                                               hal::interface::I2cClock::F_100_kHz);

  /* GLOBAL INTERRUPT *****************************************************************/
  int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::GLOBAL));


  /************************************************************************************
   * DRIVER
   ************************************************************************************/

  /* LIS3DSH **************************************************************************/
  sensor::LIS3DSH::LIS3DSH_IoI2c      lis3dsh_io_i2c (LIS3DSH_I2C_ADDR, i2c_master());
  sensor::LIS3DSH::LIS3DSH_Control    lis3dsh_control(lis3dsh_io_i2c                );
  sensor::LIS3DSH::LIS3DSH            lis3dsh        (lis3dsh_control               );

  uint8_t output_data_rate = static_cast<uint8_t>(sensor::LIS3DSH::interface::OutputDataRate::ODR_25_Hz);
  uint8_t full_scale_range = static_cast<uint8_t>(sensor::LIS3DSH::interface::FullScaleRange::FS_plus_minus_2g);
  uint8_t filter_bandwidth = static_cast<uint8_t>(sensor::LIS3DSH::interface::FilterBandwidth::BW_50_Hz);

  lis3dsh.open();

  lis3dsh.ioctl(sensor::LIS3DSH::IOCTL_SET_OUTPUT_DATA_RATE, static_cast<void *>(&output_data_rate));
  lis3dsh.ioctl(sensor::LIS3DSH::IOCTL_SET_FULL_SCALE_RANGE, static_cast<void *>(&full_scale_range));
  lis3dsh.ioctl(sensor::LIS3DSH::IOCTL_SET_FILTER_BANDWIDTH, static_cast<void *>(&filter_bandwidth));
  lis3dsh.ioctl(sensor::LIS3DSH::IOCTL_ENABLE_XYZ,           0                                     );


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  for(;;)
  {
    /* TODO Read from sensor and write to serial debug interface */
    delay.delay_ms(LOOP_DELAY_ms);
  }

  lis3dsh.close();

  return 0;
}
