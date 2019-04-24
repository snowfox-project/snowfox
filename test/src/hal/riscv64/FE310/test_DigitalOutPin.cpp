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

#include <snowfox/hal/riscv64/FE310/DigitalOutPin.h>

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

SCENARIO("A FE310::DigitalOutPin (Pin number #0) object is constructed", "[FE310::DigitalOutPin]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::VirtReg32 GPIO_INPUT_EN   = vregmap.get<vireg::VirtReg32>("GPIO_INPUT_EN"  );
  vireg::VirtReg32 GPIO_OUTPUT_EN  = vregmap.get<vireg::VirtReg32>("GPIO_OUTPUT_EN" );
  vireg::VirtReg32 GPIO_IOF_EN     = vregmap.get<vireg::VirtReg32>("GPIO_IOF_EN"    );
  vireg::VirtReg32 GPIO_OUTPUT_VAL = vregmap.get<vireg::VirtReg32>("GPIO_OUTPUT_VAL");
  
  DigitalOutPin out_pin(GPIO_INPUT_EN->ptr(), GPIO_OUTPUT_EN->ptr(), GPIO_IOF_EN->ptr(), GPIO_OUTPUT_VAL->ptr(), 0);

  THEN("GPIO_INPUT_EN bit #0 should be clr"  ) { REQUIRE(GPIO_INPUT_EN->isBitClr  (0)); }
  THEN("GPIO_OUTPUT_EN bit #0 should be set" ) { REQUIRE(GPIO_OUTPUT_EN->isBitSet (0)); }
  THEN("GPIO_IOF_EN bit #0 should be clr"    ) { REQUIRE(GPIO_IOF_EN->isBitClr    (0)); }
  THEN("GPIO_OUTPUT_VAL bit #0 should be clr") { REQUIRE(GPIO_OUTPUT_VAL->isBitClr(0)); }

  WHEN("'set' is called") {
    out_pin.set();
    THEN("GPIO_OUTPUT_VAL bit #0 should be set") { 
      REQUIRE(GPIO_OUTPUT_VAL->isBitSet(0));
      WHEN("'clr' is called") {
        out_pin.clr();
        THEN("GPIO_OUTPUT_VAL bit #0 should be clr") { 
          REQUIRE(GPIO_OUTPUT_VAL->isBitClr(0));
        }
      }
    }
  }

  WHEN("'clr' is called") {
    out_pin.clr();
    THEN("GPIO_OUTPUT_VAL bit #0 should be clr") { 
      REQUIRE(GPIO_OUTPUT_VAL->isBitClr(0));
      WHEN("'set' is called") {
        out_pin.set();
        THEN("GPIO_OUTPUT_VAL bit #0 should be set") { 
          REQUIRE(GPIO_OUTPUT_VAL->isBitSet(0));
        }
      }
    }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* FE310 */

} /* hal */

} /* snowfox */
