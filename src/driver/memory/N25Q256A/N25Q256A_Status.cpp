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

#include <snowfox/driver/memory/N25Q256A/N25Q256A_Status.h>

#include <snowfox/util/BitUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::N25Q256A
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

N25Q256A_Status::N25Q256A_Status(interface::N25Q256A_Io & io)
: _io(io)
{

}

N25Q256A_Status::~N25Q256A_Status()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool N25Q256A_Status::isProgramInProgress()
{
  return isWriteInProgress();
}

bool N25Q256A_Status::isEraseInProgress()
{
  return isWriteInProgress();
}

bool N25Q256A_Status::isNVConfigRegWriteInProgress()
{
  return isWriteInProgress();
}

bool N25Q256A_Status::isWriteStatusRegInProgress()
{
  return isWriteInProgress();
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

bool N25Q256A_Status::isWriteInProgress()
{
  uint8_t const status_reg = _io.readStatusReg();
  return util::isBitSet(status_reg, N25Q256A_STATUS_REG_WRITE_IN_PROG_bp);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::N25Q256A */
