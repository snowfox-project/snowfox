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

#include <snowfox/driver/sensor/AS5600/AS5600_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace AS5600
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const ZMCO               [] =  "ZMCO                = ");
FLASH_DECLARE(static char const ZPOS_HIGH_BYTE     [] =  "ZPOS_HIGH_BYTE      = ");
FLASH_DECLARE(static char const ZPOS_LOW_BYTE      [] =  "ZPOS_LOW_BYTE       = ");
FLASH_DECLARE(static char const MPOS_HIGH_BYTE     [] =  "MPOS_HIGH_BYTE      = ");
FLASH_DECLARE(static char const MPOS_LOW_BYTE      [] =  "MPOS_LOW_BYTE       = ");
FLASH_DECLARE(static char const MANG_HIGH_BYTE     [] =  "MANG_HIGH_BYTE      = ");
FLASH_DECLARE(static char const MANG_LOW_BYTE      [] =  "MANG_LOW_BYTE       = ");
FLASH_DECLARE(static char const CONF_HIGH_BYTE     [] =  "CONF_HIGH_BYTE      = ");
FLASH_DECLARE(static char const CONF_LOW_BYTE      [] =  "CONF_LOW_BYTE       = ");
FLASH_DECLARE(static char const RAW_ANGLE_HIGH_BYTE[] =  "RAW_ANGLE_HIGH_BYTE = ");
FLASH_DECLARE(static char const RAW_ANGLE_LOW_BYTE [] =  "RAW_ANGLE_LOW_BYTE  = ");
FLASH_DECLARE(static char const ANGLE_HIGH_BYTE    [] =  "ANGLE_HIGH_BYTE     = ");
FLASH_DECLARE(static char const ANGLE_LOW_BYTE     [] =  "ANGLE_LOW_BYTE      = ");
FLASH_DECLARE(static char const AGC                [] =  "AGC                 = ");
FLASH_DECLARE(static char const MAGNITUDE_HIGH_BYTE[] =  "MAGNITUDE_HIGH_BYTE = ");
FLASH_DECLARE(static char const MAGNITUDE_LOW_BYTE [] =  "MAGNITUDE_LOW_BYTE  = ");

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void AS5600_Debug::debug_dumpAllRegs(trace::Trace & trace, hal::interface::Flash & flash, interface::AS5600_Io & io)
{
  debug_dumpSingleReg(trace, flash, io, ZMCO               , interface::Register::ZMCO               );
  debug_dumpSingleReg(trace, flash, io, ZPOS_HIGH_BYTE     , interface::Register::ZPOS_HIGH_BYTE     );
  debug_dumpSingleReg(trace, flash, io, ZPOS_LOW_BYTE      , interface::Register::ZPOS_LOW_BYTE      );
  debug_dumpSingleReg(trace, flash, io, MPOS_HIGH_BYTE     , interface::Register::MPOS_HIGH_BYTE     );
  debug_dumpSingleReg(trace, flash, io, MPOS_LOW_BYTE      , interface::Register::MPOS_LOW_BYTE      );
  debug_dumpSingleReg(trace, flash, io, MANG_HIGH_BYTE     , interface::Register::MANG_HIGH_BYTE     );
  debug_dumpSingleReg(trace, flash, io, MANG_LOW_BYTE      , interface::Register::MANG_LOW_BYTE      );
  debug_dumpSingleReg(trace, flash, io, CONF_HIGH_BYTE     , interface::Register::CONF_HIGH_BYTE     );
  debug_dumpSingleReg(trace, flash, io, CONF_LOW_BYTE      , interface::Register::CONF_LOW_BYTE      );
  debug_dumpSingleReg(trace, flash, io, RAW_ANGLE_HIGH_BYTE, interface::Register::RAW_ANGLE_HIGH_BYTE);
  debug_dumpSingleReg(trace, flash, io, RAW_ANGLE_LOW_BYTE , interface::Register::RAW_ANGLE_LOW_BYTE );
  debug_dumpSingleReg(trace, flash, io, ANGLE_HIGH_BYTE    , interface::Register::ANGLE_HIGH_BYTE    );
  debug_dumpSingleReg(trace, flash, io, ANGLE_LOW_BYTE     , interface::Register::ANGLE_LOW_BYTE     );
  debug_dumpSingleReg(trace, flash, io, AGC                , interface::Register::AGC                );
  debug_dumpSingleReg(trace, flash, io, MAGNITUDE_HIGH_BYTE, interface::Register::MAGNITUDE_HIGH_BYTE);
  debug_dumpSingleReg(trace, flash, io, MAGNITUDE_LOW_BYTE , interface::Register::MAGNITUDE_LOW_BYTE );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void AS5600_Debug::debug_dumpSingleReg(trace::Trace & trace, hal::interface::Flash & flash, interface::AS5600_Io & io, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  io.readRegister(reg, &reg_content);

  trace.print(trace::Level::Debug, "%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* snowfox */
