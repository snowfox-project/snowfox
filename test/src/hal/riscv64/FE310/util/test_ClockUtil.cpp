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

#include <catch2/catch.hpp>

#include <snowfox/hal/riscv64/FE310/util/ClockUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace FE310
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A FE310::ClockUtil module function 'isValidPLLR' is tested", "[FE310::ClockUtil::isValidPLLR]")
{
  /* All valid Inputs */
  WHEN("'pllr' = 1") THEN("'isValidPLLR' should return true") REQUIRE(isValidPLLR(1) == true );
  WHEN("'pllr' = 2") THEN("'isValidPLLR' should return true") REQUIRE(isValidPLLR(2) == true );
  WHEN("'pllr' = 3") THEN("'isValidPLLR' should return true") REQUIRE(isValidPLLR(3) == true );
  WHEN("'pllr' = 4") THEN("'isValidPLLR' should return true") REQUIRE(isValidPLLR(4) == true );
  /* All invalid inputs */
  for(uint16_t pllr = 0; pllr < 256; pllr++)
  {
    if(pllr != 1 || pllr != 2 || pllr != 3 || pllr != 4)
    {
      WHEN("'pllr' != 1,2,3,4")
        THEN("'isValidPLLR' should return false")
          REQUIRE(isValidPLLR(static_cast<uint8_t>(pllr)) == false);
    }
  }
}

SCENARIO("A FE310::ClockUtil module function 'isValidPLLQ' is tested", "[FE310::ClockUtil::isValidPLLQ]")
{
  /* All valid Inputs */
  WHEN("'pllq' = 2") THEN("'isValidPLLQ' should return true") REQUIRE(isValidPLLQ(2) == true );
  WHEN("'pllq' = 4") THEN("'isValidPLLQ' should return true") REQUIRE(isValidPLLQ(4) == true );
  WHEN("'pllq' = 8") THEN("'isValidPLLQ' should return true") REQUIRE(isValidPLLQ(8) == true );
  /* All invalid inputs */
  for(uint16_t pllq = 0; pllq < 256; pllq++)
  {
    if(pllq != 2 || pllq != 4 || pllq != 8)
    {
      WHEN("'pllq' != 2,4,8")
        THEN("'isValidPLLQ' should return false")
          REQUIRE(isValidPLLQ(static_cast<uint8_t>(pllq)) == false);
    }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* FE310 */

} /* hal */

} /* snowfox */
