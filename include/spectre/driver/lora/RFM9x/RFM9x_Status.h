/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_STATUS_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_STATUS_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/interface/status/RFM9x_Status.h>

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

class RFM9x_Status : public interface::RFM9x_Status
{

public:

           RFM9x_Status(interface::RFM9x_Io & io);
  virtual ~RFM9x_Status();


  virtual int16_t getCurrentRssi   () override;
  virtual int16_t getLastPacketRssi() override;
  virtual int8_t  getLastPacketSnr () override;


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

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_STATUS_H_ */
