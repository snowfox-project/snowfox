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

#include <sstream>
#include <algorithm>

#include <catch2/catch.hpp>

#include <hal/avr/common/AT90CAN32_64_128/RegisterResetValueList.h>

#include <snowfox/hal/avr/common/AT90CAN32_64_128/TIMER3.h>
#include "../../../../../vireg/include/vireg/VirtualRegister.hpp"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace AT90CAN32_64_128
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER3 - A valid prescaler value is set via 'setPrescaler'", "[AT90CAN32_64_128::TIMER3]")
{
  vireg::VirtualRegister<uint16_t> TCNT3 (TCNT3_RESET_VALUE,  "TCNT3" );
  vireg::VirtualRegister<uint8_t>  TCCR3B(TCCR3B_RESET_VALUE, "TCCR3B");
  vireg::VirtualRegister<uint16_t> OCR3A (OCR3A_RESET_VALUE,  "OCR3A" ),
                     OCR3B (OCR3B_RESET_VALUE,  "OCR3B" ),
                     OCR3C (OCR3C_RESET_VALUE,  "OCR3C" );

  AT90CAN32_64_128::TIMER3 timer3(TCNT3.ptr(), TCCR3B.ptr(), OCR3A.ptr(), OCR3B.ptr(), OCR3C.ptr());

  std::vector<uint32_t> const VALID_PRESCALER_VECT = {0, 1, 8, 64, 256, 1024};

  std::for_each(
      std::begin(VALID_PRESCALER_VECT),
      std::end  (VALID_PRESCALER_VECT),
      [&timer3, &TCCR3B](uint32_t const prescaler)
      {
        std::stringstream when_msg;
        when_msg << "The prescaler is configured via calling 'setPrescaler' with an argument of '" << prescaler << "'";

        WHEN(when_msg.str())
        {
          timer3.setPrescaler(prescaler);
          WHEN("'start' is called")
          {
            timer3.start();

            switch(prescaler)
            {
            case 0    : THEN("TCCR3B bits 2-0 == 0b000") REQUIRE(TCCR3B.isBitVectSet({     })); break;
            case 1    : THEN("TCCR3B bits 2-0 == 0b001") REQUIRE(TCCR3B.isBitVectSet({    0})); break;
            case 8    : THEN("TCCR3B bits 2-0 == 0b010") REQUIRE(TCCR3B.isBitVectSet({  1  })); break;
            case 64   : THEN("TCCR3B bits 2-0 == 0b011") REQUIRE(TCCR3B.isBitVectSet({  1,0})); break;
            case 256  : THEN("TCCR3B bits 2-0 == 0b100") REQUIRE(TCCR3B.isBitVectSet({2    })); break;
            case 1024 : THEN("TCCR3B bits 2-0 == 0b101") REQUIRE(TCCR3B.isBitVectSet({2,  0})); break;
            }
          }
          WHEN("'start' is not called")
          {
            THEN("TCCR3B bits 2-0 == 0b000") REQUIRE(TCCR3B == TCCR3B_RESET_VALUE);
          }
        }
      });
}

