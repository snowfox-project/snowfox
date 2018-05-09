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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONFIGURATION_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/interface/RFM9x_FifoConfiguration.h>
#include <spectre/driver/lora/RFM9x/interface/RFM9x_TransceiverConfiguration.h>

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
 * TYPEDEFS
 **************************************************************************************/

enum class OperatingMode : uint8_t
{
  SLEEP        = 0,
  STDBY        =                                                             RFM9x_REG_OP_MODE_MODE_0_bm,
  FSTX         =                               RFM9x_REG_OP_MODE_MODE_1_bm,
  TX           =                               RFM9x_REG_OP_MODE_MODE_1_bm | RFM9x_REG_OP_MODE_MODE_0_bm,
  FSRX         = RFM9x_REG_OP_MODE_MODE_2_bm,
  RXCONTINUOUS = RFM9x_REG_OP_MODE_MODE_2_bm |                               RFM9x_REG_OP_MODE_MODE_0_bm,
  RXSINGLE     = RFM9x_REG_OP_MODE_MODE_2_bm | RFM9x_REG_OP_MODE_MODE_1_bm,
  CAD          = RFM9x_REG_OP_MODE_MODE_2_bm | RFM9x_REG_OP_MODE_MODE_1_bm | RFM9x_REG_OP_MODE_MODE_0_bm
};

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

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Configuration : public RFM9x_TransceiverConfiguration,
                            public RFM9x_FifoConfiguration
{

public:

           RFM9x_Configuration() { }
  virtual ~RFM9x_Configuration() { }


  virtual void setOperatingMode   (OperatingMode   const op_mode         ) = 0;
  virtual void setLoRaMode        (LoRaMode        const lora_mode       ) = 0;
  virtual void setModulationType  (ModulationType  const modulation_type ) = 0;
  virtual void setHeaderMode      (HeaderMode      const header_mode     ) = 0;
  virtual void setPacketFormat    (PacketFormat    const packet_format   ) = 0;

  virtual void setFrequency       (uint32_t        const freq_Hz         ) = 0;
  virtual void setSignalBandwidth (SignalBandwidth const signal_bandwidth) = 0;
  virtual void setCodingRate      (CodingRate      const coding_rate     ) = 0;
  virtual void setSpreadingFactor (SpreadingFactor const spreading_factor) = 0;
  virtual void setPreambleLength  (uint16_t        const preamble_length ) = 0;

  virtual bool setTxFifoSize      (uint16_t        const tx_fifo_size    ) = 0;
  virtual bool setRxFifoSize      (uint16_t        const rx_fifo_size    ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONFIGURATION_H_ */
