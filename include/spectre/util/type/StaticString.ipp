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
 * INCLUDE
 **************************************************************************************/

#include <string.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace util
{

namespace type
{

namespace impl
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <uint16_t MAX_STRING_LENGTH>
StaticString<MAX_STRING_LENGTH>::StaticString()
: _length(0)
{
  memset(_string, 0, sizeof(char)*MAX_STRING_LENGTH);
}

template <uint16_t MAX_STRING_LENGTH>
StaticString<MAX_STRING_LENGTH>::StaticString(char const * str)
: _length(strlen(str))
{
  strncpy(_string, str, MAX_STRING_LENGTH);
}

template <uint16_t MAX_STRING_LENGTH>
StaticString<MAX_STRING_LENGTH>::StaticString(StaticString const & other)
: StaticString(other.c_str())
{

}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* impl */

} /* type */

} /* util */

} /* spectre */
