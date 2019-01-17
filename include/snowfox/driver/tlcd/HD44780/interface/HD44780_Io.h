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

#ifndef INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_IO_H_
#define INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_IO_H_

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

namespace tlcd
{

namespace HD44780
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class HD44780_Io
{

public:

           HD44780_Io() { }
  virtual ~HD44780_Io() { }

  virtual uint8_t readStatus  (                      ) = 0;
  virtual void    writeData   (uint8_t const data_val) = 0;
  virtual void    writeCommand(uint8_t const cmd_val ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* HD44780 */

} /* tlcd */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_IO_H_ */
