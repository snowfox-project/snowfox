/**
 * Spectre is a modular RTOS with extensive IO support.
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

template <typename T>
ObjectDictionaryEntry<T>::ObjectDictionaryEntry(uint16_t               const   idx,
                                                uint8_t                const   sub_idx,
                                                T                      const & initial_value,
                                                ObjectDictionaryAccess const   access,
                                                OnValueChangeCallback          on_value_change_callback)
: _idx                     (idx                     ),
  _sub_idx                 (sub_idx                 ),
  _value                   (initial_value           ),
  _access                  (access                  ),
  _on_value_change_callback(on_value_change_callback)
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTION
 **************************************************************************************/

template <typename T>
void ObjectDictionaryEntry<T>::set(T const value)
{
  bool const is_value_different = _value != value; 
  
  if(is_value_different)
  {
    _value = value;
    if(_on_value_change_callback != 0)
    {
      _on_value_change_callback();
    }
  }
}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

template <typename T>
bool operator == (ObjectDictionaryEntry<T> const & lhs, ObjectDictionaryEntry<T> const & rhs)
{
  return (lhs.idx() == rhs.idx()) && (lhs.subIdx() == rhs.subIdx()); 
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */
