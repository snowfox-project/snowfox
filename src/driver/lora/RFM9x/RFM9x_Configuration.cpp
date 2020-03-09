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

#include <snowfox/driver/lora/RFM9x/RFM9x_Configuration.h>

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
 * CONSTANTS
 **************************************************************************************/

static uint16_t constexpr MAX_FIFO_SIZE = 256;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_Configuration::RFM9x_Configuration(interface::RFM9x_Io & io, uint32_t const fxosc_Hz)
: _io          (io      ),
  _fxosc_Hz    (fxosc_Hz),
  _tx_fifo_size(       0),
  _rx_fifo_size(       0)
{
  setTxFifoSize(0);
  setRxFifoSize(0);
}

RFM9x_Configuration::~RFM9x_Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Configuration::setLoRaMode(interface::LoRaMode const lora_mode)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_LONG_RANGE_MODE_bm);
  reg_op_mode_content |= static_cast<uint8_t>(lora_mode);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

void RFM9x_Configuration::setModulationType(interface::ModulationType const modulation_type)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_MODULATION_TYPE_1_bm | RFM9x_REG_OP_MODE_MODULATION_TYPE_0_bm);
  reg_op_mode_content |= static_cast<uint8_t>(modulation_type);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

void RFM9x_Configuration::setHeaderMode(interface::HeaderMode const header_mode)
{
  uint8_t reg_op_modem_config_1_content = 0;

  _io.readRegister(interface::Register::MODEM_CONFIG1, &reg_op_modem_config_1_content);

  reg_op_modem_config_1_content &= ~RFM9x_REG_MODEM_CONFIG_1_IMPLICIT_HEADER_MODE_ON_bm;
  reg_op_modem_config_1_content |= static_cast<uint8_t>(header_mode);

  _io.writeRegister(interface::Register::MODEM_CONFIG1, reg_op_modem_config_1_content);
}

void RFM9x_Configuration::setPacketFormat(interface::PacketFormat const packet_format)
{
  uint8_t reg_packet_config_1_content = 0;

  _io.readRegister(interface::Register::PACKET_CONFIG_1, &reg_packet_config_1_content);

  reg_packet_config_1_content &= ~RFM9x_REG_PACKET_CONFIG_1_PACKET_FORMAT_bm;
  reg_packet_config_1_content |= static_cast<uint8_t>(packet_format);

  _io.writeRegister(interface::Register::PACKET_CONFIG_1, reg_packet_config_1_content);
}

void RFM9x_Configuration::setFrequency(uint32_t const f_rf_Hz)
{
  float    const f_step_Hz = static_cast<float>(_fxosc_Hz) / 524288.0;
  uint32_t const f_rf      = static_cast<uint32_t>(static_cast<float>(f_rf_Hz) / f_step_Hz);

  uint8_t const f_rf_msb = static_cast<uint8_t>((f_rf & 0x00FF0000) >> 16);
  uint8_t const f_rf_mid = static_cast<uint8_t>((f_rf & 0x0000FF00) >>  8);
  uint8_t const f_rf_lsb = static_cast<uint8_t>((f_rf & 0x000000FF) >>  0);

  _io.writeRegister(interface::Register::FRF_MSB, f_rf_msb);
  _io.writeRegister(interface::Register::FRF_MID, f_rf_mid);
  _io.writeRegister(interface::Register::FRF_LSB, f_rf_lsb);
}

void RFM9x_Configuration::setSignalBandwidth(interface::SignalBandwidth const signal_bandwidth)
{
  uint8_t reg_op_modem_config_1_content = 0;

  _io.readRegister(interface::Register::MODEM_CONFIG1, &reg_op_modem_config_1_content);

  reg_op_modem_config_1_content &= ~(RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_3_bm | RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_2_bm | RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_1_bm | RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_0_bm);
  reg_op_modem_config_1_content |= static_cast<uint8_t>(signal_bandwidth);

  _io.writeRegister(interface::Register::MODEM_CONFIG1, reg_op_modem_config_1_content);
}

void RFM9x_Configuration::setCodingRate(interface::CodingRate const coding_rate)
{
  uint8_t reg_op_modem_config_1_content = 0;

  _io.readRegister(interface::Register::MODEM_CONFIG1, &reg_op_modem_config_1_content);

  reg_op_modem_config_1_content &= ~(RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_2_bm | RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_1_bm | RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_0_bm);
  reg_op_modem_config_1_content |= static_cast<uint8_t>(coding_rate);

  _io.writeRegister(interface::Register::MODEM_CONFIG1, reg_op_modem_config_1_content);
}