/**************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER3 - A invalid prescaler value is set via 'setPrescaler'", "[AT90CAN32_64_128::TIMER3]")
{
  vireg::VirtualRegister<uint16_t> TCNT3 (TCNT3_RESET_VALUE,  "TCNT3" );
  vireg::VirtualRegister<uint8_t>  TCCR3B(TCCR3B_RESET_VALUE, "TCCR3B");
  vireg::VirtualRegister<uint16_t> OCR3A (OCR3A_RESET_VALUE,  "OCR3A" ),
                     OCR3B (OCR3B_RESET_VALUE,  "OCR3B" ),
                     OCR3C (OCR3C_RESET_VALUE,  "OCR3C" );

  AT90CAN32_64_128::TIMER3 timer3(TCNT3.ptr(), TCCR3B.ptr(), OCR3A.ptr(), OCR3B.ptr(), OCR3C.ptr());

  uint32_t INVALID_PRESCALER = 2;

  WHEN("The prescaler is configured via calling 'setPrescaler' with an argument of '2'")
  {
    timer3.setPrescaler(INVALID_PRESCALER);
    WHEN("'start' is called")
    {
      timer3.start();
      THEN("TCCR3B bits 2-0 == 0b000 (Reset Value)") REQUIRE(TCCR3B == TCCR3B_RESET_VALUE);
    }
    WHEN("'start' is not called")
    {
      THEN("TCCR3B bits 2-0 == 0b000 (Reset Value)") REQUIRE(TCCR3B == TCCR3B_RESET_VALUE);
    }
  }
}

/**************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER3 - A timer is started ('start') and stopped ('stop')", "[AT90CAN32_64_128::TIMER3]")
{
  vireg::VirtualRegister<uint16_t> TCNT3 (TCNT3_RESET_VALUE,  "TCNT3" );
  vireg::VirtualRegister<uint8_t>  TCCR3B(TCCR3B_RESET_VALUE, "TCCR3B");
  vireg::VirtualRegister<uint16_t> OCR3A (OCR3A_RESET_VALUE,  "OCR3A" ),
                     OCR3B (OCR3B_RESET_VALUE,  "OCR3B" ),
                     OCR3C (OCR3C_RESET_VALUE,  "OCR3C" );

  uint32_t const prescaler = 8;

  AT90CAN32_64_128::TIMER3 timer3(TCNT3.ptr(), TCCR3B.ptr(), OCR3A.ptr(), OCR3B.ptr(), OCR3C.ptr());

  timer3.setPrescaler(prescaler);

  WHEN("'start' is called")
  {
    timer3.start();
    THEN("TCCR3B contains the expected prescaler bit pattern") REQUIRE(TCCR3B.isBitVectSet({1}));
    WHEN("'stop' is called")
    {
      timer3.stop();
      THEN("TCCR3B contains the RESET prescaler bit pattern") REQUIRE(TCCR3B == TCCR3B_RESET_VALUE);
      WHEN("'start' is called (again)")
      {
        timer3.start();
        THEN("TCCR3B contains the expected prescaler bit pattern (again)") REQUIRE(TCCR3B.isBitVectSet({1}));
      }
    }
  }
}

/**************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER3 - A timer's counter register is read ('get') and written ('set')", "[AT90CAN32_64_128::TIMER3]")
{
  vireg::VirtualRegister<uint16_t> TCNT3 (TCNT3_RESET_VALUE,  "TCNT3" );
  vireg::VirtualRegister<uint8_t>  TCCR3B(TCCR3B_RESET_VALUE, "TCCR3B");
  vireg::VirtualRegister<uint16_t> OCR3A (OCR3A_RESET_VALUE,  "OCR3A" ),
                     OCR3B (OCR3B_RESET_VALUE,  "OCR3B" ),
                     OCR3C (OCR3C_RESET_VALUE,  "OCR3C" );

  AT90CAN32_64_128::TIMER3 timer3(TCNT3.ptr(), TCCR3B.ptr(), OCR3A.ptr(), OCR3B.ptr(), OCR3C.ptr());

  WHEN("the counter register is read via 'get'")
  {
    TCNT3 = 0xCAFF;
    THEN("the current value should be returned")
    {
      REQUIRE(timer3.get() == 0xCAFF);
    }
  }
  WHEN("the counter register is written via 'set'")
  {
    timer3.set(0xFFEE);
    THEN("TCNT3 should contain the written value")
    {
      REQUIRE(TCNT3 == 0xFFEE);
    }
  }
}

/**************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER3 - A timer's compare register are written via 'setCompareRegister'", "[AT90CAN32_64_128::TIMER3]")
{
  vireg::VirtualRegister<uint16_t> TCNT3 (TCNT3_RESET_VALUE,  "TCNT3" );
  vireg::VirtualRegister<uint8_t>  TCCR3B(TCCR3B_RESET_VALUE, "TCCR3B");
  vireg::VirtualRegister<uint16_t> OCR3A (OCR3A_RESET_VALUE,  "OCR3A" ),
                     OCR3B (OCR3B_RESET_VALUE,  "OCR3B" ),
                     OCR3C (OCR3C_RESET_VALUE,  "OCR3C" );

  AT90CAN32_64_128::TIMER3 timer3(TCNT3.ptr(), TCCR3B.ptr(), OCR3A.ptr(), OCR3B.ptr(), OCR3C.ptr());

  WHEN("compare register A is written via 'setCompareRegister'")
  {
    timer3.setCompareRegister(TIMER3::COMPARE_A, 0xCA);
    THEN("OCR0A should contain the written value")
    {
      REQUIRE(OCR3A == 0xCA);
    }
  }
  WHEN("compare register B is written via 'setCompareRegister'")
  {
    timer3.setCompareRegister(TIMER3::COMPARE_B, 0xFF);
    THEN("OCR0B should contain the written value")
    {
      REQUIRE(OCR3B == 0xFF);
    }
  }
  WHEN("compare register C is written via 'setCompareRegister'")
  {
    timer3.setCompareRegister(TIMER3::COMPARE_C, 0xEE);
    THEN("OCR0C should contain the written value")
    {
      REQUIRE(OCR3C == 0xEE);
    }
  }
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* AT90CAN32_64_128 */

} /* hal */

} /* snowfox */
