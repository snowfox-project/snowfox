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

#include <Register.h>

#include <spectre/hal/avr/common/ATxxxx/DigitalInPort.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
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
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000),
                    PIN(0b00000000);


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
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000),
                    PIN(0b00000000);


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
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000),
                    PIN(0b10110011);


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

} /* spectre */
