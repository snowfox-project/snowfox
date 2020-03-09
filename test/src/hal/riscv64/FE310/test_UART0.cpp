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

#include <catch2/catch.hpp>

#include <snowfox/hal/riscv64/FE310/UART0.h>

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

SCENARIO("A FE310::UART0 object is constructed", "[FE310::UART0]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::Vireg32 UARTx_TXDATA = vregmap.get<vireg::Vireg32>("UARTx_TXDATA");
  vireg::Vireg32 UARTx_RXDATA = vregmap.get<vireg::Vireg32>("UARTx_RXDATA");
  vireg::Vireg32 UARTx_TXCTRL = vregmap.get<vireg::Vireg32>("UARTx_TXCTRL");
  vireg::Vireg32 UARTx_RXCTRL = vregmap.get<vireg::Vireg32>("UARTx_RXCTRL");
  vireg::Vireg32 UARTx_DIV    = vregmap.get<vireg::Vireg32>("UARTx_DIV"   );
  vireg::Vireg32 GPIO_IOF_EN  = vregmap.get<vireg::Vireg32>("GPIO_IOF_EN" );
  vireg::Vireg32 GPIO_IOF_SEL = vregmap.get<vireg::Vireg32>("GPIO_IOF_SEL");

  UART0 uart0(UARTx_TXDATA->ptr(), UARTx_RXDATA->ptr(), UARTx_TXCTRL->ptr(), UARTx_RXCTRL->ptr(), UARTx_DIV->ptr(), 200000000UL, GPIO_IOF_EN->ptr(), GPIO_IOF_SEL->ptr());


  THEN("GPIO_IOF_EN  bit #16 (UART0RX) should be set") { REQUIRE(GPIO_IOF_EN->isBitSet (16)); }
  THEN("GPIO_IOF_EN  bit #17 (UART0TX) should be set") { REQUIRE(GPIO_IOF_EN->isBitSet (17)); }
  THEN("GPIO_IOF_SEL bit #16 (UART0RX) should be clr") { REQUIRE(GPIO_IOF_SEL->isBitClr(16)); }
  THEN("GPIO_IOF_SEL bit #17 (UART0TX) should be clr") { REQUIRE(GPIO_IOF_SEL->isBitClr(17)); }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* FE310 */

} /* hal */

} /* snowfox */
