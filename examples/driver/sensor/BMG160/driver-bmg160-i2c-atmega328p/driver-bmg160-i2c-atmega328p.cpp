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

#include <spectre/driver/sensor/BMG160/BMG160.h>
#include <spectre/driver/sensor/BMG160/BMG160_IoI2c.h>
#include <spectre/driver/sensor/BMG160/BMG160_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t  const BMG160_I2C_ADDR  = (0x68 << 1);
static uint32_t const LOOP_DELAY_ms    = 1000; /* 1 s */

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

  /* BMG160 ***************************************************************************/
  sensor::BMG160::BMG160_IoI2c   bmg160_io_i2c (BMG160_I2C_ADDR, i2c_master());
  sensor::BMG160::BMG160_Control bmg160_control(bmg160_io_i2c                );
  sensor::BMG160::BMG160         bmg160        (bmg160_control               );


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  uint8_t output_data_rate_and_bandwidth = static_cast<uint8_t>(sensor::BMG160::interface::OutputDataRateAndBandwith::ODR_100_Hz_BandWidth_12_Hz);
  uint8_t full_scale_range               = static_cast<uint8_t>(sensor::BMG160::interface::FullScaleRange::FS_plus_minus_125_DPS                );

  bmg160.open();

  bmg160.ioctl(sensor::BMG160::IOCTL_SET_OUTPUT_DATA_RATE_AND_BANDWIDTH, static_cast<void *>(&output_data_rate_and_bandwidth));
  bmg160.ioctl(sensor::BMG160::IOCTL_SET_FULL_SCALE_RANGE,               static_cast<void *>(&full_scale_range              ));


  for(;;)
  {
    /* TODO Read from sensor and write to serial debug interface */
    delay.delay_ms(LOOP_DELAY_ms);
  }

  bmg160.close();

  return 0;
}
