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

#ifndef TEST_VIREG_INCLUDE_VIREG_VIRTUALREGISTERMAP_HPP_
#define TEST_VIREG_INCLUDE_VIREG_VIRTUALREGISTERMAP_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <map>
#include <string>

#include <boost/variant.hpp>

#include <vireg/VirtualRegister.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace vireg
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef boost::variant<VirtualRegister<uint8_t >,
                       VirtualRegister<uint16_t>,
                       VirtualRegister<uint32_t>,
                       VirtualRegister<uint64_t>> VirtualRegisterVariant;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class VirtualRegisterMap
{

public:

  template<typename T>
  void set(std::string const & key, T const & value);

  template<typename T>
  T const & get(std::string const & key);


private:

  std::map<std::string, VirtualRegisterVariant> _map;

  bool exists(std::string const & key) const;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* vireg */

} /* snowfox */

/**************************************************************************************
 * TEMPLATE IMPLEMENTATION
 **************************************************************************************/

#include "VirtualRegisterMap.ipp"

#endif /* TEST_VIREG_INCLUDE_VIREG_VIRTUALREGISTERMAP_HPP_ */
