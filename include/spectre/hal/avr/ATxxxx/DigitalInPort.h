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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINPORT_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINPORT_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

#include <spectre/hal/interface/gpio/DigitalInPort.h>
#include <spectre/hal/interface/gpio/DigitalInConfiguration.h>

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

class DigitalInPort : public interface::DigitalInPort<uint8_t>,
                      public interface::DigitalInConfiguration
{

public:

           DigitalInPort(volatile uint8_t * ddr, volatile uint8_t * out, volatile uint8_t * pin);
  virtual ~DigitalInPort();


  /* Digital Input Port Interface */

  virtual uint8_t get() override;


  /* Digital Input Configuration */

  virtual void setPullUpMode(interface::DigitalInConfiguration::PullUpMode const pullup_mode) override;

private:

  volatile uint8_t * _ddr,
                   * _out,
                   * _pin;

  void setGpioPortAsInput();

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINPORT_H_ */
