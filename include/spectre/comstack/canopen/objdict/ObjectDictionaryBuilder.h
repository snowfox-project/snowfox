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

#ifndef INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJDICT_OBJECTDICTIONARYBUILDER_H_
#define INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJDICT_OBJECTDICTIONARYBUILDER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/comstack/canopen/objdict/ObjectDictionary.hpp>

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
 * CLASS DECLARATION
 **************************************************************************************/

class ObjectDictionaryBuilder
{

public:

  ObjectDictionaryBuilder(ObjectDictionary & obj_dict);


private:

  ObjectDictionary & _obj_dict;

  ObjectDictionaryEntry<uint32_t>                 _device_type;
  ObjectDictionaryEntry<uint8_t>                  _error_register;
  ObjectDictionaryEntry<util::type::StaticString> _device_name,
                                                  _device_hw_version,
                                                  _device_sw_version;
  ObjectDictionaryEntry<uint16_t>                 _producer_heartbeat_time;
  ObjectDictionaryEntry<uint8_t>                  _identity_num_entries;
  ObjectDictionaryEntry<uint32_t>                 _identity_vendor_id,
                                                  _identity_product_code,
                                                  _identity_revision_number,
                                                  _identity_serial_number;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */

#endif /* INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJDICT_OBJECTDICTIONARYBUILDER_H_ */
