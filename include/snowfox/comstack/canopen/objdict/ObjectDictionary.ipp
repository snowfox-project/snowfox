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

#include <iterator>
#include <algorithm>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::comstack::canopen
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

template <>
inline void ObjectDictionary::add(ObjectDictionaryEntry<uint8_t> * entry)
{
  _od_uint8_t.push_back(entry);
}

template <>
inline void ObjectDictionary::add(ObjectDictionaryEntry<uint16_t> * entry)
{
  _od_uint16_t.push_back(entry);
}

template <>
inline void ObjectDictionary::add(ObjectDictionaryEntry<uint32_t> * entry)
{
  _od_uint32_t.push_back(entry);
}

template <>
inline void ObjectDictionary::add(ObjectDictionaryEntry<std::string> * entry)
{
  _od_string.push_back(entry);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

template <typename T>
inline ObjectDictionaryEntry<T> * ObjectDictionary::find(std::list<ObjectDictionaryEntry<T> *> & list, uint16_t const idx, uint8_t const sub_idx)
{
  typename std::list<ObjectDictionaryEntry<T> *>::iterator iter = std::find_if(list.begin(),
                                                                               list.end(),
                                                                               [idx, sub_idx](ObjectDictionaryEntry<T> * entry) -> bool
                                                                               {
                                                                                 return ((entry->idx() == idx) && (entry->subIdx() == sub_idx));
                                                                               }); 
  if(iter != list.end()) {
    return *iter;
  } else {
    return 0;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::comstack::canopen */