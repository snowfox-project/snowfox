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

#include <snowfox/hal/riscv64/FE310/DigitalInPin.h>

#include <snowfox/util/BitUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace FE310
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DigitalInPin::DigitalInPin(volatile uint32_t       * gpio_input_en,
                           volatile uint32_t       * gpio_output_en,
                           volatile uint32_t       * gpio_iof_en,
                           volatile uint32_t       * gpio_input_val,
                           volatile uint32_t       * gpio_pue,
                           uint8_t           const   in_pin_number)
: _gpio_input_val(gpio_input_val),
  _gpio_pue      (gpio_pue      ),
  _in_pin_number (in_pin_number )
{
  setGpioPinAsInput(gpio_input_en, gpio_output_en, gpio_iof_en, in_pin_number);
}

DigitalInPin::~DigitalInPin()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool DigitalInPin::isSet()
{
  bool const is_set = (*_gpio_input_val & (1<<_in_pin_number)) == (1<<_in_pin_number);

  return is_set;
}

bool DigitalInPin::setPullUpMode(interface::PullUpMode const pullup_mode)
{
  switch(pullup_mode)
  {
  case interface::PullUpMode::NONE:       util::clrBit(_gpio_pue, _in_pin_number); return true;  break;
  case interface::PullUpMode::PULL_UP:    util::setBit(_gpio_pue, _in_pin_number); return true;  break;
  case interface::PullUpMode::PULL_DOWN:                                           return false; break;
  default:                                                                         return false; break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalInPin::setGpioPinAsInput(volatile uint32_t       * gpio_input_en,
                                     volatile uint32_t       * gpio_output_en,
                                     volatile uint32_t       * gpio_iof_en,
                                     uint8_t           const   in_pin_number)
{
  util::clrBit(gpio_output_en, in_pin_number);
  util::setBit(gpio_input_en,  in_pin_number);
  util::clrBit(gpio_iof_en,    in_pin_number);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
