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

#include <spectre/driver/lora/RFM9x/RFM9x_Debug.h>

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
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Debug::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, interface::RFM9x_Io & io)
{
  debug_dumpSingleReg(debug_interface, flash, io, OP_MODE                , interface::Register::OP_MODE                );
  debug_dumpSingleReg(debug_interface, flash, io, FRF_MSB                , interface::Register::FRF_MSB                );
  debug_dumpSingleReg(debug_interface, flash, io, FRF_MID                , interface::Register::FRF_MID                );
  debug_dumpSingleReg(debug_interface, flash, io, FRF_LSB                , interface::Register::FRF_LSB                );
  debug_dumpSingleReg(debug_interface, flash, io, PA_CONFIG              , interface::Register::PA_CONFIG              );
  debug_dumpSingleReg(debug_interface, flash, io, PA_RAMP                , interface::Register::PA_RAMP                );
  debug_dumpSingleReg(debug_interface, flash, io, OCP                    , interface::Register::OCP                    );
  debug_dumpSingleReg(debug_interface, flash, io, LNA                    , interface::Register::LNA                    );
  debug_dumpSingleReg(debug_interface, flash, io, FIFO_ADDR_PTR          , interface::Register::FIFO_ADDR_PTR          );
  debug_dumpSingleReg(debug_interface, flash, io, FIFO_TX_BASE_ADDR      , interface::Register::FIFO_TX_BASE_ADDR      );
  debug_dumpSingleReg(debug_interface, flash, io, FIFO_RX_BASE_ADDR      , interface::Register::FIFO_RX_BASE_ADDR      );
  debug_dumpSingleReg(debug_interface, flash, io, FIFO_RX_CURRENT_ADDR   , interface::Register::FIFO_RX_CURRENT_ADDR   );
  debug_dumpSingleReg(debug_interface, flash, io, IRQ_FLAGS_MASK         , interface::Register::IRQ_FLAGS_MASK         );
  debug_dumpSingleReg(debug_interface, flash, io, IRQ_FLAGS              , interface::Register::IRQ_FLAGS              );
  debug_dumpSingleReg(debug_interface, flash, io, RX_NB_BYTES            , interface::Register::RX_NB_BYTES            );
  debug_dumpSingleReg(debug_interface, flash, io, RX_HEADER_CNT_VALUE_MSB, interface::Register::RX_HEADER_CNT_VALUE_MSB);
  debug_dumpSingleReg(debug_interface, flash, io, RX_HEADER_CNT_VALUE_LSB, interface::Register::RX_HEADER_CNT_VALUE_LSB);
  debug_dumpSingleReg(debug_interface, flash, io, RX_PACKET_CNT_VALUE_MSB, interface::Register::RX_PACKET_CNT_VALUE_MSB);
  debug_dumpSingleReg(debug_interface, flash, io, RX_PACKET_CNT_VALUE_LSB, interface::Register::RX_PACKET_CNT_VALUE_LSB);
  debug_dumpSingleReg(debug_interface, flash, io, MODEM_STAT             , interface::Register::MODEM_STAT             );
  debug_dumpSingleReg(debug_interface, flash, io, PKT_SNR_VALUE          , interface::Register::PKT_SNR_VALUE          );
  debug_dumpSingleReg(debug_interface, flash, io, PKT_RSSI_VALUE         , interface::Register::PKT_RSSI_VALUE         );
  debug_dumpSingleReg(debug_interface, flash, io, RSSI_VALUE             , interface::Register::RSSI_VALUE             );
  debug_dumpSingleReg(debug_interface, flash, io, HOP_CHANNEL            , interface::Register::HOP_CHANNEL            );
  debug_dumpSingleReg(debug_interface, flash, io, MODEM_CONFIG1          , interface::Register::MODEM_CONFIG1          );
  debug_dumpSingleReg(debug_interface, flash, io, MODEM_CONFIG2          , interface::Register::MODEM_CONFIG2          );
  debug_dumpSingleReg(debug_interface, flash, io, SYMB_TIMEOUT_LSB       , interface::Register::SYMB_TIMEOUT_LSB       );
  debug_dumpSingleReg(debug_interface, flash, io, PREAMBLE_MSB           , interface::Register::PREAMBLE_MSB           );
  debug_dumpSingleReg(debug_interface, flash, io, PREAMBLE_LSB           , interface::Register::PREAMBLE_LSB           );
  debug_dumpSingleReg(debug_interface, flash, io, PAYLOAD_LENGTH         , interface::Register::PAYLOAD_LENGTH         );
  debug_dumpSingleReg(debug_interface, flash, io, MAX_PAYLOAD_LENGTH     , interface::Register::MAX_PAYLOAD_LENGTH     );
  debug_dumpSingleReg(debug_interface, flash, io, HOP_PERIOD             , interface::Register::HOP_PERIOD             );
  debug_dumpSingleReg(debug_interface, flash, io, FIFO_RX_BYTE_ADDR      , interface::Register::FIFO_RX_BYTE_ADDR      );
  debug_dumpSingleReg(debug_interface, flash, io, MODEM_CONFIG3          , interface::Register::MODEM_CONFIG3          );

  debug_dumpSingleReg(debug_interface, flash, io, PPM_CORRECTION         , interface::Register::PPM_CORRECTION         );
  debug_dumpSingleReg(debug_interface, flash, io, FEI_MSB                , interface::Register::FEI_MSB                );
  debug_dumpSingleReg(debug_interface, flash, io, FEI_MID                , interface::Register::FEI_MID                );
  debug_dumpSingleReg(debug_interface, flash, io, FEI_LSB                , interface::Register::FEI_LSB                );
  debug_dumpSingleReg(debug_interface, flash, io, RSSI_WIDEBAND          , interface::Register::RSSI_WIDEBAND          );
  debug_dumpSingleReg(debug_interface, flash, io, DETECT_OPTIMIZ         , interface::Register::DETECT_OPTIMIZ         );
  debug_dumpSingleReg(debug_interface, flash, io, INVERT_IQ              , interface::Register::INVERT_IQ              );
  debug_dumpSingleReg(debug_interface, flash, io, DETECTION_THRESHOLD    , interface::Register::DETECTION_THRESHOLD    );
  debug_dumpSingleReg(debug_interface, flash, io, SYNC_WORD              , interface::Register::SYNC_WORD              );

  debug_dumpSingleReg(debug_interface, flash, io, DIO_MAPPING1           , interface::Register::DIO_MAPPING1           );
  debug_dumpSingleReg(debug_interface, flash, io, DIO_MAPPING2           , interface::Register::DIO_MAPPING2           );
  debug_dumpSingleReg(debug_interface, flash, io, VERSION                , interface::Register::VERSION                );

  debug_dumpSingleReg(debug_interface, flash, io, TCXO                   , interface::Register::TCXO                   );
  debug_dumpSingleReg(debug_interface, flash, io, PA_DAC                 , interface::Register::PA_DAC                 );
  debug_dumpSingleReg(debug_interface, flash, io, FORMER_TEMP            , interface::Register::FORMER_TEMP            );
  debug_dumpSingleReg(debug_interface, flash, io, AGC_REF                , interface::Register::AGC_REF                );
  debug_dumpSingleReg(debug_interface, flash, io, AGC_THRESH1            , interface::Register::AGC_THRESH1            );
  debug_dumpSingleReg(debug_interface, flash, io, AGC_THRESH2            , interface::Register::AGC_THRESH2            );
  debug_dumpSingleReg(debug_interface, flash, io, AGC_THRESH3            , interface::Register::AGC_THRESH3            );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Debug::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, interface::RFM9x_Io & io, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  io.readRegister(reg, &reg_content);

  debug_interface.print("%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
