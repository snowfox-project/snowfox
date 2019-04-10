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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/ioexpander/MAX6921/MAX6921_Control.h>

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

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MAX6921_Control::MAX6921_Control(interface::MAX6921_Io & io,
                                 hal::interface::Delay & delay)
: _io   (io   ),
  _delay(delay)
{
  _io.clrLoad ();
  _io.clrBlank();
}

MAX6921_Control::~MAX6921_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MAX6921_Control::setSegment(uint8_t const seg_number)
{
  /* TODO */
}

void MAX6921_Control::clrSegment(uint8_t const seg_number)
{
  /* TODO */
}

void MAX6921_Control::write()
{
  _io.write(_seg_ctrl_buf);
}

void MAX6921_Control::load()
{
  _io.setLoad();
  _delay.delay_ms(1);
  _io.clrLoad();
}

void MAX6921_Control::blank()
{
  _io.setBlank();
}

void MAX6921_Control::noBlank()
{
  _io.clrBlank();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MAX6921 */

} /* ioexpander */

} /* driver */

} /* snowfox */
