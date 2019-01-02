/**
 * Spectre is a modular RTOS with extensive IO support.
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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA3209_4809/InterruptController.h>

#include <spectre/util/BitManip.h>

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

/* CRCSCAN_CTRLA */
#define CRCSCAN_NMIEN_bp 1

/* BOD_INTCTRL */
#define BOD_VLMIE_bp     0

/* RTC_INTCTRL */
#define RTC_CMP_bp       1
#define RTC_OVF_bp       0

/* RTC_PITINTCTRL */
#define RTC_PI_bp        0

/* TCAx_INTCTRL */
#define TCAx_CMP2_bp     6
#define TCAx_CMP1_bp     5
#define TCAx_CMP0_bp     4
#define TCAx_OVF_bp      0

/* TCBx_INTCTRL */
#define TCBx_CAPT_bp     0

/* USARTx_CTRLA */
#define USARTx_RXCIE_bp  7
#define USARTx_TXCIE_bp  6
#define USARTx_DREIE_bp  5
#define USARTx_RXSIE_bp  4

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

InterruptController::InterruptController(volatile uint8_t * crcscan_ctrla,
                                         volatile uint8_t * bod_intctrl,
                                         volatile uint8_t * rtc_intctrl,
                                         volatile uint8_t * rtc_pitintctrl,
                                         volatile uint8_t * tca0_intctrl,
                                         volatile uint8_t * tcb0_intctrl,
                                         volatile uint8_t * tcb1_intctrl,
                                         volatile uint8_t * tcb2_intctrl,
                                         volatile uint8_t * tcb3_intctrl,
                                         volatile uint8_t * usart0_ctrla,
                                         volatile uint8_t * usart1_ctrla,
                                         volatile uint8_t * usart2_ctrla,
                                         volatile uint8_t * usart3_ctrla)
: _CRCSCAN_CTRLA (crcscan_ctrla ),
  _BOD_INTCTRL   (bod_intctrl   ),
  _RTC_INTCTRL   (rtc_intctrl   ),
  _RTC_PITINTCTRL(rtc_pitintctrl),
  _TCA0_INTCTRL  (tca0_intctrl  ),
  _TCB0_INTCTRL  (tcb0_intctrl  ),
  _TCB1_INTCTRL  (tcb1_intctrl  ),
  _TCB2_INTCTRL  (tcb2_intctrl  ),
  _TCB3_INTCTRL  (tcb3_intctrl  ),
  _USART0_CTRLA  (usart0_ctrla  ),
  _USART1_CTRLA  (usart1_ctrla  ),
  _USART2_CTRLA  (usart2_ctrla  ),
  _USART3_CTRLA  (usart3_ctrla  )
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
  case toIntNum(Interrupt::CRC_NMI                        ): util::setBit(_CRCSCAN_CTRLA,  CRCSCAN_NMIEN_bp); break;
  case toIntNum(Interrupt::VOLTAGE_LEVEL_MONITOR          ): util::setBit(_BOD_INTCTRL,    BOD_VLMIE_bp    ); break;
  /* RTC */
  case toIntNum(Interrupt::RTC_OVERFLOW                   ): util::setBit(_RTC_INTCTRL,    RTC_OVF_bp      ); break;
  case toIntNum(Interrupt::RTC_COMPARE                    ): util::setBit(_RTC_INTCTRL,    RTC_CMP_bp      ); break;
  case toIntNum(Interrupt::RTC_PERIODIC_INTERRUPT         ): util::setBit(_RTC_PITINTCTRL, RTC_PI_bp       ); break;
  /* TIMER A0 */
  case toIntNum(Interrupt::TIMERA0_OVER_UNDERFLOW         ): util::setBit(_TCA0_INTCTRL,   TCAx_OVF_bp     ); break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_0              ): util::setBit(_TCA0_INTCTRL,   TCAx_CMP0_bp    ); break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_1              ): util::setBit(_TCA0_INTCTRL,   TCAx_CMP1_bp    ); break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_2              ): util::setBit(_TCA0_INTCTRL,   TCAx_CMP2_bp    ); break;
  /* TIMER B0/1/2/3 */
  case toIntNum(Interrupt::TIMERB0_CAPTURE                ): util::setBit(_TCB0_INTCTRL,   TCBx_CAPT_bp    ); break;
  case toIntNum(Interrupt::TIMERB1_CAPTURE                ): util::setBit(_TCB1_INTCTRL,   TCBx_CAPT_bp    ); break;
  case toIntNum(Interrupt::TIMERB2_CAPTURE                ): util::setBit(_TCB2_INTCTRL,   TCBx_CAPT_bp    ); break;
  case toIntNum(Interrupt::TIMERB3_CAPTURE                ): util::setBit(_TCB3_INTCTRL,   TCBx_CAPT_bp    ); break;
  /* USART0 */
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): util::setBit(_USART0_CTRLA,   USARTx_RXCIE_bp ); break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): util::setBit(_USART0_CTRLA,   USARTx_TXCIE_bp ); break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): util::setBit(_USART0_CTRLA,   USARTx_DREIE_bp ); break;
  case toIntNum(Interrupt::USART0_RECEIVER_START_OF_FRAME ): util::setBit(_USART0_CTRLA,   USARTx_RXSIE_bp ); break;
  /* USART1 */
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): util::setBit(_USART1_CTRLA,   USARTx_RXCIE_bp ); break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): util::setBit(_USART1_CTRLA,   USARTx_TXCIE_bp ); break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): util::setBit(_USART1_CTRLA,   USARTx_DREIE_bp ); break;
  case toIntNum(Interrupt::USART1_RECEIVER_START_OF_FRAME ): util::setBit(_USART1_CTRLA,   USARTx_RXSIE_bp ); break;
  /* USART2 */
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): util::setBit(_USART2_CTRLA,   USARTx_RXCIE_bp ); break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): util::setBit(_USART2_CTRLA,   USARTx_TXCIE_bp ); break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): util::setBit(_USART2_CTRLA,   USARTx_DREIE_bp ); break;
  case toIntNum(Interrupt::USART2_RECEIVER_START_OF_FRAME ): util::setBit(_USART2_CTRLA,   USARTx_RXSIE_bp ); break;
  /* USART3 */
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): util::setBit(_USART3_CTRLA,   USARTx_RXCIE_bp ); break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): util::setBit(_USART3_CTRLA,   USARTx_TXCIE_bp ); break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): util::setBit(_USART3_CTRLA,   USARTx_DREIE_bp ); break;
  case toIntNum(Interrupt::USART3_RECEIVER_START_OF_FRAME ): util::setBit(_USART3_CTRLA,   USARTx_RXSIE_bp ); break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::CRC_NMI                        ): util::clrBit(_CRCSCAN_CTRLA,  CRCSCAN_NMIEN_bp); break;
  case toIntNum(Interrupt::VOLTAGE_LEVEL_MONITOR          ): util::clrBit(_BOD_INTCTRL,    BOD_VLMIE_bp    ); break;
  /* RTC */
  case toIntNum(Interrupt::RTC_OVERFLOW                   ): util::clrBit(_RTC_INTCTRL,    RTC_OVF_bp      ); break;
  case toIntNum(Interrupt::RTC_COMPARE                    ): util::clrBit(_RTC_INTCTRL,    RTC_CMP_bp      ); break;
  case toIntNum(Interrupt::RTC_PERIODIC_INTERRUPT         ): util::clrBit(_RTC_PITINTCTRL, RTC_PI_bp       ); break;
  /* TIMER A0 */
  case toIntNum(Interrupt::TIMERA0_OVER_UNDERFLOW         ): util::clrBit(_TCA0_INTCTRL,   TCAx_OVF_bp     ); break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_0              ): util::clrBit(_TCA0_INTCTRL,   TCAx_CMP0_bp    ); break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_1              ): util::clrBit(_TCA0_INTCTRL,   TCAx_CMP1_bp    ); break;
  /* TIMER B0/1/2/3 */
  case toIntNum(Interrupt::TIMERB0_CAPTURE                ): util::clrBit(_TCB0_INTCTRL,   TCBx_CAPT_bp    ); break;
  case toIntNum(Interrupt::TIMERB1_CAPTURE                ): util::clrBit(_TCB1_INTCTRL,   TCBx_CAPT_bp    ); break;
  case toIntNum(Interrupt::TIMERB2_CAPTURE                ): util::clrBit(_TCB2_INTCTRL,   TCBx_CAPT_bp    ); break;
  case toIntNum(Interrupt::TIMERB3_CAPTURE                ): util::clrBit(_TCB3_INTCTRL,   TCBx_CAPT_bp    ); break;
  /* USART0 */
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): util::clrBit(_USART0_CTRLA,   USARTx_RXCIE_bp ); break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): util::clrBit(_USART0_CTRLA,   USARTx_TXCIE_bp ); break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): util::clrBit(_USART0_CTRLA,   USARTx_DREIE_bp ); break;
  case toIntNum(Interrupt::USART0_RECEIVER_START_OF_FRAME ): util::clrBit(_USART0_CTRLA,   USARTx_RXSIE_bp ); break;
  /* USART1 */
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): util::clrBit(_USART1_CTRLA,   USARTx_RXCIE_bp ); break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): util::clrBit(_USART1_CTRLA,   USARTx_TXCIE_bp ); break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): util::clrBit(_USART1_CTRLA,   USARTx_DREIE_bp ); break;
  case toIntNum(Interrupt::USART1_RECEIVER_START_OF_FRAME ): util::clrBit(_USART1_CTRLA,   USARTx_RXSIE_bp ); break;
  /* USART2 */
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): util::clrBit(_USART2_CTRLA,   USARTx_RXCIE_bp ); break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): util::clrBit(_USART2_CTRLA,   USARTx_TXCIE_bp ); break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): util::clrBit(_USART2_CTRLA,   USARTx_DREIE_bp ); break;
  case toIntNum(Interrupt::USART2_RECEIVER_START_OF_FRAME ): util::clrBit(_USART2_CTRLA,   USARTx_RXSIE_bp ); break;
  /* USART3 */
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): util::clrBit(_USART3_CTRLA,   USARTx_RXCIE_bp ); break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): util::clrBit(_USART3_CTRLA,   USARTx_TXCIE_bp ); break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): util::clrBit(_USART3_CTRLA,   USARTx_DREIE_bp ); break;
  case toIntNum(Interrupt::USART3_RECEIVER_START_OF_FRAME ): util::clrBit(_USART3_CTRLA,   USARTx_RXSIE_bp ); break;
  }
}

