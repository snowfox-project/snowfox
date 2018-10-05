/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/driver/memory/AT45DBx/AT45DBx.h>

#include <spectre/driver/util/jedec/Jedec.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AT45DBx::AT45DBx(interface::AT45DBx_Configuration & config,
                 interface::AT45DBx_Control       & control)
: _config (config),
  _control(control)
{

}

AT45DBx::~AT45DBx()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool AT45DBx::open()
{
  uint8_t dev_id[3] = {0};

  _config.readDeviceId(dev_id[0], dev_id[1], dev_id[2]);

  util::jedec::ManufacturerId const manufacturer_id = util::jedec::toManufacturerId(dev_id[0], dev_id[1], dev_id[2]);

  if(manufacturer_id != util::jedec::ManufacturerId::Atmel)
  {
    return false;
  }

  return true;
}

ssize_t AT45DBx::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */ return -1;
}

ssize_t AT45DBx::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */ return -1;
}

bool AT45DBx::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_ERASE_CHIP *****************************************************************/
  case IOCTL_ERASE_CHIP:
  {
    _control.erase();
    return true;
  }
  break;
  }

  return false;
}

void AT45DBx::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* spectre */
