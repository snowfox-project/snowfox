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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINOUTPORT_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINOUTPORT_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <spectre/hal/interface/gpio/DigitalInOutPort.h>

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

class DigitalInOutPort : public interface::DigitalInOutPort<uint8_t>
{

public:

           DigitalInOutPort(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin);
  virtual ~DigitalInOutPort();


  /* Digital Input Port Interface */

  virtual uint8_t get(                 ) override;
  virtual void    set(uint8_t const val) override;

  virtual void    setMode(interface::DigitalInOutPortConfiguration::ModeSelect const mode, interface::PullUpMode const pullup_mode = interface::PullUpMode::NONE) override;

private:

  volatile uint8_t * _ddr,
                   * _port,
                   * _pin;

  void setGpioPortAsInput   ();
  void setGpioPortAsOutput  ();
  void setGpioPortPullUpMode(interface::PullUpMode const pullup_mode);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATXXXX_DIGITALINOUTPORT_H_ */
