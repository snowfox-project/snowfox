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

#include <fstream>
#include <stdexcept>

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

template <typename T>
std::map<std::string, VirtualRegister<T>> VirtualRegisterLoader::load(std::string const & json_file_name)
{
  std::ifstream in(file_name.c_str());
  if(!in.good()) throw std::runtime_error("'VirtualRegisterLoader::load' could not load json virtual register configuration file");
  nlohmann::json json;
  in >> json;
  in.close();
  
  /* JSON Virtual Register Example
   * {
   *   "TCNT0": 0x00,
   *   "TCCR0B": 0x00,
   *   ...
   * }
   */

  for (nlohmann::json::iterator it = json.begin(); it != json.end(); it++)
  {
    std::cout << it.key() << " : " << it.value() << "\n";
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* vireg */

} /* snowfox */
