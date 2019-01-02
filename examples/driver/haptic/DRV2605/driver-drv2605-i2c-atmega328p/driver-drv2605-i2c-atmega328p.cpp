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

#include <spectre/driver/haptic/DRV2605/DRV2605_IoI2C.h>

#include <spectre/blox/driver/haptic/DRV2605.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t  const DRV2605_I2C_ADDR = (0x5A << 1);
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

  /* DRV2605 **************************************************************************/

  haptic::DRV2605::DRV2605_IoI2C drv2605_io_i2c(DRV2605_I2C_ADDR, i2c_master());

  blox::DRV2605                  drv2605       (delay,
                                                drv2605_io_i2c,
                                                haptic::DRV2605::interface::Mode::INTERNAL_TRIGGER,
                                                haptic::DRV2605::interface::Actuator::LRA,
                                                haptic::DRV2605::interface::WaveformLibrary::LRA);


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  uint8_t  const DRV2605_MIN_LRA_LIB_WAVEFORM_NUM = 1;
  uint8_t  const DRV2605_MAX_LRA_LIB_WAVEFORM_NUM = 127;

  for(uint8_t w = DRV2605_MIN_LRA_LIB_WAVEFORM_NUM; ; w++)
  {
    haptic::DRV2605::IoctlSetWaveFormArg set_waveform_arg(haptic::DRV2605::interface::WaveformSequencer::SEQ_1, w);

    drv2605().ioctl(haptic::DRV2605::IOCTL_SET_WAVEFORM, static_cast<void *>(&set_waveform_arg));
    drv2605().ioctl(haptic::DRV2605::IOCTL_SET_GO,       0                                     );

    if(w == DRV2605_MAX_LRA_LIB_WAVEFORM_NUM) w = DRV2605_MIN_LRA_LIB_WAVEFORM_NUM;

    delay.delay_ms(LOOP_DELAY_ms);
  }

  return 0;
}
