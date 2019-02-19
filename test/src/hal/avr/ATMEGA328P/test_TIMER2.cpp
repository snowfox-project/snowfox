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

#include <snowfox/hal/avr/ATMEGA328P/TIMER2.h>

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

SCENARIO("ATMEGA328P::TIMER2 - A A valid prescaler value is set via 'setPrescaler'", "[ATMEGA328P::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::VirtReg8 TCNT2  = vregmap.get<vireg::VirtReg8>("TCNT2" );
  vireg::VirtReg8 TCCR2B = vregmap.get<vireg::VirtReg8>("TCCR2B");
  vireg::VirtReg8 OCR2A  = vregmap.get<vireg::VirtReg8>("OCR2A" );
  vireg::VirtReg8 OCR2B  = vregmap.get<vireg::VirtReg8>("OCR2B" );


  ATMEGA328P::TIMER2 timer2((*TCNT2)(), (*TCCR2B)(), (*OCR2A)(), (*OCR2B)());


  std::vector<uint32_t> const VALID_PRESCALER_VECT = {0, 1, 8, 64, 256, 1024};

  std::for_each(
      std::begin(VALID_PRESCALER_VECT),
      std::end  (VALID_PRESCALER_VECT),
      [&timer2, &TCCR2B](uint32_t const prescaler)
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
            case 0    : THEN("TCCR2B bits 2-0 == 0b000") REQUIRE(TCCR2B->isBitVectSet({     })); break;
            case 1    : THEN("TCCR2B bits 2-0 == 0b001") REQUIRE(TCCR2B->isBitVectSet({    0})); break;
            case 8    : THEN("TCCR2B bits 2-0 == 0b010") REQUIRE(TCCR2B->isBitVectSet({  1  })); break;
            case 64   : THEN("TCCR2B bits 2-0 == 0b011") REQUIRE(TCCR2B->isBitVectSet({  1,0})); break;
            case 256  : THEN("TCCR2B bits 2-0 == 0b100") REQUIRE(TCCR2B->isBitVectSet({2    })); break;
            case 1024 : THEN("TCCR2B bits 2-0 == 0b101") REQUIRE(TCCR2B->isBitVectSet({2,  0})); break;
            }
          }
          WHEN("'start' is not called")
          {
            THEN("TCCR2B bits 2-0 == 0b000") REQUIRE(*TCCR2B == 0x00);
          }
        }
      });
}

/**************************************************************************************/

SCENARIO("ATMEGA328P::TIMER2 - A invalid prescaler value is set via 'setPrescaler'", "[ATMEGA328P::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::VirtReg8 TCNT2  = vregmap.get<vireg::VirtReg8>("TCNT2" );
  vireg::VirtReg8 TCCR2B = vregmap.get<vireg::VirtReg8>("TCCR2B");
  vireg::VirtReg8 OCR2A  = vregmap.get<vireg::VirtReg8>("OCR2A" );
  vireg::VirtReg8 OCR2B  = vregmap.get<vireg::VirtReg8>("OCR2B" );


  ATMEGA328P::TIMER2 timer2((*TCNT2)(), (*TCCR2B)(), (*OCR2A)(), (*OCR2B)());


  uint32_t INVALID_PRESCALER = 2;

  WHEN("The prescaler is configured via calling 'setPrescaler' with an argument of '2'")
  {
    timer2.setPrescaler(INVALID_PRESCALER);
    WHEN("'start' is called")
    {
      timer2.start();
      THEN("TCCR2B bits 2-0 == 0b000 (Reset Value)") REQUIRE(*TCCR2B == 0x00);
    }
    WHEN("'start' is not called")
    {
      THEN("TCCR2B bits 2-0 == 0b000 (Reset Value)") REQUIRE(*TCCR2B == 0x00);
    }
  }
}

/**************************************************************************************/

SCENARIO("ATMEGA328P::TIMER2 - A timer is started ('start') and stopped ('stop')", "[ATMEGA328P::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::VirtReg8 TCNT2  = vregmap.get<vireg::VirtReg8>("TCNT2" );
  vireg::VirtReg8 TCCR2B = vregmap.get<vireg::VirtReg8>("TCCR2B");
  vireg::VirtReg8 OCR2A  = vregmap.get<vireg::VirtReg8>("OCR2A" );
  vireg::VirtReg8 OCR2B  = vregmap.get<vireg::VirtReg8>("OCR2B" );


  ATMEGA328P::TIMER2 timer2((*TCNT2)(), (*TCCR2B)(), (*OCR2A)(), (*OCR2B)());


  uint32_t const prescaler = 8;

  timer2.setPrescaler(prescaler);

  WHEN("'start' is called")
  {
    timer2.start();
    THEN("TCCR2B contains the expected prescaler bit pattern") REQUIRE(TCCR2B->isBitVectSet({1}));
    WHEN("'stop' is called")
    {
      timer2.stop();
      THEN("TCCR2B contains the RESET prescaler bit pattern") REQUIRE(*TCCR2B == 0x00);
      WHEN("'start' is called (again)")
      {
        timer2.start();
        THEN("TCCR2B contains the expected prescaler bit pattern (again)") REQUIRE(TCCR2B->isBitVectSet({1}));
      }
    }
  }
}

/**************************************************************************************/

SCENARIO("ATMEGA328P::TIMER2 - A timer's counter register is read ('get') and written ('set')", "[ATMEGA328P::TIMER2]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::VirtReg8 TCNT2  = vregmap.get<vireg::VirtReg8>("TCNT2" );
  vireg::VirtReg8 TCCR2B = vregmap.get<vireg::VirtReg8>("TCCR2B");
  vireg::VirtReg8 OCR2A  = vregmap.get<vireg::VirtReg8>("OCR2A" );
  vireg::VirtReg8 OCR2B  = vregmap.get<vireg::VirtReg8>("OCR2B" );


  ATMEGA328P::TIMER2 timer2((*TCNT2)(), (*TCCR2B)(), (*OCR2A)(), (*OCR2B)());


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

SCENARIO("ATMEGA328P::TIMER2 - A timer's compare register are written via 'setCompareRegister'", "[ATMEGA328P::TIMER]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA328P.json");

  vireg::VirtReg8 TCNT2  = vregmap.get<vireg::VirtReg8>("TCNT2" );
  vireg::VirtReg8 TCCR2B = vregmap.get<vireg::VirtReg8>("TCCR2B");
  vireg::VirtReg8 OCR2A  = vregmap.get<vireg::VirtReg8>("OCR2A" );
  vireg::VirtReg8 OCR2B  = vregmap.get<vireg::VirtReg8>("OCR2B" );


  ATMEGA328P::TIMER2 timer2((*TCNT2)(), (*TCCR2B)(), (*OCR2A)(), (*OCR2B)());


  WHEN("compare register A is written via 'setCompareRegister'")
  {
    timer2.setCompareRegister(TIMER2::COMPARE_A, 0xCA);
    THEN("OCR0A should contain the written value")
    {
      REQUIRE(*OCR2A == 0xCA);
    }
  }
  WHEN("compare register B is written via 'setCompareRegister'")
  {
    timer2.setCompareRegister(TIMER2::COMPARE_B, 0xFE);
    THEN("OCR0B should contain the written value")
    {
      REQUIRE(*OCR2B == 0xFE);
    }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* ATMEGA328P */

} /* hal */

} /* snowfox */
