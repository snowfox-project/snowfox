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

#ifndef TEST_VIREG_INCLUDE_VIREG_VIRTUALREGISTERLOADER_HPP_
#define TEST_VIREG_INCLUDE_VIREG_VIRTUALREGISTERLOADER_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <map>

#include <vireg/VirtualRegister.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace vireg
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class VirtualRegisterLoader
{

public:

  template <typename T>
  static std::map<std::string, VirtualRegister<T>> load(char const * json_file_name);


private:

  VirtualRegisterLoader() { }
  VirtualRegisterLoader(VirtualRegisterLoader & other) { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* vireg */

} /* snowfox */

/**************************************************************************************
 * TEMPLATE IMPLEMENTATION
 **************************************************************************************/

#include "VirtualRegisterLoader.ipp"

#endif /* TEST_VIREG_INCLUDE_VIREG_VIRTUALREGISTERLOADER_HPP_ */
