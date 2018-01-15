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

#include <spectre/hal/avr/ATxxxx/DigitalOutPin.h>

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

SCENARIO("A DigitalOutPin object is constructed for pin number #0", "[ATxxxx::DigitalOutPin]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000);

  ATxxxx::DigitalOutPin out_pin(DDR(), OUT(), 0);

  WHEN("the object is newly constructed")
  {
    THEN("bit #0 in the DDR register should be set")
    {
      REQUIRE(DDR.isBitSet(0));
    }
    THEN("all other bits in the DDR register should be unchanged")
    {
      REQUIRE(DDR.isBitClr(1));
      REQUIRE(DDR.isBitClr(2));
      REQUIRE(DDR.isBitClr(3));
      REQUIRE(DDR.isBitClr(4));
      REQUIRE(DDR.isBitClr(5));
      REQUIRE(DDR.isBitClr(6));
      REQUIRE(DDR.isBitClr(7));
    }
    THEN("OUT should not change at all during this operation")
    {
      REQUIRE(OUT == 0b00000000);
    }
  }
  WHEN("'set' is called")
  {
    out_pin.set();

    THEN("the corresponding bit in the OUT register should be set")
    {
      REQUIRE(OUT.isBitSet(0));
    }
  }
  WHEN("'clr' is called")
  {
    THEN("the corresponding bit in the OUT register should be clr")
    {
      REQUIRE(OUT.isBitClr(0));
    }
  }
}

/**************************************************************************************/

SCENARIO("A 'clr' DigitalOutPin is manipulated via 'set' and 'clr'", "[ATxxxx::DigitalOutPin]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000);

  ATxxxx::DigitalOutPin out_pin(DDR(), OUT(), 0);

  out_pin.clr();

  WHEN("'set' is called")
  {
    out_pin.set();

    THEN("the corresponding bit in the OUT register should be set")
    {
      REQUIRE(OUT.isBitSet(0));
    }
  }

  WHEN("'clr' is called")
  {
    out_pin.clr();

    THEN("the corresponding bit in the OUT register should not be set")
    {
      REQUIRE(OUT.isBitClr(0));
    }
  }
}

/**************************************************************************************/

SCENARIO("A 'set' DigitalOutPin is manipulated via 'set' and 'clr'", "[ATxxxx::DigitalOutPin]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000);

  ATxxxx::DigitalOutPin out_pin(DDR(), OUT(), 0);

  out_pin.set();

  WHEN("'set' is called")
  {
    out_pin.set();

    THEN("the corresponding bit in the OUT register should be set")
    {
      REQUIRE(OUT.isBitSet(0));
    }
  }

  WHEN("'clr' is called")
  {
    out_pin.clr();

    THEN("the corresponding bit in the OUT register should not be set")
    {
      REQUIRE(OUT.isBitClr(0));
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
