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
#include <iostream>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <nlohmann/json.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace vireg
{

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
    std::string const register_name        = reg_it.key();
    std::string const register_type        = json[register_name];
    std::string const register_initial_val = json[register_name];

    if(register_type == "UNSIGNED8")
    {
      uint8_t const initial_val = boost::lexical_cast<uint8_t>(register_initial_val);
      VirtualRegister<uint8_t> virt_reg(initial_val, register_name);
      virtual_reg_map.set(register_name, virt_reg);
    }
  }

  return virtual_reg_map;

//  for(nlohmann::json::iterator reg_it = json.begin(); reg_it != json.end(); reg_it++)
//  {
//    std::cout << reg_it.key() << std::endl;
//    for(nlohmann::json::iterator reg_data_it = reg_it->begin(); reg_data_it != reg_it->end(); reg_data_it++)
//    {
//      std::cout << reg_data_it.key() << " : " << reg_data_it.value() << std::endl;
//    }
//  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* vireg */

} /* snowfox */
