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

#ifndef INCLUDE_SPECTRE_DRIVER_GLCD_RA6963_INTERFACE_RA6963_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_GLCD_RA6963_INTERFACE_RA6963_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class RA6963_IO_Interface
{

public:

           RA6963_IO_Interface() { }
  virtual ~RA6963_IO_Interface() { }


  virtual void    reset       (                      ) = 0;
  virtual uint8_t readStatus  (                      ) = 0;
  virtual uint8_t readData    (                      ) = 0;
  virtual void    writeData   (uint8_t const data_val) = 0;
  virtual void    writeCommand(uint8_t const cmd_val ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* RA6963 */

} /* glcd */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_GLCD_RA6963_INTERFACE_RA6963_IO_INTERFACE_H_ */
