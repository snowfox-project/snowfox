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

#include <snowfox/hal/avr/common/ATxxxx/DigitalInPin.h>

#include <vireg/VirtualRegister.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATxxxx
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A ATxxxx::DigitalInPin (Pin Number #0) object is constructed", "[ATxxxx::DigitalInPin]")
{
  vireg::VirtualRegister<uint8_t> DDR(0b00000000, "DDR"),
                                  OUT(0b00000000, "OUT"),
                                  PIN(0b00000000, "PIN");

  ATxxxx::DigitalInPin in_pin(DDR.ptr(), OUT.ptr(), PIN.ptr(), 0);


  THEN("DDR bit #0 should be clr") { REQUIRE(DDR.isBitClr(0)); }
  THEN("OUT bit #0 should be clr") { REQUIRE(OUT.isBitClr(0)); }
  THEN("PIN bit #0 should be clr") { REQUIRE(PIN.isBitClr(0)); }


  THEN("in_pin.setPullUpMode(interface::PullUpMode::NONE) should be true"      ) { REQUIRE(in_pin.setPullUpMode(interface::PullUpMode::NONE)      == true ); }
  THEN("in_pin.setPullUpMode(interface::PullUpMode::PULL_UP) should be true"   ) { REQUIRE(in_pin.setPullUpMode(interface::PullUpMode::PULL_UP)   == true ); }
  THEN("in_pin.setPullUpMode(interface::PullUpMode::PULL_DOWN) should be false") { REQUIRE(in_pin.setPullUpMode(interface::PullUpMode::PULL_DOWN) == false); }


  WHEN("interface::PullUpMode::NONE is selected") {
    in_pin.setPullUpMode(interface::PullUpMode::NONE);
    THEN("OUT bit #0 should be clr") { 
      REQUIRE(OUT.isBitClr(0)); 
    }
  }
  WHEN("interface::PullUpMode::PULL_UP is selected") {
    in_pin.setPullUpMode(interface::PullUpMode::PULL_UP);
    THEN("OUT bit #0 should be set") { 
      REQUIRE(OUT.isBitSet(0)); 
    }
  }
  WHEN("interface::PullUpMode::PULL_DOWN is selected") {
    in_pin.setPullUpMode(interface::PullUpMode::PULL_DOWN);
    THEN("OUT bit #0 should be clr") { 
      REQUIRE(OUT.isBitClr(0)); 
    }
  }

  WHEN("PIN bit #0 is = '0'") {
    PIN.clrBit(0);
    THEN("'isSet' return false") { REQUIRE(in_pin.isSet() == false); }
    THEN("'isClr' return true" ) { REQUIRE(in_pin.isClr() == true ); }
  }

  WHEN("PIN bit #0 is = '1'") {
    PIN.setBit(0);
    THEN("'isSet' return true" ) { REQUIRE(in_pin.isSet() == true ); }
    THEN("'isClr' return false") { REQUIRE(in_pin.isClr() == false); }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* ATxxxx */

} /* hal */

} /* snowfox */
