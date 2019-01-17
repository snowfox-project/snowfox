/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_REGISTERBITS_H_
#define INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_REGISTERBITS_H_

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

/* REG_OP_MODE ************************************************************************/
#define RFM9x_REG_OP_MODE_LONG_RANGE_MODE_bm                (1<<7)
#define RFM9x_REG_OP_MODE_MODULATION_TYPE_1_bm              (1<<6)
#define RFM9x_REG_OP_MODE_MODULATION_TYPE_0_bm              (1<<5)
#define RFM9x_REG_OP_MODE_MODE_2_bm                         (1<<2)
#define RFM9x_REG_OP_MODE_MODE_1_bm                         (1<<1)
#define RFM9x_REG_OP_MODE_MODE_0_bm                         (1<<0)

/* REG_IRQ_FLAGS **********************************************************************/
#define RFM9x_REG_IRQ_FLAGS_RX_TIMEOUT                      (1<<7)
#define RFM9x_REG_IRQ_FLAGS_RX_DONE                         (1<<6)
#define RFM9x_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR               (1<<5)
#define RFM9x_REG_IRQ_FLAGS_VALID_HEADER                    (1<<4)
#define RFM9x_REG_IRQ_FLAGS_TX_DONE                         (1<<3)
#define RFM9x_REG_IRQ_FLAGS_CAD_DONE                        (1<<2)
#define RFM9x_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL             (1<<1)
#define RFM9x_REG_IRQ_FLAGS_CAD_DETECTED                    (1<<0)

/* REG_MODEM_CONFIG_1 *****************************************************************/
#define RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_3_bm             (1<<7)
#define RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_2_bm             (1<<6)
#define RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_1_bm             (1<<5)
#define RFM9x_REG_MODEM_CONFIG_1_BANDWIDTH_0_bm             (1<<4)
#define RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_2_bm           (1<<3)
#define RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_1_bm           (1<<2)
#define RFM9x_REG_MODEM_CONFIG_1_CODING_RATE_0_bm           (1<<1)
#define RFM9x_REG_MODEM_CONFIG_1_IMPLICIT_HEADER_MODE_ON_bm (1<<0)

/* REG_MODEM_CONFIG_2 *****************************************************************/
#define RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_3_bm      (1<<7)
#define RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_2_bm      (1<<6)
#define RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_1_bm      (1<<5)
#define RFM9x_REG_MODEM_CONFIG_2_SPREADING_FACTOR_0_bm      (1<<4)
#define RFM9x_REG_MODEM_CONFIG_2_SYMB_TIMEOUT_MSB_1_bm      (1<<1)
#define RFM9x_REG_MODEM_CONFIG_2_SYMB_TIMEOUT_MSB_0_bm      (1<<0)

/* REG_MODEM_CONFIG_3 *****************************************************************/
#define RFM9x_REG_MODEM_CONFIG_3_MOBILE_NODE_bm             (1<<3)

/* REG_PACKET_CONFIG_1 ****************************************************************/
#define RFM9x_REG_PACKET_CONFIG_1_PACKET_FORMAT_bm          (1<<7)

/* REG_DIO_MAPPING_1 ******************************************************************/
#define RFM9x_REG_DIO_MAPPING_1_DIO0_MAPPING_1_bm           (1<<7)
#define RFM9x_REG_DIO_MAPPING_1_DIO0_MAPPING_0_bm           (1<<6)
#define RFM9x_REG_DIO_MAPPING_1_DIO1_MAPPING_1_bm           (1<<5)
#define RFM9x_REG_DIO_MAPPING_1_DIO1_MAPPING_0_bm           (1<<4)

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RFM9x */

} /* lora */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_INTERFACE_RFM9X_REGISTERBITS_H_ */
