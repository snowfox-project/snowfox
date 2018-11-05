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

HD44780_IoGpio8Bit::HD44780_IoGpio8Bit(hal::interface::Delay                     & delay,
                                       hal::interface::DigitalOutPin             & rs,
                                       hal::interface::DigitalOutPin             & rw,
                                       hal::interface::DigitalOutPin             & enable,
                                       hal::interface::DigitalInOutPort<uint8_t> & data)
: _delay (delay ),
  _rs    (rs    ),
  _rw    (rw    ),
  _enable(enable),
  _data  (data  )
{
  _rs.set    ();
  _rw.set    ();
  _enable.clr();

  _data.setMode(hal::interface::DigitalInOutPortConfiguration::OUTPUT);
}

HD44780_IoGpio8Bit::~HD44780_IoGpio8Bit()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t HD44780_IoGpio8Bit::readStatus()
{
  _data.setMode(hal::interface::DigitalInOutPortConfiguration::INPUT);

  _enable.set    ();
  _delay.delay_us(1);
  uint8_t const status = _data.get();
  _enable.clr    ();

  _data.setMode(hal::interface::DigitalInOutPortConfiguration::OUTPUT);

  return status;
}

void HD44780_IoGpio8Bit::writeData(uint8_t const data_val)
{
  _rw.clr        ();
  _data.set      (data_val);
  _enable.set    ();
  _delay.delay_us(1);
  _enable.clr    ();
  _delay.delay_us(100);
  _rw.set        ();
}

void HD44780_IoGpio8Bit::writeCommand(uint8_t const cmd_val)
{
  _rs.clr        ();
  _rw.clr        ();
  _data.set      (cmd_val);
  _enable.set    ();
  _delay.delay_us(1);
  _enable.clr    ();
  _delay.delay_us(100);
  _rw.set        ();
  _rs.set        ();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* HD44780 */

} /* tlcd */

} /* driver */

} /* spectre */
