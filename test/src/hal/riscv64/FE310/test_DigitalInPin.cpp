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

#include <catch2/catch.hpp>

#include <snowfox/hal/riscv64/FE310/DigitalInPin.h>

#include <vireg/VirtualRegister.hpp>
#include <vireg/VirtualRegisterLoader.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace FE310
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("A FE310::DigitalInPin (Pin number #0) object is constructed", "[FE310::DigitalInPin]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::VirtReg32 GPIO_INPUT_EN  = vregmap.get<vireg::VirtReg32>("GPIO_INPUT_EN" );
  vireg::VirtReg32 GPIO_OUTPUT_EN = vregmap.get<vireg::VirtReg32>("GPIO_OUTPUT_EN");
  vireg::VirtReg32 GPIO_IOF_EN    = vregmap.get<vireg::VirtReg32>("GPIO_IOF_EN"   );
  vireg::VirtReg32 GPIO_INPUT_VAL = vregmap.get<vireg::VirtReg32>("GPIO_INPUT_VAL");
  vireg::VirtReg32 GPIO_PUE       = vregmap.get<vireg::VirtReg32>("GPIO_PUE"      );
  
  DigitalInPin in_pin(GPIO_INPUT_EN->ptr(), GPIO_OUTPUT_EN->ptr(), GPIO_IOF_EN->ptr(), GPIO_INPUT_VAL->ptr(), GPIO_PUE->ptr(), 0);

  THEN("GPIO_INPUT_EN bit #0 should be set" ) { REQUIRE(GPIO_INPUT_EN->isBitSet (0)); }
  THEN("GPIO_OUTPUT_EN bit #0 should be clr") { REQUIRE(GPIO_OUTPUT_EN->isBitClr(0)); }
  THEN("GPIO_IOF_EN bit #0 should be clr"   ) { REQUIRE(GPIO_IOF_EN->isBitClr   (0)); }
  THEN("GPIO_INPUT_VAL bit #0 should be clr") { REQUIRE(GPIO_INPUT_VAL->isBitClr(0)); }
  THEN("GPIO_PUE bit #0 should be clr"      ) { REQUIRE(GPIO_PUE->isBitClr      (0)); }

  WHEN("interface::PullUpMode::NONE is selected") {
    in_pin.setPullUpMode(interface::PullUpMode::NONE);
    THEN("GPIO_PUE bit #0 should be clr") { 
      REQUIRE(GPIO_PUE->isBitClr(0)); 
    }
  }
  WHEN("interface::PullUpMode::PULL_UP is selected") {
    in_pin.setPullUpMode(interface::PullUpMode::PULL_UP);
    THEN("GPIO_PUE bit #0 should be set") { 
      REQUIRE(GPIO_PUE->isBitSet(0)); 
    }
  }
  WHEN("interface::PullUpMode::PULL_DOWN is selected") {
    in_pin.setPullUpMode(interface::PullUpMode::PULL_DOWN);
    THEN("GPIO_PUE bit #0 should be clr") { 
      REQUIRE(GPIO_PUE->isBitClr(0)); 
    }
  }

  WHEN("GPIO_INPUT_VAL bit #0 is = '0'") {
    GPIO_INPUT_VAL->clrBit(0);
    THEN("'isSet' return false") { REQUIRE(in_pin.isSet() == false); }
    THEN("'isClr' return true" ) { REQUIRE(in_pin.isClr() == true ); }
  }

  WHEN("GPIO_INPUT_VAL bit #0 is = '1'") {
    GPIO_INPUT_VAL->setBit(0);
    THEN("'isSet' return true" ) { REQUIRE(in_pin.isSet() == true ); }
    THEN("'isClr' return false") { REQUIRE(in_pin.isClr() == false); }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* FE310 */

} /* hal */

} /* snowfox */
