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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_IO_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

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
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  CHIP_ID         = 0x00,
  ERR_REG         = 0x02,
  SENS_STATUS_REG = 0x03,
  DATA            = 0x04,
  EVENT           = 0x10,
  INT_STATUS_REG  = 0x11,
  FIFO_LENGTH     = 0x12,
  FIFO_DATA       = 0x14,
  FIFO_WM         = 0x15,
  FIFO_CONFIG_1   = 0x17,
  FIFO_CONFIG_2   = 0x18,
  INT_CTRL        = 0x19,
  IF_CONF         = 0x1A,
  PWR_CTRL        = 0x1B,
  OSR             = 0X1C,
  CALIB_DATA      = 0x31,
  CMD             = 0x7E,
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMP388_Io
{

public:

  virtual ~BMP388_Io() { }


  virtual void    readRegister  (Register const reg, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual void    writeRegister (Register const reg, uint8_t const * data, uint16_t const num_bytes) = 0;

          uint8_t readRegister  (Register const reg);
          void    writeRegister (Register const reg, uint8_t const data);
          void    modifyRegister(Register const reg, uint8_t const bitmask, uint8_t const data);
  inline  void    setBit        (Register const reg, uint8_t const bitmask) { modifyRegister(reg, bitmask, bitmask); }
  inline  void    clrBit        (Register const reg, uint8_t const bitmask) { modifyRegister(reg, bitmask, 0); }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_IO_INTERFACE_H_ */
