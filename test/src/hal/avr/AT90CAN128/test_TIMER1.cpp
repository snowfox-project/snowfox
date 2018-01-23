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

#include <sstream>
#include <algorithm>

#include <catch.hpp>

#include <Register.h>
#include <hal/avr/AT90CAN128/RegisterResetValueList.h>

#include <spectre/hal/avr/AT90CAN128/TIMER1.h>

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

SCENARIO("AT90CAN128::TIMER1 - A timer's prescaler is manipulated via 'setPrescaler'", "[AT90CAN128::TIMER1]")
{
  Register<uint16_t> TCNT1 (TCNT1_RESET_VALUE );
  Register<uint8_t>  TCCR1B(TCCR1B_RESET_VALUE);
  Register<uint16_t> OCR1A (OCR1A_RESET_VALUE ),
                     OCR1B (OCR1B_RESET_VALUE ),
                     OCR1C (OCR1C_RESET_VALUE );

  AT90CAN128::TIMER1 timer1(TCNT1(), TCCR1B(), OCR1A(), OCR1B(), OCR1C());

  std::vector<uint32_t> const VALID_PRESCALER_VECT = {0, 1, 8, 64, 256, 1024};

  std::for_each(
      std::begin(VALID_PRESCALER_VECT),
      std::end  (VALID_PRESCALER_VECT),
      [&timer1, &TCCR1B](uint32_t const prescaler)
      {
        std::stringstream when_msg;
        when_msg << "The prescaler is configured via calling 'setPrescaler' with an argument of '" << prescaler << "'";

        WHEN(when_msg.str())
        {
          timer1.setPrescaler(prescaler);
          WHEN("'start' is called")
          {
            timer1.start();

            switch(prescaler)
            {
            case 0    : THEN("TCCR1B bits 2-0 == 0b000") REQUIRE(TCCR1B.isBitVectSet({     })); break;
            case 1    : THEN("TCCR1B bits 2-0 == 0b001") REQUIRE(TCCR1B.isBitVectSet({    0})); break;
            case 8    : THEN("TCCR1B bits 2-0 == 0b010") REQUIRE(TCCR1B.isBitVectSet({  1  })); break;
            case 64   : THEN("TCCR1B bits 2-0 == 0b011") REQUIRE(TCCR1B.isBitVectSet({  1,0})); break;
            case 256  : THEN("TCCR1B bits 2-0 == 0b100") REQUIRE(TCCR1B.isBitVectSet({2    })); break;
            case 1024 : THEN("TCCR1B bits 2-0 == 0b101") REQUIRE(TCCR1B.isBitVectSet({2,  0})); break;
            }
          }
          WHEN("'start' is not called")
          {
            THEN("TCCR1B bits 2-0 == 0b000") REQUIRE(TCCR1B == TCCR1B_RESET_VALUE);
          }
        }
      });
}

/**************************************************************************************/

SCENARIO("AT90CAN128::TIMER1 - A timer's counter register is read ('get') and written ('set')", "[AT90CAN128::TIMER1]")
{
  Register<uint16_t> TCNT1 (TCNT1_RESET_VALUE );
  Register<uint8_t>  TCCR1B(TCCR1B_RESET_VALUE);
  Register<uint16_t> OCR1A (OCR1A_RESET_VALUE ),
                     OCR1B (OCR1B_RESET_VALUE ),
                     OCR1C (OCR1C_RESET_VALUE );

  AT90CAN128::TIMER1 timer1(TCNT1(), TCCR1B(), OCR1A(), OCR1B(), OCR1C());

  WHEN("the counter register is read via 'get'")
  {
    TCNT1 = 0xCAFF;
    THEN("the current value should be returned")
    {
      REQUIRE(timer1.get() == 0xCAFF);
    }
  }
  WHEN("the counter register is written via 'set'")
  {
    timer1.set(0xFFEE);
    THEN("TCNT1 should contain the written value")
    {
      REQUIRE(TCNT1 == 0xFFEE);
    }
  }
}

/**************************************************************************************/

SCENARIO("AT90CAN128::TIMER1 - A timer's compare register are written via 'setCompareRegister'", "[AT90CAN128::TIMER1]")
{
  Register<uint16_t> TCNT1 (TCNT1_RESET_VALUE );
  Register<uint8_t>  TCCR1B(TCCR1B_RESET_VALUE);
  Register<uint16_t> OCR1A (OCR1A_RESET_VALUE ),
                     OCR1B (OCR1B_RESET_VALUE ),
                     OCR1C (OCR1C_RESET_VALUE );

  AT90CAN128::TIMER1 timer1(TCNT1(), TCCR1B(), OCR1A(), OCR1B(), OCR1C());

  WHEN("compare register A is written via 'setCompareRegister'")
  {
    timer1.setCompareRegister(TIMER1::COMPARE_A, 0xCA);
    THEN("OCR0A should contain the written value")
    {
      REQUIRE(OCR1A == 0xCA);
    }
  }
  WHEN("compare register B is written via 'setCompareRegister'")
  {
    timer1.setCompareRegister(TIMER1::COMPARE_B, 0xFF);
    THEN("OCR0B should contain the written value")
    {
      REQUIRE(OCR1B == 0xFF);
    }
  }
  WHEN("compare register C is written via 'setCompareRegister'")
  {
    timer1.setCompareRegister(TIMER1::COMPARE_C, 0xEE);
    THEN("OCR0C should contain the written value")
    {
      REQUIRE(OCR1C == 0xEE);
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
