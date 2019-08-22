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

bool N25Q256A_Configuration::setAdressMode(interface::AddressMode const addr_mode)
{
  uint16_t non_volatile_config_reg = 0;
  
  if(!_io.readNonVolatileConfigReg(&non_volatile_config_reg)) return false;

  switch(addr_mode)
  {
  case interface::AddressMode::AM_3Byte: util::setBit(&non_volatile_config_reg, N25Q256A_NON_VOLATILE_CONFIG_REG_ADDRESS_BYTE_bp); break;
  case interface::AddressMode::AM_4Byte: util::clrBit(&non_volatile_config_reg, N25Q256A_NON_VOLATILE_CONFIG_REG_ADDRESS_BYTE_bp); break;
  }

  if(!_io.enableWrite()) return false;

  if(!_io.writeNonVolatileConfigReg(non_volatile_config_reg)) return false;

  uint8_t status_reg = 0;

  if(!_io.readStatusReg(&status_reg)) return false;

  switch(addr_mode)
  {
  case interface::AddressMode::AM_3Byte: return util::isBitClr(status_reg, N25Q256A_STATUS_REG_ADDRESSING_bp); break;
  case interface::AddressMode::AM_4Byte: return util::isBitSet(status_reg, N25Q256A_STATUS_REG_ADDRESSING_bp); break;
  default:                               return false;                                                         break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */
