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

#include <snowfox/driver/sensor/L3GD20/L3GD20_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace L3GD20
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const WHO_AM_I     [] = "WHO_AM_I      = ");
FLASH_DECLARE(static char const CTRL_REG1    [] = "CTRL_REG1     = ");
FLASH_DECLARE(static char const CTRL_REG2    [] = "CTRL_REG2     = ");
FLASH_DECLARE(static char const CTRL_REG3    [] = "CTRL_REG3     = ");
FLASH_DECLARE(static char const CTRL_REG4    [] = "CTRL_REG4     = ");
FLASH_DECLARE(static char const CTRL_REG5    [] = "CTRL_REG5     = ");
FLASH_DECLARE(static char const REFERENCE    [] = "REFERENCE     = ");
FLASH_DECLARE(static char const OUT_TEMP     [] = "OUT_TEMP      = ");
FLASH_DECLARE(static char const STATUS_REG   [] = "STATUS_REG    = ");
FLASH_DECLARE(static char const OUT_X_L      [] = "OUT_X_L       = ");
FLASH_DECLARE(static char const OUT_X_H      [] = "OUT_X_H       = ");
FLASH_DECLARE(static char const OUT_Y_L      [] = "OUT_Y_L       = ");
FLASH_DECLARE(static char const OUT_Y_H      [] = "OUT_Y_H       = ");
FLASH_DECLARE(static char const OUT_Z_L      [] = "OUT_Z_L       = ");
FLASH_DECLARE(static char const OUT_Z_H      [] = "OUT_Z_H       = ");
FLASH_DECLARE(static char const FIFO_CTRL_REG[] = "FIFO_CTRL_REG = ");
FLASH_DECLARE(static char const FIFO_SRC_REG [] = "FIFO_SRC_REG  = ");
FLASH_DECLARE(static char const INT1_CFG     [] = "INT1_CFG      = ");
FLASH_DECLARE(static char const INT1_SRC     [] = "INT1_SRC      = ");
FLASH_DECLARE(static char const TSH_XH       [] = "TSH_XH        = ");
FLASH_DECLARE(static char const TSH_XL       [] = "TSH_XL        = ");
FLASH_DECLARE(static char const TSH_YH       [] = "TSH_YH        = ");
FLASH_DECLARE(static char const TSH_YL       [] = "TSH_YL        = ");
FLASH_DECLARE(static char const TSH_ZH       [] = "TSH_ZH        = ");
FLASH_DECLARE(static char const TSH_ZL       [] = "TSH_ZL        = ");
FLASH_DECLARE(static char const INT1_DURATION[] = "INT1_DURATION = ");

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void L3GD20_Debug::debug_dumpAllRegs(trace::Trace & trace, hal::interface::Flash & flash, interface::L3GD20_Io & io)
{
  debug_dumpSingleReg(trace, flash, io, WHO_AM_I     , interface::Register::WHO_AM_I     );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG1    , interface::Register::CTRL_REG1    );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG2    , interface::Register::CTRL_REG2    );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG3    , interface::Register::CTRL_REG3    );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG4    , interface::Register::CTRL_REG4    );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG5    , interface::Register::CTRL_REG5    );
  debug_dumpSingleReg(trace, flash, io, REFERENCE    , interface::Register::REFERENCE    );
  debug_dumpSingleReg(trace, flash, io, OUT_TEMP     , interface::Register::OUT_TEMP     );
  debug_dumpSingleReg(trace, flash, io, STATUS_REG   , interface::Register::STATUS_REG   );
  debug_dumpSingleReg(trace, flash, io, OUT_X_L      , interface::Register::OUT_X_L      );
  debug_dumpSingleReg(trace, flash, io, OUT_X_H      , interface::Register::OUT_X_H      );
  debug_dumpSingleReg(trace, flash, io, OUT_Y_L      , interface::Register::OUT_Y_L      );
  debug_dumpSingleReg(trace, flash, io, OUT_Y_H      , interface::Register::OUT_Y_H      );
  debug_dumpSingleReg(trace, flash, io, OUT_Z_L      , interface::Register::OUT_Z_L      );
  debug_dumpSingleReg(trace, flash, io, OUT_Z_H      , interface::Register::OUT_Z_H      );
  debug_dumpSingleReg(trace, flash, io, FIFO_CTRL_REG, interface::Register::FIFO_CTRL_REG);
  debug_dumpSingleReg(trace, flash, io, FIFO_SRC_REG , interface::Register::FIFO_SRC_REG );
  debug_dumpSingleReg(trace, flash, io, INT1_CFG     , interface::Register::INT1_CFG     );
  debug_dumpSingleReg(trace, flash, io, INT1_SRC     , interface::Register::INT1_SRC     );
  debug_dumpSingleReg(trace, flash, io, TSH_XH       , interface::Register::TSH_XH       );
  debug_dumpSingleReg(trace, flash, io, TSH_XL       , interface::Register::TSH_XL       );
  debug_dumpSingleReg(trace, flash, io, TSH_YH       , interface::Register::TSH_YH       );
  debug_dumpSingleReg(trace, flash, io, TSH_YL       , interface::Register::TSH_YL       );
  debug_dumpSingleReg(trace, flash, io, TSH_ZH       , interface::Register::TSH_ZH       );
  debug_dumpSingleReg(trace, flash, io, TSH_ZL       , interface::Register::TSH_ZL       );
  debug_dumpSingleReg(trace, flash, io, INT1_DURATION, interface::Register::INT1_DURATION);
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void L3GD20_Debug::debug_dumpSingleReg(trace::Trace & trace, hal::interface::Flash & flash, interface::L3GD20_Io & io, char const * msg, interface::Register const reg)
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

} /* L3GD20 */

} /* sensor */

} /* driver */

} /* snowfox */
