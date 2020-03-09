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

#include <snowfox/driver/ioexpander/MAX6921/MAX6921_IoSpi.h>

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

MAX6921_IoSpi::MAX6921_IoSpi(hal::interface::SpiMasterControl & spi_master, 
                             hal::interface::DigitalOutPin    & load,
                             hal::interface::DigitalOutPin    & blank)
: _spi_master(spi_master),
  _load      (load      ),
  _blank     (blank     )
{

}
  
MAX6921_IoSpi::~MAX6921_IoSpi()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MAX6921_IoSpi::write(interface::SegmentControlBuffer const & seg_ctrl_buf) 
{
  uint8_t const byte[3] = 
  {
    static_cast<uint8_t>(                                                                                                                                (seg_ctrl_buf.seg.OUT19 << 3) | (seg_ctrl_buf.seg.OUT18 << 2) | (seg_ctrl_buf.seg.OUT17 << 1) | (seg_ctrl_buf.seg.OUT16 << 0)),
    static_cast<uint8_t>((seg_ctrl_buf.seg.OUT15 << 7) | (seg_ctrl_buf.seg.OUT14 << 6) | (seg_ctrl_buf.seg.OUT13 << 5) | (seg_ctrl_buf.seg.OUT12 << 4) | (seg_ctrl_buf.seg.OUT11 << 3) | (seg_ctrl_buf.seg.OUT10 << 2) | (seg_ctrl_buf.seg.OUT9  << 1) | (seg_ctrl_buf.seg.OUT8  << 0)),
    static_cast<uint8_t>((seg_ctrl_buf.seg.OUT7  << 7) | (seg_ctrl_buf.seg.OUT6  << 6) | (seg_ctrl_buf.seg.OUT5  << 5) | (seg_ctrl_buf.seg.OUT4  << 4) | (seg_ctrl_buf.seg.OUT3  << 3) | (seg_ctrl_buf.seg.OUT2  << 2) | (seg_ctrl_buf.seg.OUT1  << 1) | (seg_ctrl_buf.seg.OUT0  << 0))
  };
  
  _spi_master.exchange(byte[0]);
  _spi_master.exchange(byte[1]);
  _spi_master.exchange(byte[2]);
}

void MAX6921_IoSpi::setLoad()
{
  _load.set();
}

void MAX6921_IoSpi::clrLoad()
{
  _load.clr();
}

void MAX6921_IoSpi::setBlank()
{
  _blank.set();
}

void MAX6921_IoSpi::clrBlank()
{
  _blank.clr();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MAX6921 */

} /* ioexpander */

} /* driver */

} /* snowfox */
