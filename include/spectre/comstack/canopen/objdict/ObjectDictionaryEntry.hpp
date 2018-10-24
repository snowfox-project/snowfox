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

#ifndef INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARYENTRY_HPP_
#define INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARYENTRY_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

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

enum class ObjectDictionaryAccess
{
  ReadOnly, WriteOnly, ReadWrite
};

typedef void(*OnValueChangeCallback)(void);

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

template <typename T>
class ObjectDictionaryEntry
{

public:

  ObjectDictionaryEntry(uint16_t               const   idx,
                        uint8_t                const   sub_idx,
                        T                      const & initial_value,
                        ObjectDictionaryAccess const   access,
                        OnValueChangeCallback          on_value_change_callback);


  inline uint16_t               idx   () const { return _idx;     }
  inline uint8_t                subIdx() const { return _sub_idx; }
  inline T                      value () const { return _value;   }
  inline ObjectDictionaryAccess access() const { return _access;  }


  void set(T const value);


private:

  uint16_t               const _idx;
  uint8_t                const _sub_idx;
  T                      const _value;
  ObjectDictionaryAccess const _access;
  OnValueChangeCallback        _on_value_change_callback;

};

/**************************************************************************************
 * PUBLIC PROTOTYPES
 **************************************************************************************/

template <typename T>
bool operator == (ObjectDictionaryEntry<T> const & lhs, ObjectDictionaryEntry<T> const & rhs);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */

/**************************************************************************************
 * TEMPLATE IMPLEMENTATION
 **************************************************************************************/

#include "ObjectDictionaryEntry.ipp"

#endif /* INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARYENTRY_HPP_ */
