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

#include <snowfox/driver/memory/N25Q256A/N25Q256A_IoSpi.h>

#include <snowfox/driver/memory/N25Q256A/util/N25Q256A_Util.h>

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

N25Q256A_IoSpi::N25Q256A_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master(spi_master)
, _cs(cs)
{
  _cs.set();
}

N25Q256A_IoSpi::~N25Q256A_IoSpi()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool N25Q256A_IoSpi::enableWrite()
{
  _cs.clr();
  _spi_master.exchange(static_cast<uint8_t>(interface::Command::WRITE_ENABLE));
  _cs.set();

  return true;
}

bool N25Q256A_IoSpi::readStatusReg(uint8_t * status_reg)
{
  _cs.clr();
  _spi_master.exchange(static_cast<uint8_t>(interface::Command::READ_STATUS_REG));
  *status_reg = _spi_master.exchange(0);
  _cs.set();

  return true;
}

bool N25Q256A_IoSpi::readNonVolatileConfigReg(uint16_t * non_volatile_config_reg)
{
  _cs.clr();
  _spi_master.exchange(static_cast<uint8_t>(interface::Command::READ_NON_VOLATILE_CONFIG_REG));
  uint8_t const high = _spi_master.exchange(0);
  uint8_t const low  = _spi_master.exchange(0);
  _cs.set();

  *non_volatile_config_reg = (static_cast<uint16_t>(high) << 8) | (static_cast<uint16_t>(low));

  return true;
}

bool N25Q256A_IoSpi::writeNonVolatileConfigReg(uint16_t const non_volatile_config_reg)
{
  uint8_t const high = static_cast<uint8_t>((non_volatile_config_reg & 0xFF00) >> 8);
  uint8_t const low  = static_cast<uint8_t>((non_volatile_config_reg & 0x00FF) >> 0);

  _cs.clr();
  _spi_master.exchange(static_cast<uint8_t>(interface::Command::WRITE_NON_VOLATILE_CONFIG_REG));
  _spi_master.exchange(high);
  _spi_master.exchange(low);
  _cs.set();

  return true;
}

bool N25Q256A_IoSpi::triggerSectorErase(uint32_t const sector_num)
{
  /* The sector erase command byte is followed by a address within
   * sector which the user intends to delete. Therefore we must
   * first calculate a valid address from the supplied sector_num.
   */
  uint32_t const sector_base_addr = util::toSectorBaseAddr(sector_num);
  uint8_t const sector_base_addr_array[4] =
  {
    static_cast<uint8_t>((sector_base_addr & 0xFF000000) >> 24),
    static_cast<uint8_t>((sector_base_addr & 0x00FF0000) >> 16),
    static_cast<uint8_t>((sector_base_addr & 0x0000FF00) >>  8),
    static_cast<uint8_t>((sector_base_addr & 0x000000FF) >>  0)
  };

  _cs.clr();
  _spi_master.exchange(static_cast<uint8_t>(interface::Command::SUBSECTOR_ERASE_4_BYTE_ADDR));
  _spi_master.exchange(sector_base_addr_array[0]);
  _spi_master.exchange(sector_base_addr_array[1]);
  _spi_master.exchange(sector_base_addr_array[2]);
  _spi_master.exchange(sector_base_addr_array[3]);
  _cs.set();

  return true;
}

bool N25Q256A_IoSpi::triggerSubsectorErase(uint32_t const subsector_num)
{
  /* The subsector erase command byte is followed by a address within
   * subsector which the user intends to delete. Therefore we must
   * first calculate a valid address from the supplied subsector_num.
   */
  uint32_t const subsector_base_addr = util::toSubsectorBaseAddr(subsector_num);
  uint8_t const subsector_base_addr_array[4] =
  {
    static_cast<uint8_t>((subsector_base_addr & 0xFF000000) >> 24),
    static_cast<uint8_t>((subsector_base_addr & 0x00FF0000) >> 16),
    static_cast<uint8_t>((subsector_base_addr & 0x0000FF00) >>  8),
    static_cast<uint8_t>((subsector_base_addr & 0x000000FF) >>  0)
  };

  _cs.clr();
  _spi_master.exchange(static_cast<uint8_t>(interface::Command::SECTOR_ERASE_4_BYTE_ADDR));
  _spi_master.exchange(subsector_base_addr_array[0]);
  _spi_master.exchange(subsector_base_addr_array[1]);
  _spi_master.exchange(subsector_base_addr_array[2]);
  _spi_master.exchange(subsector_base_addr_array[3]);
  _cs.set();

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */
