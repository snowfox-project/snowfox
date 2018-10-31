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

#include <Register.h>

#include <spectre/hal/avr/common/ATxxxx/DigitalOutPort.h>

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

SCENARIO("A DigitalOutPort object is constructed", "[ATxxxx::DigitalOutPort]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000);

  ATxxxx::DigitalOutPort out_port(DDR(), OUT());

  WHEN("the object is newly constructed")
  {
    THEN("all bits in DDR should be set")
    {
      REQUIRE(DDR == 0b11111111);
    }
    THEN("all bits in OUT should be clr")
    {
      REQUIRE(OUT == 0b00000000);
    }
  }
}

/**************************************************************************************/

SCENARIO("A DigitalOutPort is manipulated via 'set'", "[ATxxxx::DigitalOutPort]")
{
  Register<uint8_t> DDR(0b00000000),
                    OUT(0b00000000);

  ATxxxx::DigitalOutPort out_port(DDR(), OUT());

  WHEN("'set' is called with a specific parameter")
  {
    out_port.set(0b10101100);

    THEN("the OUT register should take the value of the parameter of the 'set' function")
    {
      REQUIRE(OUT == 0b10101100);
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
