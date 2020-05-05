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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_AT90CAN32_64_128_TIMER0_H_
#define INCLUDE_SNOWFOX_HAL_AVR_AT90CAN32_64_128_TIMER0_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/hal/interface/timer/Timer.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::AT90CAN32_64_128
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TIMER0 : public interface::Timer<uint8_t>
{

public:

           TIMER0(volatile uint8_t * TCNT0,
                  volatile uint8_t * TCCR0A,
                  volatile uint8_t * OCR0A);
  virtual ~TIMER0();


  static uint8_t const COMPARE_A = 0;


  /* Timer Interface */

  virtual void    start             (                 ) override;
  virtual void    stop              (                 ) override;
  virtual void    set               (uint8_t const val) override;
  virtual uint8_t get               (                 ) override;

  virtual void    setCompareRegister(uint8_t const reg_sel, uint8_t const reg_val) override;


  /* Timer Configuration Interface */

  virtual void setPrescaler(uint32_t const prescaler) override;

private:

           uint32_t   _prescaler;

  volatile uint8_t  * _TCNT0,
                    * _TCCR0A,
                    * _OCR0A;


  void setPrescaler_TCCR0A(uint32_t const prescaler);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::AT90CAN32_64_128 */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_AT90CAN32_64_128_TIMER0_H_ */
