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

#include <snowfox/driver/memory/N25Q256A/N25Q256A_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::N25Q256A
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void N25Q256A_Debug::debug_dumpAllRegs(trace::Trace & trace, interface::N25Q256A_Io & io)
{
  debug_dumpStatusReg    (trace, io);
  debug_dumpFlagStatusReg(trace, io);
  debug_dumpNVConfigReg  (trace, io);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void N25Q256A_Debug::debug_dumpStatusReg(trace::Trace & trace, interface::N25Q256A_Io & io)
{
  uint8_t status_reg = io.readStatusReg();
  trace.println(trace::Level::Debug, "STATUS REG      = %02X", status_reg);
}

void N25Q256A_Debug::debug_dumpFlagStatusReg(trace::Trace & trace, interface::N25Q256A_Io & io)
{
  uint8_t flag_status_reg = io.readFlagStatusReg();
  trace.println(trace::Level::Debug, "FLAG STATUS REG = %02X", flag_status_reg);
}

void N25Q256A_Debug::debug_dumpNVConfigReg(trace::Trace & trace, interface::N25Q256A_Io & io)
{
  uint16_t non_volatile_config_reg = io.readNVConfigReg();
  trace.println(trace::Level::Debug, "NV CONFIG REG   = %04X", non_volatile_config_reg);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::N25Q256A */
