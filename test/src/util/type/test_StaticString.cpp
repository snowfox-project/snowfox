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

#include <catch.hpp>

#include <spectre/util/type/StaticString.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace util
{

namespace type
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A StaticString object is constructed with the default constructor", "[util::type::StaticString]")
{
  StaticString str;

  THEN("length() should return 0"  ) { REQUIRE(str.length() == 0); }
}

/**************************************************************************************/

SCENARIO("A StaticString object is constructed and initialized with a C string", "[util::type::StaticString]")
{
  char const TEST_C_STRING[] = "This is a test C string";

  StaticString str(TEST_C_STRING);

  THEN("length() should return the length of the test C string")
  {
    REQUIRE(str.length() == strlen(TEST_C_STRING));
  }
  THEN("c_str() should return a pointer to the memory containing the string as C string")
  {
    REQUIRE(strcmp(str.c_str(), TEST_C_STRING) == 0);
  }
}

/**************************************************************************************/

SCENARIO("A StaticString object is constructed via copy constructor", "[util::type::StaticString]")
{
  char const TEST_C_STRING[] = "This is a test C string";

  StaticString str_1(TEST_C_STRING),
               str_2(str_1);

  THEN("The length of both strings should be identical")
  {
    REQUIRE(str_1.length() == str_2.length());
  }
  THEN("The content of both strings should be identical")
  {
    REQUIRE(strcmp(str_1.c_str(), str_2.c_str()) == 0);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* type */

} /* util */

} /* spectre */
