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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_INTERRUPTCONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_INTERRUPTCONTROL_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

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

namespace interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* REG_IRQ_FLAGS **********************************************************************/
#define RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT          (1<<7)
#define RFM9x_REG_IRQ_FLAGS_RX_DONE             (1<<6)
#define RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR   (1<<5)
#define RFM9x_REG_IRQ_FLAGS_VALID_HEADER        (1<<4)
#define RFM9x_REG_IRQ_FLAGS_TX_DONE             (1<<3)
#define RFM9x_REG_IRQ_FLAGS_CAD_DONE            (1<<2)
#define RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL (1<<1)
#define RFM9x_REG_IRQ_FLAGS_CAD_DETECTED        (1<<0)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

enum class InterruptRequest : uint8_t
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

class RFM9x_InterruptControl
{

public:

           RFM9x_InterruptControl() { }
  virtual ~RFM9x_InterruptControl() { }


  virtual void getIntReqFlags (uint8_t                * irq_req_flags) = 0;
  virtual void clearIntReqFlag(InterruptRequest const   int_req      ) = 0;


  inline bool isRxTimeout         (uint8_t const irq_req_flags) { return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT          ) == RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT;          }
  inline bool isRxDone            (uint8_t const irq_req_flags) { return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_RX_DONE             ) == RFM9x_REG_IRQ_FLAGS_RX_DONE;             }
  inline bool isPayloadCrcError   (uint8_t const irq_req_flags) { return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR   ) == RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR;   }
  inline bool isValidHeader       (uint8_t const irq_req_flags) { return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_VALID_HEADER        ) == RFM9x_REG_IRQ_FLAGS_VALID_HEADER;        }
  inline bool isTxDone            (uint8_t const irq_req_flags) { return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_TX_DONE             ) == RFM9x_REG_IRQ_FLAGS_TX_DONE;             }
  inline bool isCadDone           (uint8_t const irq_req_flags) { return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_CAD_DONE            ) == RFM9x_REG_IRQ_FLAGS_CAD_DONE;            }
  inline bool isFhssChangeChannel (uint8_t const irq_req_flags) { return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL ) == RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL; }
  inline bool isCadDetected       (uint8_t const irq_req_flags) { return (irq_req_flags & RFM9x_REG_IRQ_FLAGS_CAD_DETECTED        ) == RFM9x_REG_IRQ_FLAGS_CAD_DETECTED;        }

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
