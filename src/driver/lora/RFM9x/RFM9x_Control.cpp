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

#include <spectre/driver/lora/RFM9x/RFM9x_Control.h>

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

RFM9x_Control::RFM9x_Control(interface::RFM9x_Io & io)
: _io(io)
{
//  setTxFifoBaseAddress(0);
//  setRxFifoBaseAddress(0);
}

RFM9x_Control::~RFM9x_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Control::setTxFifoBaseAddress(uint8_t const tx_base_addr)
{
  _io.writeRegister(interface::Register::FIFO_TX_BASE_ADDR, tx_base_addr);
  _fifo_tx_base_addr = tx_base_addr;
}

void RFM9x_Control::setRxFifoBaseAddress(uint8_t const rx_base_addr)
{
  _io.writeRegister(interface::Register::FIFO_RX_BASE_ADDR, rx_base_addr);
  _fifo_rx_base_addr = rx_base_addr;
}

void RFM9x_Control::writeToTxFifo(uint8_t const * data, uint16_t const bytes)
{
  _io.writeRegister(interface::Register::FIFO_ADDR_PTR, _fifo_tx_base_addr);
  _io.writeRegister(interface::Register::FIFO, data, bytes);
}

void RFM9x_Control::setOperatingMode(interface::OperatingMode const op_mode)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_MODE_2_bm | RFM9x_REG_OP_MODE_MODE_1_bm | RFM9x_REG_OP_MODE_MODE_0_bm);
  reg_op_mode_content |= static_cast<uint8_t>(op_mode);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

void RFM9x_Control::setLoraMode(interface::LoRaMode const lora_mode)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_LONG_RANGE_MODE_bm);
  reg_op_mode_content |= static_cast<uint8_t>(lora_mode);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

void RFM9x_Control::setModulationType(interface::ModulationType const modulation_type)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_MODULATION_TYPE_1_bm | RFM9x_REG_OP_MODE_MODULATION_TYPE_0_bm);
  reg_op_mode_content |= static_cast<uint8_t>(modulation_type);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

void RFM9x_Control::setFrequency(uint32_t const f_rf_Hz, uint32_t const fxosc_Hz)
{
  float    const f_step_Hz = static_cast<float>(fxosc_Hz) / 524288.0;
  uint32_t const f_rf      = static_cast<uint32_t>(f_step_Hz / static_cast<float>(f_rf_Hz));

  uint8_t const f_rf_msb = static_cast<uint8_t>((f_rf & 0x00FF0000) >> 16);
  uint8_t const f_rf_mid = static_cast<uint8_t>((f_rf & 0x0000FF00) >>  8);
  uint8_t const f_rf_lsb = static_cast<uint8_t>((f_rf & 0x000000FF) >>  0);

  _io.writeRegister(interface::Register::FRF_MSB, f_rf_msb);
  _io.writeRegister(interface::Register::FRF_MID, f_rf_mid);
  _io.writeRegister(interface::Register::FRF_LSB, f_rf_lsb);
}

