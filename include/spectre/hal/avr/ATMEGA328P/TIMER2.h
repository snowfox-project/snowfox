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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_TIMER2_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_TIMER2_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

#include <spectre/hal/interface/timer/Timer.h>
#include <spectre/hal/interface/timer/TimerConfiguration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TIMER2 : public interface::Timer<uint8_t>,
               public interface::TimerConfiguration
{

public:

           TIMER2(volatile uint8_t * TCNT2,
                  volatile uint8_t * TCCR2B);
  virtual ~TIMER2();


  /* Timer Interface */

  virtual void    start(                 ) override;
  virtual void    stop (                 ) override;
  virtual void    set  (uint8_t const val) override;
  virtual uint8_t get  (                 ) override;


  /* Timer Configuration Interface */

  virtual void setPrescaler(uint32_t const prescaler) override;

private:

           uint32_t   _prescaler;

  volatile uint8_t  * _TCNT2,
                    * _TCCR2B;


  void setPrescaler_TCCR2B(uint32_t const prescaler);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_TIMER2_H_ */
