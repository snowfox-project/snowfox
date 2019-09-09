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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/N25Q256A/interface/N25Q256A_Io.h>

#include <snowfox/util/BitUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace N25Q256A
{

namespace interface
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void N25Q256A_Io::enableWrite()
{
  transfer(Command::WRITE_ENABLE, 
           0,   /* tx_buf       */
           0);  /* tx_num_bytes */
}

uint8_t N25Q256A_Io::readStatusReg()
{
  uint8_t status_reg = 0;
  
  transfer(Command::READ_STATUS_REG, 
           0,           /* tx_buf       */
           0,           /* tx_num_bytes */
           0,           /* tx_fill_data */
           &status_reg, /* rx_buf       */
           1,           /* rx_num_bytes */
           1);          /* rx_start_pos */

  return status_reg;
}

uint16_t N25Q256A_Io::readNVConfigReg()
{
  uint16_t nv_config_reg = 0;

  transfer(Command::READ_NON_VOLATILE_CONFIG_REG, 
           0,                                           /* tx_buf       */
           0,                                           /* tx_num_bytes */
           0,                                           /* tx_fill_data */
           reinterpret_cast<uint8_t *>(&nv_config_reg), /* rx_buf       */
           2,                                           /* rx_num_bytes */
           1);                                          /* rx_start_pos */

  return nv_config_reg;
}

void N25Q256A_Io::writeNVConfigReg(uint16_t const nv_config_reg)
{
  transfer(interface::Command::WRITE_NON_VOLATILE_CONFIG_REG,
           reinterpret_cast<uint8_t const *>(&nv_config_reg), /* tx_buf       */
           2);                                                /* tx_num_bytes */
}

bool N25Q256A_Io::isBusy()
{
  uint8_t const status_reg = readStatusReg();
  return util::isBitClr(status_reg, N25Q256A_STATUS_REG_PROG_OR_ERASE_bp);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */