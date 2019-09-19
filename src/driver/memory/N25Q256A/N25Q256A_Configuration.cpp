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

#include <snowfox/driver/memory/N25Q256A/N25Q256A_Configuration.h>

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

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

N25Q256A_Configuration::N25Q256A_Configuration(interface::N25Q256A_Io & io)
: _io(io)
{

}

N25Q256A_Configuration::~N25Q256A_Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void N25Q256A_Configuration::setAdressMode(interface::AddressMode const addr_mode)
{
  uint16_t non_volatile_config_reg = _io.readNVConfigReg();

  switch(addr_mode)
  {
  case interface::AddressMode::AM_3Byte: snowfox::util::setBit(&non_volatile_config_reg, N25Q256A_NON_VOLATILE_CONFIG_REG_ADDRESS_BYTE_bp); break;
  case interface::AddressMode::AM_4Byte: snowfox::util::clrBit(&non_volatile_config_reg, N25Q256A_NON_VOLATILE_CONFIG_REG_ADDRESS_BYTE_bp); break;
  }

  _io.enableWrite();
  _io.writeNVConfigReg(non_volatile_config_reg);
}

interface::AddressMode N25Q256A_Configuration::getAdressMode()
{
  uint8_t const flag_status_reg = _io.readFlagStatusReg();

  if(snowfox::util::isBitClr(flag_status_reg, N25Q256A_FLAG_STATUS_REG_ADDRESSING_bp)) {
    return interface::AddressMode::AM_3Byte;
  } else {
    return interface::AddressMode::AM_4Byte;
  }
}

util::jedec::JedecCode N25Q256A_Configuration::readDeviceId()
{
  uint8_t device_id[3] = {0};

  _io.transfer(interface::Command::READ_DEVICE_ID, 
               0,           /* tx_buf       */
               0,           /* tx_num_bytes */
               0,           /* tx_fill_data */
               device_id,   /* rx_buf       */
               3,           /* rx_num_bytes */
               0);          /* rx_start_pos */

  util::jedec::JedecCode const jedec_code(device_id);

  return jedec_code;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */
