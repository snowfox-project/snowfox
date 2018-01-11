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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_INTERFACE_TPA81_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_INTERFACE_TPA81_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace TPA81
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_COMMAND             = 0x00,
  REG_AMBIENT_TEMPERATURE = 0x01,
  REG_PIXEL_1             = 0x02,
  REG_PIXEL_2             = 0x03,
  REG_PIXEL_3             = 0x04,
  REG_PIXEL_4             = 0x05,
  REG_PIXEL_5             = 0x06,
  REG_PIXEL_6             = 0x07,
  REG_PIXEL_7             = 0x08,
  REG_PIXEL_8             = 0x09
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TPA81_IO_Interface
{

public:

           TPA81_IO_Interface() { }
  virtual ~TPA81_IO_Interface() { }


  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const * data, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* TPA81 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_INTERFACE_TPA81_IO_INTERFACE_H_ */
