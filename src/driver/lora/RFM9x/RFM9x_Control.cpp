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

#include <snowfox/driver/lora/RFM9x/RFM9x_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

RFM9x_Control::RFM9x_Control(interface::RFM9x_Io & io)
: _io(io)
{

}

RFM9x_Control::~RFM9x_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Control::setOperatingMode(interface::OperatingMode const op_mode)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_MODE_2_bm | RFM9x_REG_OP_MODE_MODE_1_bm | RFM9x_REG_OP_MODE_MODE_0_bm);
  reg_op_mode_content |= static_cast<uint8_t>(op_mode);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

interface::OperatingMode RFM9x_Control::getOperatingMode()
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= (RFM9x_REG_OP_MODE_MODE_2_bm | RFM9x_REG_OP_MODE_MODE_1_bm | RFM9x_REG_OP_MODE_MODE_0_bm);

  return static_cast<interface::OperatingMode>(reg_op_mode_content);
}

uint8_t RFM9x_Control::getEventFlags()
{
  uint8_t irq_req_flags;

  _io.readRegister(interface::Register::IRQ_FLAGS, &irq_req_flags);

  return irq_req_flags;
}

void RFM9x_Control::clearEventFlag(interface::EventFlag const event_flag)
{
  /* The interrupt request flag can be cleared by writing
   * a '1' to the corresponding bit in the IRQ register.
   */
  _io.writeRegister(interface::Register::IRQ_FLAGS, static_cast<uint8_t>(event_flag));
}

void RFM9x_Control::writeToTransmitFifo(uint8_t const * data, uint8_t const num_bytes_to_write)
{
  uint8_t fifo_tx_base_address = 0;

  _io.readRegister (interface::Register::FIFO_TX_BASE_ADDR, &fifo_tx_base_address);
  _io.writeRegister(interface::Register::FIFO_ADDR_PTR,      fifo_tx_base_address);
  _io.writeRegister(interface::Register::FIFO, data, num_bytes_to_write          );
}

uint8_t RFM9x_Control::readFromReceiveFifo(uint8_t * data, uint8_t const num_bytes_to_read)
{
  uint8_t num_bytes_last_packet          = 0,
          rx_fifo_start_addr_last_packet = 0;

  _io.readRegister (interface::Register::RX_NB_BYTES,          &num_bytes_last_packet         );
  _io.readRegister (interface::Register::FIFO_RX_CURRENT_ADDR, &rx_fifo_start_addr_last_packet);
  _io.writeRegister(interface::Register::FIFO_ADDR_PTR,         rx_fifo_start_addr_last_packet);

  uint8_t const bytes_read = (num_bytes_to_read > num_bytes_last_packet) ? num_bytes_last_packet : num_bytes_to_read;

  _io.writeRegister(interface::Register::FIFO, data, bytes_read                               );

  return bytes_read;
}

void RFM9x_Control::setDio0EventSource(interface::Dio0EventSource const event_source)
{
  uint8_t reg_dio_mapping_1_content = 0;

  _io.readRegister(interface::Register::DIO_MAPPING1, &reg_dio_mapping_1_content);

  reg_dio_mapping_1_content &= ~(RFM9x_REG_DIO_MAPPING_1_DIO0_MAPPING_1_bm | RFM9x_REG_DIO_MAPPING_1_DIO0_MAPPING_0_bm);
  reg_dio_mapping_1_content |= static_cast<uint8_t>(event_source);

  _io.writeRegister(interface::Register::DIO_MAPPING1, reg_dio_mapping_1_content);
}

void RFM9x_Control::setDio1EventSource(interface::Dio1EventSource const event_source)
{
  uint8_t reg_dio_mapping_1_content = 0;

  _io.readRegister(interface::Register::DIO_MAPPING1, &reg_dio_mapping_1_content);

  reg_dio_mapping_1_content &= ~(RFM9x_REG_DIO_MAPPING_1_DIO1_MAPPING_1_bm | RFM9x_REG_DIO_MAPPING_1_DIO1_MAPPING_0_bm);
  reg_dio_mapping_1_content |= static_cast<uint8_t>(event_source);

  _io.writeRegister(interface::Register::DIO_MAPPING1, reg_dio_mapping_1_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* snowfox */
