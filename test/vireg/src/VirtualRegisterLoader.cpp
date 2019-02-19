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

#include <vireg/VirtualRegisterLoader.h>

#include <fstream>
#include <sstream>
#include <iomanip>

#include <nlohmann/json.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace vireg
{

/**************************************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **************************************************************************************/

uint8_t  hexStrToUint8 (std::string const & str);
uint16_t hexStrToUint16(std::string const & str);
uint32_t hexStrToUint32(std::string const & str);
uint64_t hexStrToUint64(std::string const & str);

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

VirtualRegisterMap VirtualRegisterLoader::load(char const * json_file_name)
{
  std::ifstream in(json_file_name);
  if(!in.good()) throw std::runtime_error("'VirtualRegisterLoader::load' could not load json virtual register configuration file");
  nlohmann::json json;
  in >> json;
  in.close();
  
  /* JSON Virtual Register Example
   * {
   *   "TCNT0": {
   *     "Type": "UNSIGNED16",
   *     "Initial": "0x0000"
   *   },
   *   "TCCR0B": {
   *     "Type": "UNSIGNED8",
   *     "Initial": "0x00"
   *   }
   * }
   */

  VirtualRegisterMap virtual_reg_map;

  for(nlohmann::json::iterator reg_it = json.begin(); reg_it != json.end(); reg_it++)
  {
    std::string const register_name        = reg_it.key();                   /* TCNT0      */
    std::string const register_type        = json[register_name]["Type"];    /* UNSIGNED16 */
    std::string const register_initial_val = json[register_name]["Initial"]; /* 0x0000     */

    if     (register_type == "UNSIGNED8")
    {
      VirtReg8 virt_reg = std::make_shared<VirtualRegister<uint8_t>>(hexStrToUint8(register_initial_val), register_name);
      virtual_reg_map.set(register_name, virt_reg);
    }
    else if(register_type == "UNSIGNED16")
    {
      VirtReg16 virt_reg = std::make_shared<VirtualRegister<uint16_t>>(hexStrToUint16(register_initial_val), register_name);
      virtual_reg_map.set(register_name, virt_reg);
    }
    else if(register_type == "UNSIGNED32")
    {
      VirtReg32 virt_reg = std::make_shared<VirtualRegister<uint32_t>>(hexStrToUint32(register_initial_val), register_name);
      virtual_reg_map.set(register_name, virt_reg);
    }
    else if(register_type == "UNSIGNED64")
    {
      VirtReg64 virt_reg = std::make_shared<VirtualRegister<uint64_t>>(hexStrToUint64(register_initial_val), register_name);
      virtual_reg_map.set(register_name, virt_reg);
    }
  }

  return virtual_reg_map;
}

/**************************************************************************************
 * PRIVATE FUNCTION
 **************************************************************************************/

uint8_t hexStrToUint8(std::string const & str)
{
  return static_cast<uint8_t>(hexStrToUint64(str));
}

uint16_t hexStrToUint16(std::string const & str)
{
  return static_cast<uint16_t>(hexStrToUint64(str));
}

uint32_t hexStrToUint32(std::string const & str)
{
  return static_cast<uint32_t>(hexStrToUint64(str));
}

uint64_t hexStrToUint64(std::string const & str)
{
  uint64_t hex_val = 0;
  std::stringstream ss;

  ss << std::hex << str;
  ss >> hex_val;

  return hex_val;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* vireg */

} /* snowfox */
