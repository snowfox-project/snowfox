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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <catch.hpp>

#include <spectre/memory/container/List.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace memory
{

namespace container
{

namespace test
{

/**************************************************************************************/

SCENARIO(" ... description of the scenario ...", "[memory::container::List]")
{
  List<uint8_t> list;

  THEN("list.begin() should return 0")
  {
    REQUIRE(list.begin() == 0);
  }
  THEN("list.end() should return 0")
  {
    REQUIRE(list.end() == 0);
  }
  THEN("next(list.begin()) should return 0")
  {
    REQUIRE(next(list.begin()) == 0);
  }
  THEN("prev(list.begin()) should return 0")
  {
    REQUIRE(prev(list.begin()) == 0);
  }
}

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

} /* test */

} /* container */

} /* memory */

} /* spectre */
