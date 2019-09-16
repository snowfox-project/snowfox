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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/AD7151/AD7151_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace AD7151
{

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
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void AD7151_Debug::debug_dumpAllRegs(trace::Trace & trace, hal::interface::Flash & flash, interface::AD7151_Io & io)
{
  debug_dumpSingleReg(trace, flash, io, STATUS                    , interface::Register::STATUS                    );
  debug_dumpSingleReg(trace, flash, io, DATA_HIGH                 , interface::Register::DATA_HIGH                 );
  debug_dumpSingleReg(trace, flash, io, DATA_LOW                  , interface::Register::DATA_LOW                  );
  debug_dumpSingleReg(trace, flash, io, AVERAGE_HIGH              , interface::Register::AVERAGE_HIGH              );
  debug_dumpSingleReg(trace, flash, io, AVERAGE_LOW               , interface::Register::AVERAGE_LOW               );
  debug_dumpSingleReg(trace, flash, io, SENSITIVITY_THRESHOLD_HIGH, interface::Register::SENSITIVITY_THRESHOLD_HIGH);
  debug_dumpSingleReg(trace, flash, io, SENSITIVITY_THRESHOLD_LOW , interface::Register::SENSITIVITY_THRESHOLD_LOW );
  debug_dumpSingleReg(trace, flash, io, SETUP                     , interface::Register::SETUP                     );
  debug_dumpSingleReg(trace, flash, io, CONFIGURATION             , interface::Register::CONFIGURATION             );
  debug_dumpSingleReg(trace, flash, io, POWER_DOWN_TIMER          , interface::Register::POWER_DOWN_TIMER          );
  debug_dumpSingleReg(trace, flash, io, SERIAL_NUMBER_3           , interface::Register::SERIAL_NUMBER_3           );
  debug_dumpSingleReg(trace, flash, io, SERIAL_NUMBER_2           , interface::Register::SERIAL_NUMBER_2           );
  debug_dumpSingleReg(trace, flash, io, SERIAL_NUMBER_1           , interface::Register::SERIAL_NUMBER_1           );
  debug_dumpSingleReg(trace, flash, io, SERIAL_NUMBER_0           , interface::Register::SERIAL_NUMBER_0           );
  debug_dumpSingleReg(trace, flash, io, CHIP_ID                   , interface::Register::CHIP_ID                   );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void AD7151_Debug::debug_dumpSingleReg(trace::Trace & trace, hal::interface::Flash & flash, interface::AD7151_Io & io, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  io.readRegister(reg, &reg_content);

  trace.println(trace::Level::Debug, "%s%02X", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* snowfox */
