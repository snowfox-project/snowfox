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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_REGISTERBITS_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_REGISTERBITS_H_

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
 * DEFINES
 **************************************************************************************/

/* REG_CANINTF ************************************************************************/
#define MCP2515_REG_CANINTF_MERRF_bm                        (1<<7)
#define MCP2515_REG_CANINTF_WAKIF_bm                        (1<<6)
#define MCP2515_REG_CANINTF_ERRIF_bm                        (1<<5)
#define MCP2515_REG_CANINTF_TX2IF_bm                        (1<<4)
#define MCP2515_REG_CANINTF_TX1IF_bm                        (1<<3)
#define MCP2515_REG_CANINTF_TX0IF_bm                        (1<<2)
#define MCP2515_REG_CANINTF_RX1IF_bm                        (1<<1)
#define MCP2515_REG_CANINTF_RX0IF_bm                        (1<<0)

/* REG_TXBnSIDL **********************************************************************/
#define MCP2515_REG_TXBnSIDL_EXIDE_bm                       (1<<3)

/* REG_TXBnDLC ***********************************************************************/
#define MCP2515_REG_TXBnDLC_RTR_bm                          (1<<6)

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_REGISTERBITS_H_ */
