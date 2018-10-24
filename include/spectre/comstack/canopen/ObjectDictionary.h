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

#ifndef INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARY_H_
#define INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARY_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/comstack/canopen/ObjectDictionaryEntry.hpp>

#include <spectre/util/container/List.hpp>
#include <spectre/util/type/StaticString.hpp>

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
 * TYPEDEF
 **************************************************************************************/

typedef struct
{
  uint32_t                 device_type;
  uint8_t                  error_register;
  util::type::StaticString manufacturer_device_name;
  util::type::StaticString manufacturer_hardware_version;
  util::type::StaticString manufacturer_software_version;
} ObjectDictionaryConfiguration;

typedef ObjectDictionaryEntry<uint8_t>                  ObjectDictionaryEntry_uint8_t;
typedef ObjectDictionaryEntry<uint32_t>                 ObjectDictionaryEntry_uint32_t;
typedef ObjectDictionaryEntry<util::type::StaticString> ObjectDictionaryEntry_String;

/**************************************************************************************
 * CONSTANT
 **************************************************************************************/

static ObjectDictionaryConfiguration const DEFAULT_OD_CONFIG =
{
  0,                  /* device_type                   */
  0,                  /* error_register                */
  "MY DEVICE NAME",   /* manufacturer_device_name      */
  "HARDWARE VERSION", /* manufacturer_hardware_version */
  "SOFTWARE VERSION"  /* manufacturer_software_version */
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ObjectDictionary
{

public:

  ObjectDictionary(ObjectDictionaryConfiguration const & obj_dict_config);


  template <typename T>
  ObjectDictionaryEntry<T> & operator() (uint16_t const idx, uint8_t const sub_idx);

private:

  /* Object dictionary entries */
  ObjectDictionaryEntry_uint32_t _device_type;
  ObjectDictionaryEntry_uint8_t  _error_register;
  ObjectDictionaryEntry_String   _manufacturer_device_name,
                                 _manufacturer_hardware_version,
                                 _manufacturer_software_version;

  /* Object dictionary empty entries */
  ObjectDictionaryEntry_uint8_t  _od_empty_entry_uint8_t;
  ObjectDictionaryEntry_uint32_t _od_empty_entry_uint32_t;
  ObjectDictionaryEntry_String   _od_empty_entry_string;

  util::container::List<ObjectDictionaryEntry_uint8_t  &> _od_uint8_t;
  util::container::List<ObjectDictionaryEntry_uint32_t &> _od_uint32_t;
  util::container::List<ObjectDictionaryEntry_String   &> _od_string;

  template <typename T>
  void push_back(T & entry);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */

/**************************************************************************************
 * TEMPLATE CODE
 **************************************************************************************/

#include "ObjectDictionary.ipp"

#endif /* INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARY_H_ */
