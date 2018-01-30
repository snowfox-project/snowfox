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

#ifndef INCLUDE_SPECTRE_DRIVER_GLCD_RA6963_INTERFACE_RA6963_DATA_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_GLCD_RA6963_INTERFACE_RA6963_DATA_INTERFACE_H_

/**************************************************************************************
 * INCLUDES
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

namespace glcd
{

namespace RA6963
{

namespace interface
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

enum class OpMode : uint8_t
{
  NORMAL,
  AUTO
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RA6963_Data
{

public:

           RA6963_Data() { }
  virtual ~RA6963_Data() { }


  virtual uint8_t readData    (OpMode const mode                        ) = 0;
  virtual void    writeData   (OpMode const mode, uint8_t const data_val) = 0;
  virtual void    writeCommand(OpMode const mode, uint8_t const cmd_val ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RA6963 */

} /* glcd */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_GLCD_RA6963_INTERFACE_RA6963_DATA_INTERFACE_H_ */
