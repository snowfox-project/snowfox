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

#include <snowfox/driver/sensor/BMP388/interface/BMP388_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

namespace interface
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t BMP388_Io::readRegister(Register const reg)
{
  uint8_t data = 0;
  readRegister(reg, &data, 1);
  return data;
}

void BMP388_Io::writeRegister(Register const reg, uint8_t const data)
{
  writeRegister(reg, reinterpret_cast<uint8_t const *>(&data), 1);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */
