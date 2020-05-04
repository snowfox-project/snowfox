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

#include <snowfox/driver/sensor/LIS3DSH/LIS3DSH_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::LIS3DSH
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const INFO_1    [] = "INFO_1     = ");
FLASH_DECLARE(static char const INFO_2    [] = "INFO_2     = ");
FLASH_DECLARE(static char const WHO_AM_I  [] = "WHO_AM_I   = ");
FLASH_DECLARE(static char const CTRL_REG_1[] = "CTRL_REG_1 = ");
FLASH_DECLARE(static char const CTRL_REG_2[] = "CTRL_REG_2 = ");
FLASH_DECLARE(static char const CTRL_REG_3[] = "CTRL_REG_3 = ");
FLASH_DECLARE(static char const CTRL_REG_4[] = "CTRL_REG_4 = ");
FLASH_DECLARE(static char const CTRL_REG_5[] = "CTRL_REG_5 = ");
FLASH_DECLARE(static char const CTRL_REG_6[] = "CTRL_REG_6 = ");
FLASH_DECLARE(static char const STATUS    [] = "STATUS     = ");
FLASH_DECLARE(static char const OUT_T     [] = "OUT_T      = ");
FLASH_DECLARE(static char const OFF_X     [] = "OFF_X      = ");
FLASH_DECLARE(static char const OFF_Y     [] = "OFF_Y      = ");
FLASH_DECLARE(static char const OFF_Z     [] = "OFF_Z      = ");
FLASH_DECLARE(static char const CS_X      [] = "CS_X       = ");
FLASH_DECLARE(static char const CS_Y      [] = "CS_Y       = ");
FLASH_DECLARE(static char const CS_Z      [] = "CS_Z       = ");
FLASH_DECLARE(static char const OUT_X_L   [] = "OUT_X_L    = ");
FLASH_DECLARE(static char const OUT_X_H   [] = "OUT_X_H    = ");
FLASH_DECLARE(static char const OUT_Y_L   [] = "OUT_Y_L    = ");
FLASH_DECLARE(static char const OUT_Y_H   [] = "OUT_Y_H    = ");
FLASH_DECLARE(static char const OUT_Z_L   [] = "OUT_Z_L    = ");
FLASH_DECLARE(static char const OUT_Z_H   [] = "OUT_Z_H    = ");
FLASH_DECLARE(static char const FIFO_CTRL [] = "FIFO_CTRL  = ");
FLASH_DECLARE(static char const FIFO_SRC  [] = "FIFO_SRC   = ");

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void LIS3DSH_Debug::debug_dumpAllRegs(trace::Trace & trace, hal::interface::Flash & flash, interface::LIS3DSH_Io & io)
{
  debug_dumpSingleReg(trace, flash, io, INFO_1    , interface::Register::INFO_1    );
  debug_dumpSingleReg(trace, flash, io, INFO_2    , interface::Register::INFO_2    );
  debug_dumpSingleReg(trace, flash, io, WHO_AM_I  , interface::Register::WHO_AM_I  );

  debug_dumpSingleReg(trace, flash, io, CTRL_REG_1, interface::Register::CTRL_REG_1);
  debug_dumpSingleReg(trace, flash, io, CTRL_REG_2, interface::Register::CTRL_REG_2);
  debug_dumpSingleReg(trace, flash, io, CTRL_REG_3, interface::Register::CTRL_REG_3);
  debug_dumpSingleReg(trace, flash, io, CTRL_REG_4, interface::Register::CTRL_REG_4);
  debug_dumpSingleReg(trace, flash, io, CTRL_REG_5, interface::Register::CTRL_REG_5);
  debug_dumpSingleReg(trace, flash, io, CTRL_REG_6, interface::Register::CTRL_REG_6);

  debug_dumpSingleReg(trace, flash, io, STATUS    , interface::Register::STATUS    );

  debug_dumpSingleReg(trace, flash, io, OUT_T     , interface::Register::OUT_T     );

  debug_dumpSingleReg(trace, flash, io, OFF_X     , interface::Register::OFF_X     );
  debug_dumpSingleReg(trace, flash, io, OFF_Y     , interface::Register::OFF_Y     );
  debug_dumpSingleReg(trace, flash, io, OFF_Z     , interface::Register::OFF_Z     );
  debug_dumpSingleReg(trace, flash, io, CS_X      , interface::Register::CS_X      );
  debug_dumpSingleReg(trace, flash, io, CS_Y      , interface::Register::CS_Y      );
  debug_dumpSingleReg(trace, flash, io, CS_Z      , interface::Register::CS_Z      );

  debug_dumpSingleReg(trace, flash, io, OUT_X_L   , interface::Register::OUT_X_L   );
  debug_dumpSingleReg(trace, flash, io, OUT_X_H   , interface::Register::OUT_X_H   );
  debug_dumpSingleReg(trace, flash, io, OUT_Y_L   , interface::Register::OUT_Y_L   );
  debug_dumpSingleReg(trace, flash, io, OUT_Y_H   , interface::Register::OUT_Y_H   );
  debug_dumpSingleReg(trace, flash, io, OUT_Z_L   , interface::Register::OUT_Z_L   );
  debug_dumpSingleReg(trace, flash, io, OUT_Z_H   , interface::Register::OUT_Z_H   );

  debug_dumpSingleReg(trace, flash, io, FIFO_CTRL , interface::Register::FIFO_CTRL );
  debug_dumpSingleReg(trace, flash, io, FIFO_SRC  , interface::Register::FIFO_SRC  );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void LIS3DSH_Debug::debug_dumpSingleReg(trace::Trace & trace, hal::interface::Flash & flash, interface::LIS3DSH_Io & io, char const * msg, interface::Register const reg)
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

} /* snowfox::driver::sensor::LIS3DSH */
