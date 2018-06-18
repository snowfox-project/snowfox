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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>

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

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT7_bm   (1<<7)
#define INT6_bm   (1<<6)
#define INT5_bm   (1<<5)
#define INT4_bm   (1<<4)
#define INT3_bm   (1<<3)
#define INT2_bm   (1<<2)
#define INT1_bm   (1<<1)
#define INT0_bm   (1<<0)

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

static interface::InterruptCallback * isr_external_int0                   = 0,
                                    * isr_external_int1                   = 0,
                                    * isr_external_int2                   = 0,
                                    * isr_external_int3                   = 0,
                                    * isr_external_int4                   = 0,
                                    * isr_external_int5                   = 0,
                                    * isr_external_int6                   = 0,
                                    * isr_external_int7                   = 0,
                                    * isr_pin_change_int0                 = 0,
                                    * isr_pin_change_int1                 = 0,
                                    * isr_pin_change_int2                 = 0,
                                    * isr_watchdog_timer                  = 0,
                                    * isr_timer2_compare_a                = 0,
                                    * isr_timer2_compare_b                = 0,
                                    * isr_timer2_overflow                 = 0,
                                    * isr_timer1_capture                  = 0,
                                    * isr_timer1_compare_a                = 0,
                                    * isr_timer1_compare_b                = 0,
                                    * isr_timer1_compare_c                = 0,
                                    * isr_timer1_overflow                 = 0,
                                    * isr_timer0_compare_a                = 0,
                                    * isr_timer0_compare_b                = 0,
                                    * isr_timer0_overflow                 = 0,
                                    * isr_spi_serial_transfer_complete    = 0,
                                    * isr_usart0_receive_complete         = 0,
                                    * isr_usart0_uart_data_register_empty = 0,
                                    * isr_usart0_transmit_complete        = 0;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk)
: _EIMSK (eimsk)
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
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): *_EIMSK   |= INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): *_EIMSK   |= INT1_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): *_EIMSK   |= INT2_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): *_EIMSK   |= INT3_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): *_EIMSK   |= INT4_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): *_EIMSK   |= INT5_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): *_EIMSK   |= INT6_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): *_EIMSK   |= INT7_bm;   break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): break;
  case toIntNum(Interrupt::EEPROM_READY                   ): break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): break;
  case toIntNum(Interrupt::SPM_READY                      ): break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("sei");    break;
#endif
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): *_EIMSK   &= ~INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): *_EIMSK   &= ~INT1_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): *_EIMSK   &= ~INT2_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): *_EIMSK   &= ~INT3_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): *_EIMSK   &= ~INT4_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): *_EIMSK   &= ~INT5_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): *_EIMSK   &= ~INT6_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): *_EIMSK   &= ~INT7_bm;   break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): break;
  case toIntNum(Interrupt::EEPROM_READY                   ): break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): break;
  case toIntNum(Interrupt::SPM_READY                      ): break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("cli");     break;
#endif
  }
}

void InterruptController::registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback)
{
  switch(isr_num)
  {
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT0                  ): isr_external_int0                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT1                  ): isr_external_int1                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT2                  ): isr_external_int2                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT3                  ): isr_external_int3                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT4                  ): isr_external_int4                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT5                  ): isr_external_int5                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT6                  ): isr_external_int6                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT7                  ): isr_external_int7                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT0                ): isr_pin_change_int0                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT1                ): isr_pin_change_int1                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT2                ): isr_pin_change_int2                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::WATCHDOG_TIMER                 ): isr_watchdog_timer                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_COMPARE_A               ): isr_timer2_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_COMPARE_B               ): isr_timer2_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_OVERFLOW                ): isr_timer2_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_CAPTURE                 ): isr_timer1_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_A               ): isr_timer1_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_B               ): isr_timer1_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_C               ): isr_timer1_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_OVERFLOW                ): isr_timer1_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE_A               ): isr_timer0_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE_B               ): isr_timer0_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_OVERFLOW                ): isr_timer0_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPI_SERIAL_TRANSFER_COMPLETE   ): isr_spi_serial_transfer_complete    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_RECEIVE_COMPLETE        ): isr_usart0_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_UART_DATA_REGISTER_EMPTY): isr_usart0_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_TRANSMIT_COMPLETE       ): isr_usart0_transmit_complete        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_COMPARATOR              ): break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_DIGITAL_CONVERTER       ): break;
  case toIsrNum(InterruptServiceRoutine::EEPROM_READY                   ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_CAPTURE                 ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_A               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_B               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_C               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_OVERFLOW                ): break;
  case toIsrNum(InterruptServiceRoutine::USART1_RECEIVE_COMPLETE        ): break;
  case toIsrNum(InterruptServiceRoutine::USART1_UART_DATA_REGISTER_EMPTY): break;
  case toIsrNum(InterruptServiceRoutine::USART1_TRANSMIT_COMPLETE       ): break;
  case toIsrNum(InterruptServiceRoutine::TWO_WIRE_INT                   ): break;
  case toIsrNum(InterruptServiceRoutine::SPM_READY                      ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_CAPTURE                 ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_A               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_B               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_C               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_OVERFLOW                ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_CAPTURE                 ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_COMPARE_A               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_COMPARE_B               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_COMPARE_C               ): break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_OVERFLOW                ): break;
  case toIsrNum(InterruptServiceRoutine::USART2_RECEIVE_COMPLETE        ): break;
  case toIsrNum(InterruptServiceRoutine::USART2_UART_DATA_REGISTER_EMPTY): break;
  case toIsrNum(InterruptServiceRoutine::USART2_TRANSMIT_COMPLETE       ): break;
  case toIsrNum(InterruptServiceRoutine::USART3_RECEIVE_COMPLETE        ): break;
  case toIsrNum(InterruptServiceRoutine::USART3_UART_DATA_REGISTER_EMPTY): break;
  case toIsrNum(InterruptServiceRoutine::USART3_TRANSMIT_COMPLETE       ): break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* spectre */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640) )

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::ATMEGA640_1280_2560;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(INT0_vect)
{
  if(isr_external_int0) isr_external_int0->interruptServiceRoutine();
}

