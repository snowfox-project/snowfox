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
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/DigitalInPin.h>

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

DigitalInPin::DigitalInPin(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin, uint8_t const in_pin_number)
: _ddr           (ddr               ),
  _port          (port              ),
  _pin           (pin               ),
  _in_pin_bitmask(1 << in_pin_number)
{
  setGpioPinAsInput();
}

DigitalInPin::~DigitalInPin()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool DigitalInPin::isSet()
{
  bool const is_set = (*_pin & _in_pin_bitmask) == _in_pin_bitmask;

  return is_set;
}

void DigitalInPin::setPullUpMode(interface::PullUpMode const pullup_mode)
{
  switch(pullup_mode)
  {
  case interface::PullUpMode::NONE:      *_port &= ~_in_pin_bitmask; break;
  case interface::PullUpMode::PULL_UP:   *_port |=  _in_pin_bitmask; break;
  case interface::PullUpMode::PULL_DOWN:                             break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalInPin::setGpioPinAsInput()
{
  *_ddr &= ~_in_pin_bitmask;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
