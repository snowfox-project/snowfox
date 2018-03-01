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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONTROL_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/interface/RFM9x_FifoControl.h>
#include <spectre/driver/lora/RFM9x/interface/RFM9x_Configuration.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Control : public RFM9x_FifoControl,
                      public RFM9x_Configuration
{

public:

           RFM9x_Control() { }
  virtual ~RFM9x_Control() { }


  /* RFM9x Fifo Control */

  virtual void setTxFifoBaseAddress (uint8_t const tx_base_addr                ) = 0;
  virtual void setRxFifoBaseAddress (uint8_t const rx_base_addr                ) = 0;
  virtual void writeToTxFifo        (uint8_t const * data, uint16_t const bytes) = 0;


  /* RFM9x Configuration */

  virtual void setOperatingMode (OperatingMode  const op_mode                                ) = 0;
  virtual void setLoraMode      (LoRaMode       const lora_mode                              ) = 0;
  virtual void setModulationType(ModulationType const modulation_type                        ) = 0;
  virtual void setFrequency     (uint32_t       const freq_Hz,        uint32_t const fxosc_Hz) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONTROL_H_ */
