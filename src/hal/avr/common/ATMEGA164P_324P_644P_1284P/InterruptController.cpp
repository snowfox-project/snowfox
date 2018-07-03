/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA164P_324P_644P_1284P/InterruptController.h>

#include <assert.h>

/* Required for 'assert' which in turn needs 'abort' in avr-gcc */
#if defined(MCU_ARCH_avr)
  #include <stdlib.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* TODO */

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

/* TODO */

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController()
{
  /* TODO */
}

InterruptController::~InterruptController()
{
  /* TODO */
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void InterruptController::enableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                          ): asm volatile("sei");    break;
#endif
  case toIntNum(Interrupt::INVALID                         ): /* DO NOTHING */        break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                          ): asm volatile("cli");     break;
#endif
  }
}

void InterruptController::registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback)
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA164P_324P_644P_1284P */

} /* hal */

} /* spectre */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega164p) || defined(MCU_TYPE_atmega324p) || defined(MCU_TYPE_atmega644p) || defined(MCU_TYPE_atmega1284p) )

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::ATMEGA164P_324P_644P_1284P;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(INT0_vect)
{

}

ISR(INT1_vect)
{

}

ISR(INT2_vect)
{

}

ISR(PCINT0_vect)
{

}

ISR(PCINT1_vect)
{

}

ISR(PCINT2_vect)
{

}

ISR(PCINT3_vect)
{

}

ISR(WDT_vect)
{

}

ISR(TIMER2_COMPA_vect)
{

}

ISR(TIMER2_COMPB_vect)
{

}

ISR(TIMER2_OVF_vect)
{

}

ISR(TIMER1_CAPT_vect)
{

}

ISR(TIMER1_COMPA_vect)
{

}

ISR(TIMER1_COMPB_vect)
{

}

ISR(TIMER1_OVF_vect)
{

}

ISR(TIMER0_COMPA_vect)
{

}

ISR(TIMER0_COMPB_vect)
{

}

ISR(TIMER0_OVF_vect)
{

}

ISR(SPI_STC_vect)
{

}

ISR(USART0_RX_vect)
{

}

ISR(USART0_UDRE_vect)
{

}

ISR(USART0_TX_vect)
{

}

ISR(ANALOG_COMP_vect)
{

}

ISR(ADC_vect)
{

}

ISR(EE_READY_vect)
{

}

ISR(TWI_vect)
{

}

ISR(SPM_READY_vect)
{

}

ISR(USART1_RX_vect)
{

}

ISR(USART1_UDRE_vect)
{

}

ISR(USART1_TX_vect)
{

}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega164p) || defined(MCU_TYPE_atmega324p) || defined(MCU_TYPE_atmega644p) || defined(MCU_TYPE_atmega1284p) ) ) */
