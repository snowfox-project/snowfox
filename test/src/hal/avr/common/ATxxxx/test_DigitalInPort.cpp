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

#include <snowfox/hal/avr/common/ATxxxx/DigitalInPort.h>

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

SCENARIO("A ATxxxx::DigitalInPort object is constructed", "[ATxxxx::DigitalInPort]")
{
  vireg::VirtualRegister<uint8_t> DDR(0b00000000, "DDR"),
                                  OUT(0b00000000, "OUT"),
                                  PIN(0b00000000, "PIN");

  ATxxxx::DigitalInPort in_port(DDR.ptr(), OUT.ptr(), PIN.ptr());


  THEN("All DDR bits should be clr") { REQUIRE(DDR == 0b00000000); }
  THEN("All OUT bits should be clr") { REQUIRE(OUT == 0b00000000); }
  THEN("All PIN bits should be clr") { REQUIRE(PIN == 0b00000000); }


  THEN("in_port.setPullUpMode(interface::PullUpMode::NONE) should be true"      ) { REQUIRE(in_port.setPullUpMode(interface::PullUpMode::NONE)      == true ); }
  THEN("in_port.setPullUpMode(interface::PullUpMode::PULL_UP) should be true"   ) { REQUIRE(in_port.setPullUpMode(interface::PullUpMode::PULL_UP)   == true ); }
  THEN("in_port.setPullUpMode(interface::PullUpMode::PULL_DOWN) should be false") { REQUIRE(in_port.setPullUpMode(interface::PullUpMode::PULL_DOWN) == false); }


  WHEN("interface::PullUpMode::NONE is selected") {
    in_port.setPullUpMode(interface::PullUpMode::NONE);
    THEN("All OUT bits should be clr") { 
      REQUIRE(OUT == 0b00000000); 
    }
  }
  WHEN("interface::PullUpMode::PULL_UP is selected") {
    in_port.setPullUpMode(interface::PullUpMode::PULL_UP);
    THEN("All OUT bits should be set") { 
      REQUIRE(OUT == 0b11111111); 
    }
  }
  WHEN("interface::PullUpMode::PULL_DOWN is selected") {
    in_port.setPullUpMode(interface::PullUpMode::PULL_DOWN);
    THEN("All OUT bits should be clr") { 
      REQUIRE(OUT == 0b00000000); 
    }
  }

  WHEN("the current value of the PIN register is read via 'get'") { 
    PIN = 0b10110011;
    THEN("the returned value should be equal with the current content of the PIN register") {
      REQUIRE(in_port.get() == 0b10110011);
    }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* ATxxxx */

} /* hal */

} /* snowfox */
