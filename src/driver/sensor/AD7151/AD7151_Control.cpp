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
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const STATUS                    [] = "STATUS                     = ");
FLASH_DECLARE(static char const DATA_HIGH                 [] = "DATA_HIGH                  = ");
FLASH_DECLARE(static char const DATA_LOW                  [] = "DATA_LOW                   = ");
FLASH_DECLARE(static char const AVERAGE_HIGH              [] = "AVERAGE_HIGH               = ");
FLASH_DECLARE(static char const AVERAGE_LOW               [] = "AVERAGE_LOW                = ");
FLASH_DECLARE(static char const SENSITIVITY_THRESHOLD_HIGH[] = "SENSITIVITY_THRESHOLD_HIGH = ");
FLASH_DECLARE(static char const SENSITIVITY_THRESHOLD_LOW [] = "SENSITIVITY_THRESHOLD_LOW  = ");
FLASH_DECLARE(static char const SETUP                     [] = "SETUP                      = ");
FLASH_DECLARE(static char const CONFIGURATION             [] = "CONFIGURATION              = ");
FLASH_DECLARE(static char const POWER_DOWN_TIMER          [] = "POWER_DOWN_TIMER           = ");
FLASH_DECLARE(static char const SERIAL_NUMBER_3           [] = "SERIAL_NUMBER_3            = ");
FLASH_DECLARE(static char const SERIAL_NUMBER_2           [] = "SERIAL_NUMBER_2            = ");
FLASH_DECLARE(static char const SERIAL_NUMBER_1           [] = "SERIAL_NUMBER_1            = ");
FLASH_DECLARE(static char const SERIAL_NUMBER_0           [] = "SERIAL_NUMBER_0            = ");
FLASH_DECLARE(static char const CHIP_ID                   [] = "CHIP_ID                    = ");

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AD7151_Control::AD7151_Control(interface::AD7151_IO_Interface & io)
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

void AD7151_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash)
{
  debug_dumpSingleReg(debug_interface, flash, STATUS                    , interface::Register::STATUS                    );
  debug_dumpSingleReg(debug_interface, flash, DATA_HIGH                 , interface::Register::DATA_HIGH                 );
  debug_dumpSingleReg(debug_interface, flash, DATA_LOW                  , interface::Register::DATA_LOW                  );
  debug_dumpSingleReg(debug_interface, flash, AVERAGE_HIGH              , interface::Register::AVERAGE_HIGH              );
  debug_dumpSingleReg(debug_interface, flash, AVERAGE_LOW               , interface::Register::AVERAGE_LOW               );
  debug_dumpSingleReg(debug_interface, flash, SENSITIVITY_THRESHOLD_HIGH, interface::Register::SENSITIVITY_THRESHOLD_HIGH);
  debug_dumpSingleReg(debug_interface, flash, SENSITIVITY_THRESHOLD_LOW , interface::Register::SENSITIVITY_THRESHOLD_LOW );
  debug_dumpSingleReg(debug_interface, flash, SETUP                     , interface::Register::SETUP                     );
  debug_dumpSingleReg(debug_interface, flash, CONFIGURATION             , interface::Register::CONFIGURATION             );
  debug_dumpSingleReg(debug_interface, flash, POWER_DOWN_TIMER          , interface::Register::POWER_DOWN_TIMER          );
  debug_dumpSingleReg(debug_interface, flash, SERIAL_NUMBER_3           , interface::Register::SERIAL_NUMBER_3           );
  debug_dumpSingleReg(debug_interface, flash, SERIAL_NUMBER_2           , interface::Register::SERIAL_NUMBER_2           );
  debug_dumpSingleReg(debug_interface, flash, SERIAL_NUMBER_1           , interface::Register::SERIAL_NUMBER_1           );
  debug_dumpSingleReg(debug_interface, flash, SERIAL_NUMBER_0           , interface::Register::SERIAL_NUMBER_0           );
  debug_dumpSingleReg(debug_interface, flash, CHIP_ID                   , interface::Register::CHIP_ID                   );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void AD7151_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  _io.readRegister(reg, &reg_content);

  debug_interface.print("%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */
