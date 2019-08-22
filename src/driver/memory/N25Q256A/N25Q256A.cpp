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

#include <snowfox/driver/memory/N25Q256A/N25Q256A.h>

#include <snowfox/driver/memory/N25Q256A/util/N25Q256A_Util.h>
#include <snowfox/driver/memory/N25Q256A/N25Q256A_Capabilities.h>

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

N25Q256A::N25Q256A()
{

}

N25Q256A::~N25Q256A()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool N25Q256A::open()
{
  /* TODO */ return false;
}

ssize_t N25Q256A::read(uint8_t * /* buffer */, ssize_t const /* num_bytes */)
{
  /* TODO */ return -1;
}

ssize_t N25Q256A::write(uint8_t const * /* buffer */, ssize_t const /* num_bytes */)
{
  /* TODO */ return -1;
}

void N25Q256A::close()
{
  /* TODO */
}

/**************************************************************************************
 * PROTECTE MEMBER FUNCTIONS
 **************************************************************************************/

bool N25Q256A::ioctl_get_capabilities(NorDriverCapabilities * capabilities)
{
  *capabilities = CAPABILITIES;
  return true;
}

bool N25Q256A::iotcl_erase_chip()
{
  /* TODO */ return false;
}

bool N25Q256A::ioctl_erase_sector(uint32_t const sector)
{
  if(!util::isValidSector(sector)) return false;
  /* TODO */ return false;
}

bool N25Q256A::ioctl_erase_subsector(uint32_t const /* subsector */)
{
  /* TODO */ return false;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */
