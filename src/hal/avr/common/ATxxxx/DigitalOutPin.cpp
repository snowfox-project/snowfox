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

#include <snowfox/hal/avr/common/ATxxxx/DigitalOutPin.h>

#include <snowfox/util/BitManip.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DigitalOutPin::DigitalOutPin(volatile uint8_t * ddr, volatile uint8_t * port, uint8_t const out_pin_number)
: _port          (port          ),
  _out_pin_number(out_pin_number)
{
  setGpioPinAsOutput(ddr, out_pin_number);
}

DigitalOutPin::~DigitalOutPin()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalOutPin::set()
{
  util::setBit(_port, _out_pin_number);
}

void DigitalOutPin::clr()
{
  util::clrBit(_port, _out_pin_number);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalOutPin::setGpioPinAsOutput(volatile uint8_t * ddr, uint8_t const out_pin_number)
{
  util::setBit(ddr, out_pin_number);

}
/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* snowfox */
