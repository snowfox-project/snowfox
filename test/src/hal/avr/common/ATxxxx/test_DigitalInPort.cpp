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
#include "../../../../../vireg/include/vireg/VirtualRegister.hpp"

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

/**************************************************************************************/

SCENARIO("A DigitalInPort object is constructed", "[ATxxxx::DigitalInPort]")
{
  vireg::VirtualRegister<uint8_t> DDR(0b00000000, "DDR"),
                    OUT(0b00000000, "OUT"),
                    PIN(0b00000000, "PIN");


  ATxxxx::DigitalInPort in_port(DDR(), OUT(), PIN());

  WHEN("the object is newly constructed")
  {
    THEN("all bits in DDR should be clr")
    {
      REQUIRE(DDR == 0b00000000);
    }
    THEN("all bits in OUT should be clr")
    {
      REQUIRE(OUT == 0b00000000);
    }
    THEN("all bits in PIN should be clr")
    {
      REQUIRE(PIN == 0b00000000);
    }
  }
}

/**************************************************************************************/

SCENARIO("A DigitalInPort interface::PullUpMode is manipulated", "[ATxxxx::DigitalInPort]")
{
  vireg::VirtualRegister<uint8_t> DDR(0b00000000, "DDR"),
                    OUT(0b00000000, "OUT"),
                    PIN(0b00000000, "PIN");


  ATxxxx::DigitalInPort in_port(DDR(), OUT(), PIN());

  WHEN("interface::PullUpMode 'NONE' is selected")
  {
    in_port.setPullUpMode(interface::PullUpMode::NONE);

    THEN("all bits in OUT should be clr")
    {
      REQUIRE(OUT == 0b00000000);
    }
  }
  WHEN("interface::PullUpMode 'PULL_UP' is selected")
  {
    in_port.setPullUpMode(interface::PullUpMode::PULL_UP);

    THEN("all bits in OUT should be set")
    {
      REQUIRE(OUT == 0b11111111);
    }
  }
  WHEN("interface::PullUpMode 'NONE' is selected")
  {
    in_port.setPullUpMode(interface::PullUpMode::PULL_DOWN);

    THEN("all bits in OUT should be (still) clr - ATMega does not support pull downs")
    {
      REQUIRE(OUT == 0b00000000);
    }
  }
}

/**************************************************************************************/

SCENARIO("A DigitalInPort value is read", "[ATxxxx::DigitalInPort]")
{
  vireg::VirtualRegister<uint8_t> DDR(0b00000000, "DDR"),
                    OUT(0b00000000, "OUT"),
                    PIN(0b10110011, "PIN");


  ATxxxx::DigitalInPort in_port(DDR(), OUT(), PIN());

  WHEN("the current value of the PIN register is read via 'get'")
  {
    THEN("the returned value should be equal with the current content of the PIN register")
    {
      REQUIRE(PIN == in_port.get());
    }
  }
}

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

} /* test */

} /* ATxxxx */

} /* hal */

} /* snowfox */
