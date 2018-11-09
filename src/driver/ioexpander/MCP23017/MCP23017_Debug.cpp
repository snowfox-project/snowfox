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

#include <spectre/driver/ioexpander/MCP23017/MCP23017_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace ioexpander
{

namespace MCP23017
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const IODIR_A   [] = "IODIR_A   = ");
FLASH_DECLARE(static char const IODIR_B   [] = "IODIR_B   = ");
FLASH_DECLARE(static char const IPOL_A    [] = "IPOL_A    = ");
FLASH_DECLARE(static char const IPOL_B    [] = "IPOL_B    = ");
FLASH_DECLARE(static char const GPINTEN_A [] = "GPINTEN_A = ");
FLASH_DECLARE(static char const GPINTEN_B [] = "GPINTEN_B = ");
FLASH_DECLARE(static char const DEFVAL_A  [] = "DEFVAL_A  = ");
FLASH_DECLARE(static char const DEFVAL_B  [] = "DEFVAL_B  = ");
FLASH_DECLARE(static char const INTCON_A  [] = "INTCON_A  = ");
FLASH_DECLARE(static char const INTCON_B  [] = "INTCON_B  = ");
FLASH_DECLARE(static char const IOCON_A   [] = "IOCON_A   = ");
FLASH_DECLARE(static char const IOCON_B   [] = "IOCON_B   = ");
FLASH_DECLARE(static char const GPPU_A    [] = "GPPU_A    = ");
FLASH_DECLARE(static char const GPPU_B    [] = "GPPU_B    = ");
FLASH_DECLARE(static char const INTF_A    [] = "INTF_A    = ");
FLASH_DECLARE(static char const INTF_B    [] = "INTF_B    = ");
FLASH_DECLARE(static char const INTCAP_A  [] = "INTCAP_A  = ");
FLASH_DECLARE(static char const INTCAP_B  [] = "INTCAP_B  = ");
FLASH_DECLARE(static char const GPIO_A    [] = "GPIO_A    = ");
FLASH_DECLARE(static char const GPIO_B    [] = "GPIO_B    = ");
FLASH_DECLARE(static char const OLAT_A    [] = "OLAT_A    = ");
FLASH_DECLARE(static char const OLAT_B    [] = "OLAT_B    = ");

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP23017_Debug::debug_dumpAllRegs(trace::Trace & trace, hal::interface::Flash & flash, interface::MCP23017_Io & io)
{
  debug_dumpSingleReg(trace, flash, io, IODIR_A  , interface::Register::IODIR_A  );
  debug_dumpSingleReg(trace, flash, io, IODIR_B  , interface::Register::IODIR_B  );
  debug_dumpSingleReg(trace, flash, io, IPOL_A   , interface::Register::IPOL_A   );
  debug_dumpSingleReg(trace, flash, io, IPOL_B   , interface::Register::IPOL_B   );
  debug_dumpSingleReg(trace, flash, io, GPINTEN_A, interface::Register::GPINTEN_A);
  debug_dumpSingleReg(trace, flash, io, GPINTEN_B, interface::Register::GPINTEN_B);
  debug_dumpSingleReg(trace, flash, io, DEFVAL_A , interface::Register::DEFVAL_A );
  debug_dumpSingleReg(trace, flash, io, DEFVAL_B , interface::Register::DEFVAL_B );
  debug_dumpSingleReg(trace, flash, io, INTCON_A , interface::Register::INTCON_A );
  debug_dumpSingleReg(trace, flash, io, INTCON_B , interface::Register::INTCON_B );
  debug_dumpSingleReg(trace, flash, io, IOCON_A  , interface::Register::IOCON_A  );
  debug_dumpSingleReg(trace, flash, io, IOCON_B  , interface::Register::IOCON_B  );
  debug_dumpSingleReg(trace, flash, io, GPPU_A   , interface::Register::GPPU_A   );
  debug_dumpSingleReg(trace, flash, io, GPPU_B   , interface::Register::GPPU_B   );
  debug_dumpSingleReg(trace, flash, io, INTF_A   , interface::Register::INTF_A   );
  debug_dumpSingleReg(trace, flash, io, INTF_B   , interface::Register::INTF_B   );
  debug_dumpSingleReg(trace, flash, io, INTCAP_A , interface::Register::INTCAP_A );
  debug_dumpSingleReg(trace, flash, io, INTCAP_B , interface::Register::INTCAP_B );
  debug_dumpSingleReg(trace, flash, io, GPIO_A   , interface::Register::GPIO_A   );
  debug_dumpSingleReg(trace, flash, io, GPIO_B   , interface::Register::GPIO_B   );
  debug_dumpSingleReg(trace, flash, io, OLAT_A   , interface::Register::OLAT_A   );
  debug_dumpSingleReg(trace, flash, io, OLAT_B   , interface::Register::OLAT_B   );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void MCP23017_Debug::debug_dumpSingleReg(trace::Trace & trace, hal::interface::Flash & flash, interface::MCP23017_Io & io, char const * msg, interface::Register const reg)
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

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */
