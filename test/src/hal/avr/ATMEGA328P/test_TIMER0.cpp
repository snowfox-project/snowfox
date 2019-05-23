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

#include <snowfox/hal/avr/ATMEGA328P/TIMER0.h>

#include <vireg/VirtualRegister.hpp>
#include <vireg/VirtualRegisterLoader.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA328P
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("ATMEGA328P::TIMER0 - A valid prescaler value is set via 'setPrescaler'", "[ATMEGA328P::TIMER0]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::Vireg8 TCNT0  = vregmap.get<vireg::Vireg8>("TCNT0" );
  vireg::Vireg8 TCCR0B = vregmap.get<vireg::Vireg8>("TCCR0B");
  vireg::Vireg8 OCR0A  = vregmap.get<vireg::Vireg8>("OCR0A" );
  vireg::Vireg8 OCR0B  = vregmap.get<vireg::Vireg8>("OCR0B" );


  ATMEGA328P::TIMER0 timer0(TCNT0->ptr(), TCCR0B->ptr(), OCR0A->ptr(), OCR0B->ptr());


  std::vector<uint32_t> const VALID_PRESCALER_VECT = {0, 1, 8, 64, 256, 1024};

  std::for_each(
      std::begin(VALID_PRESCALER_VECT),
      std::end  (VALID_PRESCALER_VECT),
      [&timer0, &TCCR0B](uint32_t const prescaler)
      {
        std::stringstream when_msg;
        when_msg << "The prescaler is configured via calling 'setPrescaler' with an argument of '" << prescaler << "'";

        WHEN(when_msg.str())
        {
          timer0.setPrescaler(prescaler);
          WHEN("'start' is called")
          {
            timer0.start();

            switch(prescaler)
            {
            case 0    : THEN("TCCR0B bits 2-0 == 0b000") REQUIRE(TCCR0B->isBitVectSet({     })); break;
            case 1    : THEN("TCCR0B bits 2-0 == 0b001") REQUIRE(TCCR0B->isBitVectSet({    0})); break;
            case 8    : THEN("TCCR0B bits 2-0 == 0b010") REQUIRE(TCCR0B->isBitVectSet({  1  })); break;
            case 64   : THEN("TCCR0B bits 2-0 == 0b011") REQUIRE(TCCR0B->isBitVectSet({  1,0})); break;
            case 256  : THEN("TCCR0B bits 2-0 == 0b100") REQUIRE(TCCR0B->isBitVectSet({2    })); break;
            case 1024 : THEN("TCCR0B bits 2-0 == 0b101") REQUIRE(TCCR0B->isBitVectSet({2,  0})); break;
            }
          }
          WHEN("'start' is not called")
          {
            THEN("TCCR0B bits 2-0 == 0b000") REQUIRE(*TCCR0B == 0x00);
          }
        }
      });
}

/**************************************************************************************/

SCENARIO("ATMEGA328P::TIMER0 - A invalid prescaler value is set via 'setPrescaler'", "[ATMEGA328P::TIMER0]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::Vireg8 TCNT0  = vregmap.get<vireg::Vireg8>("TCNT0" );
  vireg::Vireg8 TCCR0B = vregmap.get<vireg::Vireg8>("TCCR0B");
  vireg::Vireg8 OCR0A  = vregmap.get<vireg::Vireg8>("OCR0A" );
  vireg::Vireg8 OCR0B  = vregmap.get<vireg::Vireg8>("OCR0B" );


  ATMEGA328P::TIMER0 timer0(TCNT0->ptr(), TCCR0B->ptr(), OCR0A->ptr(), OCR0B->ptr());


  uint32_t INVALID_PRESCALER = 2;

  WHEN("The prescaler is configured via calling 'setPrescaler' with an argument of '2'")
  {
    timer0.setPrescaler(INVALID_PRESCALER);
    WHEN("'start' is called")
    {
      timer0.start();
      THEN("TCCR0B bits 2-0 == 0b000 (Reset Value)") REQUIRE((*TCCR0B) == 0x00);
    }
    WHEN("'start' is not called")
    {
      THEN("TCCR0B bits 2-0 == 0b000 (Reset Value)") REQUIRE(*TCCR0B == 0x00);
    }
  }
}

/**************************************************************************************/

SCENARIO("ATMEGA328P::TIMER0 - A timer is started ('start') and stopped ('stop')", "[ATMEGA328P::TIMER0]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::Vireg8 TCNT0  = vregmap.get<vireg::Vireg8>("TCNT0" );
  vireg::Vireg8 TCCR0B = vregmap.get<vireg::Vireg8>("TCCR0B");
  vireg::Vireg8 OCR0A  = vregmap.get<vireg::Vireg8>("OCR0A" );
  vireg::Vireg8 OCR0B  = vregmap.get<vireg::Vireg8>("OCR0B" );


  ATMEGA328P::TIMER0 timer0(TCNT0->ptr(), TCCR0B->ptr(), OCR0A->ptr(), OCR0B->ptr());


  uint32_t const prescaler = 8;

  timer0.setPrescaler(prescaler);

  WHEN("'start' is called")
  {
    timer0.start();
    THEN("TCCR0B contains the expected prescaler bit pattern") REQUIRE(TCCR0B->isBitVectSet({1}));
    WHEN("'stop' is called")
    {
      timer0.stop();
      THEN("TCCR0B contains the RESET prescaler bit pattern") REQUIRE(*TCCR0B == 0x00);
      WHEN("'start' is called (again)")
      {
        timer0.start();
        THEN("TCCR0B contains the expected prescaler bit pattern (again)") REQUIRE(TCCR0B->isBitVectSet({1}));
      }
    }
  }
}

/**************************************************************************************/

SCENARIO("ATMEGA328P::TIMER0 - A timer's counter register is read ('get') and written ('set')", "[ATMEGA328P::TIMER0]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::Vireg8 TCNT0  = vregmap.get<vireg::Vireg8>("TCNT0" );
  vireg::Vireg8 TCCR0B = vregmap.get<vireg::Vireg8>("TCCR0B");
  vireg::Vireg8 OCR0A  = vregmap.get<vireg::Vireg8>("OCR0A" );
  vireg::Vireg8 OCR0B  = vregmap.get<vireg::Vireg8>("OCR0B" );


  ATMEGA328P::TIMER0 timer0(TCNT0->ptr(), TCCR0B->ptr(), OCR0A->ptr(), OCR0B->ptr());


  WHEN("the counter register is read via 'get'")
  {
    *TCNT0 = 0xCA;
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
      REQUIRE(*TCNT0 == 0xFF);
    }
  }
}

/**************************************************************************************/

SCENARIO("ATMEGA328P::TIMER0 - A timer's compare register are written via 'setCompareRegister'", "[ATMEGA328P::TIMER0]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::Vireg8 TCNT0  = vregmap.get<vireg::Vireg8>("TCNT0" );
  vireg::Vireg8 TCCR0B = vregmap.get<vireg::Vireg8>("TCCR0B");
  vireg::Vireg8 OCR0A  = vregmap.get<vireg::Vireg8>("OCR0A" );
  vireg::Vireg8 OCR0B  = vregmap.get<vireg::Vireg8>("OCR0B" );


  ATMEGA328P::TIMER0 timer0(TCNT0->ptr(), TCCR0B->ptr(), OCR0A->ptr(), OCR0B->ptr());


  WHEN("compare register A is written via 'setCompareRegister'")
  {
    timer0.setCompareRegister(TIMER0::COMPARE_A, 0xCA);
    THEN("OCR0A should contain the written value")
    {
      REQUIRE(*OCR0A == 0xCA);
    }
  }
  WHEN("compare register B is written via 'setCompareRegister'")
  {
    timer0.setCompareRegister(TIMER0::COMPARE_B, 0xFE);
    THEN("OCR0B should contain the written value")
    {
      REQUIRE(*OCR0B == 0xFE);
    }
  }
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* ATMEGA328P */

} /* hal */

} /* snowfox */
