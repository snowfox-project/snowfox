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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace BMG160
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  /* Chip ID */
  REG_CHIP_ID                 = 0x00,  /* Contains the chip identification code */
  /* Data Register */
  REG_RATE_X_LSB              = 0x02,
  REG_RATE_X_MSB              = 0x03,
  REG_RATE_Y_LSB              = 0x04,
  REG_RATE_Y_MSB              = 0x05,
  REG_RATE_Z_LSB              = 0x06,
  REG_RATE_Z_MSB              = 0x07,
  REG_TEMP                    = 0x08,
  /* Status Register */
  REG_INT_STATUS_0            = 0x09,  /* Contains interrupt status bits */
  REG_INT_STATUS_1            = 0x0A,  /* Contains interrupt status bits */
  REG_INT_STATUS_2            = 0x0B,  /* Contains any motion interrupt status bits */
  REG_INT_STATUS_3            = 0x0C,  /* Contains high rate interrupt status bits */
  REG_FIFO_STATUS             = 0x0E,  /* Contains FIFO status flags */
  /* Control Register */
  REG_RANGE                   = 0x0F,  /* enables to select FSR */
  REG_BW                      = 0x10,  /* enables to select ODR */
  REG_LPM1                    = 0x11,  /* Selection of the main power modes */
  REG_LPM2                    = 0x12,  /* Configuration settings for fast power-up and external trigger */
  REG_RATE_HBW                = 0x13,  /* Angular rate data acquisition and data output format */
  REG_BGW_SOFTRESET           = 0x14,  /* Controls user triggered reset of the sensor */
  /* Interrupt Status Register */
  REG_INT_EN_0                = 0x15,  /* Controls which interrupts are enabled */
  REG_INT_EN_1                = 0x16,  /* Contains interrupt pin configuration */
  REG_INT_MAP_0               = 0x17,  /* Controls which interrupt signals are mapped to the INT1 pin */
  REG_INT_MAP_1               = 0x18,  /* Controls which interrupt signals are mapped to the INT1 pin and INT2 pin */
  REG_INT_MAP_2               = 0x19,  /* Controls which interrupt signals are mapped to the INT2 pin */
  REG_INT_ZERO                = 0x1A,  /* Contains the data source definition of those interrupts with selectable data source */
  REG_INT_ONE                 = 0x1B,  /* Contains the data source definition of fast offset compensation and the any motion threshold */
  REG_INT_TWO                 = 0x1C,  /* Contains the any motion configuration for x-, y- and z-axis */
  REG_INT_FOUR                = 0x1E,
  REG_INT_RST_LATCH           = 0x21,  /* Contains the interrupt reset bit and the interrupt mode selection */
  /* Interrupt High Rate Configuration Register */
  REG_HIGH_TH_X               = 0x22,  /* Contains the high rate threshold and high rate hysteresis setting for the x-axis */
  REG_HIGH_DUR_X              = 0x23,  /* Contains high rate duration setting for the x-axis */
  REG_HIGH_TH_Y               = 0x24,  /* Contains the high rate threshold and high rate hysteresis setting for the y-axis */
  REG_HIGH_DUR_Y              = 0x25,  /* Contains high rate duration setting for the y-axis */
  REG_HIGH_TH_Z               = 0x26,  /* Contains the high rate threshold and high rate hysteresis setting for the z-axis */
  REG_HIGH_DUR_Z              = 0x27,  /* Contains high rate duration setting for the z-axis */
  /* Offset Register */
  REG_SOC                     = 0x31,  /* Contains the slow offset cancellation setting */
  REG_FOC                     = 0x32,  /* Contains the fast offset cancellation setting */
  /* NVM Control Register */
  REG_TRIM_NVM_CTRL           = 0x33,  /* Contains the control settings for the few-time programmable non-volatile memory (NVM) */
  /* Digital Interface Register */
  REG_BGW_SPI3_WDT            = 0x34,  /* Contains settings for the digital interfaces */
  /* Offset Configuration Register */
  REG_OFC1                    = 0x36,  /* Contains offset compensation values */
  REG_OFC2                    = 0x37,  /* Contains offset compensation values for X-channel */
  REG_OFC3                    = 0x38,  /* Contains offset compensation values for Y-channel */
  REG_OFC4                    = 0x39,  /* Contains offset compensation values for Z-channel */
  REG_TRIM_GP0                = 0x3A,  /* Contains general purpose data register with NVM back-up */
  REG_TRIM_GP1                = 0x3B,  /* Contains general purpose data register with NVM back-up */
  /* Self-test Register */
  REG_BIST                    = 0x3C,  /* Contains Built in Self-Test possibilities */
  /* FIFO Register */
  REG_FIFO_CONFIG_0           = 0x3D,  /* Contains the FIFO watermark level */
  REG_FIFO_CONFIG_1           = 0x3E,  /* Contains FIFO configuration settings. The FIFO buffer memory is cleared and the FIFO-full flag cleared when writing to FIFO_CONFIG_1 register */
  REG_FIFO_DATA               = 0x3F  /* FIFO data readout register */
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMG160_IO_Interface
{

public:

           BMG160_IO_Interface() { }
  virtual ~BMG160_IO_Interface() { }


  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const * data, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMG160 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_IO_INTERFACE_H_ */
