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

#include <snowfox/hal/riscv64/FE310/SpiMasterBase.h>

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

SCENARIO("A FE310::SpiMasterBase is constructed", "[FE310::SpiMasterBase]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::Vireg32 SPIx_SCKMODE = vregmap.get<vireg::Vireg32>("SPIx_SCKMODE");
  vireg::Vireg32 SPIx_FMT     = vregmap.get<vireg::Vireg32>("SPIx_FMT"    );
  vireg::Vireg32 SPIx_CSMODE  = vregmap.get<vireg::Vireg32>("SPIx_CSMODE" );
  
  SpiMasterBase spi_master(SPIx_SCKMODE->ptr(), SPIx_FMT->ptr(), SPIx_CSMODE->ptr());


  THEN("FMT[1:0] should be 0b00 (SpiProtocol::Single)") {
    REQUIRE(SPIx_FMT->isBitClr(0));
    REQUIRE(SPIx_FMT->isBitClr(1));
  }

  THEN("CSMODE[1:0] should be 0b11 (ChipSelectMode::Off)") {
    REQUIRE(SPIx_CSMODE->isBitSet(0));
    REQUIRE(SPIx_CSMODE->isBitSet(1));
  }
}

/**************************************************************************************/

SCENARIO("A FE310::SpiMasterBase's SpiMode is configured", "[FE310::SpiMasterBase]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::Vireg32 SPIx_SCKMODE = vregmap.get<vireg::Vireg32>("SPIx_SCKMODE");
  vireg::Vireg32 SPIx_FMT     = vregmap.get<vireg::Vireg32>("SPIx_FMT"    );
  vireg::Vireg32 SPIx_CSMODE  = vregmap.get<vireg::Vireg32>("SPIx_CSMODE" );
  
  SpiMasterBase spi_master(SPIx_SCKMODE->ptr(), SPIx_FMT->ptr(), SPIx_CSMODE->ptr());


  THEN("setSpiMode(interface::SpiMode::MODE_0) should return true") REQUIRE(spi_master.setSpiMode(interface::SpiMode::MODE_0) == true); 
  THEN("setSpiMode(interface::SpiMode::MODE_1) should return true") REQUIRE(spi_master.setSpiMode(interface::SpiMode::MODE_1) == true); 
  THEN("setSpiMode(interface::SpiMode::MODE_2) should return true") REQUIRE(spi_master.setSpiMode(interface::SpiMode::MODE_2) == true); 
  THEN("setSpiMode(interface::SpiMode::MODE_3) should return true") REQUIRE(spi_master.setSpiMode(interface::SpiMode::MODE_3) == true); 


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
}

/**************************************************************************************/

SCENARIO("A FE310::SpiMasterBase's SpiBitOrder is configured", "[FE310::SpiMasterBase]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::Vireg32 SPIx_SCKMODE = vregmap.get<vireg::Vireg32>("SPIx_SCKMODE");
  vireg::Vireg32 SPIx_FMT     = vregmap.get<vireg::Vireg32>("SPIx_FMT"    );
  vireg::Vireg32 SPIx_CSMODE  = vregmap.get<vireg::Vireg32>("SPIx_CSMODE" );
  
  SpiMasterBase spi_master(SPIx_SCKMODE->ptr(), SPIx_FMT->ptr(), SPIx_CSMODE->ptr());


  THEN("setSpiBitOrder(SpiBitOrder::MSB_FIRST) should return true") REQUIRE(spi_master.setSpiBitOrder(interface::SpiBitOrder::MSB_FIRST) == true); 
  THEN("setSpiBitOrder(SpiBitOrder::LSB_FIRST) should return true") REQUIRE(spi_master.setSpiBitOrder(interface::SpiBitOrder::LSB_FIRST) == true); 

  
  WHEN("SpiBitOrder::MSB_FIRST is set") { spi_master.setSpiBitOrder(interface::SpiBitOrder::MSB_FIRST); THEN("FMT[2] should be clr") { REQUIRE(SPIx_FMT->isBitClr(2)); } }
  WHEN("SpiBitOrder::LSB_FIRST is set") { spi_master.setSpiBitOrder(interface::SpiBitOrder::LSB_FIRST); THEN("FMT[2] should be set") { REQUIRE(SPIx_FMT->isBitSet(2)); } }
}

/**************************************************************************************/

SCENARIO("A FE310::SpiMasterBase's Bits per frame are configured", "[FE310::SpiMasterBase]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/riscv64/FE310.json");

  vireg::Vireg32 SPIx_SCKMODE = vregmap.get<vireg::Vireg32>("SPIx_SCKMODE");
  vireg::Vireg32 SPIx_FMT     = vregmap.get<vireg::Vireg32>("SPIx_FMT"    );
  vireg::Vireg32 SPIx_CSMODE  = vregmap.get<vireg::Vireg32>("SPIx_CSMODE" );
  
  SpiMasterBase spi_master(SPIx_SCKMODE->ptr(), SPIx_FMT->ptr(), SPIx_CSMODE->ptr());


  THEN("setSpiBitsPerFrame(8) should return true") REQUIRE(spi_master.setSpiBitsPerFrame(8) == true);

  
  WHEN("8 bits per frame are set") { spi_master.setSpiBitsPerFrame(8); THEN("FMT[19:16] should be 0x0008") { REQUIRE((SPIx_FMT->val() & 0x000F0000) == 0x00080000); } }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* FE310 */

} /* hal */

} /* snowfox */
