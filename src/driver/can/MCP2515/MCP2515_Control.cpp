/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/can/MCP2515/MCP2515_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace can
{

namespace MCP2515
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef struct
{
  uint8_t CNF1, CNF2, CNF3;
} CanBitRateConfiguration;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static CanBitRateConfiguration BitRate_1MBPS_8MHz    = {0x00, 0xC0, 0x80};
static CanBitRateConfiguration BitRate_500kBPS_8MHz  = {0x00, 0xD1, 0x81};
static CanBitRateConfiguration BitRate_250kBPS_8MHz  = {0x80, 0xE5, 0x83};
static CanBitRateConfiguration BitRate_125kBPS_8MHz  = {0x81, 0xE5, 0x83};

static CanBitRateConfiguration BitRate_1MBPS_16MHz   = {0x00, 0xCA, 0x81};
static CanBitRateConfiguration BitRate_500kBPS_16MHz = {0x40, 0xE5, 0x83};
static CanBitRateConfiguration BitRate_250kBPS_16MHz = {0x41, 0xE5, 0x83};
static CanBitRateConfiguration BitRate_125kBPS_16MHz = {0x43, 0xE5, 0x83};

static CanBitRateConfiguration BitRate_1MBPS_20MHz   = {0x00, 0xD9, 0x82};
static CanBitRateConfiguration BitRate_500kBPS_20MHz = {0x40, 0xF6, 0x84};
static CanBitRateConfiguration BitRate_250kBPS_20MHz = {0x41, 0xF6, 0x84};
static CanBitRateConfiguration BitRate_125kBPS_20MHz = {0x44, 0xE5, 0x83};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MCP2515_Control::MCP2515_Control(interface::MCP2515_Io & io)
: _io(io)
{

}

MCP2515_Control::~MCP2515_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_Control::setCanBitRate(uint8_t const clk_MHz, interface::CanBitRate const can_bit_rate)
{
  switch(clk_MHz)
  {
  case  8: setCanBitRate_Clock_8MHz (can_bit_rate); break;
  case 16: setCanBitRate_Clock_16MHz(can_bit_rate); break;
  case 20: setCanBitRate_Clock_20MHz(can_bit_rate); break;
  default:                                          break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_Control::setCanBitRate_Clock_8MHz(interface::CanBitRate const can_bit_rate)
{
  switch(can_bit_rate)
  {
  case interface::CanBitRate::BR_1MBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_1MBPS_8MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_1MBPS_8MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_1MBPS_8MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_500kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_500kBPS_8MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_500kBPS_8MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_500kBPS_8MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_250kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_250kBPS_8MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_250kBPS_8MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_250kBPS_8MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_125kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_125kBPS_8MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_125kBPS_8MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_125kBPS_8MHz.CNF3);
  }
  break;
  }
}

void MCP2515_Control::setCanBitRate_Clock_16MHz(interface::CanBitRate const can_bit_rate)
{
  switch(can_bit_rate)
  {
  case interface::CanBitRate::BR_1MBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_1MBPS_16MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_1MBPS_16MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_1MBPS_16MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_500kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_500kBPS_16MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_500kBPS_16MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_500kBPS_16MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_250kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_250kBPS_16MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_250kBPS_16MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_250kBPS_16MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_125kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_125kBPS_16MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_125kBPS_16MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_125kBPS_16MHz.CNF3);
  }
  break;
  }
}

void MCP2515_Control::setCanBitRate_Clock_20MHz(interface::CanBitRate const can_bit_rate)
{
  switch(can_bit_rate)
  {
  case interface::CanBitRate::BR_1MBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_1MBPS_20MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_1MBPS_20MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_1MBPS_20MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_500kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_500kBPS_20MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_500kBPS_20MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_500kBPS_20MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_250kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_250kBPS_20MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_250kBPS_20MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_250kBPS_20MHz.CNF3);
  }
  break;
  case interface::CanBitRate::BR_125kBPS:
  {
    _io.writeRegister(interface::Register::CNF1, BitRate_125kBPS_20MHz.CNF1);
    _io.writeRegister(interface::Register::CNF2, BitRate_125kBPS_20MHz.CNF2);
    _io.writeRegister(interface::Register::CNF3, BitRate_125kBPS_20MHz.CNF3);
  }
  break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
