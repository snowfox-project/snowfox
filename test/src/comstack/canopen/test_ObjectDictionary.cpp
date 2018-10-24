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

#include <catch.hpp>

#include <spectre/comstack/canopen/ObjectDictionary.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace comstack
{

namespace canopen
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A ObjectDictionary object is constructed", "[comstack::canopen::ObjectDictionary]")
{
  ObjectDictionary obj_dict;

  WHEN("No entries have been added yet")
  {
    THEN("When requesting a UINT8 entry a empty entry object should be returned" ) { REQUIRE(obj_dict.isEmpty(obj_dict.get_UINT8 (0x0001, 0x01)) == true); }
    THEN("When requesting a UINT32 entry a empty entry object should be returned") { REQUIRE(obj_dict.isEmpty(obj_dict.get_UINT32(0x0001, 0x01)) == true); }
    THEN("When requesting a STRING entry a empty entry object should be returned") { REQUIRE(obj_dict.isEmpty(obj_dict.get_STRING(0x0001, 0x01)) == true); }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* canopen */

} /* comstack */

} /* spectre */
