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

#include <spectre/driver/sensor/LIS3MDL/LIS3MDL_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace LIS3MDL
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const WHO_AM_I  [] = "WHO_AM_I   = ");
FLASH_DECLARE(static char const CTRL_REG_1[] = "CTRL_REG_1 = ");
FLASH_DECLARE(static char const CTRL_REG_2[] = "CTRL_REG_2 = ");
FLASH_DECLARE(static char const CTRL_REG_3[] = "CTRL_REG_3 = ");
FLASH_DECLARE(static char const CTRL_REG_4[] = "CTRL_REG_4 = ");
FLASH_DECLARE(static char const CTRL_REG_5[] = "CTRL_REG_5 = ");
FLASH_DECLARE(static char const STATUS_REG[] = "STATUS_REG = ");
FLASH_DECLARE(static char const OUT_X_L   [] = "OUT_X_L    = ");
FLASH_DECLARE(static char const OUT_X_H   [] = "OUT_X_H    = ");
FLASH_DECLARE(static char const OUT_Y_L   [] = "OUT_Y_L    = ");
FLASH_DECLARE(static char const OUT_Y_H   [] = "OUT_Y_H    = ");
FLASH_DECLARE(static char const OUT_Z_L   [] = "OUT_Z_L    = ");
FLASH_DECLARE(static char const OUT_Z_H   [] = "OUT_Z_H    = ");
FLASH_DECLARE(static char const TEMP_OUT_L[] = "TEMP_OUT_L = ");
FLASH_DECLARE(static char const TEMP_OUT_H[] = "TEMP_OUT_H = ");
FLASH_DECLARE(static char const INT_CFG   [] = "INT_CFG    = ");
FLASH_DECLARE(static char const INT_SRC   [] = "INT_SRC    = ");
FLASH_DECLARE(static char const INT_THS_L [] = "INT_THS_L  = ");
FLASH_DECLARE(static char const INT_THS_H [] = "INT_THS_H  = ");

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void LIS3MDL_Debug::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, interface::LIS3MDL_Io & io)
{
  debug_dumpSingleReg(debug_interface, flash, io, WHO_AM_I  , interface::Register::WHO_AM_I  );
  debug_dumpSingleReg(debug_interface, flash, io, CTRL_REG_1, interface::Register::CTRL_REG_1);
  debug_dumpSingleReg(debug_interface, flash, io, CTRL_REG_2, interface::Register::CTRL_REG_2);
  debug_dumpSingleReg(debug_interface, flash, io, CTRL_REG_3, interface::Register::CTRL_REG_3);
  debug_dumpSingleReg(debug_interface, flash, io, CTRL_REG_4, interface::Register::CTRL_REG_4);
  debug_dumpSingleReg(debug_interface, flash, io, CTRL_REG_5, interface::Register::CTRL_REG_5);
  debug_dumpSingleReg(debug_interface, flash, io, STATUS_REG, interface::Register::STATUS_REG);
  debug_dumpSingleReg(debug_interface, flash, io, OUT_X_L   , interface::Register::OUT_X_L   );
  debug_dumpSingleReg(debug_interface, flash, io, OUT_X_H   , interface::Register::OUT_X_H   );
  debug_dumpSingleReg(debug_interface, flash, io, OUT_Y_L   , interface::Register::OUT_Y_L   );
  debug_dumpSingleReg(debug_interface, flash, io, OUT_Y_H   , interface::Register::OUT_Y_H   );
  debug_dumpSingleReg(debug_interface, flash, io, OUT_Z_L   , interface::Register::OUT_Z_L   );
  debug_dumpSingleReg(debug_interface, flash, io, OUT_Z_H   , interface::Register::OUT_Z_H   );
  debug_dumpSingleReg(debug_interface, flash, io, TEMP_OUT_L, interface::Register::TEMP_OUT_L);
  debug_dumpSingleReg(debug_interface, flash, io, TEMP_OUT_H, interface::Register::TEMP_OUT_H);
  debug_dumpSingleReg(debug_interface, flash, io, INT_CFG   , interface::Register::INT_CFG   );
  debug_dumpSingleReg(debug_interface, flash, io, INT_SRC   , interface::Register::INT_SRC   );
  debug_dumpSingleReg(debug_interface, flash, io, INT_THS_L , interface::Register::INT_THS_L );
  debug_dumpSingleReg(debug_interface, flash, io, INT_THS_H , interface::Register::INT_THS_H );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void LIS3MDL_Debug::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, interface::LIS3MDL_Io & io, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  io.readRegister(reg, &reg_content);

  debug_interface.print("%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* spectre */
