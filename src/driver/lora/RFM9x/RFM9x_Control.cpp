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

#if defined(MCU_ARCH_avr)
#include <avr/pgmspace.h>
#endif

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
 * DEFINES
 **************************************************************************************/

#if not defined(MCU_ARCH_avr)
//#define PROGMEM /* Define PROGMEM as empty string if we are not using avr-gcc since this macro is used to store the strings into flash instead of RAM */
#endif

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static char const OP_MODE                [] PROGMEM = "OP_MODE                 = ";
static char const FRF_MSB                [] PROGMEM = "FRF_MSB                 = ";
static char const FRF_MID                [] PROGMEM = "FRF_MID                 = ";
static char const FRF_LSB                [] PROGMEM = "FRF_LSB                 = ";
static char const PA_CONFIG              [] PROGMEM = "PA_CONFIG               = ";
static char const PA_RAMP                [] PROGMEM = "PA_RAMP                 = ";
static char const OCP                    [] PROGMEM = "OCP                     = ";
static char const LNA                    [] PROGMEM = "LNA                     = ";
static char const FIFO_ADDR_PTR          [] PROGMEM = "FIFO_ADDR_PTR           = ";
static char const FIFO_TX_BASE_ADDR      [] PROGMEM = "FIFO_TX_BASE_ADDR       = ";
static char const FIFO_RX_BASE_ADDR      [] PROGMEM = "FIFO_RX_BASE_ADDR       = ";
static char const FIFO_RX_CURRENT_ADDR   [] PROGMEM = "FIFO_RX_CURRENT_ADDR    = ";
static char const IRQ_FLAGS_MASK         [] PROGMEM = "IRQ_FLAGS_MASK          = ";
static char const IRQ_FLAGS              [] PROGMEM = "IRQ_FLAGS               = ";
static char const RX_NB_BYTES            [] PROGMEM = "RX_NB_BYTES             = ";
static char const RX_HEADER_CNT_VALUE_MSB[] PROGMEM = "RX_HEADER_CNT_VALUE_MSB = ";
static char const RX_HEADER_CNT_VALUE_LSB[] PROGMEM = "RX_HEADER_CNT_VALUE_LSB = ";
static char const RX_PACKET_CNT_VALUE_MSB[] PROGMEM = "RX_PACKET_CNT_VALUE_MSB = ";
static char const RX_PACKET_CNT_VALUE_LSB[] PROGMEM = "RX_PACKET_CNT_VALUE_LSB = ";
static char const MODEM_STAT             [] PROGMEM = "MODEM_STAT              = ";
static char const PKT_SNR_VALUE          [] PROGMEM = "PKT_SNR_VALUE           = ";
static char const PKT_RSSI_VALUE         [] PROGMEM = "PKT_RSSI_VALUE          = ";
static char const RSSI_VALUE             [] PROGMEM = "RSSI_VALUE              = ";
static char const HOP_CHANNEL            [] PROGMEM = "HOP_CHANNEL             = ";
static char const MODEM_CONFIG1          [] PROGMEM = "MODEM_CONFIG1           = ";
static char const MODEM_CONFIG2          [] PROGMEM = "MODEM_CONFIG2           = ";
static char const SYMB_TIMEOUT_LSB       [] PROGMEM = "SYMB_TIMEOUT_LSB        = ";
static char const PREAMBLE_MSB           [] PROGMEM = "PREAMBLE_MSB            = ";
static char const PREAMBLE_LSB           [] PROGMEM = "PREAMBLE_LSB            = ";
static char const PAYLOAD_LENGTH         [] PROGMEM = "PAYLOAD_LENGTH          = ";
static char const MAX_PAYLOAD_LENGTH     [] PROGMEM = "MAX_PAYLOAD_LENGTH      = ";
static char const HOP_PERIOD             [] PROGMEM = "HOP_PERIOD              = ";
static char const FIFO_RX_BYTE_ADDR      [] PROGMEM = "FIFO_RX_BYTE_ADDR       = ";
static char const MODEM_CONFIG3          [] PROGMEM = "MODEM_CONFIG3           = ";

static char const PPM_CORRECTION         [] PROGMEM = "PPM_CORRECTION          = ";
static char const FEI_MSB                [] PROGMEM = "FEI_MSB                 = ";
static char const FEI_MID                [] PROGMEM = "FEI_MID                 = ";
static char const FEI_LSB                [] PROGMEM = "FEI_LSB                 = ";
static char const RSSI_WIDEBAND          [] PROGMEM = "RSSI_WIDEBAND           = ";
static char const DETECT_OPTIMIZ         [] PROGMEM = "DETECT_OPTIMIZ          = ";
static char const INVERT_IQ              [] PROGMEM = "INVERT_IQ               = ";
static char const DETECTION_THRESHOLD    [] PROGMEM = "DETECTION_THRESHOLD     = ";
static char const SYNC_WORD              [] PROGMEM = "SYNC_WORD               = ";

