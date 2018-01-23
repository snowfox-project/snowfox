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

#include <spectre/hal/avr/AT90CAN128/TIMER0.h>

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

SCENARIO("AT90CAN128::TIMER0 - A timer's prescaler is manipulated via 'setPrescaler'", "[AT90CAN128::TIMER0]")
{
  Register<uint8_t> TCNT0 (TCNT0_RESET_VALUE ),
                    TCCR0A(TCCR0A_RESET_VALUE),
                    OCR0A (OCR0A_RESET_VALUE );

  AT90CAN128::TIMER0 timer0(TCNT0(), TCCR0A(), OCR0A());

  /* TODO */

}

/**************************************************************************************/

SCENARIO("AT90CAN128::TIMER0 - A timer's counter register is read ('get') and written ('set')", "[AT90CAN128::TIMER0]")
{
  Register<uint8_t> TCNT0 (TCNT0_RESET_VALUE ),
                    TCCR0A(TCCR0A_RESET_VALUE),
                    OCR0A (OCR0A_RESET_VALUE );

  AT90CAN128::TIMER0 timer0(TCNT0(), TCCR0A(), OCR0A());

  WHEN("the counter register is read via 'get'")
  {
    TCNT0 = 0xCA;
    THEN("the current value should be returned")
    {
      REQUIRE(timer0.get() == 0xCA);
    }
  }
  WHEN("the counter register is written via 'set'")
  {
    timer0.set(0xFF);
    THEN("TCNT0 should contain the written value")
    {
      REQUIRE(TCNT0 == 0xFF);
    }
  }
}

/**************************************************************************************/

SCENARIO("AT90CAN128::TIMER0 - A timer's compare register are written via 'setCompareRegister'", "[AT90CAN128::TIMER0]")
{
  Register<uint8_t> TCNT0 (TCNT0_RESET_VALUE ),
                    TCCR0A(TCCR0A_RESET_VALUE),
                    OCR0A (OCR0A_RESET_VALUE );

  AT90CAN128::TIMER0 timer0(TCNT0(), TCCR0A(), OCR0A());

  WHEN("compare register A is written via 'setCompareRegister'")
  {
    timer0.setCompareRegister(TIMER0::COMPARE_A, 0xCA);
    THEN("OCR0A should contain the written value")
    {
      REQUIRE(OCR0A == 0xCA);
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
