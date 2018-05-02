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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/RFM9x_InterruptControl.h>

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
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_InterruptControl::RFM9x_InterruptControl(interface::RFM9x_Io & io)
: _io(io)
{

}

RFM9x_InterruptControl::~RFM9x_InterruptControl()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_InterruptControl::getIntReqFlags(uint8_t * irq_req_flags)
{
  _io.readRegister(interface::Register::IRQ_FLAGS, irq_req_flags);
}

void RFM9x_InterruptControl::clearIntReqFlag(interface::InterruptRequest const int_req)
{
  /* The interrupt request flag can be cleared by writing
   * a '1' to the corresponding bit in the IRQ register.
   */
  _io.writeRegister(interface::Register::IRQ_FLAGS, static_cast<uint8_t>(int_req));
}

bool RFM9x_InterruptControl::isRxTimeout(uint8_t const irq_req_flags)
{
  return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT) == RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT;
}

bool RFM9x_InterruptControl::isRxDone(uint8_t const irq_req_flags)
{
  return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_RX_DONE) == RFM9x_REG_IRQ_FLAGS_RX_DONE;
}

bool RFM9x_InterruptControl::isPayloadCrcError(uint8_t const irq_req_flags)
{
  return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR) == RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR;
}

bool RFM9x_InterruptControl::isValidHeader(uint8_t const irq_req_flags)
{
  return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_VALID_HEADER) == RFM9x_REG_IRQ_FLAGS_VALID_HEADER;
}

bool RFM9x_InterruptControl::isTxDone(uint8_t const irq_req_flags)
{
  return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_TX_DONE) == RFM9x_REG_IRQ_FLAGS_TX_DONE;
}

bool RFM9x_InterruptControl::isCadDone(uint8_t const irq_req_flags)
{
  return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_CAD_DONE) == RFM9x_REG_IRQ_FLAGS_CAD_DONE;
}

bool RFM9x_InterruptControl::isFhssChangeChannel(uint8_t const irq_req_flags)
{
  return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL) == RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL;
}

bool RFM9x_InterruptControl::isCadDetected(uint8_t const irq_req_flags)
{
  return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_CAD_DETECTED) == RFM9x_REG_IRQ_FLAGS_CAD_DETECTED;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