void RFM9x_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "OP_MODE                 = ", interface::Register::OP_MODE                );
  debug_dumpSingleReg(debug_interface, "FRF_MSB                 = ", interface::Register::FRF_MSB                );
  debug_dumpSingleReg(debug_interface, "FRF_MID                 = ", interface::Register::FRF_MID                );
  debug_dumpSingleReg(debug_interface, "FRF_LSB                 = ", interface::Register::FRF_LSB                );
  debug_dumpSingleReg(debug_interface, "PA_CONFIG               = ", interface::Register::PA_CONFIG              );
  debug_dumpSingleReg(debug_interface, "PA_RAMP                 = ", interface::Register::PA_RAMP                );
  debug_dumpSingleReg(debug_interface, "OCP                     = ", interface::Register::OCP                    );
  debug_dumpSingleReg(debug_interface, "LNA                     = ", interface::Register::LNA                    );
  debug_dumpSingleReg(debug_interface, "FIFO_ADDR_PTR           = ", interface::Register::FIFO_ADDR_PTR          );
  debug_dumpSingleReg(debug_interface, "FIFO_TX_BASE_ADDR       = ", interface::Register::FIFO_TX_BASE_ADDR      );
  debug_dumpSingleReg(debug_interface, "FIFO_RX_BASE_ADDR       = ", interface::Register::FIFO_RX_BASE_ADDR      );
  debug_dumpSingleReg(debug_interface, "FIFO_RX_CURRENT_ADDR    = ", interface::Register::FIFO_RX_CURRENT_ADDR   );
  debug_dumpSingleReg(debug_interface, "IRQ_FLAGS_MASK          = ", interface::Register::IRQ_FLAGS_MASK         );
  debug_dumpSingleReg(debug_interface, "IRQ_FLAGS               = ", interface::Register::IRQ_FLAGS              );
  debug_dumpSingleReg(debug_interface, "RX_NB_BYTES             = ", interface::Register::RX_NB_BYTES            );
  debug_dumpSingleReg(debug_interface, "RX_HEADER_CNT_VALUE_MSB = ", interface::Register::RX_HEADER_CNT_VALUE_MSB);
  debug_dumpSingleReg(debug_interface, "RX_HEADER_CNT_VALUE_LSB = ", interface::Register::RX_HEADER_CNT_VALUE_LSB);
  debug_dumpSingleReg(debug_interface, "RX_PACKET_CNT_VALUE_MSB = ", interface::Register::RX_PACKET_CNT_VALUE_MSB);
  debug_dumpSingleReg(debug_interface, "RX_PACKET_CNT_VALUE_LSB = ", interface::Register::RX_PACKET_CNT_VALUE_LSB);
  debug_dumpSingleReg(debug_interface, "MODEM_STAT              = ", interface::Register::MODEM_STAT             );
  debug_dumpSingleReg(debug_interface, "PKT_SNR_VALUE           = ", interface::Register::PKT_SNR_VALUE          );
  debug_dumpSingleReg(debug_interface, "PKT_RSSI_VALUE          = ", interface::Register::PKT_RSSI_VALUE         );
  debug_dumpSingleReg(debug_interface, "RSSI_VALUE              = ", interface::Register::RSSI_VALUE             );
  debug_dumpSingleReg(debug_interface, "HOP_CHANNEL             = ", interface::Register::HOP_CHANNEL            );
  debug_dumpSingleReg(debug_interface, "MODEM_CONFIG1           = ", interface::Register::MODEM_CONFIG1          );
  debug_dumpSingleReg(debug_interface, "MODEM_CONFIG2           = ", interface::Register::MODEM_CONFIG2          );
  debug_dumpSingleReg(debug_interface, "SYMB_TIMEOUT_LSB        = ", interface::Register::SYMB_TIMEOUT_LSB       );
  debug_dumpSingleReg(debug_interface, "PREAMBLE_MSB            = ", interface::Register::PREAMBLE_MSB           );
  debug_dumpSingleReg(debug_interface, "PREAMBLE_LSB            = ", interface::Register::PREAMBLE_LSB           );
  debug_dumpSingleReg(debug_interface, "PAYLOAD_LENGTH          = ", interface::Register::PAYLOAD_LENGTH         );
  debug_dumpSingleReg(debug_interface, "MAX_PAYLOAD_LENGTH      = ", interface::Register::MAX_PAYLOAD_LENGTH     );
  debug_dumpSingleReg(debug_interface, "HOP_PERIOD              = ", interface::Register::HOP_PERIOD             );
  debug_dumpSingleReg(debug_interface, "FIFO_RX_BYTE_ADDR       = ", interface::Register::FIFO_RX_BYTE_ADDR      );
  debug_dumpSingleReg(debug_interface, "MODEM_CONFIG3           = ", interface::Register::MODEM_CONFIG3          );

  debug_dumpSingleReg(debug_interface, "PPM_CORRECTION          = ", interface::Register::PPM_CORRECTION         );
  debug_dumpSingleReg(debug_interface, "FEI_MSB                 = ", interface::Register::FEI_MSB                );
  debug_dumpSingleReg(debug_interface, "FEI_MID                 = ", interface::Register::FEI_MID                );
  debug_dumpSingleReg(debug_interface, "FEI_LSB                 = ", interface::Register::FEI_LSB                );
  debug_dumpSingleReg(debug_interface, "RSSI_WIDEBAND           = ", interface::Register::RSSI_WIDEBAND          );
  debug_dumpSingleReg(debug_interface, "DETECT_OPTIMIZ          = ", interface::Register::DETECT_OPTIMIZ         );
  debug_dumpSingleReg(debug_interface, "INVERT_IQ               = ", interface::Register::INVERT_IQ              );
  debug_dumpSingleReg(debug_interface, "DETECTION_THRESHOLD     = ", interface::Register::DETECTION_THRESHOLD    );
  debug_dumpSingleReg(debug_interface, "SYNC_WORD               = ", interface::Register::SYNC_WORD              );

  debug_dumpSingleReg(debug_interface, "DIO_MAPPING1            = ", interface::Register::DIO_MAPPING1           );
  debug_dumpSingleReg(debug_interface, "DIO_MAPPING2            = ", interface::Register::DIO_MAPPING2           );
  debug_dumpSingleReg(debug_interface, "VERSION                 = ", interface::Register::VERSION                );

  debug_dumpSingleReg(debug_interface, "TCXO                    = ", interface::Register::TCXO                   );
  debug_dumpSingleReg(debug_interface, "PA_DAC                  = ", interface::Register::PA_DAC                 );
  debug_dumpSingleReg(debug_interface, "FORMER_TEMP             = ", interface::Register::FORMER_TEMP            );
  debug_dumpSingleReg(debug_interface, "AGC_REF                 = ", interface::Register::AGC_REF                );
  debug_dumpSingleReg(debug_interface, "AGC_THRESH1             = ", interface::Register::AGC_THRESH1            );
  debug_dumpSingleReg(debug_interface, "AGC_THRESH2             = ", interface::Register::AGC_THRESH2            );
  debug_dumpSingleReg(debug_interface, "AGC_THRESH3             = ", interface::Register::AGC_THRESH3            );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, interface::Register const reg)
{
  uint8_t reg_content = 0;

  _io.readRegister(reg, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
