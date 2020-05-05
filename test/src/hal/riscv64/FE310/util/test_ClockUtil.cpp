/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

namespace snowfox::hal::FE310::test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A FE310::ClockUtil module function 'findPllParam' is tested", "[FE310::ClockUtil::findPllParam]")
{
  WHEN("pllref_Hz = 16MHz and pllout_Hz = 200MHz") {
    uint8_t r = 0, f = 0, q = 0;
    THEN("'findPllParam' should return true") {
      REQUIRE(findPllParam(16000000UL, 200000000UL, r, f, q) == true);

      THEN("R should be 2")  REQUIRE(r == 2);
      THEN("F should be 50") REQUIRE(f == 50);
      THEN("Q should be 2")  REQUIRE(q == 2);
    } 
  }
}

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
      WHEN("'pllr' != 1,2,3,4")
        THEN("'isValidPLLR' should return false")
          REQUIRE(isValidPLLR(static_cast<uint8_t>(pllr)) == false);
  }
}

SCENARIO("A FE310::ClockUtil module function 'isValidPLLF' is tested", "[FE310::ClockUtil::isValidPLLF]")
{
  for(uint16_t pllf = 0; pllf < 256; pllf++)
  {
    if(pllf < 1 || pllf > 129)
      WHEN("'pllf' < 1 || 'pllf' > 129")
        THEN("'isValidPLLF' should return false")
          REQUIRE(isValidPLLF(static_cast<uint8_t>(pllf)) == false);
    else
      WHEN("'pllf' > 1 && 'pllf' < 129")
        THEN("'isValidPLLF' should return true")
          REQUIRE(isValidPLLF(static_cast<uint8_t>(pllf)) == true);
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
      WHEN("'pllq' != 2,4,8")
        THEN("'isValidPLLQ' should return false")
          REQUIRE(isValidPLLQ(static_cast<uint8_t>(pllq)) == false);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310::test */