static char const DIO_MAPPING1           [] PROGMEM = "DIO_MAPPING1            = ";
static char const DIO_MAPPING2           [] PROGMEM = "DIO_MAPPING2            = ";
static char const VERSION                [] PROGMEM = "VERSION                 = ";

static char const TCXO                   [] PROGMEM = "TCXO                    = ";
static char const PA_DAC                 [] PROGMEM = "PA_DAC                  = ";
static char const FORMER_TEMP            [] PROGMEM = "FORMER_TEMP             = ";
static char const AGC_REF                [] PROGMEM = "AGC_REF                 = ";
static char const AGC_THRESH1            [] PROGMEM = "AGC_THRESH1             = ";
static char const AGC_THRESH2            [] PROGMEM = "AGC_THRESH2             = ";
static char const AGC_THRESH3            [] PROGMEM = "AGC_THRESH3             = ";

/**************************************************************************************
 * PROTOTYPES
 **************************************************************************************/

char const * loadFromFlash(const char * flash_str);

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_Control::RFM9x_Control(interface::RFM9x_Io & io)
: _io(io)
{
  setTxFifoBaseAddress(0);
  setRxFifoBaseAddress(0);
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
  debug_dumpSingleReg(debug_interface, loadFromFlash(OP_MODE                ), interface::Register::OP_MODE                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FRF_MSB                ), interface::Register::FRF_MSB                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FRF_MID                ), interface::Register::FRF_MID                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FRF_LSB                ), interface::Register::FRF_LSB                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(PA_CONFIG              ), interface::Register::PA_CONFIG              );
  debug_dumpSingleReg(debug_interface, loadFromFlash(PA_RAMP                ), interface::Register::PA_RAMP                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(OCP                    ), interface::Register::OCP                    );
  debug_dumpSingleReg(debug_interface, loadFromFlash(LNA                    ), interface::Register::LNA                    );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FIFO_ADDR_PTR          ), interface::Register::FIFO_ADDR_PTR          );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FIFO_TX_BASE_ADDR      ), interface::Register::FIFO_TX_BASE_ADDR      );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FIFO_RX_BASE_ADDR      ), interface::Register::FIFO_RX_BASE_ADDR      );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FIFO_RX_CURRENT_ADDR   ), interface::Register::FIFO_RX_CURRENT_ADDR   );
  debug_dumpSingleReg(debug_interface, loadFromFlash(IRQ_FLAGS_MASK         ), interface::Register::IRQ_FLAGS_MASK         );
  debug_dumpSingleReg(debug_interface, loadFromFlash(IRQ_FLAGS              ), interface::Register::IRQ_FLAGS              );
  debug_dumpSingleReg(debug_interface, loadFromFlash(RX_NB_BYTES            ), interface::Register::RX_NB_BYTES            );
  debug_dumpSingleReg(debug_interface, loadFromFlash(RX_HEADER_CNT_VALUE_MSB), interface::Register::RX_HEADER_CNT_VALUE_MSB);
  debug_dumpSingleReg(debug_interface, loadFromFlash(RX_HEADER_CNT_VALUE_LSB), interface::Register::RX_HEADER_CNT_VALUE_LSB);
  debug_dumpSingleReg(debug_interface, loadFromFlash(RX_PACKET_CNT_VALUE_MSB), interface::Register::RX_PACKET_CNT_VALUE_MSB);
  debug_dumpSingleReg(debug_interface, loadFromFlash(RX_PACKET_CNT_VALUE_LSB), interface::Register::RX_PACKET_CNT_VALUE_LSB);
  debug_dumpSingleReg(debug_interface, loadFromFlash(MODEM_STAT             ), interface::Register::MODEM_STAT             );
  debug_dumpSingleReg(debug_interface, loadFromFlash(PKT_SNR_VALUE          ), interface::Register::PKT_SNR_VALUE          );
  debug_dumpSingleReg(debug_interface, loadFromFlash(PKT_RSSI_VALUE         ), interface::Register::PKT_RSSI_VALUE         );
  debug_dumpSingleReg(debug_interface, loadFromFlash(RSSI_VALUE             ), interface::Register::RSSI_VALUE             );
  debug_dumpSingleReg(debug_interface, loadFromFlash(HOP_CHANNEL            ), interface::Register::HOP_CHANNEL            );
  debug_dumpSingleReg(debug_interface, loadFromFlash(MODEM_CONFIG1          ), interface::Register::MODEM_CONFIG1          );
  debug_dumpSingleReg(debug_interface, loadFromFlash(MODEM_CONFIG2          ), interface::Register::MODEM_CONFIG2          );
  debug_dumpSingleReg(debug_interface, loadFromFlash(SYMB_TIMEOUT_LSB       ), interface::Register::SYMB_TIMEOUT_LSB       );
  debug_dumpSingleReg(debug_interface, loadFromFlash(PREAMBLE_MSB           ), interface::Register::PREAMBLE_MSB           );
  debug_dumpSingleReg(debug_interface, loadFromFlash(PREAMBLE_LSB           ), interface::Register::PREAMBLE_LSB           );
  debug_dumpSingleReg(debug_interface, loadFromFlash(PAYLOAD_LENGTH         ), interface::Register::PAYLOAD_LENGTH         );
  debug_dumpSingleReg(debug_interface, loadFromFlash(MAX_PAYLOAD_LENGTH     ), interface::Register::MAX_PAYLOAD_LENGTH     );
  debug_dumpSingleReg(debug_interface, loadFromFlash(HOP_PERIOD             ), interface::Register::HOP_PERIOD             );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FIFO_RX_BYTE_ADDR      ), interface::Register::FIFO_RX_BYTE_ADDR      );
  debug_dumpSingleReg(debug_interface, loadFromFlash(MODEM_CONFIG3          ), interface::Register::MODEM_CONFIG3          );

  debug_dumpSingleReg(debug_interface, loadFromFlash(PPM_CORRECTION         ), interface::Register::PPM_CORRECTION         );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FEI_MSB                ), interface::Register::FEI_MSB                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FEI_MID                ), interface::Register::FEI_MID                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FEI_LSB                ), interface::Register::FEI_LSB                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(RSSI_WIDEBAND          ), interface::Register::RSSI_WIDEBAND          );
  debug_dumpSingleReg(debug_interface, loadFromFlash(DETECT_OPTIMIZ         ), interface::Register::DETECT_OPTIMIZ         );
  debug_dumpSingleReg(debug_interface, loadFromFlash(INVERT_IQ              ), interface::Register::INVERT_IQ              );
  debug_dumpSingleReg(debug_interface, loadFromFlash(DETECTION_THRESHOLD    ), interface::Register::DETECTION_THRESHOLD    );
  debug_dumpSingleReg(debug_interface, loadFromFlash(SYNC_WORD              ), interface::Register::SYNC_WORD              );

  debug_dumpSingleReg(debug_interface, loadFromFlash(DIO_MAPPING1           ), interface::Register::DIO_MAPPING1           );
  debug_dumpSingleReg(debug_interface, loadFromFlash(DIO_MAPPING2           ), interface::Register::DIO_MAPPING2           );
  debug_dumpSingleReg(debug_interface, loadFromFlash(VERSION                ), interface::Register::VERSION                );

  debug_dumpSingleReg(debug_interface, loadFromFlash(TCXO                   ), interface::Register::TCXO                   );
  debug_dumpSingleReg(debug_interface, loadFromFlash(PA_DAC                 ), interface::Register::PA_DAC                 );
  debug_dumpSingleReg(debug_interface, loadFromFlash(FORMER_TEMP            ), interface::Register::FORMER_TEMP            );
  debug_dumpSingleReg(debug_interface, loadFromFlash(AGC_REF                ), interface::Register::AGC_REF                );
  debug_dumpSingleReg(debug_interface, loadFromFlash(AGC_THRESH1            ), interface::Register::AGC_THRESH1            );
  debug_dumpSingleReg(debug_interface, loadFromFlash(AGC_THRESH2            ), interface::Register::AGC_THRESH2            );
  debug_dumpSingleReg(debug_interface, loadFromFlash(AGC_THRESH3            ), interface::Register::AGC_THRESH3            );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, interface::Register const reg)
{
  uint8_t reg_content = 0;

  _io.readRegister(reg, &reg_content);

  debug_interface.print("%s%02X\n\r", msg, reg_content);
}

/**************************************************************************************
 * FUNCTIONS
 **************************************************************************************/

char const * loadFromFlash(const char * flash_str)
{
#if defined(MCU_ARCH_avr)
  static char buffer[32];
  strcpy_P(buffer, flash_str);
  return buffer;
#else
  return flash_str;
#endif
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
