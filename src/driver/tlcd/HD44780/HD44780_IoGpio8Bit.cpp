/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/driver/tlcd/HD44780/HD44780_IoGpio8Bit.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace tlcd
{

namespace HD44780
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

HD44780_IoGpio8Bit::HD44780_IoGpio8Bit(hal::interface::DigitalOutPin             & rs,
                                       hal::interface::DigitalOutPin             & rw,
                                       hal::interface::DigitalOutPin             & enable,
                                       hal::interface::DigitalInOutPort<uint8_t> & data)
: _rs    (rs    ),
  _rw    (rw    ),
  _enable(enable),
  _data  (data  )
{

}

HD44780_IoGpio8Bit::~HD44780_IoGpio8Bit()
{

}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* HD44780 */

} /* tlcd */

} /* driver */

} /* spectre */
