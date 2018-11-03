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

#include <testutil/hal/Register.hpp>

#include <spectre/hal/avr/common/ATxxxx/DigitalInPin.h>

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

SCENARIO("A DigitalInPin (Pin Number 0) object is constructed", "[ATxxxx::DigitalInPin]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000),
                    PIN(0b00000000);

  ATxxxx::DigitalInPin in_pin(DDR(), OUT(), PIN(), 0);

  WHEN("the object is newly constructed")
  {
    THEN("all bits DDR should be clr")
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

SCENARIO("A DigitalInPin (Pin Number 0) interface::PullUpMode is manipulated", "[ATxxxx::DigitalInPin]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000),
                    PIN(0b00000000);

  ATxxxx::DigitalInPin in_pin(DDR(), OUT(), PIN(), 0);

  WHEN("interface::PullUpMode 'NONE' is selected")
  {
    in_pin.setPullUpMode(interface::PullUpMode::NONE);

    THEN("bit #0 of OUT should be clr")
    {
      REQUIRE(OUT.isBitClr(0));
    }
  }
  WHEN("interface::PullUpMode 'PULL_UP' is selected")
  {
    in_pin.setPullUpMode(interface::PullUpMode::PULL_UP);

    THEN("bit #0 of OUT should be set")
    {
      REQUIRE(OUT.isBitSet(0));
    }
  }
  WHEN("interface::PullUpMode 'NONE' is selected")
  {
    in_pin.setPullUpMode(interface::PullUpMode::PULL_DOWN);

    THEN("bit #0 of OUT should be (still) clr - ATMega does not support pull down")
    {
      REQUIRE(OUT.isBitClr(0));
    }
  }
}

/**************************************************************************************/

SCENARIO("A 'clr' DigitalInPin (Pin Number 0) current value is retrieved vis 'isSet' and 'isClr'", "[ATxxxx::DigitalInPin]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000),
                    PIN(0b00000000);

  ATxxxx::DigitalInPin in_pin(DDR(), OUT(), PIN(), 0);

  WHEN("'isSet' is called")
  {
    THEN("the function call should return false")
    {
      REQUIRE(in_pin.isSet() == false);
    }
  }
  WHEN("'isClr' is called")
  {
    THEN("the function call should return true")
    {
      REQUIRE(in_pin.isClr() == true);
    }
  }
}

/**************************************************************************************/

SCENARIO("A 'set' DigitalInPin (Pin Number 0) current value is retrieved vis 'isSet' and 'isClr'", "[ATxxxx::DigitalInPin]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000),
                    PIN(0b00000001);

  ATxxxx::DigitalInPin in_pin(DDR(), OUT(), PIN(), 0);

  WHEN("'isSet' is called")
  {
    THEN("the function call should return true")
    {
      REQUIRE(in_pin.isSet() == true);
    }
  }
  WHEN("'isClr' is called")
  {
    THEN("the function call should return false")
    {
      REQUIRE(in_pin.isClr() == false);
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
