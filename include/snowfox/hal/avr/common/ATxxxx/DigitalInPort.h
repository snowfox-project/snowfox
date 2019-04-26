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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DIGITALINPORT_H_
#define INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DIGITALINPORT_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/hal/interface/gpio/DigitalInPort.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class DigitalInPort : public interface::DigitalInPort<uint8_t>
{

public:

           DigitalInPort(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin);
  virtual ~DigitalInPort();


  /* Digital Input Port Interface */

  virtual uint8_t get() override;


  /* Digital Input Configuration */

  virtual bool setPullUpMode(interface::PullUpMode const pullup_mode) override;

private:

  volatile uint8_t * _port,
                   * _pin;

  static void setGpioPortAsInput(volatile uint8_t * ddr);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DIGITALINPORT_H_ */
