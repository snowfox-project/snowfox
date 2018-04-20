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

#if defined(MCU_ARCH_avr)
  #define FLASH_DECLARE(x) PROGMEM x
#else
  #define FLASH_DECLARE(x) x
#endif

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const OP_MODE                [] = "OP_MODE                 = ");
FLASH_DECLARE(static char const FRF_MSB                [] = "FRF_MSB                 = ");
FLASH_DECLARE(static char const FRF_MID                [] = "FRF_MID                 = ");
FLASH_DECLARE(static char const FRF_LSB                [] = "FRF_LSB                 = ");
FLASH_DECLARE(static char const PA_CONFIG              [] = "PA_CONFIG               = ");
FLASH_DECLARE(static char const PA_RAMP                [] = "PA_RAMP                 = ");
FLASH_DECLARE(static char const OCP                    [] = "OCP                     = ");
FLASH_DECLARE(static char const LNA                    [] = "LNA                     = ");
FLASH_DECLARE(static char const FIFO_ADDR_PTR          [] = "FIFO_ADDR_PTR           = ");
FLASH_DECLARE(static char const FIFO_TX_BASE_ADDR      [] = "FIFO_TX_BASE_ADDR       = ");
FLASH_DECLARE(static char const FIFO_RX_BASE_ADDR      [] = "FIFO_RX_BASE_ADDR       = ");
FLASH_DECLARE(static char const FIFO_RX_CURRENT_ADDR   [] = "FIFO_RX_CURRENT_ADDR    = ");
FLASH_DECLARE(static char const IRQ_FLAGS_MASK         [] = "IRQ_FLAGS_MASK          = ");
FLASH_DECLARE(static char const IRQ_FLAGS              [] = "IRQ_FLAGS               = ");
FLASH_DECLARE(static char const RX_NB_BYTES            [] = "RX_NB_BYTES             = ");
FLASH_DECLARE(static char const RX_HEADER_CNT_VALUE_MSB[] = "RX_HEADER_CNT_VALUE_MSB = ");
FLASH_DECLARE(static char const RX_HEADER_CNT_VALUE_LSB[] = "RX_HEADER_CNT_VALUE_LSB = ");
FLASH_DECLARE(static char const RX_PACKET_CNT_VALUE_MSB[] = "RX_PACKET_CNT_VALUE_MSB = ");
FLASH_DECLARE(static char const RX_PACKET_CNT_VALUE_LSB[] = "RX_PACKET_CNT_VALUE_LSB = ");
FLASH_DECLARE(static char const MODEM_STAT             [] = "MODEM_STAT              = ");
FLASH_DECLARE(static char const PKT_SNR_VALUE          [] = "PKT_SNR_VALUE           = ");
FLASH_DECLARE(static char const PKT_RSSI_VALUE         [] = "PKT_RSSI_VALUE          = ");
FLASH_DECLARE(static char const RSSI_VALUE             [] = "RSSI_VALUE              = ");
FLASH_DECLARE(static char const HOP_CHANNEL            [] = "HOP_CHANNEL             = ");
FLASH_DECLARE(static char const MODEM_CONFIG1          [] = "MODEM_CONFIG1           = ");
FLASH_DECLARE(static char const MODEM_CONFIG2          [] = "MODEM_CONFIG2           = ");
FLASH_DECLARE(static char const SYMB_TIMEOUT_LSB       [] = "SYMB_TIMEOUT_LSB        = ");
FLASH_DECLARE(static char const PREAMBLE_MSB           [] = "PREAMBLE_MSB            = ");
FLASH_DECLARE(static char const PREAMBLE_LSB           [] = "PREAMBLE_LSB            = ");
FLASH_DECLARE(static char const PAYLOAD_LENGTH         [] = "PAYLOAD_LENGTH          = ");
FLASH_DECLARE(static char const MAX_PAYLOAD_LENGTH     [] = "MAX_PAYLOAD_LENGTH      = ");
FLASH_DECLARE(static char const HOP_PERIOD             [] = "HOP_PERIOD              = ");
FLASH_DECLARE(static char const FIFO_RX_BYTE_ADDR      [] = "FIFO_RX_BYTE_ADDR       = ");
FLASH_DECLARE(static char const MODEM_CONFIG3          [] = "MODEM_CONFIG3           = ");

FLASH_DECLARE(static char const PPM_CORRECTION         [] = "PPM_CORRECTION          = ");
FLASH_DECLARE(static char const FEI_MSB                [] = "FEI_MSB                 = ");
FLASH_DECLARE(static char const FEI_MID                [] = "FEI_MID                 = ");
FLASH_DECLARE(static char const FEI_LSB                [] = "FEI_LSB                 = ");
FLASH_DECLARE(static char const RSSI_WIDEBAND          [] = "RSSI_WIDEBAND           = ");
FLASH_DECLARE(static char const DETECT_OPTIMIZ         [] = "DETECT_OPTIMIZ          = ");
FLASH_DECLARE(static char const INVERT_IQ              [] = "INVERT_IQ               = ");
FLASH_DECLARE(static char const DETECTION_THRESHOLD    [] = "DETECTION_THRESHOLD     = ");
FLASH_DECLARE(static char const SYNC_WORD              [] = "SYNC_WORD               = ");

FLASH_DECLARE(static char const DIO_MAPPING1           [] = "DIO_MAPPING1            = ");
FLASH_DECLARE(static char const DIO_MAPPING2           [] = "DIO_MAPPING2            = ");
FLASH_DECLARE(static char const VERSION                [] = "VERSION                 = ");

FLASH_DECLARE(static char const TCXO                   [] = "TCXO                    = ");
FLASH_DECLARE(static char const PA_DAC                 [] = "PA_DAC                  = ");
FLASH_DECLARE(static char const FORMER_TEMP            [] = "FORMER_TEMP             = ");
FLASH_DECLARE(static char const AGC_REF                [] = "AGC_REF                 = ");
FLASH_DECLARE(static char const AGC_THRESH1            [] = "AGC_THRESH1             = ");
FLASH_DECLARE(static char const AGC_THRESH2            [] = "AGC_THRESH2             = ");
FLASH_DECLARE(static char const AGC_THRESH3            [] = "AGC_THRESH3             = ");

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_Control::RFM9x_Control(interface::RFM9x_Io & io, uint32_t const fxosc_Hz)
: _io      (io      ),
  _fxosc_Hz(fxosc_Hz)
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

void RFM9x_Control::setLoRaMode(interface::LoRaMode const lora_mode)
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

void RFM9x_Control::setFrequency(uint32_t const f_rf_Hz)
{
  float    const f_step_Hz = static_cast<float>(_fxosc_Hz) / 524288.0;
  uint32_t const f_rf      = static_cast<uint32_t>(f_step_Hz / static_cast<float>(f_rf_Hz));

  uint8_t const f_rf_msb = static_cast<uint8_t>((f_rf & 0x00FF0000) >> 16);
  uint8_t const f_rf_mid = static_cast<uint8_t>((f_rf & 0x0000FF00) >>  8);
  uint8_t const f_rf_lsb = static_cast<uint8_t>((f_rf & 0x000000FF) >>  0);

  _io.writeRegister(interface::Register::FRF_MSB, f_rf_msb);
  _io.writeRegister(interface::Register::FRF_MID, f_rf_mid);
  _io.writeRegister(interface::Register::FRF_LSB, f_rf_lsb);
}

