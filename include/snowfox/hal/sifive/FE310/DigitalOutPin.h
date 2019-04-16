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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_DIGITALOUTPIN_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_DIGITALOUTPIN_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/hal/interface/gpio/DigitalOutPin.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class DigitalOutPin : public interface::DigitalOutPin
{

public:

           DigitalOutPin(volatile uint32_t       * gpio_input_en,
                         volatile uint32_t       * gpio_output_en,
                         volatile uint32_t       * gpio_output_val,
                                  uint8_t  const   out_pin_number);
  virtual ~DigitalOutPin();


  virtual void set() override;
  virtual void clr() override;


private:

  volatile uint32_t       * _gpio_output_val;
          uint8_t   const   _out_pin_number;

  static void setGpioPinAsOutput(volatile uint32_t * gpio_input_en, volatile uint32_t * gpio_output_en, uint8_t const out_pin_number);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_DIGITALOUTPIN_H_ */
