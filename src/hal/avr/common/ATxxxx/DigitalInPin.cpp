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

#include <snowfox/hal/avr/common/ATxxxx/DigitalInPin.h>

#include <snowfox/util/BitUtil.h>

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

DigitalInPin::DigitalInPin(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin, uint8_t const in_pin_number)
: _port         (port         ),
  _pin          (pin          ),
  _in_pin_number(in_pin_number)
{
  setGpioPinAsInput(ddr, in_pin_number);
}

DigitalInPin::~DigitalInPin()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool DigitalInPin::isSet()
{
  bool const is_set = (*_pin & (1<<_in_pin_number)) == (1<<_in_pin_number);

  return is_set;
}

bool DigitalInPin::setPullUpMode(interface::PullUpMode const pullup_mode)
{
  switch(pullup_mode)
  {
  case interface::PullUpMode::NONE:      util::clrBit(_port, _in_pin_number); return true;  break;
  case interface::PullUpMode::PULL_UP:   util::setBit(_port, _in_pin_number); return true;  break;
  case interface::PullUpMode::PULL_DOWN:                                      return false; break;
  default:                                                                    return false; break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalInPin::setGpioPinAsInput(volatile uint8_t * ddr, uint8_t const in_pin_number)
{
  util::clrBit(ddr, in_pin_number);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* snowfox */
