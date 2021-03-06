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

#ifndef INCLUDE_SNOWFOX_HAL_INTERFACE_I2C_I2CMASTERCONTROL_H_
#define INCLUDE_SNOWFOX_HAL_INTERFACE_I2C_I2CMASTERCONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class I2cMasterControl
{

public:

           I2cMasterControl() { }
  virtual ~I2cMasterControl() { }


  virtual bool begin      (uint8_t const address, bool const is_read_access               ) = 0;
  virtual void end        (                                                               ) = 0;
  virtual bool write      (uint8_t const data                                             ) = 0;
  virtual bool requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes) = 0;

  inline uint8_t convertI2cAddress(uint8_t const address, bool is_read_access) const {
    return is_read_access ? (address | 0x01) : address;
  }
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::interface*/

#endif /* INCLUDE_SNOWFOX_HAL_INTERFACE_I2C_I2CMASTERCONTROL_H_ */
