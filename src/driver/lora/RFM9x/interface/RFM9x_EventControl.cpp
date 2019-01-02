/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/interface/control/RFM9x_EventControl.h>

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
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool RFM9x_EventControl::isRxTimeoutEvent(uint8_t const event_flags)
{
  return ((event_flags & RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT) == RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT);
}

bool RFM9x_EventControl::isRxDoneEvent(uint8_t const event_flags)
{
  return ((event_flags & RFM9x_REG_IRQ_FLAGS_RX_DONE) == RFM9x_REG_IRQ_FLAGS_RX_DONE);
}

bool RFM9x_EventControl::isPayloadCrcErrorEvent(uint8_t const event_flags)
{
  return ((event_flags & RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR) == RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR);
}

bool RFM9x_EventControl::isValidHeaderEvent(uint8_t const event_flags)
{
  return ((event_flags & RFM9x_REG_IRQ_FLAGS_VALID_HEADER) == RFM9x_REG_IRQ_FLAGS_VALID_HEADER);
}

bool RFM9x_EventControl::isTxDoneEvent(uint8_t const event_flags)
{
  return ((event_flags & RFM9x_REG_IRQ_FLAGS_TX_DONE) == RFM9x_REG_IRQ_FLAGS_TX_DONE);
}

bool RFM9x_EventControl::isCadDoneEvent(uint8_t const event_flags)
{
  return ((event_flags & RFM9x_REG_IRQ_FLAGS_CAD_DONE) == RFM9x_REG_IRQ_FLAGS_CAD_DONE);
}

bool RFM9x_EventControl::isFhssChangeChannelEvent(uint8_t const event_flags)
{
  return ((event_flags & RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL) == RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL);
}

bool RFM9x_EventControl::isCadDetectedEvent(uint8_t const event_flags)
{
  return ((event_flags & RFM9x_REG_IRQ_FLAGS_CAD_DETECTED) == RFM9x_REG_IRQ_FLAGS_CAD_DETECTED);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
