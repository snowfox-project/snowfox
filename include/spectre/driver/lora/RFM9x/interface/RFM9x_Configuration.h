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

#include <stdint.h>

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
 * DEFINES
 **************************************************************************************/

/* REG_OP_MODE ************************************************************************/
#define RFM9x_REG_OP_MODE_LONG_RANGE_MODE_bm    (1<<7)
#define RFM9x_REG_OP_MODE_MODULATION_TYPE_1_bm  (1<<6)
#define RFM9x_REG_OP_MODE_MODULATION_TYPE_0_bm  (1<<5)
#define RFM9x_REG_OP_MODE_MODE_2_bm             (1<<2)
#define RFM9x_REG_OP_MODE_MODE_1_bm             (1<<1)
#define RFM9x_REG_OP_MODE_MODE_0_bm             (1<<0)

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

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Configuration
{

public:

           RFM9x_Configuration() { }
  virtual ~RFM9x_Configuration() { }


  virtual void setOperatingMode (OperatingMode  const op_mode        ) = 0;
  virtual void setLoraMode      (LoRaMode       const lora_mode      ) = 0;
  virtual void setModulationType(ModulationType const modulation_type) = 0;
  virtual void setFrequency     (uint32_t       const freq_Hz        ) = 0;

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
