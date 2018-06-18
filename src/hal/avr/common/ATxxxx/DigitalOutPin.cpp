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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/DigitalOutPin.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DigitalOutPin::DigitalOutPin(volatile uint8_t * ddr, volatile uint8_t * port, uint8_t const out_pin_number)
: _ddr              (ddr                ),
  _port             (port               ),
  _out_pin_bitmask  (1 << out_pin_number)
{
  setGpioPinAsOutput();
}

DigitalOutPin::~DigitalOutPin()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalOutPin::set()
{
  *_port |= _out_pin_bitmask;
}

void DigitalOutPin::clr()
{
  *_port &= ~_out_pin_bitmask;
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalOutPin::setGpioPinAsOutput()
{
  *_ddr |= _out_pin_bitmask;

}
/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
