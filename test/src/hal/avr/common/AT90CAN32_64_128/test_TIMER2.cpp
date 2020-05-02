/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/hal/avr/common/AT90CAN32_64_128/TIMER2.h>

#include <vireg/VirtualRegister.hpp>
#include <vireg/VirtualRegisterLoader.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::AT90CAN32_64_128::test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER2 - A valid prescaler value is set via 'setPrescaler'", "[AT90CAN32_64_128::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/AT90CAN32_64_128.json");

  vireg::Vireg8 TCNT2  = vregmap.get<vireg::Vireg8>("TCNT2" );
  vireg::Vireg8 TCCR2A = vregmap.get<vireg::Vireg8>("TCCR2A");
  vireg::Vireg8 OCR2A  = vregmap.get<vireg::Vireg8>("OCR2A" );

  AT90CAN32_64_128::TIMER2 timer2(TCNT2->ptr(), TCCR2A->ptr(), OCR2A->ptr());


  std::vector<uint32_t> const VALID_PRESCALER_VECT = {0, 1, 8, 64, 256, 1024};

  std::for_each(
      std::begin(VALID_PRESCALER_VECT),
      std::end  (VALID_PRESCALER_VECT),
      [&timer2, &TCCR2A](uint32_t const prescaler)
      {
        std::stringstream when_msg;
        when_msg << "The prescaler is configured via calling 'setPrescaler' with an argument of '" << prescaler << "'";

        WHEN(when_msg.str())
        {
          timer2.setPrescaler(prescaler);
          WHEN("'start' is called")
          {
            timer2.start();

            switch(prescaler)
            {
            case 0    : THEN("TCCR2A bits 2-0 == 0b000") REQUIRE(TCCR2A->isBitVectSet({     })); break;
            case 1    : THEN("TCCR2A bits 2-0 == 0b001") REQUIRE(TCCR2A->isBitVectSet({    0})); break;
            case 8    : THEN("TCCR2A bits 2-0 == 0b010") REQUIRE(TCCR2A->isBitVectSet({  1  })); break;
            case 32   : THEN("TCCR2A bits 2-0 == 0b011") REQUIRE(TCCR2A->isBitVectSet({  1,0})); break;
            case 64   : THEN("TCCR2A bits 2-0 == 0b100") REQUIRE(TCCR2A->isBitVectSet({2    })); break;
            case 128  : THEN("TCCR2A bits 2-0 == 0b101") REQUIRE(TCCR2A->isBitVectSet({2,  0})); break;
            case 256  : THEN("TCCR2A bits 2-0 == 0b110") REQUIRE(TCCR2A->isBitVectSet({2,1  })); break;
            case 1024 : THEN("TCCR2A bits 2-0 == 0b1!1") REQUIRE(TCCR2A->isBitVectSet({2,1,0})); break;
            }
          }
          WHEN("'start' is not called")
          {
            THEN("TCCR2A bits 2-0 == 0b000") REQUIRE(*TCCR2A == 0x00);
          }
        }
      });
}

/**************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER2 - A invalid prescaler value is set via 'setPrescaler'", "[AT90CAN32_64_128::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/AT90CAN32_64_128.json");

  vireg::Vireg8 TCNT2  = vregmap.get<vireg::Vireg8>("TCNT2" );
  vireg::Vireg8 TCCR2A = vregmap.get<vireg::Vireg8>("TCCR2A");
  vireg::Vireg8 OCR2A  = vregmap.get<vireg::Vireg8>("OCR2A" );

  AT90CAN32_64_128::TIMER2 timer2(TCNT2->ptr(), TCCR2A->ptr(), OCR2A->ptr());


  uint32_t INVALID_PRESCALER = 2;

  WHEN("The prescaler is configured via calling 'setPrescaler' with an argument of '2'")
  {
    timer2.setPrescaler(INVALID_PRESCALER);
    WHEN("'start' is called")
    {
      timer2.start();
      THEN("TCCR2A bits 2-0 == 0b000 (Reset Value)") REQUIRE(*TCCR2A == 0x00);
    }
    WHEN("'start' is not called")
    {
      THEN("TCCR2A bits 2-0 == 0b000 (Reset Value)") REQUIRE(*TCCR2A == 0x00);
    }
  }
}

/**************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER2 - A timer is started ('start') and stopped ('stop')", "[ATMEGA328P::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/AT90CAN32_64_128.json");

  vireg::Vireg8 TCNT2  = vregmap.get<vireg::Vireg8>("TCNT2" );
  vireg::Vireg8 TCCR2A = vregmap.get<vireg::Vireg8>("TCCR2A");
  vireg::Vireg8 OCR2A  = vregmap.get<vireg::Vireg8>("OCR2A" );

  AT90CAN32_64_128::TIMER2 timer2(TCNT2->ptr(), TCCR2A->ptr(), OCR2A->ptr());


  uint32_t const prescaler = 8;

  timer2.setPrescaler(prescaler);

  WHEN("'start' is called")
  {
    timer2.start();
    THEN("TCCR2A contains the expected prescaler bit pattern") REQUIRE(TCCR2A->isBitVectSet({1}));
    WHEN("'stop' is called")
    {
      timer2.stop();
      THEN("TCCR2A contains the RESET prescaler bit pattern") REQUIRE(*TCCR2A == 0x00);
      WHEN("'start' is called (again)")
      {
        timer2.start();
        THEN("TCCR2A contains the expected prescaler bit pattern (again)") REQUIRE(TCCR2A->isBitVectSet({1}));
      }
    }
  }
}

/**************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER2 - A timer's counter register is read ('get') and written ('set')", "[AT90CAN32_64_128::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/AT90CAN32_64_128.json");

  vireg::Vireg8 TCNT2  = vregmap.get<vireg::Vireg8>("TCNT2" );
  vireg::Vireg8 TCCR2A = vregmap.get<vireg::Vireg8>("TCCR2A");
  vireg::Vireg8 OCR2A  = vregmap.get<vireg::Vireg8>("OCR2A" );

  AT90CAN32_64_128::TIMER2 timer2(TCNT2->ptr(), TCCR2A->ptr(), OCR2A->ptr());


  WHEN("the counter register is read via 'get'")
  {
    *TCNT2 = 0xCA;
    THEN("the current value should be returned")
    {
      REQUIRE(timer2.get() == 0xCA);
    }
  }
  WHEN("the counter register is written via 'set'")
  {
    timer2.set(0xFF);
    THEN("TCNT2 should contain the written value")
    {
      REQUIRE(*TCNT2 == 0xFF);
    }
  }
}

/**************************************************************************************/

SCENARIO("AT90CAN32_64_128::TIMER2 - A timer's compare register are written via 'setCompareRegister'", "[AT90CAN32_64_128::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/AT90CAN32_64_128.json");

  vireg::Vireg8 TCNT2  = vregmap.get<vireg::Vireg8>("TCNT2" );
  vireg::Vireg8 TCCR2A = vregmap.get<vireg::Vireg8>("TCCR2A");
  vireg::Vireg8 OCR2A  = vregmap.get<vireg::Vireg8>("OCR2A" );

  AT90CAN32_64_128::TIMER2 timer2(TCNT2->ptr(), TCCR2A->ptr(), OCR2A->ptr());


  WHEN("compare register A is written via 'setCompareRegister'")
  {
    timer2.setCompareRegister(TIMER2::COMPARE_A, 0xCA);
    THEN("OCR2A should contain the written value")
    {
      REQUIRE(*OCR2A == 0xCA);
    }
  }
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* snowfox::hal::AT90CAN32_64_128::test */
