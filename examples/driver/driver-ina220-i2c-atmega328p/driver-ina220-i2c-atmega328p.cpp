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

#include <spectre/driver/sensor/INA220/INA220.h>
#include <spectre/driver/sensor/INA220/INA220_IoI2c.h>
#include <spectre/driver/sensor/INA220/INA220_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t  const INA220_I2C_ADDR  = (0x5A << 1);
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

  sensor::INA220::INA220_IoI2c      ina220_io_i2c (INA220_I2C_ADDR, i2c_master);
  sensor::INA220::INA220_Control    ina220_control(ina220_io_i2c              );
  sensor::INA220::INA220            ina220        (ina220_control             );

  /* APPLICATION **********************************************************************/

  uint8_t bus_voltage           = static_cast<uint8_t>(sensor::INA220::interface::V_BUS_RANGE_16V                );
  uint8_t shunt_pga_gain        = static_cast<uint8_t>(sensor::INA220::interface::GAIN_0_5_RANGE_plus_minus_80_mV);
  uint8_t bus_adc_resolution    = static_cast<uint8_t>(sensor::INA220::interface::RES_BUS_12_Bit                 );
  uint8_t shunt_adc_resolution  = static_cast<uint8_t>(sensor::INA220::interface::RES_SHUNT_12_Bit               );
  uint8_t operating_mode        = static_cast<uint8_t>(sensor::INA220::interface::OM_V_SHUNT_and_BUS_continous   );

  ina220.open();

  ina220.ioctl(sensor::INA220::IOCTL_SET_BUS_VOLTAGE_RANGE,     static_cast<void *>(&bus_voltage         ));
  ina220.ioctl(sensor::INA220::IOCTL_SET_SHUNT_PGA_GAIN,        static_cast<void *>(&shunt_pga_gain      ));
  ina220.ioctl(sensor::INA220::IOCTL_SET_BUS_ADC_RESOLUTION,    static_cast<void *>(&bus_adc_resolution  ));
  ina220.ioctl(sensor::INA220::IOCTL_SET_SHUNT_ADC_RESOLUTION,  static_cast<void *>(&shunt_adc_resolution));
  ina220.ioctl(sensor::INA220::IOCTL_SET_OPERATING_MODE,        static_cast<void *>(&operating_mode      ));

  for(;;)
  {
    int16_t shunt_voltage  = 0,
            bus_voltage    = 0;
    int16_t ina220_data[2] = {0};

    ina220.read(reinterpret_cast<uint8_t *>(&ina220_data[0]), 4);

    shunt_voltage = ina220_data[0];
    bus_voltage   = ina220_data[1];

    char msg[16];
    sprintf(msg, "V_SHUNT / RAW = %04X\n", shunt_voltage);
    sprintf(msg, "V_BUS   / RAW = %04X\n", bus_voltage  );

    delay.delay_ms(LOOP_DELAY_ms);
  }

  ina220.close();

  return 0;
}
