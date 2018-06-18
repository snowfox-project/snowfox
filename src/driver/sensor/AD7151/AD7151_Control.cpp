/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/driver/sensor/AD7151/AD7151_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace AD7151
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* AD7151_STATUS_REG Bit Definitions **************************************************/
#define AD7151_SETUP_REG_nDRDY_bm                 (1<<0)

/* AD7151_CONFIG_REG Bit Definitions **************************************************/
#define AD7151_CONFIG_REG_THRESHOLD_FIXED_bm      (1<<7)
#define AD7151_CONFIG_REG_THRESHOLD_MODE_1_bm     (1<<6)
#define AD7151_CONFIG_REG_THRESHOLD_MODE_2_bm     (1<<5)
#define AD7151_CONFIG_REG_ENABLE_CONVERSION_bm    (1<<4)
#define AD7151_CONFIG_REG_MODE_2_bm               (1<<2)
#define AD7151_CONFIG_REG_MODE_1_bm               (1<<1)
#define AD7151_CONFIG_REG_MODE_0_bm               (1<<0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AD7151_Control::AD7151_Control(interface::AD7151_Io & io)
: _io(io)
{

}

AD7151_Control::~AD7151_Control()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool AD7151_Control::setCapacitiveInputRange(interface::CapacitiveInputRange const capacitive_input_range)
{
  uint8_t setup_reg_content = 0;

  if(!_io.readRegister(interface::Register::SETUP, &setup_reg_content)) return false;

  setup_reg_content &= ~(AD7151_SETUP_REG_RNG_H_bm | AD7151_SETUP_REG_RNG_L_bm);
  setup_reg_content |= static_cast<uint8_t>(capacitive_input_range);

  if(!_io.writeRegister(interface::Register::SETUP, setup_reg_content)) return false;

  return true;
}

bool AD7151_Control::startSingleConversion()
{
  uint8_t configuration_reg_content = 0;

  if(!_io.readRegister(interface::Register::CONFIGURATION, &configuration_reg_content)) return false;

  configuration_reg_content &= ~(AD7151_CONFIG_REG_ENABLE_CONVERSION_bm | AD7151_CONFIG_REG_MODE_2_bm | AD7151_CONFIG_REG_MODE_1_bm | AD7151_CONFIG_REG_MODE_0_bm);
  configuration_reg_content |= (AD7151_CONFIG_REG_ENABLE_CONVERSION_bm | AD7151_CONFIG_REG_MODE_1_bm);

  if(!_io.writeRegister(interface::Register::CONFIGURATION, configuration_reg_content)) return false;

  return true;
}

bool AD7151_Control::checkIfConversionIsComplete(bool * is_conversion_complete)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_conversion_complete = (status_reg_content & AD7151_SETUP_REG_nDRDY_bm) == 0;

  return true;
}

bool AD7151_Control::readConversionResult(uint16_t * raw_data)
{
  uint8_t data_regs_content[2] = {0};

  if(!_io.readRegister(interface::Register::DATA_HIGH, data_regs_content, 2)) return false;

  *raw_data = (static_cast<uint16_t>(data_regs_content[0]) << 8) + static_cast<uint16_t>(data_regs_content[1]);

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */
