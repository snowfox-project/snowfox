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

#include <snowfox/hal/riscv64/FE310/Spi1Master.h>

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

SCENARIO("A FE310::Spi1Master is constructed", "[FE310::Spi1Master]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::Vireg32 SPIx_SCKMODE = vregmap.get<vireg::Vireg32>("SPIx_SCKMODE");
  vireg::Vireg32 SPIx_FMT     = vregmap.get<vireg::Vireg32>("SPIx_FMT"    );
  vireg::Vireg32 GPIO_IOF_EN  = vregmap.get<vireg::Vireg32>("GPIO_IOF_EN" );
  vireg::Vireg32 GPIO_IOF_SEL = vregmap.get<vireg::Vireg32>("GPIO_IOF_SEL");
  
  Spi1Master spi1_master(SPIx_SCKMODE->ptr(), SPIx_FMT->ptr(), GPIO_IOF_EN->ptr(), GPIO_IOF_SEL->ptr());


  THEN("GPIO_IOF_EN  bit #3 (SPI1_DQ0 - MOSI) should be set") { REQUIRE(GPIO_IOF_EN->isBitSet (3)); }
  THEN("GPIO_IOF_EN  bit #4 (SPI1_DQ1 - MISO) should be set") { REQUIRE(GPIO_IOF_EN->isBitSet (4)); }
  THEN("GPIO_IOF_EN  bit #5 (SPI1_SCK) should be set")        { REQUIRE(GPIO_IOF_EN->isBitSet (5)); }
  THEN("GPIO_IOF_SEL bit #3 (SPI1_DQ0 - MOSI) should be clr") { REQUIRE(GPIO_IOF_SEL->isBitClr(3)); }
  THEN("GPIO_IOF_SEL bit #4 (SPI1_DQ1 - MISO) should be clr") { REQUIRE(GPIO_IOF_SEL->isBitClr(4)); }
  THEN("GPIO_IOF_SEL bit #5 (SPI1_SCK) should be clr")        { REQUIRE(GPIO_IOF_SEL->isBitClr(5)); }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* FE310 */

} /* hal */

} /* snowfox */
