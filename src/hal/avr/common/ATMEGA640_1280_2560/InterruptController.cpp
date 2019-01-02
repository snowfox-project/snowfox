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

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>

#include <spectre/util/BitManip.h>

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
#define INT7_bp   (7)
#define INT6_bp   (6)
#define INT5_bp   (5)
#define INT4_bp   (4)
#define INT3_bp   (3)
#define INT2_bp   (2)
#define INT1_bp   (1)
#define INT0_bp   (0)

/* PCICR */
#define PCIE0_bp  (0)
#define PCIE1_bp  (1)
#define PCIE2_bp  (2)

/* WDTCSR */
#define WDIE_bp   (6)

/* TIMSK2 */
#define OCIE2B_bp (2)
#define OCIE2A_bp (1)
#define TOIE2_bp  (0)

/* TIMSK1 */
#define ICIE1_bp  (5)
#define OCIE1C_bp (3)
#define OCIE1B_bp (2)
#define OCIE1A_bp (1)
#define TOIE1_bp  (0)

/* TIMSK0 */
#define OCIE0B_bp (2)
#define OCIE0A_bp (1)
#define TOIE0_bp  (0)

/* SPCR */
#define SPIE_bp   (7)

/* UCSR0B */
#define RXCIE0_bp (7)
#define TXCIE0_bp (6)
#define UDRIE0_bp (5)

/* ACSR */
#define ACIE_bp   (3)

/* ADCSRA */
#define ADIE_bp   (3)

/* EECR */
#define EERIE_bp  (3)

/* TIMSK3 */
#define ICIE3_bp  (5)
#define OCIE3C_bp (3)
#define OCIE3B_bp (2)
#define OCIE3A_bp (1)
#define TOIE3_bp  (0)

/* UCSR1B */
#define RXCIE1_bp (7)
#define TXCIE1_bp (6)
#define UDRIE1_bp (5)

/* TIMSK4 */
#define ICIE4_bp  (5)
#define OCIE4C_bp (3)
#define OCIE4B_bp (2)
#define OCIE4A_bp (1)
#define TOIE4_bp  (0)

/* TIMSK5 */
#define ICIE5_bp  (5)
#define OCIE5C_bp (3)
#define OCIE5B_bp (2)
#define OCIE5A_bp (1)
#define TOIE5_bp  (0)

/* UCSR2B */
#define RXCIE2_bp (7)
#define TXCIE2_bp (6)
#define UDRIE2_bp (5)

/* UCSR3B */
#define RXCIE3_bp (7)
#define TXCIE3_bp (6)
#define UDRIE3_bp (5)

/* TWCR */
#define TWIE_bp   (0)

/* SPMCSR */
#define SPMIE_bp  (7)

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
                                    * isr_usart0_transmit_complete        = 0,
                                    * isr_analog_comparator               = 0,
                                    * isr_analog_digital_converter        = 0,
                                    * isr_eeprom_ready                    = 0,
                                    * isr_timer3_capture                  = 0,
                                    * isr_timer3_compare_a                = 0,
                                    * isr_timer3_compare_b                = 0,
                                    * isr_timer3_compare_c                = 0,
                                    * isr_timer3_overflow                 = 0,
                                    * isr_usart1_receive_complete         = 0,
                                    * isr_usart1_uart_data_register_empty = 0,
                                    * isr_usart1_transmit_complete        = 0,
                                    * isr_two_wire_int                    = 0,
                                    * isr_spm_ready                       = 0,
                                    * isr_timer4_capture                  = 0,
                                    * isr_timer4_compare_a                = 0,
                                    * isr_timer4_compare_b                = 0,
                                    * isr_timer4_compare_c                = 0,
                                    * isr_timer4_overflow                 = 0,
                                    * isr_timer5_capture                  = 0,
                                    * isr_timer5_compare_a                = 0,
                                    * isr_timer5_compare_b                = 0,
                                    * isr_timer5_compare_c                = 0,
                                    * isr_timer5_overflow                 = 0,
                                    * isr_usart2_receive_complete         = 0,
                                    * isr_usart2_uart_data_register_empty = 0,
                                    * isr_usart2_transmit_complete        = 0,
                                    * isr_usart3_receive_complete         = 0,
                                    * isr_usart3_uart_data_register_empty = 0,
                                    * isr_usart3_transmit_complete        = 0;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
                                         volatile uint8_t * pcicr,
                                         volatile uint8_t * wdtcsr,
                                         volatile uint8_t * timsk0,
                                         volatile uint8_t * timsk1,
                                         volatile uint8_t * timsk2,
                                         volatile uint8_t * timsk3,
                                         volatile uint8_t * timsk4,
                                         volatile uint8_t * timsk5,
                                         volatile uint8_t * ucsr0b,
                                         volatile uint8_t * ucsr1b,
                                         volatile uint8_t * ucsr2b,
                                         volatile uint8_t * ucsr3b,
                                         volatile uint8_t * spcr,
                                         volatile uint8_t * twcr,
                                         volatile uint8_t * eecr,
                                         volatile uint8_t * spmcsr,
                                         volatile uint8_t * acsr,
                                         volatile uint8_t * adcsra)
: _EIMSK (eimsk ),
  _PCICR (pcicr ),
  _WDTCSR(wdtcsr),
  _TIMSK0(timsk0),
  _TIMSK1(timsk1),
  _TIMSK2(timsk2),
  _TIMSK3(timsk3),
  _TIMSK4(timsk4),
  _TIMSK5(timsk5),
  _UCSR0B(ucsr0b),
  _UCSR1B(ucsr1b),
  _UCSR2B(ucsr2b),
  _UCSR3B(ucsr3b),
  _SPCR  (spcr  ),
  _TWCR  (twcr  ),
  _EECR  (eecr  ),
  _SPMCSR(spmcsr),
  _ACSR  (acsr  ),
  _ADCSRA(adcsra)
{

}

InterruptController::InterruptController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void InterruptController::enableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): util::setBit(_EIMSK , INT0_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): util::setBit(_EIMSK , INT1_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): util::setBit(_EIMSK , INT2_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): util::setBit(_EIMSK , INT3_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): util::setBit(_EIMSK , INT4_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): util::setBit(_EIMSK , INT5_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): util::setBit(_EIMSK , INT6_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): util::setBit(_EIMSK , INT7_bp  ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): util::setBit(_PCICR , PCIE0_bp ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): util::setBit(_PCICR , PCIE1_bp ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): util::setBit(_PCICR , PCIE2_bp ); break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): util::setBit(_WDTCSR, WDIE_bp  ); break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): util::setBit(_TIMSK2, OCIE2A_bp); break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): util::setBit(_TIMSK2, OCIE2B_bp); break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): util::setBit(_TIMSK2, TOIE2_bp ); break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): util::setBit(_TIMSK1, ICIE1_bp ); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): util::setBit(_TIMSK1, OCIE1A_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): util::setBit(_TIMSK1, OCIE1B_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): util::setBit(_TIMSK1, OCIE1C_bp); break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): util::setBit(_TIMSK1, TOIE1_bp ); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): util::setBit(_TIMSK0, OCIE0A_bp); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): util::setBit(_TIMSK0, OCIE0B_bp); break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): util::setBit(_TIMSK0, TOIE0_bp ); break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): util::setBit(_SPCR  , SPIE_bp  ); break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): util::setBit(_UCSR0B, RXCIE0_bp); break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): util::setBit(_UCSR0B, UDRIE0_bp); break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): util::setBit(_UCSR0B, TXCIE0_bp); break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): util::setBit(_ACSR  , ACIE_bp  ); break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): util::setBit(_ADCSRA, ADIE_bp  ); break;
  case toIntNum(Interrupt::EEPROM_READY                   ): util::setBit(_EECR  , EERIE_bp ); break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): util::setBit(_TIMSK3, ICIE3_bp ); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): util::setBit(_TIMSK3, OCIE3A_bp); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): util::setBit(_TIMSK3, OCIE3B_bp); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): util::setBit(_TIMSK3, OCIE3C_bp); break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): util::setBit(_TIMSK3, TOIE3_bp ); break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): util::setBit(_UCSR1B, RXCIE1_bp); break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): util::setBit(_UCSR1B, UDRIE1_bp); break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): util::setBit(_UCSR1B, TXCIE1_bp); break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): util::setBit(_TWCR  , TWIE_bp  ); break;
  case toIntNum(Interrupt::SPM_READY                      ): util::setBit(_SPMCSR, SPMIE_bp ); break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): util::setBit(_TIMSK4, ICIE4_bp ); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): util::setBit(_TIMSK4, OCIE4A_bp); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): util::setBit(_TIMSK4, OCIE4B_bp); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): util::setBit(_TIMSK4, OCIE4C_bp); break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): util::setBit(_TIMSK4, TOIE4_bp ); break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): util::setBit(_TIMSK5, ICIE5_bp ); break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): util::setBit(_TIMSK5, OCIE5A_bp); break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): util::setBit(_TIMSK5, OCIE5B_bp); break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): util::setBit(_TIMSK5, OCIE5C_bp); break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): util::setBit(_TIMSK5, TOIE5_bp ); break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): util::setBit(_UCSR2B, RXCIE2_bp); break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): util::setBit(_UCSR2B, UDRIE2_bp); break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): util::setBit(_UCSR2B, TXCIE2_bp); break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): util::setBit(_UCSR3B, RXCIE3_bp); break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): util::setBit(_UCSR3B, UDRIE3_bp); break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): util::setBit(_UCSR3B, TXCIE3_bp); break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("sei");    break;
#endif
  default                                                  : /* DO NOTHING */        break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): util::clrBit(_EIMSK , INT0_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): util::clrBit(_EIMSK , INT1_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): util::clrBit(_EIMSK , INT2_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): util::clrBit(_EIMSK , INT3_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): util::clrBit(_EIMSK , INT4_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): util::clrBit(_EIMSK , INT5_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): util::clrBit(_EIMSK , INT6_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): util::clrBit(_EIMSK , INT7_bp  ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): util::clrBit(_PCICR , PCIE0_bp ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): util::clrBit(_PCICR , PCIE1_bp ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): util::clrBit(_PCICR , PCIE2_bp ); break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): util::clrBit(_WDTCSR, WDIE_bp  ); break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): util::clrBit(_TIMSK2, OCIE2A_bp); break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): util::clrBit(_TIMSK2, OCIE2B_bp); break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): util::clrBit(_TIMSK2, TOIE2_bp ); break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): util::clrBit(_TIMSK1, ICIE1_bp ); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): util::clrBit(_TIMSK1, OCIE1A_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): util::clrBit(_TIMSK1, OCIE1B_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): util::clrBit(_TIMSK1, OCIE1C_bp); break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): util::clrBit(_TIMSK1, TOIE1_bp ); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): util::clrBit(_TIMSK0, OCIE0A_bp); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): util::clrBit(_TIMSK0, OCIE0B_bp); break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): util::clrBit(_TIMSK0, TOIE0_bp ); break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): util::clrBit(_SPCR  , SPIE_bp  ); break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): util::clrBit(_UCSR0B, RXCIE0_bp); break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): util::clrBit(_UCSR0B, UDRIE0_bp); break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): util::clrBit(_UCSR0B, TXCIE0_bp); break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): util::clrBit(_ACSR  , ACIE_bp  ); break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): util::clrBit(_ADCSRA, ADIE_bp  ); break;
  case toIntNum(Interrupt::EEPROM_READY                   ): util::clrBit(_EECR  , EERIE_bp ); break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): util::clrBit(_TIMSK3, ICIE3_bp ); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): util::clrBit(_TIMSK3, OCIE3A_bp); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): util::clrBit(_TIMSK3, OCIE3B_bp); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): util::clrBit(_TIMSK3, OCIE3C_bp); break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): util::clrBit(_TIMSK3, TOIE3_bp ); break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): util::clrBit(_UCSR1B, RXCIE1_bp); break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): util::clrBit(_UCSR1B, UDRIE1_bp); break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): util::clrBit(_UCSR1B, TXCIE1_bp); break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): util::clrBit(_TWCR  , TWIE_bp  ); break;
  case toIntNum(Interrupt::SPM_READY                      ): util::clrBit(_SPMCSR, SPMIE_bp ); break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): util::clrBit(_TIMSK4, ICIE4_bp ); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): util::clrBit(_TIMSK4, OCIE4A_bp); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): util::clrBit(_TIMSK4, OCIE4B_bp); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): util::clrBit(_TIMSK4, OCIE4C_bp); break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): util::clrBit(_TIMSK4, TOIE4_bp ); break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): util::clrBit(_TIMSK5, ICIE5_bp ); break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): util::clrBit(_TIMSK5, OCIE5A_bp); break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): util::clrBit(_TIMSK5, OCIE5B_bp); break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): util::clrBit(_TIMSK5, OCIE5C_bp); break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): util::clrBit(_TIMSK5, TOIE5_bp ); break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): util::clrBit(_UCSR2B, RXCIE2_bp); break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): util::clrBit(_UCSR2B, UDRIE2_bp); break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): util::clrBit(_UCSR2B, TXCIE2_bp); break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): util::clrBit(_UCSR3B, RXCIE3_bp); break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): util::clrBit(_UCSR3B, UDRIE3_bp); break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): util::clrBit(_UCSR3B, TXCIE3_bp); break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("cli");     break;
#endif
  default                                                  : /* DO NOTHING */         break;
  }
}

void InterruptController::registerInterruptCallback(uint8_t const int_num, interface::InterruptCallback * interrupt_callback)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): isr_external_int0                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): isr_external_int1                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): isr_external_int2                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): isr_external_int3                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): isr_external_int4                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): isr_external_int5                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): isr_external_int6                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): isr_external_int7                   = interrupt_callback; break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): isr_pin_change_int0                 = interrupt_callback; break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): isr_pin_change_int1                 = interrupt_callback; break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): isr_pin_change_int2                 = interrupt_callback; break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): isr_watchdog_timer                  = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): isr_timer2_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): isr_timer2_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): isr_timer2_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): isr_timer1_capture                  = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): isr_timer1_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): isr_timer1_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): isr_timer1_compare_c                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): isr_timer1_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): isr_timer0_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): isr_timer0_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): isr_timer0_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): isr_spi_serial_transfer_complete    = interrupt_callback; break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): isr_usart0_receive_complete         = interrupt_callback; break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): isr_usart0_uart_data_register_empty = interrupt_callback; break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): isr_usart0_transmit_complete        = interrupt_callback; break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): isr_analog_comparator               = interrupt_callback; break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): isr_analog_digital_converter        = interrupt_callback; break;
  case toIntNum(Interrupt::EEPROM_READY                   ): isr_eeprom_ready                    = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): isr_timer3_capture                  = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): isr_timer3_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): isr_timer3_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): isr_timer3_compare_c                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): isr_timer3_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): isr_usart1_receive_complete         = interrupt_callback; break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): isr_usart1_uart_data_register_empty = interrupt_callback; break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): isr_usart1_transmit_complete        = interrupt_callback; break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): isr_two_wire_int                    = interrupt_callback; break;
  case toIntNum(Interrupt::SPM_READY                      ): isr_spm_ready                       = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): isr_timer4_capture                  = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): isr_timer4_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): isr_timer4_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): isr_timer4_compare_c                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): isr_timer4_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): isr_timer5_capture                  = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): isr_timer5_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): isr_timer5_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): isr_timer5_compare_c                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): isr_timer5_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): isr_usart2_receive_complete         = interrupt_callback; break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): isr_usart2_uart_data_register_empty = interrupt_callback; break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): isr_usart2_transmit_complete        = interrupt_callback; break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): isr_usart3_receive_complete         = interrupt_callback; break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): isr_usart3_uart_data_register_empty = interrupt_callback; break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): isr_usart3_transmit_complete        = interrupt_callback; break;
  default                                                  : /* DO NOTHING */                                          break;
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
  executeCallbackIfValid(isr_external_int0);
}

ISR(INT1_vect)
{
  executeCallbackIfValid(isr_external_int1);
}

ISR(INT2_vect)
{
  executeCallbackIfValid(isr_external_int2);
}

ISR(INT3_vect)
{
  executeCallbackIfValid(isr_external_int3);
}

ISR(INT4_vect)
{
  executeCallbackIfValid(isr_external_int4);
}

ISR(INT5_vect)
{
  executeCallbackIfValid(isr_external_int5);
}

ISR(INT6_vect)
{
  executeCallbackIfValid(isr_external_int6);
}

ISR(INT7_vect)
{
  executeCallbackIfValid(isr_external_int7);
}

ISR(PCINT0_vect)
{
  executeCallbackIfValid(isr_pin_change_int0);
}

ISR(PCINT1_vect)
{
  executeCallbackIfValid(isr_pin_change_int1);
}

ISR(PCINT2_vect)
{
  executeCallbackIfValid(isr_pin_change_int2);
}

ISR(WDT_vect)
{
  executeCallbackIfValid(isr_watchdog_timer);
}

ISR(TIMER2_COMPA_vect)
{
  executeCallbackIfValid(isr_timer2_compare_a);
}

ISR(TIMER2_COMPB_vect)
{
  executeCallbackIfValid(isr_timer2_compare_b);
}

ISR(TIMER2_OVF_vect)
{
  executeCallbackIfValid(isr_timer2_overflow);
}

ISR(TIMER1_CAPT_vect)
{
  executeCallbackIfValid(isr_timer1_capture);
}

ISR(TIMER1_COMPA_vect)
{
  executeCallbackIfValid(isr_timer1_compare_a);
}

ISR(TIMER1_COMPB_vect)
{
  executeCallbackIfValid(isr_timer1_compare_b);
}

