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

#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA328P/I2cMaster.h>

#include <spectre/driver/ioexpander/PCA9547/PCA9547.h>
#include <spectre/driver/ioexpander/PCA9547/PCA9547_IoI2c.h>
#include <spectre/driver/ioexpander/PCA9547/PCA9547_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t const PCA9547_I2C_ADDR = (0x70 << 1);

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /************************************************************************************
   * HAL
   ************************************************************************************/

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

  /* PCA9547 **************************************************************************/
  ioexpander::PCA9547::PCA9547_IoI2c    pca9547_io_i2c(PCA9547_I2C_ADDR, i2c_master());
  ioexpander::PCA9547::PCA9547_Control  pca9547_ctrl  (pca9547_io_i2c                );
  ioexpander::PCA9547::PCA9547          pca9547       (pca9547_ctrl                  );


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  uint8_t i2c_channel_set = static_cast<uint8_t>(ioexpander::PCA9547::interface::I2cChannel::CH_0      );
  uint8_t i2c_channel_get = static_cast<uint8_t>(ioexpander::PCA9547::interface::I2cChannel::NO_CHANNEL);

  pca9547.open ();
  pca9547.ioctl(ioexpander::PCA9547::IOCTL_SET_CHANNEL, static_cast<void *>(&i2c_channel_set));
  pca9547.ioctl(ioexpander::PCA9547::IOCTL_GET_CHANNEL, static_cast<void *>(&i2c_channel_get));
  pca9547.close();

  for(;;)
  {
  }

  return 0;
}
