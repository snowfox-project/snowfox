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

#include <spectre/driver/lora/RFM9x/RFM9x_TransmitFifo.h>

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

RFM9x_TransmitFifo::RFM9x_TransmitFifo(interface::RFM9x_Io & io)
: _io(io)
{

}

RFM9x_TransmitFifo::~RFM9x_TransmitFifo()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_TransmitFifo::writeToFifo(uint8_t const * data, uint16_t const num_bytes)
{
  uint8_t fifo_tx_base_address = 0;

  _io.readRegister (interface::Register::FIFO_TX_BASE_ADDR, &fifo_tx_base_address);
  _io.writeRegister(interface::Register::FIFO_ADDR_PTR,      fifo_tx_base_address);
  _io.writeRegister(interface::Register::FIFO, data, num_bytes                   );
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
