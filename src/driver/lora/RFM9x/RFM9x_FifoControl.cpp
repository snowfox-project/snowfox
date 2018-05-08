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

#include <spectre/driver/lora/RFM9x/RFM9x_FifoControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace lora
{

namespace RFM9x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_FifoControl::RFM9x_FifoControl(interface::RFM9x_Io & io)
: _io          (io)
{

}

RFM9x_FifoControl::~RFM9x_FifoControl()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint16_t RFM9x_FifoControl::writeToTxFifo(uint8_t const * data, uint16_t const num_bytes)
{
//  _io.writeRegister(interface::Register::FIFO_ADDR_PTR, calcTxFifoBaseAddress());
//
//  uint16_t bytes_to_write = (num_bytes <= _tx_fifo_size) ? num_bytes : _tx_fifo_size;
//
//  _io.writeRegister(interface::Register::FIFO, data, bytes_to_write);
//
//  return bytes_to_write;
  return 0;
}

uint16_t RFM9x_FifoControl::readFromRxFifo(uint8_t * data, uint16_t const num_bytes)
{
//  _io.writeRegister(interface::Register::FIFO_ADDR_PTR, calcRxFifoBaseAddress());
//
//  uint16_t bytes_to_read = (num_bytes <= _rx_fifo_size) ? num_bytes : _rx_fifo_size;
//
//  _io.readRegister(interface::Register::FIFO, data, bytes_to_read);
//
//  return bytes_to_read;

  return 0;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
