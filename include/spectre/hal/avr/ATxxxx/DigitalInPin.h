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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINPIN_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINPIN_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

#include <spectre/hal/interface/gpio/DigitalInPin.h>
#include <spectre/hal/interface/gpio/DigitalInPinConfiguration.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class DigitalInPin : public interface::DigitalInPin,
                     public interface::DigitalInPinConfiguration
{

public:

           DigitalInPin(volatile uint8_t * ddr, volatile uint8_t * out, volatile uint8_t * pin, uint8_t const in_pin_number);
  virtual ~DigitalInPin();


  /* Digital Input Pin Interface */

  virtual bool isHigh() override;


  /* Digital Input Pin Configuration Interface */

  virtual void setPullUpMode(interface::DigitalInPinConfiguration::ePullUpMode const pullup_mode) override;

private:

  volatile uint8_t * _ddr,
                   * _out,
                   * _pin;

  uint8_t            _in_pin_bitmask;


  void setGpioAsInput();

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINPIN_H_ */
