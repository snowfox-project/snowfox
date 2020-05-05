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

#ifndef INCLUDE_SNOWFOX_DRIVER_UTIL_JEDEC_JEDECCODE_H_
#define INCLUDE_SNOWFOX_DRIVER_UTIL_JEDEC_JEDECCODE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::util::jedec
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class JedecCode
{

public:

  JedecCode();
  JedecCode(uint8_t const * device_id);


  inline uint8_t deviceId0() const { return  _device_id_0; }
  inline uint8_t deviceId1() const { return  _device_id_1; }
  inline uint8_t deviceId2() const { return  _device_id_2; }


private:

  uint8_t _device_id_0,
          _device_id_1,
          _device_id_2;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::util::jedec */

#endif /* INCLUDE_SNOWFOX_DRIVER_UTIL_JEDEC_JEDECCODE_H_ */
