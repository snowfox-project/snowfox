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

#include <spectre/driver/can/MCP2515/MCP2515_IoSpi.h>

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
 * CTOR/DTOR
 **************************************************************************************/

MCP2515_IoSpi::MCP2515_IoSpi(hal::interface::SPIMaster & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master(spi_master),
  _cs        (cs        )
{

}

MCP2515_IoSpi::~MCP2515_IoSpi()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_IoSpi::reset()
{
  uint8_t const instruction = static_cast<uint8_t>(interface::Instruction::RESET);

  _cs.clr();
  _spi_master.exchange(instruction);
  _cs.set();
}

void MCP2515_IoSpi::readRegister(interface::Register const reg, uint8_t * data)
{
  uint8_t const instruction = static_cast<uint8_t>(interface::Instruction::READ);
  uint8_t const reg_addr    = static_cast<uint8_t>(reg                         );

  _cs.clr();
          _spi_master.exchange(instruction);
          _spi_master.exchange(reg_addr   );
  *data = _spi_master.exchange(0          );
  _cs.set();
}

void MCP2515_IoSpi::writeRegister(interface::Register const reg, uint8_t const data)
{
  uint8_t const instruction = static_cast<uint8_t>(interface::Instruction::WRITE);
  uint8_t const reg_addr    = static_cast<uint8_t>(reg                          );

  _cs.clr();
  _spi_master.exchange(instruction);
  _spi_master.exchange(reg_addr   );
  _spi_master.exchange(data       );
  _cs.set();
}

void MCP2515_IoSpi::modifyRegister(interface::Register const reg, uint8_t const   data, uint8_t const mask)
{
  uint8_t const instruction = static_cast<uint8_t>(interface::Instruction::BITMOD);
  uint8_t const reg_addr    = static_cast<uint8_t>(reg                           );

  _cs.clr();
  _spi_master.exchange(instruction);
  _spi_master.exchange(reg_addr   );
  _spi_master.exchange(mask       );
  _spi_master.exchange(data       );
  _cs.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