void RFM9x_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash)
{
  debug_dumpSingleReg(debug_interface, flash, OP_MODE                , interface::Register::OP_MODE                );
  debug_dumpSingleReg(debug_interface, flash, FRF_MSB                , interface::Register::FRF_MSB                );
  debug_dumpSingleReg(debug_interface, flash, FRF_MID                , interface::Register::FRF_MID                );
  debug_dumpSingleReg(debug_interface, flash, FRF_LSB                , interface::Register::FRF_LSB                );
  debug_dumpSingleReg(debug_interface, flash, PA_CONFIG              , interface::Register::PA_CONFIG              );
  debug_dumpSingleReg(debug_interface, flash, PA_RAMP                , interface::Register::PA_RAMP                );
  debug_dumpSingleReg(debug_interface, flash, OCP                    , interface::Register::OCP                    );
  debug_dumpSingleReg(debug_interface, flash, LNA                    , interface::Register::LNA                    );
  debug_dumpSingleReg(debug_interface, flash, FIFO_ADDR_PTR          , interface::Register::FIFO_ADDR_PTR          );
  debug_dumpSingleReg(debug_interface, flash, FIFO_TX_BASE_ADDR      , interface::Register::FIFO_TX_BASE_ADDR      );
  debug_dumpSingleReg(debug_interface, flash, FIFO_RX_BASE_ADDR      , interface::Register::FIFO_RX_BASE_ADDR      );
  debug_dumpSingleReg(debug_interface, flash, FIFO_RX_CURRENT_ADDR   , interface::Register::FIFO_RX_CURRENT_ADDR   );
  debug_dumpSingleReg(debug_interface, flash, IRQ_FLAGS_MASK         , interface::Register::IRQ_FLAGS_MASK         );
  debug_dumpSingleReg(debug_interface, flash, IRQ_FLAGS              , interface::Register::IRQ_FLAGS              );
  debug_dumpSingleReg(debug_interface, flash, RX_NB_BYTES            , interface::Register::RX_NB_BYTES            );
  debug_dumpSingleReg(debug_interface, flash, RX_HEADER_CNT_VALUE_MSB, interface::Register::RX_HEADER_CNT_VALUE_MSB);
  debug_dumpSingleReg(debug_interface, flash, RX_HEADER_CNT_VALUE_LSB, interface::Register::RX_HEADER_CNT_VALUE_LSB);
  debug_dumpSingleReg(debug_interface, flash, RX_PACKET_CNT_VALUE_MSB, interface::Register::RX_PACKET_CNT_VALUE_MSB);
  debug_dumpSingleReg(debug_interface, flash, RX_PACKET_CNT_VALUE_LSB, interface::Register::RX_PACKET_CNT_VALUE_LSB);
  debug_dumpSingleReg(debug_interface, flash, MODEM_STAT             , interface::Register::MODEM_STAT             );
  debug_dumpSingleReg(debug_interface, flash, PKT_SNR_VALUE          , interface::Register::PKT_SNR_VALUE          );
  debug_dumpSingleReg(debug_interface, flash, PKT_RSSI_VALUE         , interface::Register::PKT_RSSI_VALUE         );
  debug_dumpSingleReg(debug_interface, flash, RSSI_VALUE             , interface::Register::RSSI_VALUE             );
  debug_dumpSingleReg(debug_interface, flash, HOP_CHANNEL            , interface::Register::HOP_CHANNEL            );
  debug_dumpSingleReg(debug_interface, flash, MODEM_CONFIG1          , interface::Register::MODEM_CONFIG1          );
  debug_dumpSingleReg(debug_interface, flash, MODEM_CONFIG2          , interface::Register::MODEM_CONFIG2          );
  debug_dumpSingleReg(debug_interface, flash, SYMB_TIMEOUT_LSB       , interface::Register::SYMB_TIMEOUT_LSB       );
  debug_dumpSingleReg(debug_interface, flash, PREAMBLE_MSB           , interface::Register::PREAMBLE_MSB           );
  debug_dumpSingleReg(debug_interface, flash, PREAMBLE_LSB           , interface::Register::PREAMBLE_LSB           );
  debug_dumpSingleReg(debug_interface, flash, PAYLOAD_LENGTH         , interface::Register::PAYLOAD_LENGTH         );
  debug_dumpSingleReg(debug_interface, flash, MAX_PAYLOAD_LENGTH     , interface::Register::MAX_PAYLOAD_LENGTH     );
  debug_dumpSingleReg(debug_interface, flash, HOP_PERIOD             , interface::Register::HOP_PERIOD             );
  debug_dumpSingleReg(debug_interface, flash, FIFO_RX_BYTE_ADDR      , interface::Register::FIFO_RX_BYTE_ADDR      );
  debug_dumpSingleReg(debug_interface, flash, MODEM_CONFIG3          , interface::Register::MODEM_CONFIG3          );

  debug_dumpSingleReg(debug_interface, flash, PPM_CORRECTION         , interface::Register::PPM_CORRECTION         );
  debug_dumpSingleReg(debug_interface, flash, FEI_MSB                , interface::Register::FEI_MSB                );
  debug_dumpSingleReg(debug_interface, flash, FEI_MID                , interface::Register::FEI_MID                );
  debug_dumpSingleReg(debug_interface, flash, FEI_LSB                , interface::Register::FEI_LSB                );
  debug_dumpSingleReg(debug_interface, flash, RSSI_WIDEBAND          , interface::Register::RSSI_WIDEBAND          );
  debug_dumpSingleReg(debug_interface, flash, DETECT_OPTIMIZ         , interface::Register::DETECT_OPTIMIZ         );
  debug_dumpSingleReg(debug_interface, flash, INVERT_IQ              , interface::Register::INVERT_IQ              );
  debug_dumpSingleReg(debug_interface, flash, DETECTION_THRESHOLD    , interface::Register::DETECTION_THRESHOLD    );
  debug_dumpSingleReg(debug_interface, flash, SYNC_WORD              , interface::Register::SYNC_WORD              );

  debug_dumpSingleReg(debug_interface, flash, DIO_MAPPING1           , interface::Register::DIO_MAPPING1           );
  debug_dumpSingleReg(debug_interface, flash, DIO_MAPPING2           , interface::Register::DIO_MAPPING2           );
  debug_dumpSingleReg(debug_interface, flash, VERSION                , interface::Register::VERSION                );

  debug_dumpSingleReg(debug_interface, flash, TCXO                   , interface::Register::TCXO                   );
  debug_dumpSingleReg(debug_interface, flash, PA_DAC                 , interface::Register::PA_DAC                 );
  debug_dumpSingleReg(debug_interface, flash, FORMER_TEMP            , interface::Register::FORMER_TEMP            );
  debug_dumpSingleReg(debug_interface, flash, AGC_REF                , interface::Register::AGC_REF                );
  debug_dumpSingleReg(debug_interface, flash, AGC_THRESH1            , interface::Register::AGC_THRESH1            );
  debug_dumpSingleReg(debug_interface, flash, AGC_THRESH2            , interface::Register::AGC_THRESH2            );
  debug_dumpSingleReg(debug_interface, flash, AGC_THRESH3            , interface::Register::AGC_THRESH3            );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  _io.readRegister(reg, &reg_content);

  debug_interface.print("%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
