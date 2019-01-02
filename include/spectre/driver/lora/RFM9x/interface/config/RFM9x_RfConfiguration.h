/**
 * Spectre is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_TRANSCEIVERCONFIGURATION_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_TRANSCEIVERCONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <spectre/driver/lora/RFM9x/interface/RFM9x_RegisterBits.h>

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

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class LoRaMode : uint8_t
{
  FSK_OOK       = 0,
  LoRa          = RFM9x_REG_OP_MODE_LONG_RANGE_MODE_bm
};

enum class ModulationType : uint8_t
{
  FSK           = 0,
  OOK           = RFM9x_REG_OP_MODE_MODULATION_TYPE_0_bm
};

enum class HeaderMode : uint8_t
{
  Explicit = 0,
  Implicit = RFM9x_REG_MODEM_CONFIG_1_IMPLICIT_HEADER_MODE_ON_bm
};

enum class PacketFormat : uint8_t
{
  FixedLength    = 0,
  VariableLength = RFM9x_REG_PACKET_CONFIG_1_PACKET_FORMAT_bm
};

enum class SignalBandwidth : uint8_t
{
  BW_7_8_kHz    = 0,
  BW_10_4_kHz   =                                                                                                                               RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_0_bm,
  BW_15_6_kHz   =                                                                                     RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_1_bm,
  BW_20_8_kHz   =                                                                                     RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_1_bm | RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_0_bm,
  BW_31_25_kHz  =                                           RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_2_bm,
  BW_41_7_kHz   =                                           RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_2_bm |                                           RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_0_bm,
  BW_62_5_kHz   =                                           RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_2_bm | RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_1_bm,
  BW_125_kHz    =                                           RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_2_bm | RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_1_bm | RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_0_bm,
  BW_250_kHz    = RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_3_bm,
  BW_500_kHz    = RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_3_bm |                                                                                     RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_0_bm
};

enum class CodingRate : uint8_t
{
  CR_4_5 =                                                                                        RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_0_bm,
  CR_4_6 =                                            RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_1_bm,
  CR_4_7 =                                            RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_1_bm | RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_0_bm,
  CR_4_8 = RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_2_bm
};

enum class SpreadingFactor : uint8_t
{
  SF_64   = /*  6 */                                                  RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_2_bm | RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_1_bm,
  SF_128  = /*  7 */                                                  RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_2_bm | RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_1_bm | RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_0_bm,
  SF_256  = /*  8 */ RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_3_bm,
  SF_512  = /*  9 */ RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_3_bm |                                                                                                   RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_0_bm,
  SF_1024 = /* 10 */ RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_3_bm |                                                  RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_1_bm,
  SF_2048 = /* 11 */ RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_3_bm |                                                  RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_1_bm | RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_0_bm,
  SF_4096 = /* 12 */ RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_3_bm |  RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_2_bm
};

enum class TransceiverLocation : uint8_t
{
  Static = 0,
  Mobile = RFM9x_REG_MODEM_CONFIG_3_MOBILE_NODE_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_RfConfiguration
{

public:

           RFM9x_RfConfiguration() { }
  virtual ~RFM9x_RfConfiguration() { }


  virtual void setLoRaMode            (LoRaMode            const lora_mode           ) = 0;
  virtual void setModulationType      (ModulationType      const modulation_type     ) = 0;
  virtual void setHeaderMode          (HeaderMode          const header_mode         ) = 0;
  virtual void setPacketFormat        (PacketFormat        const packet_format       ) = 0;
  virtual void setFrequency           (uint32_t            const freq_Hz             ) = 0;
  virtual void setSignalBandwidth     (SignalBandwidth     const signal_bandwidth    ) = 0;
  virtual void setCodingRate          (CodingRate          const coding_rate         ) = 0;
  virtual void setSpreadingFactor     (SpreadingFactor     const spreading_factor    ) = 0;
  virtual void setPreambleLength      (uint16_t            const preamble_length     ) = 0;
  virtual void setTransceiverLocation (TransceiverLocation const transceiver_location) = 0;
  virtual void setRxSymbolTimeout     (uint16_t            const rx_symbol_timeout   ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_TRANSCEIVERCONFIGURATION_H_ */
