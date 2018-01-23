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
#include <hal/avr/AT90CAN128/RegisterResetValueList.h>

#include <spectre/hal/avr/AT90CAN128/TIMER2.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("AT90CAN128::TIMER2 - A timer's prescaler is manipulated via 'setPrescaler'", "[AT90CAN128::TIMER2]")
{
  Register<uint8_t> TCNT2 (TCNT2_RESET_VALUE ),
                    TCCR2A(TCCR2A_RESET_VALUE),
                    OCR2A (OCR2A_RESET_VALUE );

  AT90CAN128::TIMER2 timer2(TCNT2(), TCCR2A(), OCR2A());

  /* TODO */

}

/**************************************************************************************/

SCENARIO("AT90CAN128::TIMER2 - A timer's compare register are written via 'setCompareRegister'", "[AT90CAN128::TIMER2]")
{
  Register<uint8_t> TCNT2 (TCNT2_RESET_VALUE ),
                    TCCR2A(TCCR2A_RESET_VALUE),
                    OCR2A (OCR2A_RESET_VALUE );

  AT90CAN128::TIMER2 timer2(TCNT2(), TCCR2A(), OCR2A());

  WHEN("compare register A is written via 'setCompareRegister'")
  {
    timer2.setCompareRegister(TIMER2::COMPARE_A, 0xCA);
    THEN("OCR2A should contain the written value")
    {
      REQUIRE(OCR2A == 0xCA);
    }
  }
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* AT90CAN128 */

} /* hal */

} /* spectre */
