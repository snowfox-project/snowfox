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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DIGITALINPIN_H_
#define INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DIGITALINPIN_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/hal/interface/gpio/DigitalInPin.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATxxxx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DigitalInPin : public interface::DigitalInPin
{

public:

           DigitalInPin(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin, uint8_t const in_pin_number);
  virtual ~DigitalInPin();


  /* DigitalIn Interface */

  virtual bool isSet() override;


  /* Digital In Configuration */

  virtual bool setPullUpMode(interface::PullUpMode const pullup_mode) override;

private:

  volatile uint8_t       * _port,
                         * _pin;
           uint8_t const   _in_pin_number;

  static void setGpioPinAsInput(volatile uint8_t * ddr, uint8_t const in_pin_number);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATxxxx */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DIGITALINPIN_H_ */
