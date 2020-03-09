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
  switch(seg_number) {
  case  0: _seg_ctrl_buf.seg.OUT0  = 1; break;
  case  1: _seg_ctrl_buf.seg.OUT1  = 1; break;
  case  2: _seg_ctrl_buf.seg.OUT2  = 1; break;
  case  3: _seg_ctrl_buf.seg.OUT3  = 1; break;
  case  4: _seg_ctrl_buf.seg.OUT4  = 1; break;
  case  5: _seg_ctrl_buf.seg.OUT5  = 1; break;
  case  6: _seg_ctrl_buf.seg.OUT6  = 1; break;
  case  7: _seg_ctrl_buf.seg.OUT7  = 1; break;
  case  8: _seg_ctrl_buf.seg.OUT8  = 1; break;
  case  9: _seg_ctrl_buf.seg.OUT9  = 1; break;
  case 10: _seg_ctrl_buf.seg.OUT10 = 1; break;
  case 11: _seg_ctrl_buf.seg.OUT11 = 1; break;
  case 12: _seg_ctrl_buf.seg.OUT12 = 1; break;
  case 13: _seg_ctrl_buf.seg.OUT13 = 1; break;
  case 14: _seg_ctrl_buf.seg.OUT14 = 1; break;
  case 15: _seg_ctrl_buf.seg.OUT15 = 1; break;
  case 16: _seg_ctrl_buf.seg.OUT16 = 1; break;
  case 17: _seg_ctrl_buf.seg.OUT17 = 1; break;
  case 18: _seg_ctrl_buf.seg.OUT18 = 1; break;
  case 19: _seg_ctrl_buf.seg.OUT19 = 1; break;
  }
}

void MAX6921_Control::clrSegment(uint8_t const seg_number)
{
  switch(seg_number) {
  case  0: _seg_ctrl_buf.seg.OUT0  = 0; break;
  case  1: _seg_ctrl_buf.seg.OUT1  = 0; break;
  case  2: _seg_ctrl_buf.seg.OUT2  = 0; break;
  case  3: _seg_ctrl_buf.seg.OUT3  = 0; break;
  case  4: _seg_ctrl_buf.seg.OUT4  = 0; break;
  case  5: _seg_ctrl_buf.seg.OUT5  = 0; break;
  case  6: _seg_ctrl_buf.seg.OUT6  = 0; break;
  case  7: _seg_ctrl_buf.seg.OUT7  = 0; break;
  case  8: _seg_ctrl_buf.seg.OUT8  = 0; break;
  case  9: _seg_ctrl_buf.seg.OUT9  = 0; break;
  case 10: _seg_ctrl_buf.seg.OUT10 = 0; break;
  case 11: _seg_ctrl_buf.seg.OUT11 = 0; break;
  case 12: _seg_ctrl_buf.seg.OUT12 = 0; break;
  case 13: _seg_ctrl_buf.seg.OUT13 = 0; break;
  case 14: _seg_ctrl_buf.seg.OUT14 = 0; break;
  case 15: _seg_ctrl_buf.seg.OUT15 = 0; break;
  case 16: _seg_ctrl_buf.seg.OUT16 = 0; break;
  case 17: _seg_ctrl_buf.seg.OUT17 = 0; break;
  case 18: _seg_ctrl_buf.seg.OUT18 = 0; break;
  case 19: _seg_ctrl_buf.seg.OUT19 = 0; break;
  }
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
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void MAX6921_Control::initSegCtrlBuf()
{
  _seg_ctrl_buf.all = 0;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MAX6921 */

} /* ioexpander */

} /* driver */

} /* snowfox */
