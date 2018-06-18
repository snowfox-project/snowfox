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

#include <spectre/driver/can/MCP2515/MCP2515_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace can
{

namespace MCP2515
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const CANSTAT [] = "CANSTAT = ");
FLASH_DECLARE(static char const CANCTRL [] = "CANCTRL = ");
FLASH_DECLARE(static char const TEC     [] = "TEC     = ");
FLASH_DECLARE(static char const REC     [] = "REC     = ");
FLASH_DECLARE(static char const CNF3    [] = "CNF3    = ");
FLASH_DECLARE(static char const CNF2    [] = "CNF2    = ");
FLASH_DECLARE(static char const CNF1    [] = "CNF1    = ");
FLASH_DECLARE(static char const CANINTE [] = "CANINTE = ");
FLASH_DECLARE(static char const CANINTF [] = "CANINTF = ");
FLASH_DECLARE(static char const EFLG    [] = "EFLG    = ");

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_Debug::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, interface::MCP2515_Io & io)
{
  debug_dumpSingleReg(debug_interface, flash, io, CANSTAT, interface::Register::CANSTAT);
  debug_dumpSingleReg(debug_interface, flash, io, CANCTRL, interface::Register::CANCTRL);
  debug_dumpSingleReg(debug_interface, flash, io, TEC,     interface::Register::TEC);
  debug_dumpSingleReg(debug_interface, flash, io, REC,     interface::Register::REC);
  debug_dumpSingleReg(debug_interface, flash, io, CNF3,    interface::Register::CNF3);
  debug_dumpSingleReg(debug_interface, flash, io, CNF2,    interface::Register::CNF2);
  debug_dumpSingleReg(debug_interface, flash, io, CNF1,    interface::Register::CNF1);
  debug_dumpSingleReg(debug_interface, flash, io, CANINTE, interface::Register::CANINTE);
  debug_dumpSingleReg(debug_interface, flash, io, CANINTF, interface::Register::CANINTF);
  debug_dumpSingleReg(debug_interface, flash, io, EFLG,    interface::Register::EFLG);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_Debug::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, interface::MCP2515_Io & io, char const * msg, interface::Register const reg)
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

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
