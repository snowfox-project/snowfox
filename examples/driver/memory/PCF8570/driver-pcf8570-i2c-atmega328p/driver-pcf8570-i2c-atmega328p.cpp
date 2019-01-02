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

#include <spectre/driver/memory/PCF8570/PCF8570.h>
#include <spectre/driver/memory/PCF8570/PCF8570_IoI2c.h>
#include <spectre/driver/memory/PCF8570/PCF8570_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t const PCF8570_I2C_ADDR = (0x50 << 1);

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

  /* PCF8570 **************************************************************************/
  memory::PCF8570::PCF8570_IoI2c    pcf8570_io_i2c(PCF8570_I2C_ADDR, i2c_master());
  memory::PCF8570::PCF8570_Control  pcf8570_ctrl  (pcf8570_io_i2c                );
  memory::PCF8570::PCF8570          pcf8570       (pcf8570_ctrl                  );


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  pcf8570.open();

  for(uint8_t address = 0; address < 0xFF; address += 4)
  {
    uint8_t const buffer_write[5] = {address, 0xBE, 0xEF, 0xCA, 0xFE};
    pcf8570.write(buffer_write, 5);
  }

  for(uint8_t address = 0; address < 0xFF; address += 4)
  {
    uint8_t buffer_read[5] = {address, 0, 0, 0, 0};
    pcf8570.read(buffer_read, 5);
  }

  pcf8570.close();

  for(;;) { }

  return 0;
}