void RFM9x_Configuration::setSpreadingFactor(interface::SpreadingFactor const spreading_factor)
{
  uint8_t reg_op_modem_config_2_content = 0;

  _io.readRegister(interface::Register::MODEM_CONFIG2, &reg_op_modem_config_2_content);

  reg_op_modem_config_2_content &= ~(RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_3_bm | RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_2_bm | RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_1_bm | RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_0_bm);
  reg_op_modem_config_2_content |= static_cast<uint8_t>(spreading_factor);

  _io.writeRegister(interface::Register::MODEM_CONFIG2, reg_op_modem_config_2_content);
}

void RFM9x_Configuration::setPreambleLength(uint16_t const preamble_length)
{
  _io.writeRegister(interface::Register::PREAMBLE_MSB, static_cast<uint8_t>((preamble_length & 0xFF00) >> 8));
  _io.writeRegister(interface::Register::PREAMBLE_LSB, static_cast<uint8_t>((preamble_length & 0x00FF) >> 0));
}

void RFM9x_Configuration::setTransceiverLocation(interface::TransceiverLocation const transceiver_location)
{
  uint8_t reg_op_modem_config_3_content = 0;

  _io.readRegister(interface::Register::MODEM_CONFIG3, &reg_op_modem_config_3_content);

  reg_op_modem_config_3_content &= ~RFM9x_REG_MODEM_CONFIG_3_MOBILE_NODE_bm;
  reg_op_modem_config_3_content |= static_cast<uint8_t>(transceiver_location);

  _io.writeRegister(interface::Register::MODEM_CONFIG3, reg_op_modem_config_3_content);
}

void RFM9x_Configuration::setRxSymbolTimeout(uint16_t const rx_symbol_timeout)
{
  uint8_t const rx_symbol_timeout_msb = static_cast<uint8_t>((rx_symbol_timeout & 0x0300) >> 8); /* RegModemConfig2  (1:0) = SymbTimeout(9:8) */
  uint8_t const rx_symbol_timeout_lsb = static_cast<uint8_t>((rx_symbol_timeout & 0x00FF) >> 0); /* RegSymbTimeoutLsb(7:0) = SymbTimeout(7:0) */

  uint8_t reg_op_modem_config_2_content = 0;

  _io.readRegister(interface::Register::MODEM_CONFIG2, &reg_op_modem_config_2_content);

  reg_op_modem_config_2_content &= ~(RFM9x_REG_MODEM_CONFIG_2_SYMB_TIMEOUT_MSB_1_bm | RFM9x_REG_MODEM_CONFIG_2_SYMB_TIMEOUT_MSB_0_bm);
  reg_op_modem_config_2_content |= rx_symbol_timeout_msb;

  _io.writeRegister(interface::Register::MODEM_CONFIG2, reg_op_modem_config_2_content);

  _io.writeRegister(interface::Register::SYMB_TIMEOUT_LSB, rx_symbol_timeout_lsb);
}

bool RFM9x_Configuration::setTxFifoSize(uint16_t const tx_fifo_size)
{
  uint16_t const new_total_fifo_size = tx_fifo_size + _rx_fifo_size;

  if(new_total_fifo_size <= MAX_FIFO_SIZE)
  {
    _tx_fifo_size = tx_fifo_size;

    setTxFifoBaseAddress(            0);
    setRxFifoBaseAddress(_rx_fifo_size);

    return true;
  }
  else
  {
    return false;
  }
}

bool RFM9x_Configuration::setRxFifoSize(uint16_t const rx_fifo_size)
{
  uint16_t const new_total_fifo_size = _tx_fifo_size + rx_fifo_size;

  if(new_total_fifo_size <= MAX_FIFO_SIZE)
  {
    _rx_fifo_size = rx_fifo_size;

    setTxFifoBaseAddress(            0);
    setRxFifoBaseAddress(_rx_fifo_size);

    return true;
  }
  else
  {
    return false;
  }
}

uint16_t RFM9x_Configuration::getTxFifoSize() const
{
  return _tx_fifo_size;
}

uint16_t RFM9x_Configuration::getRxFifoSize() const
{
  return _rx_fifo_size;
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Configuration::setTxFifoBaseAddress(uint8_t const tx_fifo_base_address)
{
  _io.writeRegister(interface::Register::FIFO_TX_BASE_ADDR, tx_fifo_base_address);
}

void RFM9x_Configuration::setRxFifoBaseAddress(uint8_t const rx_fifo_base_address)
{
  _io.writeRegister(interface::Register::FIFO_RX_BASE_ADDR, rx_fifo_base_address);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* snowfox */
