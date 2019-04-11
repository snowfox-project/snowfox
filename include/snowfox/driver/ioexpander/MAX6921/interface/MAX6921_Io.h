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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_INTERFACE_MAX6921_IO_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_INTERFACE_MAX6921_IO_H_

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

namespace ioexpander
{

namespace MAX6921
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef union 
{
  struct
  {
    uint8_t OUT0  : 1;
    uint8_t OUT1  : 1;
    uint8_t OUT2  : 1;
    uint8_t OUT3  : 1;
    uint8_t OUT4  : 1;
    uint8_t OUT5  : 1;
    uint8_t OUT6  : 1;
    uint8_t OUT7  : 1;
    uint8_t OUT8  : 1;
    uint8_t OUT9  : 1;
    uint8_t OUT10 : 1;
    uint8_t OUT11 : 1;
    uint8_t OUT12 : 1;
    uint8_t OUT13 : 1;
    uint8_t OUT14 : 1;
    uint8_t OUT15 : 1;
    uint8_t OUT16 : 1;
    uint8_t OUT17 : 1;
    uint8_t OUT18 : 1;
    uint8_t OUT19 : 1;
  } seg;
  uint32_t all;
} SegmentControlBuffer;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MAX6921_Io
{

public:

           MAX6921_Io() { }
  virtual ~MAX6921_Io() { }


  virtual void write   (SegmentControlBuffer const & seg_ctrl_buf) = 0;
  virtual void setLoad () = 0;
  virtual void clrLoad () = 0;
  virtual void setBlank() = 0;
  virtual void clrBlank() = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MAX6921 */

} /* ioexpander */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_INTERFACE_MAX6921_IO_H_ */