ISR(TIMER1_COMPC_vect)
{
  executeCallbackIfValid(isr_timer1_compare_c);
}

ISR(TIMER1_OVF_vect)
{
  executeCallbackIfValid(isr_timer1_overflow);
}

ISR(TIMER0_COMPA_vect)
{
  executeCallbackIfValid(isr_timer0_compare_a);
}

ISR(TIMER0_COMPB_vect)
{
  executeCallbackIfValid(isr_timer0_compare_b);
}

ISR(TIMER0_OVF_vect)
{
  executeCallbackIfValid(isr_timer0_overflow);
}

ISR(SPI_STC_vect)
{
  executeCallbackIfValid(isr_spi_serial_transfer_complete);
}

ISR(USART0_RX_vect)
{
  executeCallbackIfValid(isr_usart0_receive_complete);
}

ISR(USART0_UDRE_vect)
{
  executeCallbackIfValid(isr_usart0_uart_data_register_empty);
}

ISR(USART0_TX_vect)
{
  executeCallbackIfValid(isr_usart0_transmit_complete);
}

ISR(ANALOG_COMP_vect)
{
  executeCallbackIfValid(isr_analog_comparator);
}

ISR(ADC_vect)
{
  executeCallbackIfValid(isr_analog_digital_converter);
}

ISR(EE_READY_vect)
{
  executeCallbackIfValid(isr_eeprom_ready);
}

ISR(TIMER3_CAPT_vect)
{
  executeCallbackIfValid(isr_timer3_capture);
}

ISR(TIMER3_COMPA_vect)
{
  executeCallbackIfValid(isr_timer3_compare_a);
}

ISR(TIMER3_COMPB_vect)
{
  executeCallbackIfValid(isr_timer3_compare_b);
}

ISR(TIMER3_COMPC_vect)
{
  executeCallbackIfValid(isr_timer3_compare_c);
}

ISR(TIMER3_OVF_vect)
{
  executeCallbackIfValid(isr_timer3_overflow);
}

ISR(USART1_RX_vect)
{
  executeCallbackIfValid(isr_usart1_receive_complete);
}

ISR(USART1_UDRE_vect)
{
  executeCallbackIfValid(isr_usart1_uart_data_register_empty);
}

ISR(USART1_TX_vect)
{
  executeCallbackIfValid(isr_usart1_transmit_complete);
}

ISR(TWI_vect)
{
  executeCallbackIfValid(isr_two_wire_int);
}

ISR(SPM_READY_vect)
{
  executeCallbackIfValid(isr_spm_ready);
}

ISR(TIMER4_CAPT_vect)
{
  executeCallbackIfValid(isr_timer4_capture);
}

ISR(TIMER4_COMPA_vect)
{
  executeCallbackIfValid(isr_timer4_compare_a);
}

ISR(TIMER4_COMPB_vect)
{
  executeCallbackIfValid(isr_timer4_compare_b);
}

ISR(TIMER4_COMPC_vect)
{
  executeCallbackIfValid(isr_timer4_compare_c);
}

ISR(TIMER4_OVF_vect)
{
  executeCallbackIfValid(isr_timer4_overflow);
}

ISR(TIMER5_CAPT_vect)
{
  executeCallbackIfValid(isr_timer5_capture);
}

ISR(TIMER5_COMPA_vect)
{
  executeCallbackIfValid(isr_timer5_compare_a);
}

ISR(TIMER5_COMPB_vect)
{
  executeCallbackIfValid(isr_timer5_compare_b);
}

ISR(TIMER5_COMPC_vect)
{
  executeCallbackIfValid(isr_timer5_compare_c);
}

ISR(TIMER5_OVF_vect)
{
  executeCallbackIfValid(isr_timer5_overflow);
}

ISR(USART2_RX_vect)
{
  executeCallbackIfValid(isr_usart2_receive_complete);
}

ISR(USART2_UDRE_vect)
{
  executeCallbackIfValid(isr_usart2_uart_data_register_empty);
}

ISR(USART2_TX_vect)
{
  executeCallbackIfValid(isr_usart2_transmit_complete);
}

ISR(USART3_RX_vect)
{
  executeCallbackIfValid(isr_usart3_receive_complete);
}

ISR(USART3_UDRE_vect)
{
  executeCallbackIfValid(isr_usart3_uart_data_register_empty);
}

ISR(USART3_TX_vect)
{
  executeCallbackIfValid(isr_usart3_transmit_complete);
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640) ) */
