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
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/sensor/AD7151.h>

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
 * CTOR/DTOR
 **************************************************************************************/

AD7151::AD7151(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master )
{

}

AD7151::~AD7151()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool AD7151::setCapacitiveInputRange(CapacitiveInputRangeSelect const sel)
{
  uint8_t setup_reg_content = 0;

  if(!readSingleRegister(REG_SETUP, &setup_reg_content)) return false;

  setup_reg_content &= ~(AD7151_SETUP_REG_RNG_H_bm | AD7151_SETUP_REG_RNG_L_bm);
  setup_reg_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_SETUP, setup_reg_content)) return false;

  return true;
}

bool AD7151::startSingleConversion()
{
  uint8_t configuration_reg_content = 0;

  if(!readSingleRegister(REG_CONFIGURATION, &configuration_reg_content)) return false;

  configuration_reg_content &= ~(AD7151_CONFIG_REG_ENABLE_CONVERSION_bm | AD7151_CONFIG_REG_MODE_2_bm | AD7151_CONFIG_REG_MODE_1_bm | AD7151_CONFIG_REG_MODE_0_bm);
  configuration_reg_content |= (AD7151_CONFIG_REG_ENABLE_CONVERSION_bm | AD7151_CONFIG_REG_MODE_1_bm);

  if(!writeSingleRegister(REG_CONFIGURATION, configuration_reg_content)) return false;

  return true;
}

bool AD7151::checkIfConversionIsComplete(bool *is_conversion_complete)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_conversion_complete = (status_reg_content & AD7151_SETUP_REG_nDRDY_bm) == 0;

  return true;
}

bool AD7151::readConversionResult(uint16_t * raw_data)
{
  uint8_t data_regs_content[2] = {0};

  if(!readMultipleRegister(REG_DATA_HIGH, data_regs_content, 2)) return false;

  *raw_data = (static_cast<uint16_t>(data_regs_content[0]) << 8) + static_cast<uint16_t>(data_regs_content[1]);

  return true;
}

void AD7151::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_STATUS                     = ", REG_STATUS                    );
  debug_dumpSingleReg(debug_interface, "REG_DATA_HIGH                  = ", REG_DATA_HIGH                 );
  debug_dumpSingleReg(debug_interface, "REG_DATA_LOW                   = ", REG_DATA_LOW                  );
  debug_dumpSingleReg(debug_interface, "REG_AVERAGE_HIGH               = ", REG_AVERAGE_HIGH              );
  debug_dumpSingleReg(debug_interface, "REG_AVERAGE_LOW                = ", REG_AVERAGE_LOW               );
  debug_dumpSingleReg(debug_interface, "REG_SENSITIVITY_THRESHOLD_HIGH = ", REG_SENSITIVITY_THRESHOLD_HIGH);
  debug_dumpSingleReg(debug_interface, "REG_SENSITIVITY_THRESHOLD_LOW  = ", REG_SENSITIVITY_THRESHOLD_LOW );
  debug_dumpSingleReg(debug_interface, "REG_SETUP                      = ", REG_SETUP                     );
  debug_dumpSingleReg(debug_interface, "REG_CONFIGURATION              = ", REG_CONFIGURATION             );
  debug_dumpSingleReg(debug_interface, "REG_POWER_DOWN_TIMER           = ", REG_POWER_DOWN_TIMER          );
  debug_dumpSingleReg(debug_interface, "REG_SERIAL_NUMBER_3            = ", REG_SERIAL_NUMBER_3           );
  debug_dumpSingleReg(debug_interface, "REG_SERIAL_NUMBER_2            = ", REG_SERIAL_NUMBER_2           );
  debug_dumpSingleReg(debug_interface, "REG_SERIAL_NUMBER_1            = ", REG_SERIAL_NUMBER_1           );
  debug_dumpSingleReg(debug_interface, "REG_SERIAL_NUMBER_0            = ", REG_SERIAL_NUMBER_0           );
  debug_dumpSingleReg(debug_interface, "REG_CHIP_ID                    = ", REG_CHIP_ID                   );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool AD7151::readSingleRegister(uint8_t const reg_addr, uint8_t * data)
{
  return readMultipleRegister(reg_addr, data, 1);
}

bool AD7151::writeSingleRegister(uint8_t const reg_addr, uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

bool AD7151::readMultipleRegister(uint8_t const reg_addr, uint8_t * data, uint16_t const num_bytes)
{
  if(!_i2c_master.begin      (_i2c_address, false          )) return false;
  if(!_i2c_master.write      (reg_addr                     )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, num_bytes)) return false;

  return true;
}

void AD7151::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */
