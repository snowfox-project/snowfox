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

#include <spectre/comstack/canopen/ObjectDictionary.h>

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

ObjectDictionary::ObjectDictionary(ObjectDictionaryConfiguration const & obj_dict_config)
: _device_type                  (0x1000, 0x00, obj_dict_config.device_type,                   ObjectDictionaryAccess::ReadOnly, 0),
  _error_register               (0x1001, 0x00, obj_dict_config.error_register,                ObjectDictionaryAccess::ReadOnly, 0),
  _manufacturer_device_name     (0x1008, 0x00, obj_dict_config.manufacturer_device_name,      ObjectDictionaryAccess::ReadOnly, 0),
  _manufacturer_hardware_version(0x1009, 0x00, obj_dict_config.manufacturer_hardware_version, ObjectDictionaryAccess::ReadOnly, 0),
  _manufacturer_software_version(0x100A, 0x00, obj_dict_config.manufacturer_software_version, ObjectDictionaryAccess::ReadOnly, 0),
  _od_empty_entry_uint8_t       (0,0,0,ObjectDictionaryAccess::ReadOnly, 0),
  _od_empty_entry_uint32_t      (0,0,0,ObjectDictionaryAccess::ReadOnly, 0),
  _od_empty_entry_string        (0,0,"",ObjectDictionaryAccess::ReadOnly, 0)
{
  push_back(_device_type                  );
  push_back(_error_register               );
  push_back(_manufacturer_device_name     );
  push_back(_manufacturer_hardware_version);
  push_back(_manufacturer_software_version);
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/


/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */
