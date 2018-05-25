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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CONTROL_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/interface/control/RFM9x_Control.h>

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

class RFM9x_Control : public interface::RFM9x_Control
{

public:

           RFM9x_Control(interface::RFM9x_Io & io);
  virtual ~RFM9x_Control();


  virtual void                     setOperatingMode   (interface::OperatingMode    const op_mode            ) override;
  virtual interface::OperatingMode getOperatingMode   (                                                     ) override;

  virtual uint8_t                  getEventFlags      (                                                     ) override;
  virtual void                     clearEventFlag     (interface::EventFlag        const   event_flag       ) override;

  virtual void                    writeToTransmitFifo(uint8_t const * data, uint8_t const num_bytes_to_write) override;
  virtual uint8_t                 readFromReceiveFifo(uint8_t       * data, uint8_t const num_bytes_to_read ) override;


private:

  interface::RFM9x_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CONTROL_H_ */
