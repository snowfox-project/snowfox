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

#ifndef INCLUDE_SNOWFOX_COMSTACK_CANOPEN_OBJECTDICTIONARY_HPP_
#define INCLUDE_SNOWFOX_COMSTACK_CANOPEN_OBJECTDICTIONARY_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/comstack/canopen/objdict/ObjectDictionaryEntry.hpp>

#include <stdbool.h>

#include <list>
#include <string>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace comstack
{

namespace canopen
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ObjectDictionary
{

public:

  template <typename T>
  void add(ObjectDictionaryEntry<T> * entry);

  inline ObjectDictionaryEntry<uint8_t>     * get_UINT8 (uint16_t const idx, uint8_t const sub_idx) { return find(_od_uint8_t,  idx, sub_idx); }
  inline ObjectDictionaryEntry<uint16_t>    * get_UINT16(uint16_t const idx, uint8_t const sub_idx) { return find(_od_uint16_t, idx, sub_idx); }
  inline ObjectDictionaryEntry<uint32_t>    * get_UINT32(uint16_t const idx, uint8_t const sub_idx) { return find(_od_uint32_t, idx, sub_idx); }
  inline ObjectDictionaryEntry<std::string> * get_STRING(uint16_t const idx, uint8_t const sub_idx) { return find(_od_string,   idx, sub_idx); }


private:

  std::list<ObjectDictionaryEntry<uint8_t>     *> _od_uint8_t;
  std::list<ObjectDictionaryEntry<uint16_t>    *> _od_uint16_t;
  std::list<ObjectDictionaryEntry<uint32_t>    *> _od_uint32_t;
  std::list<ObjectDictionaryEntry<std::string> *> _od_string;

  template <typename T>
  ObjectDictionaryEntry<T> * find(std::list<ObjectDictionaryEntry<T> *> & list, uint16_t const idx, uint8_t const sub_idx);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* snowfox */

/**************************************************************************************
 * TEMPLATE CODE
 **************************************************************************************/

#include "ObjectDictionary.ipp"

#endif /* INCLUDE_SNOWFOX_COMSTACK_CANOPEN_OBJECTDICTIONARY_HPP_ */
