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

#include <snowfox/driver/glcd/RA6963/RA6963_IoGpio8Bit.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::glcd::RA6963
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RA6963_IoGpio8Bit::RA6963_IoGpio8Bit(hal::interface::Delay                     & delay,
                                     hal::interface::DigitalOutPin             & wr,
                                     hal::interface::DigitalOutPin             & rd,
                                     hal::interface::DigitalOutPin             & ce,
                                     hal::interface::DigitalOutPin             & c_d,
                                     hal::interface::DigitalOutPin             & rst,
                                     hal::interface::DigitalOutPin             & fs,
                                     hal::interface::DigitalInOutPort<uint8_t> & data)
: _delay(delay),
  _wr   (wr   ),
  _rd   (rd   ),
  _ce   (ce   ),
  _c_d  (c_d  ),
  _rst  (rst  ),
  _fs   (fs   ),
  _data (data )
{
  _data.setMode(hal::interface::DigitalInOutPortConfiguration::INPUT);
}

RA6963_IoGpio8Bit::~RA6963_IoGpio8Bit()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RA6963_IoGpio8Bit::reset()
{
  _rst.set();

  _delay.delay_us(5000);

  _rst.clr();

  _delay.delay_us(5000);

  _rst.set();
}

uint8_t RA6963_IoGpio8Bit::readStatus()
{
  _data.setMode(hal::interface::DigitalInOutPortConfiguration::INPUT);

  _rd.clr();
  _ce.clr();

  _delay.delay_us(1);

  uint8_t const status = _data.get();

  _ce.set();
  _rd.set();

  return status;
}

uint8_t RA6963_IoGpio8Bit::readData()
{
  _data.setMode(hal::interface::DigitalInOutPortConfiguration::INPUT);

  _c_d.clr();
  _rd.clr ();
  _ce.clr ();

  uint8_t const data = _data.get();

  _ce.set ();
  _rd.set ();
  _c_d.set();

  return data;
}

void RA6963_IoGpio8Bit::writeData(uint8_t const data_val)
{
  _data.setMode(hal::interface::DigitalInOutPortConfiguration::OUTPUT);

  _c_d.clr();

  _data.set(data_val);

  _wr.clr ();
  _ce.clr ();

  _delay.delay_us(1);

  _ce.set ();
  _wr.set ();
  _c_d.set();
}

void RA6963_IoGpio8Bit::writeCommand(uint8_t const cmd_val)
{
  _data.setMode(hal::interface::DigitalInOutPortConfiguration::OUTPUT);

  _data.set(cmd_val);

  _wr.clr();
  _ce.clr();

  _delay.delay_us(1);

  _ce.set();
  _wr.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::glcd::RA6963 */
