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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DELAY_H_
#define INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DELAY_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/delay/Delay.h>

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

class Delay : public interface::Delay
{

public:

           Delay();
  virtual ~Delay();


  virtual void delay_ms(uint32_t const ms) override;
  virtual void delay_us(uint32_t const us) override;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_ATXXXX_DELAY_H_ */
