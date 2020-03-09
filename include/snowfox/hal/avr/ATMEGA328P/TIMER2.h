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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_ATMEGA328P_TIMER2_H_
#define INCLUDE_SNOWFOX_HAL_AVR_ATMEGA328P_TIMER2_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/hal/interface/timer/Timer.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TIMER2 : public interface::Timer<uint8_t>
{

public:

           TIMER2(volatile uint8_t * tcnt2,
                  volatile uint8_t * tccr2b,
                  volatile uint8_t * ocr2a,
                  volatile uint8_t * ocr2b);
  virtual ~TIMER2();


  static uint8_t const COMPARE_A = 0;
  static uint8_t const COMPARE_B = 1;


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

  volatile uint8_t  * _TCNT2,
                    * _TCCR2B,
                    * _OCR2A,
                    * _OCR2B;


  void setPrescaler_TCCR2B(uint32_t const prescaler);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_ATMEGA328P_TIMER2_H_ */
