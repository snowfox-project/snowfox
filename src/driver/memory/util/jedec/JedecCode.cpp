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

#include <snowfox/driver/memory/util/jedec/JedecCode.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace util
{

namespace jedec
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

JedecCode::JedecCode()
: _device_id_0(0)
, _device_id_1(0)
, _device_id_2(0)
{
  
}

JedecCode::JedecCode(uint8_t const * device_id)
: _device_id_0(device_id[0])
, _device_id_1(device_id[1])
, _device_id_2(device_id[2])
{

}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* jedec */

} /* util */

} /* driver */

} /* snowfox */
