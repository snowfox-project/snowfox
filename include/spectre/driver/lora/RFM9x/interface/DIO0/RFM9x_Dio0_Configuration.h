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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_DIO0_RFM9X_DIO0_CONFIGURATION_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_DIO0_RFM9X_DIO0_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

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

enum class Dio0EventSource : uint8_t
{
  RxDone  = 0,
  TxDone  =                                             RFM9x_REG_DIO_MAPPING_1_DIO0_MAPPING_0_bm,
  CadDone = RFM9x_REG_DIO_MAPPING_1_DIO0_MAPPING_1_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Dio0_Configuration
{

public:

           RFM9x_Dio0_Configuration() { }
  virtual ~RFM9x_Dio0_Configuration() { }


  virtual void setDio0EventSource(Dio0EventSource const dio_0_event_source) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_DIO0_RFM9X_DIO0_CONFIGURATION_H_ */
