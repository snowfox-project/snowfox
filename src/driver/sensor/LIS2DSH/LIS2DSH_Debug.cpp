/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/driver/sensor/LIS2DSH/LIS2DSH_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensorLIS2DSH
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const STATUS_REG_AUX [] = "STATUS_REG_AUX  = ");
FLASH_DECLARE(static char const OUT_TEMP_L     [] = "OUT_TEMP_L      = ");
FLASH_DECLARE(static char const OUT_TEMP_H     [] = "OUT_TEMP_H      = ");
FLASH_DECLARE(static char const INT_COUNTER_REG[] = "INT_COUNTER_REG = ");
FLASH_DECLARE(static char const WHO_AM_I       [] = "WHO_AM_I        = ");
FLASH_DECLARE(static char const TEMP_CFG_REG   [] = "TEMP_CFG_REG    = ");
FLASH_DECLARE(static char const CTRL_REG1      [] = "CTRL_REG1       = ");
FLASH_DECLARE(static char const CTRL_REG2      [] = "CTRL_REG2       = ");
FLASH_DECLARE(static char const CTRL_REG3      [] = "CTRL_REG3       = ");
FLASH_DECLARE(static char const CTRL_REG4      [] = "CTRL_REG4       = ");
FLASH_DECLARE(static char const CTRL_REG5      [] = "CTRL_REG5       = ");
FLASH_DECLARE(static char const CTRL_REG6      [] = "CTRL_REG6       = ");
FLASH_DECLARE(static char const STATUS_REG     [] = "STATUS_REG      = ");
FLASH_DECLARE(static char const OUT_X_L        [] = "OUT_X_L         = ");
FLASH_DECLARE(static char const OUT_X_H        [] = "OUT_X_H         = ");
FLASH_DECLARE(static char const OUT_Y_L        [] = "OUT_Y_L         = ");
FLASH_DECLARE(static char const OUT_Y_H        [] = "OUT_Y_H         = ");
FLASH_DECLARE(static char const OUT_Z_L        [] = "OUT_Z_L         = ");
FLASH_DECLARE(static char const OUT_Z_H        [] = "OUT_Z_H         = ");
FLASH_DECLARE(static char const FIFO_CTRL_REG  [] = "FIFO_CTRL_REG   = ");
FLASH_DECLARE(static char const FIFO_SRC_REG   [] = "FIFO_SRC_REG    = ");
FLASH_DECLARE(static char const INT1_CFG       [] = "INT1_CFG        = ");
FLASH_DECLARE(static char const INT1_SOURCE    [] = "INT1_SOURCE     = ");
FLASH_DECLARE(static char const INT1_THS       [] = "INT1_THS        = ");
FLASH_DECLARE(static char const INT1_DURATION  [] = "INT1_DURATION   = ");
FLASH_DECLARE(static char const INT2_CFG       [] = "INT2_CFG        = ");
FLASH_DECLARE(static char const INT2_SOURCE    [] = "INT2_SOURCE     = ");
FLASH_DECLARE(static char const INT2_THS       [] = "INT2_THS        = ");
FLASH_DECLARE(static char const INT2_DURATION  [] = "INT2_DURATION   = ");
FLASH_DECLARE(static char const CLICK_CFG      [] = "CLICK_CFG       = ");
FLASH_DECLARE(static char const CLICK_SRC      [] = "CLICK_SRC       = ");
FLASH_DECLARE(static char const CLICK_THS      [] = "CLICK_THS       = ");
FLASH_DECLARE(static char const TIME_LIMIT     [] = "TIME_LIMIT      = ");
FLASH_DECLARE(static char const TIME_LATENCY   [] = "TIME_LATENCY    = ");
FLASH_DECLARE(static char const TIME_WINDOW    [] = "TIME_WINDOW     = ");
FLASH_DECLARE(static char const ACT_THS        [] = "ACT_THS         = ");
FLASH_DECLARE(static char const ACT_DUR        [] = "ACT_DUR         = ");

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void LIS2DSH_Debug::debug_dumpAllRegs(trace::Trace & trace, hal::interface::Flash & flash, interface::LIS2DSH_Io & io)
{
  debug_dumpSingleReg(trace, flash, io, STATUS_REG_AUX , interface::Register::STATUS_REG_AUX );

  debug_dumpSingleReg(trace, flash, io, OUT_TEMP_L     , interface::Register::OUT_TEMP_L     );
  debug_dumpSingleReg(trace, flash, io, OUT_TEMP_H     , interface::Register::OUT_TEMP_H     );

  debug_dumpSingleReg(trace, flash, io, INT_COUNTER_REG, interface::Register::INT_COUNTER_REG);

  debug_dumpSingleReg(trace, flash, io, WHO_AM_I       , interface::Register::WHO_AM_I       );

  debug_dumpSingleReg(trace, flash, io, TEMP_CFG_REG   , interface::Register::TEMP_CFG_REG   );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG1      , interface::Register::CTRL_REG1      );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG2      , interface::Register::CTRL_REG2      );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG3      , interface::Register::CTRL_REG3      );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG4      , interface::Register::CTRL_REG4      );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG5      , interface::Register::CTRL_REG5      );
  debug_dumpSingleReg(trace, flash, io, CTRL_REG6      , interface::Register::CTRL_REG6      );

  debug_dumpSingleReg(trace, flash, io, STATUS_REG     , interface::Register::STATUS_REG    );

  debug_dumpSingleReg(trace, flash, io, OUT_X_L        , interface::Register::OUT_X_L        );
  debug_dumpSingleReg(trace, flash, io, OUT_X_H        , interface::Register::OUT_X_H        );
  debug_dumpSingleReg(trace, flash, io, OUT_Y_L        , interface::Register::OUT_Y_L        );
  debug_dumpSingleReg(trace, flash, io, OUT_Y_H        , interface::Register::OUT_Y_H        );
  debug_dumpSingleReg(trace, flash, io, OUT_Z_L        , interface::Register::OUT_Z_L        );
  debug_dumpSingleReg(trace, flash, io, OUT_Z_H        , interface::Register::OUT_Z_H        );

  debug_dumpSingleReg(trace, flash, io, FIFO_CTRL_REG  , interface::Register::FIFO_CTRL_REG  );
  debug_dumpSingleReg(trace, flash, io, FIFO_SRC_REG   , interface::Register::FIFO_SRC_REG   );

  debug_dumpSingleReg(trace, flash, io, INT1_CFG       , interface::Register::INT1_CFG       );
  debug_dumpSingleReg(trace, flash, io, INT1_SOURCE    , interface::Register::INT1_SOURCE    );
  debug_dumpSingleReg(trace, flash, io, INT1_THS       , interface::Register::INT1_THS       );
  debug_dumpSingleReg(trace, flash, io, INT1_DURATION  , interface::Register::INT1_DURATION  );

  debug_dumpSingleReg(trace, flash, io, INT2_CFG       , interface::Register::INT2_CFG       );
  debug_dumpSingleReg(trace, flash, io, INT2_SOURCE    , interface::Register::INT2_SOURCE    );
  debug_dumpSingleReg(trace, flash, io, INT2_THS       , interface::Register::INT2_THS       );
  debug_dumpSingleReg(trace, flash, io, INT2_DURATION  , interface::Register::INT2_DURATION  );

  debug_dumpSingleReg(trace, flash, io, CLICK_CFG      , interface::Register::CLICK_CFG      );
  debug_dumpSingleReg(trace, flash, io, CLICK_SRC      , interface::Register::CLICK_SRC      );
  debug_dumpSingleReg(trace, flash, io, CLICK_THS      , interface::Register::CLICK_THS      );

  debug_dumpSingleReg(trace, flash, io, TIME_LIMIT     , interface::Register::TIME_LIMIT     );
  debug_dumpSingleReg(trace, flash, io, TIME_LATENCY   , interface::Register::TIME_LATENCY   );
  debug_dumpSingleReg(trace, flash, io, TIME_WINDOW    , interface::Register::TIME_WINDOW    );

  debug_dumpSingleReg(trace, flash, io, ACT_THS        , interface::Register::ACT_THS        );
  debug_dumpSingleReg(trace, flash, io, ACT_DUR        , interface::Register::ACT_DUR        );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void LIS2DSH_Debug::debug_dumpSingleReg(trace::Trace & trace, hal::interface::Flash & flash, interface::LIS2DSH_Io & io, char const * msg, interface::Register const reg)
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

} /* snowfox::driver::sensorLIS2DSH */
