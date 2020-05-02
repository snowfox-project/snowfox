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

#include <snowfox/hal/avr/common/ATxxxx/DigitalOutPort.h>

#include <vireg/VirtualRegister.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATxxxx::test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A ATxxxx::DigitalOutPort object is constructed", "[ATxxxx::DigitalOutPort]")
{
  vireg::VirtualRegister<uint8_t> DDR(0b00000000, "DDR"),
                                  OUT(0b00000000, "OUT");

  ATxxxx::DigitalOutPort out_port(DDR.ptr(), OUT.ptr());


  THEN("All DDR bits should be set") { REQUIRE(DDR == 0b11111111); }
  THEN("All OUT bits should be clr") { REQUIRE(OUT == 0b00000000); }

  WHEN("'set' is called with a specific parameter") {
    out_port.set(0b10101100);
    THEN("the OUT register should contain the value of the parameter of the 'set' function") {
      REQUIRE(OUT == 0b10101100);
    }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATxxxx::test */
