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

#include <snowfox/hal/avr/common/ATxxxx/DigitalOutPin.h>

#include <vireg/VirtualRegister.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATxxxx::test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A ATxxxx::DigitalOutPin (Pin number #0) object is constructed", "[ATxxxx::DigitalOutPin]")
{
  vireg::VirtualRegister<uint8_t> DDR(0b00000000, "DDR"),
                                  OUT(0b00000000, "OUT");

  ATxxxx::DigitalOutPin out_pin(DDR.ptr(), OUT.ptr(), 0);


  THEN("DDR bit #0 should be set") { REQUIRE(DDR.isBitSet(0)); }
  THEN("OUT bit #0 should be clr") { REQUIRE(OUT.isBitClr(0)); }

  WHEN("'set' is called") {
    out_pin.set();
    THEN("OUT bit #0 should be set") { 
      REQUIRE(OUT.isBitSet(0));
      WHEN("'clr' is called") {
        out_pin.clr();
        THEN("OUT bit #0 should be clr") { 
          REQUIRE(OUT.isBitClr(0));
        }
      }
    }
  }

  WHEN("'clr' is called") {
    out_pin.clr();
    THEN("OUT bit #0 should be clr") { 
      REQUIRE(OUT.isBitClr(0));
      WHEN("'set' is called") {
        out_pin.set();
        THEN("OUT bit #0 should be set") { 
          REQUIRE(OUT.isBitSet(0));
        }
      }
    }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATxxxx::test */
