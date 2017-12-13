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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/interrupt/InterruptController.h>

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

class InterruptController : public interface::InterruptController
{

public:

           InterruptController();
  virtual ~InterruptController();


  static uint16_t const GLOBAL_INT   =  0;
  static uint16_t const EXT_INT0     =  1;
  static uint16_t const EXT_INT1     =  2;
  static uint16_t const PCINT0       =  3;
  static uint16_t const PCINT1       =  4;
  static uint16_t const PCINT2       =  5;
  static uint16_t const WDT          =  6;
  static uint16_t const TIMER2_COMPA =  7;
  static uint16_t const TIMER2_COMPB =  8;
  static uint16_t const TIMER2_OVF   =  9;
  static uint16_t const TIMER1_CAPT  = 10;
  static uint16_t const TIMER1_COMPA = 11;
  static uint16_t const TIMER1_COMPB = 12;
  static uint16_t const TIMER1_OVF   = 13;
  static uint16_t const TIMER0_COMPA = 14;
  static uint16_t const TIMER0_COMPB = 15;
  static uint16_t const TIMER0_OVF   = 16;
  static uint16_t const SPI_STC      = 17;
  static uint16_t const USART_RX     = 18;
  static uint16_t const USART_UDRE   = 19;
  static uint16_t const USART_TX     = 20;
  static uint16_t const ADC          = 21;
  static uint16_t const EE_READY     = 22;
  static uint16_t const ANALOG_COMP  = 23;
  static uint16_t const TWI          = 24;
  static uint16_t const SPM_READY    = 25;



  /* Interrupt Controller Interface */

  virtual void enableInterrupt (uint16_t const int_num) override;
  virtual void disableInterrupt(uint16_t const int_num) override;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_ */
