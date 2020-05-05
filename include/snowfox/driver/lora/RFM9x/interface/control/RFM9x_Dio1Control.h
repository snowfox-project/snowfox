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

#ifndef INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_DIO1_RFM9X_DIO1CONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_DIO1_RFM9X_DIO1CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/driver/lora/RFM9x/interface/RFM9x_RegisterBits.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::lora::RFM9x::interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Dio1EventSource : uint8_t
{
  RxTimeout         = 0,
  FhssChangeChannel =                                             RFM9x_REG_DIO_MAPPING_1_DIO1_MAPPING_0_bm,
  CadDetected       = RFM9x_REG_DIO_MAPPING_1_DIO1_MAPPING_1_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Dio1Control
{

public:

           RFM9x_Dio1Control() { }
  virtual ~RFM9x_Dio1Control() { }


  virtual void setDio1EventSource(Dio1EventSource const event_source) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::lora::RFM9x::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_DIO1_RFM9X_DIO1CONFIGURATION_H_ */
