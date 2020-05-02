/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/lora/RFM9x/interface/control/RFM9x_FifoControl.h>
#include <snowfox/driver/lora/RFM9x/interface/control/RFM9x_Dio0Control.h>
#include <snowfox/driver/lora/RFM9x/interface/control/RFM9x_Dio1Control.h>
#include <snowfox/driver/lora/RFM9x/interface/control/RFM9x_EventControl.h>
#include <snowfox/driver/lora/RFM9x/interface/control/RFM9x_OperationModeControl.h>


/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::lora::RFM9x::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Control : public RFM9x_OperationModeControl,
                      public RFM9x_EventControl,
                      public RFM9x_FifoControl,
                      public RFM9x_Dio0Control,
                      public RFM9x_Dio1Control
{

public:

           RFM9x_Control() { }
  virtual ~RFM9x_Control() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::lora::RFM9x::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_CONTROL_H_ */
