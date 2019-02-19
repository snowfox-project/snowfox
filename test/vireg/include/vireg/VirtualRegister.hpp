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

#ifndef TEST_INCLUDE_REGISTER_H_
#define TEST_INCLUDE_REGISTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <vector>
#include <string>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace vireg
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

template <typename T>
class VirtualRegister
{

public:

  VirtualRegister(T const init_reg_val, std::string const & name);


  inline std::string name() const { return _name; }


  T    * operator () ();
  bool   operator == (T const val) const;
  void   operator =  (T const val);


  void   setBit      (uint32_t const bit_pos);
  void   clrBit      (uint32_t const bit_pos);

  bool   isBitSet    (uint32_t const bit_pos) const;
  bool   isBitClr    (uint32_t const bit_pos) const;
  bool   isBitVectSet(std::vector<uint32_t> const bit_pos_vect) const;


private:

  T                 _reg_val;
  std::string const _name;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* vireg */

} /* snowfox */

/**************************************************************************************
 * TEMPLATE IMPLEMENTATION
 **************************************************************************************/

#include "VirtualRegister.ipp"

#endif /* TEST_INCLUDE_REGISTER_H_ */
