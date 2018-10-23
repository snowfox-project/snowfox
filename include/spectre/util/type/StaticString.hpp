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

#ifndef INCLUDE_SPECTRE_UTIL_STRING_HPP_
#define INCLUDE_SPECTRE_UTIL_STRING_HPP_

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

namespace type
{

/**************************************************************************************
 * CONSTANT
 **************************************************************************************/

static uint16_t constexpr DEFAULT_MAX_STRING_LENGTH = 32;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

template <uint16_t MAX_STRING_LENGTH = DEFAULT_MAX_STRING_LENGTH>
class StaticString
{

public:

  StaticString();


private:

  char     _string[MAX_STRING_LENGTH];
  uint16_t _length;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* type */

} /* util */

} /* spectre */

#endif /* INCLUDE_SPECTRE_UTIL_STRING_HPP_ */
