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

#include <snowfox/driver/sensor/LSM6DSM/LSM6DSM.h>

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

LSM6DSM::LSM6DSM(interface::LSM6DSM_Configuration & config,
                 interface::LSM6DSM_Control       & control)
: _config (config) ,
  _control(control)
{

}

LSM6DSM::~LSM6DSM()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool LSM6DSM::open()
{
  if(!_control.reset                    ()) return false;
  if(!_config.enableRegAddrAutoIncrement()) return false;
  if(!_config.enableBlockDataUpdate     ()) return false;
  return true;
}

ssize_t LSM6DSM::read(uint8_t * /* buffer */, ssize_t const /* num_bytes */)
{
  /* TODO */ return -1;
}

ssize_t LSM6DSM::write(uint8_t const * /* buffer */, ssize_t const /* num_bytes */)
{
  /* TODO */ return -1;
}

bool LSM6DSM::ioctl(uint32_t const /* cmd */, void * /* arg */)
{
  /* TODO */ return false;
}

void LSM6DSM::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LSM6DSM */

} /* sensor */

} /* driver */

} /* snowfox */
