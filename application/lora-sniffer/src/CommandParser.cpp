/**
 * lora-sniffer is a LoRa packet sniffer based on the HopeRF RF95.
 * Copyright (C) 2018 Alexander Entinger / LXRobotics GmbH
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

#include <lora-sniffer/CommandParser.h>

#include <string.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace application
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool CommandParser::isDebugCommand(char const * cmd_str)
{
  bool const is_debug_cmd = strcmp(cmd_str, "DB\r") == 0;
  return is_debug_cmd;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* application */
