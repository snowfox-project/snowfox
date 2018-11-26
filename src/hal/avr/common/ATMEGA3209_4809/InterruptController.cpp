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

#include <spectre/hal/avr/common/ATMEGA3209_4809/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA3209_4809
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController()
{

}

InterruptController::~InterruptController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void InterruptController::enableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  }
}

void InterruptController::registerInterruptCallback(uint8_t const int_num, interface::InterruptCallback * interrupt_callback)
{
  switch(int_num)
  {
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA3209_4809 */

} /* hal */

} /* spectre */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega3209) || defined(MCU_TYPE_atmega4809) )

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::ATMEGA3209_4809;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(CRCSCAN_NMI_vect)
{

}

ISR(BOD_VLM_vect)
{

}

ISR(RTC_CNT_vect)
{

}

ISR(RTC_PIT_vect)
{

}

ISR(CCL_CCL_vect)
{

}

ISR(PORTA_PORT_vect)
{

}

ISR(TCA0_OVF_vect)
{

}

ISR(TCA0_CMP0_vect)
{

}

ISR(TCA0_CMP1_vect)
{

}

ISR(TCA0_CMP2_vect)
{

}

ISR(TCB0_INT_vect)
{

}

ISR(TCB1_INT_vect)
{

}

ISR(TWI0_TWIS_vect)
{

}

ISR(TWI0_TWIM_vect)
{

}

ISR(SPI0_INT_vect)
{

}

ISR(USART0_RXC_vect)
{

}

ISR(USART0_DRE_vect)
{

}

ISR(USART0_TXC_vect)
{

}

ISR(PORTD_PORT_vect)
{

}

ISR(AC0_AC_vect)
{

}

ISR(ADC0_RESRDY_vect)
{

}

ISR(ADC0_WCOMP_vect)
{

}

ISR(PORTC_PORT_vect)
{

}

ISR(TCB2_INT_vect)
{

}

ISR(USART1_RXC_vect)
{

}

ISR(USART1_DRE_vect)
{

}

ISR(USART1_TXC_vect)
{

}

ISR(PORTF_PORT_vect)
{

}

ISR(NVMCTRL_EE_vect)
{

}

ISR(USART2_RXC_vect)
{

}

ISR(USART2_DRE_vect)
{

}

ISR(USART2_TXC_vect)
{

}

ISR(PORTB_PORT_vect)
{

}

ISR(PORTE_PORT_vect)
{

}

ISR(TCB3_INT_vect)
{

}

ISR(USART3_RXC_vect)
{

}

ISR(USART3_DRE_vect)
{

}

ISR(USART3_TXC_vect)
{

}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega3209) || defined(MCU_TYPE_atmega4809) ) */
