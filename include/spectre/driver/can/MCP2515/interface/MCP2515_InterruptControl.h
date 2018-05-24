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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_INTERRUPTCONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_INTERRUPTCONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <spectre/driver/can/MCP2515/interface/MCP2515_RegisterBits.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace can
{

namespace MCP2515
{

namespace interface
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

enum class InterruptFlag : uint8_t
{
  MessageError = MCP2515_REG_CANINTF_MERRF_bm,
  Wakeup       = MCP2515_REG_CANINTF_WAKIF_bm,
  GeneralError = MCP2515_REG_CANINTF_ERRIF_bm,
  TxBuf2Empty  = MCP2515_REG_CANINTF_TX2IF_bm,
  TxBuf1Empty  = MCP2515_REG_CANINTF_TX1IF_bm,
  TxBuf0Empty  = MCP2515_REG_CANINTF_TX0IF_bm,
  RxBuf1Full   = MCP2515_REG_CANINTF_RX1IF_bm,
  RxBuf0Full   = MCP2515_REG_CANINTF_RX0IF_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_InterruptControl
{

public:

           MCP2515_InterruptControl() { }
  virtual ~MCP2515_InterruptControl() { }


  virtual void getIntFlags (uint8_t             * irq_flags) = 0;
  virtual void clearIntFlag(InterruptFlag const   int_flag ) = 0;


  static  bool isMessageError(uint8_t const irq_flags);
  static  bool isWakeup      (uint8_t const irq_flags);
  static  bool isGeneralError(uint8_t const irq_flags);
  static  bool isTxBuf2Empty (uint8_t const irq_flags);
  static  bool isTxBuf1Empty (uint8_t const irq_flags);
  static  bool isTxBuf0Empty (uint8_t const irq_flags);
  static  bool isRxBuf1Full  (uint8_t const irq_flags);
  static  bool isRxBuf0Full  (uint8_t const irq_flags);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_INTERRUPTCONTROL_H_ */