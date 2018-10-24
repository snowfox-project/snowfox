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
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace comstack
{

namespace canopen
{

/**************************************************************************************
 * INTERNAL PROTOTYPES
 **************************************************************************************/

template <typename T>
ObjectDictionaryEntry<T> & find(util::container::List<ObjectDictionaryEntry<T> &> & list, ObjectDictionaryEntry<T> & od_empty_entry, uint16_t const idx, uint8_t const sub_idx);

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

template <>
ObjectDictionaryEntry<uint8_t> & ObjectDictionary::operator() (uint16_t const idx, uint8_t const sub_idx)
{
  return find(_od_uint8_t, _od_empty_entry_uint8_t, idx, sub_idx);
}

template <>
ObjectDictionaryEntry<uint32_t> & ObjectDictionary::operator() (uint16_t const idx, uint8_t const sub_idx)
{
  return find(_od_uint32_t, _od_empty_entry_uint32_t, idx, sub_idx);
}

template <>
ObjectDictionaryEntry<util::type::StaticString> & ObjectDictionary::operator() (uint16_t const idx, uint8_t const sub_idx)
{
  return find(_od_string, _od_empty_entry_string, idx, sub_idx);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

template <>
void ObjectDictionary::push_back(ObjectDictionaryEntry_uint8_t & entry)
{
  _od_uint8_t.push_back(entry);
}

template <>
void ObjectDictionary::push_back(ObjectDictionaryEntry_uint32_t & entry)
{
  _od_uint32_t.push_back(entry);
}

template <>
void ObjectDictionary::push_back(ObjectDictionaryEntry_String & entry)
{
  _od_string.push_back(entry);
}

/**************************************************************************************
 * INTERNAL FUNCTIONS
 **************************************************************************************/

template <typename T>
ObjectDictionaryEntry<T> & find(util::container::List<ObjectDictionaryEntry<T> &> & list, ObjectDictionaryEntry<T> & od_empty_entry, uint16_t const idx, uint8_t const sub_idx)
{
  for(util::container::ListNode<ObjectDictionaryEntry<T> &> * iter = list.begin();
      iter != list.end();
      iter = iter->next())
  {
    if(iter->data().idx() == idx && iter->data().subIdx() == sub_idx) return iter->data();
  }
  
  return od_empty_entry;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */