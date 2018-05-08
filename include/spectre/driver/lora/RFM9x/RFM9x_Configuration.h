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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CONFIGURATION_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/interface/RFM9x_Configuration.h>

#include <spectre/driver/lora/RFM9x/interface/RFM9x_Io.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Configuration : public interface::RFM9x_Configuration
{

public:

           RFM9x_Configuration(interface::RFM9x_Io & io, uint32_t const fxosc_Hz);
  virtual ~RFM9x_Configuration();


  virtual void setOperatingMode   (interface::OperatingMode   const op_mode         ) override;
  virtual void setLoRaMode        (interface::LoRaMode        const lora_mode       ) override;
  virtual void setModulationType  (interface::ModulationType  const modulation_type ) override;

  virtual void setFrequency       (uint32_t                   const freq_Hz         ) override;
  virtual void setSignalBandwidth (interface::SignalBandwidth const signal_bandwidth) override;
  virtual void setCodingRate      (interface::CodingRate      const coding_rate     ) override;
  virtual void setHeaderMode      (interface::HeaderMode      const header_mode     ) override;
  virtual void setSpreadingFactor (interface::SpreadingFactor const spreading_factor) override;
  virtual void setPreambleLength  (uint16_t                   const preamble_length ) override;

  virtual bool setTxFifoSize      (uint16_t                   const tx_fifo_size    ) override;
  virtual bool setRxFifoSize      (uint16_t                   const rx_fifo_size    ) override;

private:

  interface::RFM9x_Io       & _io;
  uint32_t            const   _fxosc_Hz;
  uint16_t                    _tx_fifo_size,
                              _rx_fifo_size;

  void    setTxFifoBaseAddress (uint8_t const tx_base_addr);
  void    setRxFifoBaseAddress (uint8_t const rx_base_addr);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CONFIGURATION_H_ */
