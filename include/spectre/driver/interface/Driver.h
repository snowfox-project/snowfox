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

#ifndef INCLUDE_SPECTRE_DRIVER_INTERFACE_DRIVER_H_
#define INCLUDE_SPECTRE_DRIVER_INTERFACE_DRIVER_H_

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

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Driver
{

public:

           Driver() { }
  virtual ~Driver() { }


  virtual bool open (                                                   ) = 0;
  virtual bool read (uint8_t        * buffer, uint32_t const   num_bytes) = 0;
  virtual bool write(uint8_t  const * buffer, uint32_t const   num_bytes) = 0;
  virtual bool ioctl(uint32_t const   cmd,    void           * arg      ) = 0;
  virtual bool close(                                                   ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_INTERFACE_DRIVER_H_ */
