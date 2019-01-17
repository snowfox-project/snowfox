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

#include <snowfox/driver/ioexpander/PCA9547/PCA9547_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace ioexpander
{

namespace PCA9547
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

PCA9547_Control::PCA9547_Control(interface::PCA9547_Io & io)
: _io(io)
{

}

PCA9547_Control::~PCA9547_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool PCA9547_Control::setChannel(interface::I2cChannel const sel)
{
  uint8_t const data = static_cast<uint8_t>(sel);

  return _io.writeControlRegister(data);
}

bool PCA9547_Control::getChannel(interface::I2cChannel * sel)
{
  uint8_t data = 0;

  if(!_io.readControlRegister(&data)) return false;

  *sel = static_cast<interface::I2cChannel>(data);

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCA9547 */

} /* ioexpander */

} /* driver */

} /* snowfox */
