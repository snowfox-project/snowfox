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
 * INCLUDE
 **************************************************************************************/

#include <spectre/comstack/canopen/objdict/ObjectDictionaryBuilder.h>

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
 * CTOR/DTOR
 **************************************************************************************/

void ObjectDictionaryBuilder::build(ObjectDictionary & obj_dict)
{
  obj_dict.add(new ObjectDictionaryEntry<uint32_t>                (0x1000, 0, 0,  ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<uint8_t>                 (0x1001, 0, 0,  ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<util::type::StaticString>(0x1008, 0, "", ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<util::type::StaticString>(0x1009, 0, "", ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<util::type::StaticString>(0x100A, 0, "", ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<uint16_t>                (0x1017, 0, 0,  ObjectDictionaryAccess::ReadWrite, 0));

  obj_dict.add(new ObjectDictionaryEntry<uint8_t>                 (0x1018, 0, 4,  ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<uint32_t>                (0x1018, 1, 0,  ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<uint32_t>                (0x1018, 2, 0,  ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<uint32_t>                (0x1018, 3, 0,  ObjectDictionaryAccess::ReadOnly,  0));
  obj_dict.add(new ObjectDictionaryEntry<uint32_t>                (0x1018, 4, 0,  ObjectDictionaryAccess::ReadOnly,  0));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */
