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
: _io(io)
{
  setTxFifoSize(0);
  setRxFifoSize(0);
}

RFM9x_FifoControl::~RFM9x_FifoControl()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_FifoControl::setTxFifoSize(uint16_t const tx_fifo_size)
{
  /* TODO */

  _tx_fifo_size = tx_fifo_size;
}

void RFM9x_FifoControl::setRxFifoSize(uint16_t const rx_fifo_size)
{
  /* TODO */

  _rx_fifo_size = rx_fifo_size;
}

/*
void RFM9x_FifoControl::setTxFifoBaseAddress(uint8_t const tx_base_addr)
{
  _io.writeRegister(interface::Register::FIFO_TX_BASE_ADDR, tx_base_addr);
  _fifo_tx_base_addr = tx_base_addr;
}

void RFM9x_FifoControl::setRxFifoBaseAddress(uint8_t const rx_base_addr)
{
  _io.writeRegister(interface::Register::FIFO_RX_BASE_ADDR, rx_base_addr);
  _fifo_rx_base_addr = rx_base_addr;
}

void RFM9x_FifoControl::writeToTxFifo(uint8_t const * data, uint16_t const bytes)
{
  _io.writeRegister(interface::Register::FIFO_ADDR_PTR, _fifo_tx_base_addr);
  _io.writeRegister(interface::Register::FIFO, data, bytes);
}
*/

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
