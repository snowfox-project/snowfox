/**
 * Spectre is a modular RTOS with extensive IO support.
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

#include <spectre/hal/avr/common/ATxxxx/DigitalInPort.h>

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

DigitalInPort::DigitalInPort(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin)
: _ddr (ddr ),
  _port(port),
  _pin (pin )
{
  setGpioPortAsInput();
}

DigitalInPort::~DigitalInPort()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t DigitalInPort::get()
{
  return *_pin;
}

void DigitalInPort::setPullUpMode(interface::PullUpMode const pullup_mode)
{
  switch(pullup_mode)
  {
  case interface::PullUpMode::NONE:      *_port = 0x00; break;
  case interface::PullUpMode::PULL_UP:   *_port = 0xFF; break;
  case interface::PullUpMode::PULL_DOWN:                break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalInPort::setGpioPortAsInput()
{
  *_ddr = 0x00;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
