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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/haptic/DRV2605/DRV2605.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace haptic
{

namespace DRV2605
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DRV2605::DRV2605(DRV2605_ControlInterface & ctrl)
: _ctrl(ctrl)
{
  _ctrl.reset();
}

DRV2605::~DRV2605()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool DRV2605::open()
{
  return _ctrl.clrStandby();
}

bool DRV2605::read(uint8_t * buffer, uint32_t const num_bytes)
{
  return false; /* Not supported for this driver */
}

bool DRV2605::write(uint8_t const * buffer, uint32_t const num_bytes)
{
  return false; /* Not supported for this driver */
}

bool DRV2605::ioctl(uint32_t const cmd, void * arg)
{
  /* TODO */
  return false;
}

bool DRV2605::close()
{
  return _ctrl.setStandby();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */
