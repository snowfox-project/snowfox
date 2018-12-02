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

static interface::InterruptCallback * isr_crc_nmi                         = 0,
                                    * isr_voltage_level_monitor           = 0,
                                    * isr_rtc_overflow_or_compare         = 0,
                                    * isr_rtc_periodic_interrupt          = 0,
                                    * isr_configurable_custom_logic       = 0,
                                    * isr_porta_external_int              = 0,
                                    * isr_timera0_overflow                = 0,
                                    * isr_timera0_underflow               = 0, /* For Timer A0 "Split Mode" */
                                    * isr_timera0_compare_0               = 0,
                                    * isr_timera0_compare_1               = 0,
                                    * isr_timera0_compare_2               = 0,
                                    * isr_timerb0_capture                 = 0,
                                    * isr_timerb1_capture                 = 0,
                                    * isr_twi0_slave                      = 0,
                                    * isr_twi0_master                     = 0,
                                    * isr_spi0                            = 0,
                                    * isr_usart0_receive_complete         = 0,
                                    * isr_usart0_uart_data_register_empty = 0,
                                    * isr_usart0_transmit_complete        = 0,
                                    * isr_portd_external_int              = 0,
                                    * isr_analog_comparator               = 0,
                                    * isr_adc0_result_ready               = 0,
                                    * isr_adc0_window_compare             = 0,
                                    * isr_portc_external_int              = 0,
                                    * isr_timerb2_capture                 = 0,
                                    * isr_usart1_receive_complete         = 0,
                                    * isr_usart1_uart_data_register_empty = 0,
                                    * isr_usart1_transmit_complete        = 0,
                                    * isr_portf_external_int              = 0,
                                    * isr_non_volatile_memory_ready       = 0,
                                    * isr_usart2_receive_complete         = 0,
                                    * isr_usart2_uart_data_register_empty = 0,
                                    * isr_usart2_transmit_complete        = 0,
                                    * isr_portb_external_int              = 0, /* Only for 48 pin package */
                                    * isr_porte_external_int              = 0, /* Only for 48 pin package */
                                    * isr_timerb3_capture                 = 0, /* Only for 48 pin package */
                                    * isr_usart3_receive_complete         = 0, /* Only for 48 pin package */
                                    * isr_usart3_uart_data_register_empty = 0, /* Only for 48 pin package */
                                    * isr_usart3_transmit_complete        = 0; /* Only for 48 pin package */

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
  if(isr_crc_nmi) isr_crc_nmi->interruptServiceRoutine();
}

ISR(BOD_VLM_vect)
{
  if(isr_voltage_level_monitor) isr_voltage_level_monitor->interruptServiceRoutine();
}

ISR(RTC_CNT_vect)
{
  if(isr_rtc_overflow_or_compare) isr_rtc_overflow_or_compare->interruptServiceRoutine();
}

ISR(RTC_PIT_vect)
{
  if(isr_rtc_periodic_interrupt) isr_rtc_periodic_interrupt->interruptServiceRoutine();
}

ISR(CCL_CCL_vect)
{
  if(isr_configurable_custom_logic) isr_configurable_custom_logic->interruptServiceRoutine();
}

ISR(PORTA_PORT_vect)
{
  if(isr_porta_external_int) isr_porta_external_int->interruptServiceRoutine();
}

ISR(TCA0_OVF_vect)
{
  if(isr_timera0_overflow) isr_timera0_overflow->interruptServiceRoutine();
}

ISR(TCA0_HUNF_vect)
{
  if(isr_timera0_underflow) isr_timera0_underflow->interruptServiceRoutine();
}

ISR(TCA0_CMP0_vect)
{
  if(isr_timera0_compare_0) isr_timera0_compare_0->interruptServiceRoutine();
}

ISR(TCA0_CMP1_vect)
{
  if(isr_timera0_compare_1) isr_timera0_compare_1->interruptServiceRoutine();
}

ISR(TCA0_CMP2_vect)
{
  if(isr_timera0_compare_2) isr_timera0_compare_2->interruptServiceRoutine();
}

ISR(TCB0_INT_vect)
{
  if(isr_timerb0_capture) isr_timerb0_capture->interruptServiceRoutine();
}

ISR(TCB1_INT_vect)
{
  if(isr_timerb1_capture) isr_timerb1_capture->interruptServiceRoutine();
}

ISR(TWI0_TWIS_vect)
{
  if(isr_twi0_slave) isr_twi0_slave->interruptServiceRoutine();
}

ISR(TWI0_TWIM_vect)
{
  if(isr_twi0_master) isr_twi0_master->interruptServiceRoutine();
}

ISR(SPI0_INT_vect)
{
  if(isr_spi0) isr_spi0->interruptServiceRoutine();
}

ISR(USART0_RXC_vect)
{
  if(isr_usart0_receive_complete) isr_usart0_receive_complete->interruptServiceRoutine();
}

ISR(USART0_DRE_vect)
{
  if(isr_usart0_uart_data_register_empty) isr_usart0_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART0_TXC_vect)
{
  if(isr_usart0_transmit_complete) isr_usart0_transmit_complete->interruptServiceRoutine();
}

ISR(PORTD_PORT_vect)
{
  if(isr_portd_external_int) isr_portd_external_int->interruptServiceRoutine();
}

ISR(AC0_AC_vect)
{
  if(isr_analog_comparator) isr_analog_comparator->interruptServiceRoutine();
}

ISR(ADC0_RESRDY_vect)
{
  if(isr_adc0_result_ready) isr_adc0_result_ready->interruptServiceRoutine();
}

ISR(ADC0_WCOMP_vect)
{
  if(isr_adc0_window_compare) isr_adc0_window_compare->interruptServiceRoutine();
}

ISR(PORTC_PORT_vect)
{
  if(isr_portc_external_int) isr_portc_external_int->interruptServiceRoutine();
}

ISR(TCB2_INT_vect)
{
  if(isr_timerb2_capture) isr_timerb2_capture->interruptServiceRoutine();
}

ISR(USART1_RXC_vect)
{
  if(isr_usart1_receive_complete) isr_usart1_receive_complete->interruptServiceRoutine();
}

ISR(USART1_DRE_vect)
{
  if(isr_usart1_uart_data_register_empty) isr_usart1_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART1_TXC_vect)
{
  if(isr_usart1_transmit_complete) isr_usart1_transmit_complete->interruptServiceRoutine();
}

ISR(PORTF_PORT_vect)
{
  if(isr_portf_external_int) isr_portf_external_int->interruptServiceRoutine();
}

ISR(NVMCTRL_EE_vect)
{
  if(isr_non_volatile_memory_ready) isr_non_volatile_memory_ready->interruptServiceRoutine();
}

ISR(USART2_RXC_vect)
{
  if(isr_usart2_receive_complete) isr_usart2_receive_complete->interruptServiceRoutine();
}

ISR(USART2_DRE_vect)
{
  if(isr_usart2_uart_data_register_empty) isr_usart2_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART2_TXC_vect)
{
  if(isr_usart2_transmit_complete) isr_usart2_transmit_complete->interruptServiceRoutine();
}

ISR(PORTB_PORT_vect)
{
  if(isr_portb_external_int) isr_portb_external_int->interruptServiceRoutine();
}

ISR(PORTE_PORT_vect)
{
  if(isr_porte_external_int) isr_porte_external_int->interruptServiceRoutine();
}

ISR(TCB3_INT_vect)
{
  if(isr_timerb3_capture) isr_timerb3_capture->interruptServiceRoutine();
}

ISR(USART3_RXC_vect)
{
  if(isr_usart3_receive_complete) isr_usart3_receive_complete->interruptServiceRoutine();
}

ISR(USART3_DRE_vect)
{
  if(isr_usart3_uart_data_register_empty) isr_usart3_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART3_TXC_vect)
{
  if(isr_usart3_transmit_complete) isr_usart3_transmit_complete->interruptServiceRoutine();
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega3209) || defined(MCU_TYPE_atmega4809) ) */
