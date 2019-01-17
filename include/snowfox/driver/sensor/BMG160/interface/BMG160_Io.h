/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_IO_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMG160
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  /* Chip ID */
  CHIP_ID                 = 0x00,  /* Contains the chip identification code */
  /* Data Register */
  RATE_X_LSB              = 0x02,
  RATE_X_MSB              = 0x03,
  RATE_Y_LSB              = 0x04,
  RATE_Y_MSB              = 0x05,
  RATE_Z_LSB              = 0x06,
  RATE_Z_MSB              = 0x07,
  TEMP                    = 0x08,
  /* Status Register */
  INT_STATUS_0            = 0x09,  /* Contains interrupt status bits */
  INT_STATUS_1            = 0x0A,  /* Contains interrupt status bits */
  INT_STATUS_2            = 0x0B,  /* Contains any motion interrupt status bits */
  INT_STATUS_3            = 0x0C,  /* Contains high rate interrupt status bits */
  FIFO_STATUS             = 0x0E,  /* Contains FIFO status flags */
  /* Control Register */
  RANGE                   = 0x0F,  /* enables to select FSR */
  BW                      = 0x10,  /* enables to select ODR */
  LPM1                    = 0x11,  /* Selection of the main power modes */
  LPM2                    = 0x12,  /* Configuration settings for fast power-up and external trigger */
  RATE_HBW                = 0x13,  /* Angular rate data acquisition and data output format */
  BGW_SOFTRESET           = 0x14,  /* Controls user triggered reset of the sensor */
  /* Interrupt Status Register */
  INT_EN_0                = 0x15,  /* Controls which interrupts are enabled */
  INT_EN_1                = 0x16,  /* Contains interrupt pin configuration */
  INT_MAP_0               = 0x17,  /* Controls which interrupt signals are mapped to the INT1 pin */
  INT_MAP_1               = 0x18,  /* Controls which interrupt signals are mapped to the INT1 pin and INT2 pin */
  INT_MAP_2               = 0x19,  /* Controls which interrupt signals are mapped to the INT2 pin */
  INT_ZERO                = 0x1A,  /* Contains the data source definition of those interrupts with selectable data source */
  INT_ONE                 = 0x1B,  /* Contains the data source definition of fast offset compensation and the any motion threshold */
  INT_TWO                 = 0x1C,  /* Contains the any motion configuration for x-, y- and z-axis */
  INT_FOUR                = 0x1E,
  INT_RST_LATCH           = 0x21,  /* Contains the interrupt reset bit and the interrupt mode selection */
  /* Interrupt High Rate Configuration Register */
  HIGH_TH_X               = 0x22,  /* Contains the high rate threshold and high rate hysteresis setting for the x-axis */
  HIGH_DUR_X              = 0x23,  /* Contains high rate duration setting for the x-axis */
  HIGH_TH_Y               = 0x24,  /* Contains the high rate threshold and high rate hysteresis setting for the y-axis */
  HIGH_DUR_Y              = 0x25,  /* Contains high rate duration setting for the y-axis */
  HIGH_TH_Z               = 0x26,  /* Contains the high rate threshold and high rate hysteresis setting for the z-axis */
  HIGH_DUR_Z              = 0x27,  /* Contains high rate duration setting for the z-axis */
  /* Offset Register */
  SOC                     = 0x31,  /* Contains the slow offset cancellation setting */
  FOC                     = 0x32,  /* Contains the fast offset cancellation setting */
  /* NVM Control Register */
  TRIM_NVM_CTRL           = 0x33,  /* Contains the control settings for the few-time programmable non-volatile memory (NVM) */
  /* Digital Interface Register */
  BGW_SPI3_WDT            = 0x34,  /* Contains settings for the digital interfaces */
  /* Offset Configuration Register */
  OFC1                    = 0x36,  /* Contains offset compensation values */
  OFC2                    = 0x37,  /* Contains offset compensation values for X-channel */
  OFC3                    = 0x38,  /* Contains offset compensation values for Y-channel */
  OFC4                    = 0x39,  /* Contains offset compensation values for Z-channel */
  TRIM_GP0                = 0x3A,  /* Contains general purpose data register with NVM back-up */
  TRIM_GP1                = 0x3B,  /* Contains general purpose data register with NVM back-up */
  /* Self-test Register */
  BIST                    = 0x3C,  /* Contains Built in Self-Test possibilities */
  /* FIFO Register */
  FIFO_CONFIG_0           = 0x3D,  /* Contains the FIFO watermark level */
  FIFO_CONFIG_1           = 0x3E,  /* Contains FIFO configuration settings. The FIFO buffer memory is cleared and the FIFO-full flag cleared when writing to FIFO_CONFIG_1 register */
  FIFO_DATA               = 0x3F  /* FIFO data readout register */
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMG160_Io
{

public:

           BMG160_Io() { }
  virtual ~BMG160_Io() { }


  virtual bool readRegister (Register const reg, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool readRegister (Register const reg, uint8_t       * data                          ) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const * data, uint16_t const num_bytes) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const   data                          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* BMG160 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_IO_INTERFACE_H_ */
