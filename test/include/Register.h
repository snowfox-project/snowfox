/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <vector>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

template <typename T>
class Register
{

public:

  Register(T const initial_reg_val);


  T    * operator () ();
  bool   operator == (T const val) const;

  void   setBit      (uint32_t       const bit_pos ) const;
  void   clrBit      (uint32_t       const bit_pos ) const;
  bool   isBitSet    (uint32_t       const bit_pos ) const;
  bool   isBitClr    (uint32_t       const bit_pos ) const;

  bool   isBitVectSet(std::vector<uint32_t> const bit_pos_vect) const;

private:

  T _reg_val;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* spectre */

/**************************************************************************************
 * TEMPLATE IMPLEMENTATION
 **************************************************************************************/

#include "Register.ipp"

#endif /* TEST_INCLUDE_REGISTER_H_ */
