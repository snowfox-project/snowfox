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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_TRANSMITFIFO_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_TRANSMITFIFO_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/interface/RFM9x_TransmitFifo.h>

#include <spectre/driver/lora/RFM9x/interface/RFM9x_Io.h>
#include <spectre/driver/lora/RFM9x/interface/RFM9x_FifoConfiguration.h>

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

class RFM9x_TransmitFifo : public interface::RFM9x_TransmitFifo
{

public:

           RFM9x_TransmitFifo(interface::RFM9x_Io                & io,
                              interface::RFM9x_FifoConfiguration & fifo_config);
  virtual ~RFM9x_TransmitFifo();


  virtual uint16_t writeToFifo(uint8_t const * data, uint16_t const num_bytes) override;

private:

  interface::RFM9x_Io                & _io;
  interface::RFM9x_FifoConfiguration & _fifo_config;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_TRANSMITFIFO_H_ */
