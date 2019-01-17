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

#ifndef INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_IO_H_
#define INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_IO_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

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

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  FIFO                    = 0x00,
  OP_MODE                 = 0x01,
  FRF_MSB                 = 0x06,
  FRF_MID                 = 0x07,
  FRF_LSB                 = 0x08,
  PA_CONFIG               = 0x09,
  PA_RAMP                 = 0x0A,
  OCP                     = 0x0B,
  LNA                     = 0x0C,
  FIFO_ADDR_PTR           = 0x0D,
  FIFO_TX_BASE_ADDR       = 0x0E,
  FIFO_RX_BASE_ADDR       = 0x0F,
  FIFO_RX_CURRENT_ADDR    = 0x10,
  IRQ_FLAGS_MASK          = 0x11,
  IRQ_FLAGS               = 0x12,
  RX_NB_BYTES             = 0x13,
  RX_HEADER_CNT_VALUE_MSB = 0x14,
  RX_HEADER_CNT_VALUE_LSB = 0x15,
  RX_PACKET_CNT_VALUE_MSB = 0x16,
  RX_PACKET_CNT_VALUE_LSB = 0x17,
  MODEM_STAT              = 0x18,
  PKT_SNR_VALUE           = 0x19,
  PKT_RSSI_VALUE          = 0x1A,
  RSSI_VALUE              = 0x1B,
  HOP_CHANNEL             = 0x1C,
  MODEM_CONFIG1           = 0x1D,
  MODEM_CONFIG2           = 0x1E,
  SYMB_TIMEOUT_LSB        = 0x1F,
  PREAMBLE_MSB            = 0x20,
  PREAMBLE_LSB            = 0x21,
  PAYLOAD_LENGTH          = 0x22,
  MAX_PAYLOAD_LENGTH      = 0x23,
  HOP_PERIOD              = 0x24,
  FIFO_RX_BYTE_ADDR       = 0x25,
  MODEM_CONFIG3           = 0x26,

  PPM_CORRECTION          = 0x27,
  FEI_MSB                 = 0x28,
  FEI_MID                 = 0x29,
  FEI_LSB                 = 0x2A,
  RSSI_WIDEBAND           = 0x2C,
  PACKET_CONFIG_1         = 0x30,
  DETECT_OPTIMIZ          = 0x31,
  INVERT_IQ               = 0x33,
  DETECTION_THRESHOLD     = 0x37,
  SYNC_WORD               = 0x39,

  DIO_MAPPING1            = 0x40,
  DIO_MAPPING2            = 0x41,
  VERSION                 = 0x42,

  TCXO                    = 0x4B,
  PA_DAC                  = 0x4D,
  FORMER_TEMP             = 0x5B,
  AGC_REF                 = 0x61,
  AGC_THRESH1             = 0x62,
  AGC_THRESH2             = 0x63,
  AGC_THRESH3             = 0x64
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Io
{

public:

           RFM9x_Io() { }
  virtual ~RFM9x_Io() { }


  virtual void readRegister  (Register const reg, uint8_t       * data                      ) = 0;
  virtual void readRegister  (Register const reg, uint8_t       * data, uint16_t const bytes) = 0;
  virtual void writeRegister (Register const reg, uint8_t const   data                      ) = 0;
  virtual void writeRegister (Register const reg, uint8_t const * data, uint16_t const bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RFM9x */

} /* lora */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_IO_H_ */
