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

#include <snowfox/hal/riscv64/FE310/SpiMaster.h>

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

SCENARIO("A FE310::SpiMaster is constructed", "[FE310::SpiMaster]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::VirtReg32 SPIx_SCKMODE = vregmap.get<vireg::VirtReg32>("SPIx_SCKMODE");
  vireg::VirtReg32 SPIx_FMT     = vregmap.get<vireg::VirtReg32>("SPIx_FMT"    );
  
  SpiMaster spi_master(SPIx_SCKMODE->ptr(), SPIx_FMT->ptr());


  THEN("FMT[1:0] should be 0b00 (SpiProtocol::Single)") {
    REQUIRE(SPIx_FMT->isBitClr(0));
    REQUIRE(SPIx_FMT->isBitClr(1));
  }
}

/**************************************************************************************/

SCENARIO("A FE310::SpiMaster is configured", "[FE310::SpiMaster]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::VirtReg32 SPIx_SCKMODE = vregmap.get<vireg::VirtReg32>("SPIx_SCKMODE");
  vireg::VirtReg32 SPIx_FMT     = vregmap.get<vireg::VirtReg32>("SPIx_FMT"    );
  
  SpiMaster spi_master(SPIx_SCKMODE->ptr(), SPIx_FMT->ptr());


  /* SPI MODE */
  WHEN("SpiMode::MODE_0 is set") { 
    spi_master.setSpiMode(interface::SpiMode::MODE_0); 
    THEN("SCKMODE[1:0] should be 0b00") { 
      REQUIRE(SPIx_SCKMODE->isBitClr(0));
      REQUIRE(SPIx_SCKMODE->isBitClr(1));
    }
  }
  WHEN("SpiMode::MODE_1 is set") { 
    spi_master.setSpiMode(interface::SpiMode::MODE_1); 
    THEN("SCKMODE[1:0] should be 0b01") { 
      REQUIRE(SPIx_SCKMODE->isBitSet(0));
      REQUIRE(SPIx_SCKMODE->isBitClr(1));
    }
  }
  WHEN("SpiMode::MODE_2 is set") { 
    spi_master.setSpiMode(interface::SpiMode::MODE_2); 
    THEN("SCKMODE[1:0] should be 0b10") { 
      REQUIRE(SPIx_SCKMODE->isBitClr(0));
      REQUIRE(SPIx_SCKMODE->isBitSet(1));
    }
  }
  WHEN("SpiMode::MODE_3 is set") { 
    spi_master.setSpiMode(interface::SpiMode::MODE_3); 
    THEN("SCKMODE[1:0] should be 0b11") { 
      REQUIRE(SPIx_SCKMODE->isBitSet(0));
      REQUIRE(SPIx_SCKMODE->isBitSet(1));
    }
  }

  /* BIT ORDER */
  WHEN("SpiBitOrder::MSB_FIRST is set") { spi_master.setSpiBitOrder(interface::SpiBitOrder::MSB_FIRST); THEN("FMT[2] should be clr") { REQUIRE(SPIx_FMT->isBitClr(2)); } }
  WHEN("SpiBitOrder::LSB_FIRST is set") { spi_master.setSpiBitOrder(interface::SpiBitOrder::LSB_FIRST); THEN("FMT[2] should be set") { REQUIRE(SPIx_FMT->isBitSet(2)); } }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* FE310 */

} /* hal */

} /* snowfox */
