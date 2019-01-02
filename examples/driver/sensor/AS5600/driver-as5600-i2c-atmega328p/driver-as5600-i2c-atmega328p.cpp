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

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/Delay.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA328P/I2cMaster.h>

#include <spectre/driver/sensor/AS5600/AS5600.h>
#include <spectre/driver/sensor/AS5600/AS5600_IoI2c.h>
#include <spectre/driver/sensor/AS5600/AS5600_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t  const AS5600_I2C_ADDR  = (0x36 << 1);
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

  /* AS5600 ***************************************************************************/
  sensor::AS5600::AS5600_IoI2c      as5600_io_i2c (AS5600_I2C_ADDR, i2c_master());
  sensor::AS5600::AS5600_Control    as5600_control(as5600_io_i2c                );
  sensor::AS5600::AS5600            as5600        (as5600_control               );


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  uint8_t power_mode            = static_cast<uint8_t>(sensor::AS5600::interface::PowerMode::NORMAL                    );
  uint8_t hysteresis            = static_cast<uint8_t>(sensor::AS5600::interface::Hysteresis::HYST_OFF                 );
  uint8_t output_stage          = static_cast<uint8_t>(sensor::AS5600::interface::OutputStage::REDUCED_ANALOG          );
  uint8_t pwm_frequency         = static_cast<uint8_t>(sensor::AS5600::interface::PwmFrequency::F_115_Hz               );
  uint8_t slow_filter           = static_cast<uint8_t>(sensor::AS5600::interface::SlowFilter::SF_4x                    );
  uint8_t fast_filter_threshold = static_cast<uint8_t>(sensor::AS5600::interface::FastFilterThreshold::ONLY_SLOW_FILTER);

  as5600.open();

  as5600.ioctl(sensor::AS5600::IOCTL_SET_POWER_MODE,            static_cast<void *>(&power_mode           ));
  as5600.ioctl(sensor::AS5600::IOCTL_SET_HYSTERESIS,            static_cast<void *>(&hysteresis           ));
  as5600.ioctl(sensor::AS5600::IOCTL_SET_OUTPUT_STAGE,          static_cast<void *>(&output_stage         ));
  as5600.ioctl(sensor::AS5600::IOCTL_SET_PWM_FREQUENCY,         static_cast<void *>(&pwm_frequency        ));
  as5600.ioctl(sensor::AS5600::IOCTL_SET_SLOW_FILTER,           static_cast<void *>(&slow_filter          ));
  as5600.ioctl(sensor::AS5600::IOCTL_SET_FAST_FILTER_THRESHOLD, static_cast<void *>(&fast_filter_threshold));
  as5600.ioctl(sensor::AS5600::IOCTL_DISABLE_WATCHDOG,          0                                          );

  for(;;)
  {
    /* TODO Read from sensor and write to serial debug interface */
    delay.delay_ms(LOOP_DELAY_ms);
  }

  as5600.close();

  return 0;
}
