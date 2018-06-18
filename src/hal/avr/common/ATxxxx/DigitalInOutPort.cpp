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

#include <spectre/hal/avr/common/ATxxxx/DigitalInOutPort.h>

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

DigitalInOutPort::DigitalInOutPort(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin)
: _ddr (ddr ),
  _port(port),
  _pin (pin )
{

}

DigitalInOutPort::~DigitalInOutPort()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t DigitalInOutPort::get()
{
  return *_pin;
}

void DigitalInOutPort::set(uint8_t const val)
{
  *_port = val;
}

void DigitalInOutPort::setMode(interface::DigitalInOutPortConfiguration::ModeSelect const mode, interface::PullUpMode const pullup_mode)
{
  switch(mode)
  {
  case interface::DigitalInOutPortConfiguration::INPUT : { setGpioPortAsInput(); setGpioPortPullUpMode(pullup_mode); } break;
  case interface::DigitalInOutPortConfiguration::OUTPUT: { setGpioPortAsOutput();                                    } break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalInOutPort::setGpioPortAsInput()
{
  *_ddr = 0x00;
}

void DigitalInOutPort::setGpioPortAsOutput()
{
  *_ddr = 0xFF;
}

void DigitalInOutPort::setGpioPortPullUpMode(interface::PullUpMode const pullup_mode)
{
  switch(pullup_mode)
  {
  case interface::PullUpMode::NONE:      *_port = 0x00; break;
  case interface::PullUpMode::PULL_UP:   *_port = 0xFF; break;
  case interface::PullUpMode::PULL_DOWN:                break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
