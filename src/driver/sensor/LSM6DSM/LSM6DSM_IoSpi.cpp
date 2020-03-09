/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/driver/sensor/LSM6DSM/LSM6DSM_IoSpi.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace LSM6DSM
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LSM6DSM_IoSpi::LSM6DSM_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master(spi_master),
  _cs        (cs        )
{
  _cs.set();
}

LSM6DSM_IoSpi::~LSM6DSM_IoSpi()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool LSM6DSM_IoSpi::readRegister(interface::Register const reg, uint8_t * data)
{
  uint8_t const reg_addr = (0x80 | static_cast<uint8_t>(reg));

  _cs.clr();
          _spi_master.exchange(reg_addr);
  *data = _spi_master.exchange(0       );
  _cs.set();

  return true;
}

bool LSM6DSM_IoSpi::readRegister(interface::Register const reg, uint8_t * data, uint16_t const num_bytes)
{
  uint8_t const reg_addr = (0x80 | static_cast<uint8_t>(reg));

  _cs.clr();
  _spi_master.exchange(reg_addr);
  for(uint16_t b = 0; b < num_bytes; b++) data[b] = _spi_master.exchange(0);
  _cs.set();

  return true;
}

bool LSM6DSM_IoSpi::writeRegister(interface::Register const reg, uint8_t const data)
{
  uint8_t const reg_addr = static_cast<uint8_t>(reg);

  _cs.clr();
  _spi_master.exchange(reg_addr);
  _spi_master.exchange(data    );
  _cs.set();

  return true;
}

bool LSM6DSM_IoSpi::writeRegister(interface::Register const reg, uint8_t const * data, uint16_t const num_bytes)
{
  uint8_t const reg_addr = static_cast<uint8_t>(reg);

  _cs.clr();
  _spi_master.exchange(reg_addr);
  for(uint16_t b = 0; b < num_bytes; b++) _spi_master.exchange(data[b]);
  _cs.set();

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LSM6DSM */

} /* sensor */

} /* driver */

} /* snowfox */
