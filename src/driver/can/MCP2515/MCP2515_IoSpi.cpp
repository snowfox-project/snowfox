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
 * TYPEDEFS
 **************************************************************************************/

enum class TxBufferBytePos : uint8_t
{
  SIDH = 0,
  SIDL = 1,
  EID8 = 2,
  EID0 = 3,
  DLC  = 4,
  DATA = 5
};

enum class RxBufferBytePos : uint8_t
{
  SIDH = 0,
  SIDL = 1,
  EID8 = 2,
  EID0 = 3,
  DLC  = 4,
  DATA = 5
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MCP2515_IoSpi::MCP2515_IoSpi(hal::interface::SPIMaster & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master(spi_master),
  _cs        (cs        )
{
  _cs.set();
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

uint8_t MCP2515_IoSpi::status()
{
  uint8_t const instruction = static_cast<uint8_t>(interface::Instruction::READ_STATUS);

  _cs.clr();
                         _spi_master.exchange(instruction);
  uint8_t const status = _spi_master.exchange(0);
  _cs.set();

  return status;
}

void MCP2515_IoSpi::loadTx0(uint8_t const * tx_buf)
{
  loadTxX(static_cast<uint8_t>(interface::Instruction::LOAD_TX0), tx_buf);
}

void MCP2515_IoSpi::loadTx1(uint8_t const * tx_buf)
{
  loadTxX(static_cast<uint8_t>(interface::Instruction::LOAD_TX1), tx_buf);
}

void MCP2515_IoSpi::loadTx2(uint8_t const * tx_buf)
{
  loadTxX(static_cast<uint8_t>(interface::Instruction::LOAD_TX2), tx_buf);
}

void MCP2515_IoSpi::readRx0(uint8_t * rx_buf)
{
  loadRxX(static_cast<uint8_t>(interface::Instruction::READ_RX0), rx_buf);
}

void MCP2515_IoSpi::readRx1(uint8_t * rx_buf)
{
  loadRxX(static_cast<uint8_t>(interface::Instruction::READ_RX1), rx_buf);
}

void MCP2515_IoSpi::requestToTransmitTx0()
{
  uint8_t const instruction = static_cast<uint8_t>(interface::Instruction::RTS_TX0);

  _cs.clr();
  _spi_master.exchange(instruction);
  _cs.set();
}

void MCP2515_IoSpi::requestToTransmitTx1()
{
  uint8_t const instruction = static_cast<uint8_t>(interface::Instruction::RTS_TX1);

  _cs.clr();
  _spi_master.exchange(instruction);
  _cs.set();
}

void MCP2515_IoSpi::requestToTransmitTx2()
{
  uint8_t const instruction = static_cast<uint8_t>(interface::Instruction::RTS_TX2);

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
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_IoSpi::loadTxX(uint8_t const instruction, uint8_t const * tx_buf)
{
  uint8_t const num_data_bytes = tx_buf[static_cast<uint8_t>(TxBufferBytePos::DLC)] & 0x0F;

  _cs.clr();
  _spi_master.exchange(instruction);
  _spi_master.exchange(tx_buf[static_cast<uint8_t>(TxBufferBytePos::SIDH)]);
  _spi_master.exchange(tx_buf[static_cast<uint8_t>(TxBufferBytePos::SIDL)]);
  _spi_master.exchange(tx_buf[static_cast<uint8_t>(TxBufferBytePos::EID8)]);
  _spi_master.exchange(tx_buf[static_cast<uint8_t>(TxBufferBytePos::EID0)]);
  _spi_master.exchange(tx_buf[static_cast<uint8_t>(TxBufferBytePos::DLC )]);
  for(uint8_t b = 0; b < num_data_bytes; b++)
  {
    _spi_master.exchange(tx_buf[static_cast<uint8_t>(TxBufferBytePos::DATA) + b]);
  }
  _cs.set();
}

void MCP2515_IoSpi::loadRxX(uint8_t const instruction, uint8_t * rx_buf)
{
  _cs.clr();
                                                        _spi_master.exchange(instruction);
  rx_buf[static_cast<uint8_t>(RxBufferBytePos::SIDH)] = _spi_master.exchange(0);
  rx_buf[static_cast<uint8_t>(RxBufferBytePos::SIDL)] = _spi_master.exchange(0);
  rx_buf[static_cast<uint8_t>(RxBufferBytePos::EID8)] = _spi_master.exchange(0);
  rx_buf[static_cast<uint8_t>(RxBufferBytePos::EID0)] = _spi_master.exchange(0);
  rx_buf[static_cast<uint8_t>(RxBufferBytePos::DLC )] = _spi_master.exchange(0);
  uint8_t const num_data_bytes = rx_buf[static_cast<uint8_t>(RxBufferBytePos::DLC)] & 0x0F;
  for(uint8_t b = 0; b < num_data_bytes; b++)
  {
    rx_buf[static_cast<uint8_t>(RxBufferBytePos::DATA) + b] = _spi_master.exchange(0);
  }
  _cs.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
