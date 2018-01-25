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

bool MCP2515_IoSpi::readRegister (interface::Register const reg, uint8_t * data)
{
  _cs.clr();
          _spi_master.exchange(static_cast<uint8_t>(interface::Instruction::READ));
          _spi_master.exchange(static_cast<uint8_t>(reg                         ));
  *data = _spi_master.exchange(                     0                            );
  _cs.set();

  return true;
}

bool MCP2515_IoSpi::writeRegister(interface::Register const reg, uint8_t const data)
{
  _cs.clr();
  _spi_master.exchange(static_cast<uint8_t>(interface::Instruction::WRITE));
  _spi_master.exchange(static_cast<uint8_t>(reg                          ));
  _spi_master.exchange(                     data                          );
  _cs.set();

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
