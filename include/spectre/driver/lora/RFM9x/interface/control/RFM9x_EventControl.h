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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_INTERRUPTCONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_INTERRUPTCONTROL_H_

/**************************************************************************************
 * INCLUDE
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
 * TYPEDEF
 **************************************************************************************/

enum class EventFlag : uint8_t
{
  RxTimeout         = RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT,
  RxDone            = RFM9x_REG_IRQ_FLAGS_RX_DONE,
  PayloadCrcError   = RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR,
  ValidHeader       = RFM9x_REG_IRQ_FLAGS_VALID_HEADER,
  TxDone            = RFM9x_REG_IRQ_FLAGS_TX_DONE,
  CadDone           = RFM9x_REG_IRQ_FLAGS_CAD_DONE,
  FhssChangeChannel = RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL,
  CadDetected       = RFM9x_REG_IRQ_FLAGS_CAD_DETECTED
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_EventControl
{

public:

           RFM9x_EventControl() { }
  virtual ~RFM9x_EventControl() { }


  virtual uint8_t getEventFlags (                          ) = 0;
  virtual void    clearEventFlag(EventFlag const event_flag) = 0;


  static  bool isRxTimeoutEvent         (uint8_t const event_flags);
  static  bool isRxDoneEvent            (uint8_t const event_flags);
  static  bool isPayloadCrcErrorEvent   (uint8_t const event_flags);
  static  bool isValidHeaderEvent       (uint8_t const event_flags);
  static  bool isTxDoneEvent            (uint8_t const event_flags);
  static  bool isCadDoneEvent           (uint8_t const event_flags);
  static  bool isFhssChangeChannelEvent (uint8_t const event_flags);
  static  bool isCadDetectedEvent       (uint8_t const event_flags);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_INTERRUPTCONTROL_H_ */