void InterruptController::registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback)
{
  switch(isr_num)
  {
  case toIsrNum(Isr::CRC_NMI                        ): isr_crc_nmi                         = interrupt_callback; break;
  case toIsrNum(Isr::VOLTAGE_LEVEL_MONITOR          ): isr_voltage_level_monitor           = interrupt_callback; break;
  case toIsrNum(Isr::RTC_OVERFLOW_OR_COMPARE        ): isr_rtc_overflow_or_compare         = interrupt_callback; break;
  case toIsrNum(Isr::RTC_PERIODIC_INTERRUPT         ): isr_rtc_periodic_interrupt          = interrupt_callback; break;
  case toIsrNum(Isr::CONFIGURABLE_CUSTOM_LOGIC      ): isr_configurable_custom_logic       = interrupt_callback; break;
  case toIsrNum(Isr::PORTA_EXTERNAL_INT             ): isr_porta_external_int              = interrupt_callback; break;
  case toIsrNum(Isr::TIMERA0_OVERFLOW               ): isr_timera0_overflow                = interrupt_callback; break;
  case toIsrNum(Isr::TIMERA0_UNDERFLOW              ): isr_timera0_underflow               = interrupt_callback; break;
  case toIsrNum(Isr::TIMERA0_COMPARE_0              ): isr_timera0_compare_0               = interrupt_callback; break;
  case toIsrNum(Isr::TIMERA0_COMPARE_1              ): isr_timera0_compare_1               = interrupt_callback; break;
  case toIsrNum(Isr::TIMERA0_COMPARE_2              ): isr_timera0_compare_2               = interrupt_callback; break;
  case toIsrNum(Isr::TIMERB0_CAPTURE                ): isr_timerb0_capture                 = interrupt_callback; break;
  case toIsrNum(Isr::TIMERB1_CAPTURE                ): isr_timerb1_capture                 = interrupt_callback; break;
  case toIsrNum(Isr::TWI0_SLAVE                     ): isr_twi0_slave                      = interrupt_callback; break;
  case toIsrNum(Isr::TWI0_MASTER                    ): isr_twi0_master                     = interrupt_callback; break;
  case toIsrNum(Isr::SPI0                           ): isr_spi0                            = interrupt_callback; break;
  case toIsrNum(Isr::USART0_RECEIVE_COMPLETE        ): isr_usart0_receive_complete         = interrupt_callback; break;
  case toIsrNum(Isr::USART0_UART_DATA_REGISTER_EMPTY): isr_usart0_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(Isr::USART0_TRANSMIT_COMPLETE       ): isr_usart0_transmit_complete        = interrupt_callback; break;
  case toIsrNum(Isr::PORTD_EXTERNAL_INT             ): isr_portd_external_int              = interrupt_callback; break;
  case toIsrNum(Isr::ANALOG_COMPARATOR              ): isr_analog_comparator               = interrupt_callback; break;
  case toIsrNum(Isr::ADC0_RESULT_READY              ): isr_adc0_result_ready               = interrupt_callback; break;
  case toIsrNum(Isr::ADC0_WINDOW_COMPARE            ): isr_adc0_window_compare             = interrupt_callback; break;
  case toIsrNum(Isr::PORTC_EXTERNAL_INT             ): isr_portc_external_int              = interrupt_callback; break;
  case toIsrNum(Isr::TIMERB2_CAPTURE                ): isr_timerb2_capture                 = interrupt_callback; break;
  case toIsrNum(Isr::USART1_RECEIVE_COMPLETE        ): isr_usart1_receive_complete         = interrupt_callback; break;
  case toIsrNum(Isr::USART1_UART_DATA_REGISTER_EMPTY): isr_usart1_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(Isr::USART1_TRANSMIT_COMPLETE       ): isr_usart1_transmit_complete        = interrupt_callback; break;
  case toIsrNum(Isr::PORTF_EXTERNAL_INT             ): isr_portf_external_int              = interrupt_callback; break;
  case toIsrNum(Isr::NON_VOLATILE_MEMORY_READY      ): isr_non_volatile_memory_ready       = interrupt_callback; break;
  case toIsrNum(Isr::USART2_RECEIVE_COMPLETE        ): isr_usart2_receive_complete         = interrupt_callback; break;
  case toIsrNum(Isr::USART2_UART_DATA_REGISTER_EMPTY): isr_usart2_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(Isr::USART2_TRANSMIT_COMPLETE       ): isr_usart2_transmit_complete        = interrupt_callback; break;
  case toIsrNum(Isr::PORTB_EXTERNAL_INT             ): isr_portb_external_int              = interrupt_callback; break;
  case toIsrNum(Isr::PORTE_EXTERNAL_INT             ): isr_porte_external_int              = interrupt_callback; break;
  case toIsrNum(Isr::TIMERB3_CAPTURE                ): isr_timerb3_capture                 = interrupt_callback; break;
  case toIsrNum(Isr::USART3_RECEIVE_COMPLETE        ): isr_usart3_receive_complete         = interrupt_callback; break;
  case toIsrNum(Isr::USART3_UART_DATA_REGISTER_EMPTY): isr_usart3_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(Isr::USART3_TRANSMIT_COMPLETE       ): isr_usart3_transmit_complete        = interrupt_callback; break;
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
  executeCallbackIfValid(isr_crc_nmi);
}

ISR(BOD_VLM_vect)
{
  executeCallbackIfValid(isr_voltage_level_monitor);
}

ISR(RTC_CNT_vect)
{
  executeCallbackIfValid(isr_rtc_overflow_or_compare);
}

ISR(RTC_PIT_vect)
{
  executeCallbackIfValid(isr_rtc_periodic_interrupt);
}

ISR(CCL_CCL_vect)
{
  executeCallbackIfValid(isr_configurable_custom_logic);
}

ISR(PORTA_PORT_vect)
{
  executeCallbackIfValid(isr_porta_external_int);
}

ISR(TCA0_OVF_vect)
{
  executeCallbackIfValid(isr_timera0_overflow);
}

ISR(TCA0_HUNF_vect)
{
  executeCallbackIfValid(isr_timera0_underflow);
}

ISR(TCA0_CMP0_vect)
{
  executeCallbackIfValid(isr_timera0_compare_0);
}

ISR(TCA0_CMP1_vect)
{
  executeCallbackIfValid(isr_timera0_compare_1);
}

ISR(TCA0_CMP2_vect)
{
  executeCallbackIfValid(isr_timera0_compare_2);
}

ISR(TCB0_INT_vect)
{
  executeCallbackIfValid(isr_timerb0_capture);
}

ISR(TCB1_INT_vect)
{
  executeCallbackIfValid(isr_timerb1_capture);
}

ISR(TWI0_TWIS_vect)
{
  executeCallbackIfValid(isr_twi0_slave);
}

ISR(TWI0_TWIM_vect)
{
  executeCallbackIfValid(isr_twi0_master);
}

ISR(SPI0_INT_vect)
{
  executeCallbackIfValid(isr_spi0);
}

ISR(USART0_RXC_vect)
{
  executeCallbackIfValid(isr_usart0_receive_complete);
}

ISR(USART0_DRE_vect)
{
  executeCallbackIfValid(isr_usart0_uart_data_register_empty);
}

ISR(USART0_TXC_vect)
{
  executeCallbackIfValid(isr_usart0_transmit_complete);
}

ISR(PORTD_PORT_vect)
{
  executeCallbackIfValid(isr_portd_external_int);
}

ISR(AC0_AC_vect)
{
  executeCallbackIfValid(isr_analog_comparator);
}

ISR(ADC0_RESRDY_vect)
{
  executeCallbackIfValid(isr_adc0_result_ready);
}

ISR(ADC0_WCOMP_vect)
{
  executeCallbackIfValid(isr_adc0_window_compare);
}

ISR(PORTC_PORT_vect)
{
  executeCallbackIfValid(isr_portc_external_int);
}

ISR(TCB2_INT_vect)
{
  executeCallbackIfValid(isr_timerb2_capture);
}

ISR(USART1_RXC_vect)
{
  executeCallbackIfValid(isr_usart1_receive_complete);
}

ISR(USART1_DRE_vect)
{
  executeCallbackIfValid(isr_usart1_uart_data_register_empty);
}

ISR(USART1_TXC_vect)
{
  executeCallbackIfValid(isr_usart1_transmit_complete);
}

ISR(PORTF_PORT_vect)
{
  executeCallbackIfValid(isr_portf_external_int);
}

ISR(NVMCTRL_EE_vect)
{
  executeCallbackIfValid(isr_non_volatile_memory_ready);
}

ISR(USART2_RXC_vect)
{
  executeCallbackIfValid(isr_usart2_receive_complete);
}

ISR(USART2_DRE_vect)
{
  executeCallbackIfValid(isr_usart2_uart_data_register_empty);
}

ISR(USART2_TXC_vect)
{
  executeCallbackIfValid(isr_usart2_transmit_complete);
}

ISR(PORTB_PORT_vect)
{
  executeCallbackIfValid(isr_portb_external_int);
}

ISR(PORTE_PORT_vect)
{
  executeCallbackIfValid(isr_porte_external_int);
}

ISR(TCB3_INT_vect)
{
  executeCallbackIfValid(isr_timerb3_capture);
}

ISR(USART3_RXC_vect)
{
  executeCallbackIfValid(isr_usart3_receive_complete);
}

ISR(USART3_DRE_vect)
{
  executeCallbackIfValid(isr_usart3_uart_data_register_empty);
}

ISR(USART3_TXC_vect)
{
  executeCallbackIfValid(isr_usart3_transmit_complete);
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega3209) || defined(MCU_TYPE_atmega4809) ) */
