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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <algorithm>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace vireg
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <typename T>
VirtualRegister<T>::VirtualRegister()
: _reg_val     (0 ),
  _init_reg_val(0 ),
  _name        ("")
{

}

template <typename T>
VirtualRegister<T>::VirtualRegister(T const initial_reg_val, std::string const & name)
: _reg_val     (initial_reg_val),
  _init_reg_val(initial_reg_val),
  _name        (name           )
{

}

template <typename T>
VirtualRegister<T> & VirtualRegister<T>::operator = (VirtualRegister const & other)
{
  if(this != &other)
  {
    _reg_val      = other.regVal    ();
    _init_reg_val = other.initRegVal();
    _name         = other.name      ();
  }
  return *this;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

template <typename T>
T * VirtualRegister<T>::operator()()
{
  return &_reg_val;
}

template <typename T>
bool VirtualRegister<T>::operator == (T const val) const
{
  return (_reg_val == val);
}

template <typename T>
void VirtualRegister<T>::operator = (T const val)
{
  _reg_val = val;
}

template <typename T>
void VirtualRegister<T>::setBit(uint32_t const bit_pos)
{
  _reg_val |= (1<<bit_pos);
}

template <typename T>
void VirtualRegister<T>::clrBit(uint32_t const bit_pos)
{
  _reg_val &= ~(1<<bit_pos);
}

template <typename T>
bool VirtualRegister<T>::isBitSet(uint32_t const bit_pos) const
{
  T const bit_mask = (1<<bit_pos);
  bool const is_bit_set = (_reg_val & bit_mask) == bit_mask;
  return is_bit_set;
}

template <typename T>
bool VirtualRegister<T>::isBitClr(uint32_t const bit_pos) const
{
  T const bit_mask = (1<<bit_pos);
  bool const is_bit_clr = (_reg_val & bit_mask) == 0;
  return is_bit_clr;
}

template <typename T>
bool VirtualRegister<T>::isBitVectSet(std::vector<uint32_t> const bit_pos_vect) const
{
  T bit_mask = 0;
  std::for_each(std::begin(bit_pos_vect),
                std::end  (bit_pos_vect),
                [&bit_mask](uint32_t const bit_pos)
                {
                  bit_mask |= (1<<bit_pos);
                });
  bool const is_bit_vect_set = (_reg_val & bit_mask) == bit_mask;
  return is_bit_vect_set; 
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* vireg */

} /* snowfox */