ISR(INT1_vect)
{
  if(isr_external_int1) isr_external_int1->interruptServiceRoutine();
}

ISR(INT2_vect)
{
  if(isr_external_int2) isr_external_int2->interruptServiceRoutine();
}

ISR(INT3_vect)
{
  if(isr_external_int3) isr_external_int3->interruptServiceRoutine();
}

ISR(INT4_vect)
{
  if(isr_external_int4) isr_external_int4->interruptServiceRoutine();
}

ISR(INT5_vect)
{
  if(isr_external_int5) isr_external_int5->interruptServiceRoutine();
}

ISR(INT6_vect)
{
  if(isr_external_int6) isr_external_int6->interruptServiceRoutine();
}

ISR(INT7_vect)
{
  if(isr_external_int7) isr_external_int7->interruptServiceRoutine();
}

ISR(PCINT0_vect)
{
  if(isr_pin_change_int0) isr_pin_change_int0->interruptServiceRoutine();
}

ISR(PCINT1_vect)
{
  if(isr_pin_change_int1) isr_pin_change_int1->interruptServiceRoutine();
}

ISR(PCINT2_vect)
{
  if(isr_pin_change_int2) isr_pin_change_int2->interruptServiceRoutine();
}

ISR(WDT_vect)
{
  if(isr_watchdog_timer) isr_watchdog_timer->interruptServiceRoutine();
}

ISR(TIMER2_COMPA_vect)
{
  if(isr_timer2_compare_a) isr_timer2_compare_a->interruptServiceRoutine();
}

ISR(TIMER2_COMPB_vect)
{
  if(isr_timer2_compare_b) isr_timer2_compare_b->interruptServiceRoutine();
}

ISR(TIMER2_OVF_vect)
{
  if(isr_timer2_overflow) isr_timer2_overflow->interruptServiceRoutine();
}

ISR(TIMER1_CAPT_vect)
{
  if(isr_timer1_capture) isr_timer1_capture->interruptServiceRoutine();
}

ISR(TIMER1_COMPA_vect)
{
  if(isr_timer1_compare_a) isr_timer1_compare_a->interruptServiceRoutine();
}

ISR(TIMER1_COMPB_vect)
{
  if(isr_timer1_compare_b) isr_timer1_compare_b->interruptServiceRoutine();
}

ISR(TIMER1_COMPC_vect)
{
  if(isr_timer1_compare_c) isr_timer1_compare_c->interruptServiceRoutine();
}

ISR(TIMER1_OVF_vect)
{
  if(isr_timer1_overflow) isr_timer1_overflow->interruptServiceRoutine();
}

ISR(TIMER0_COMPA_vect)
{
  if(isr_timer0_compare_a) isr_timer0_compare_a->interruptServiceRoutine();
}

ISR(TIMER0_COMPB_vect)
{
  if(isr_timer0_compare_b) isr_timer0_compare_b->interruptServiceRoutine();
}

ISR(TIMER0_OVF_vect)
{
  if(isr_timer0_overflow) isr_timer0_overflow->interruptServiceRoutine();
}

ISR(SPI_STC_vect)
{
  if(isr_spi_serial_transfer_complete) isr_spi_serial_transfer_complete->interruptServiceRoutine();
}

ISR(USART0_RX_vect)
{
  if(isr_usart0_receive_complete) isr_usart0_receive_complete->interruptServiceRoutine();
}

ISR(USART0_UDRE_vect)
{
  if(isr_usart0_uart_data_register_empty) isr_usart0_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART0_TX_vect)
{
  if(isr_usart0_transmit_complete) isr_usart0_transmit_complete->interruptServiceRoutine();
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

ISR(TIMER3_CAPT_vect)
{

}

ISR(TIMER3_COMPA_vect)
{

}

ISR(TIMER3_COMPB_vect)
{

}

ISR(TIMER3_COMPC_vect)
{

}

ISR(TIMER3_OVF_vect)
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

ISR(TWI_vect)
{

}

ISR(SPM_READY_vect)
{

}

ISR(TIMER4_CAPT_vect)
{

}

ISR(TIMER4_COMPA_vect)
{

}

ISR(TIMER4_COMPB_vect)
{

}

ISR(TIMER4_COMPC_vect)
{

}

ISR(TIMER4_OVF_vect)
{

}

ISR(TIMER5_CAPT_vect)
{

}

ISR(TIMER5_COMPA_vect)
{

}

ISR(TIMER5_COMPB_vect)
{

}

ISR(TIMER5_COMPC_vect)
{

}

ISR(TIMER5_OVF_vect)
{

}

ISR(USART2_RX_vect)
{

}

ISR(USART2_UDRE_vect)
{

}

ISR(USART2_TX_vect)
{

}

ISR(USART3_RX_vect)
{

}

ISR(USART3_UDRE_vect)
{

}

ISR(USART3_TX_vect)
{

}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640) ) */
