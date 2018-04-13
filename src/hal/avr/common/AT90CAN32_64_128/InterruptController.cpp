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
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/InterruptController.h>

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

namespace AT90CAN32_64_128
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

/* TIMSK2 */
#define OCIE2A_bm (1<<1)
#define TOIE2_bm  (1<<0)

/* TIMSK1 */
#define ICIE1_bm  (1<<5)
#define OCIE1C_bm (1<<3)
#define OCIE1B_bm (1<<2)
#define OCIE1A_bm (1<<1)
#define TOIE1_bm  (1<<0)

/* TIMSK0 */
#define OCIE0A_bm (1<<1)
#define TOIE0_bm  (1<<0)

/* CANGIE */
#define ENIT_bm   (1<<7)
#define ENBOFF_bm (1<<6)
#define ENRX_bm   (1<<5)
#define ENTX_bm   (1<<4)
#define ENERR_bm  (1<<3)
#define ENBX_bm   (1<<2)
#define ENERG_bm  (1<<1)
#define ENOVRT_bm (1<<0)

/* CANGIT */
#define CANIT_bm  (1<<7)
#define BOFFIT_bm (1<<6)
#define OVRTIM_bm (1<<5)
#define BXOK_bm   (1<<4)
#define SERG_bm   (1<<3)
#define CERG_bm   (1<<2)
#define FERG_bm   (1<<1)
#define AERG_bm   (1<<0)

/* CANSTMOB */
#define DLCW_bm   (1<<7)
#define TXOK_bm   (1<<6)
#define RXOK_bm   (1<<5)
#define BERR_bm   (1<<4)
#define SERR_bm   (1<<3)
#define CERR_bm   (1<<2)
#define FERR_bm   (1<<1)
#define AERR_bm   (1<<0)

/* SPCR */
#define SPIE_bm   (1<<7)

/* UCSR0B */
#define UDRIE0_bm (1<<5)
#define TXCIE0_bm (1<<6)
#define RXCIE0_bm (1<<7)

/* ACSR */
#define ACIE_bm   (1<<3)

/* ADCSRA */
#define ADIE_bm   (1<<3)

/* EECR */
#define EERIE_bm  (1<<3)

/* TIMSK3 */
#define ICIE3_bm  (1<<5)
#define OCIE3C_bm (1<<3)
#define OCIE3B_bm (1<<2)
#define OCIE3A_bm (1<<1)
#define TOIE3_bm  (1<<0)

/* UCSR1B */
#define UDRIE1_bm (1<<5)
#define TXCIE1_bm (1<<6)
#define RXCIE1_bm (1<<7)

/* TWCR */
#define TWIE_bm   (1<<0)

/* SPMCSR */
#define SPMIE_bm  (1<<7)

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
                                    * isr_timer2_compare                  = 0,
                                    * isr_timer2_overflow                 = 0,
                                    * isr_timer1_capture                  = 0,
                                    * isr_timer1_compare_a                = 0,
                                    * isr_timer1_compare_b                = 0,
                                    * isr_timer1_compare_c                = 0,
                                    * isr_timer1_overflow                 = 0,
                                    * isr_timer0_compare                  = 0,
                                    * isr_timer0_overflow                 = 0,
                                    * isr_can_all                         = 0,
                                    * isr_can_timer_overrun               = 0,
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
                                    * isr_spm_ready                       = 0;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
                                         volatile uint8_t * timsk2,
                                         volatile uint8_t * timsk1,
                                         volatile uint8_t * timsk0,
                                         volatile uint8_t * cangie,
                                         volatile uint8_t * spcr,
                                         volatile uint8_t * ucsr0b,
                                         volatile uint8_t * acsr,
                                         volatile uint8_t * adcsra,
                                         volatile uint8_t * eecr,
                                         volatile uint8_t * timsk3,
                                         volatile uint8_t * ucsr1b,
                                         volatile uint8_t * twcr,
                                         volatile uint8_t * spmcsr)
: _EIMSK (eimsk ),
  _TIMSK2(timsk2),
  _TIMSK1(timsk1),
  _TIMSK0(timsk0),
  _CANGIE(cangie),
  _SPCR  (spcr  ),
  _UCSR0B(ucsr0b),
  _ACSR  (acsr  ),
  _ADCSRA(adcsra),
  _EECR  (eecr  ),
  _TIMSK3(timsk3),
  _UCSR1B(ucsr1b),
  _TWCR  (twcr  ),
  _SPMCSR(spmcsr)
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
  case toIntNum(Interrupt::EXTERNAL_INT0                   ): *_EIMSK   |= INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                   ): *_EIMSK   |= INT1_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT2                   ): *_EIMSK   |= INT2_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT3                   ): *_EIMSK   |= INT3_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT4                   ): *_EIMSK   |= INT4_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT5                   ): *_EIMSK   |= INT5_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT6                   ): *_EIMSK   |= INT6_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT7                   ): *_EIMSK   |= INT7_bm;   break;
  case toIntNum(Interrupt::TIMER2_COMPARE                  ): *_TIMSK2  |= OCIE2A_bm; break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                 ): *_TIMSK2  |= TOIE2_bm;  break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                  ): *_TIMSK1  |= ICIE1_bm;  break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A                ): *_TIMSK1  |= OCIE1C_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B                ): *_TIMSK1  |= OCIE1B_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C                ): *_TIMSK1  |= OCIE1A_bm; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                 ): *_TIMSK1  |= TOIE1_bm;  break;
  case toIntNum(Interrupt::TIMER0_COMPARE                  ): *_TIMSK0  |= OCIE0A_bm; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                 ): *_TIMSK0  |= TOIE0_bm;  break;
  case toIntNum(Interrupt::CAN_ALL                         ): *_CANGIE  |= ENIT_bm;   break;
  case toIntNum(Interrupt::CAN_BUS_OFF                     ): *_CANGIE  |= ENBOFF_bm; break;
  case toIntNum(Interrupt::CAN_RECEIVE                     ): *_CANGIE  |= ENRX_bm;   break;
  case toIntNum(Interrupt::CAN_TRANSMIT                    ): *_CANGIE  |= ENTX_bm;   break;
  case toIntNum(Interrupt::CAN_FRAME_BUFFER                ): *_CANGIE  |= ENBX_bm;   break;
  case toIntNum(Interrupt::CAN_GENERAL_ERROR               ): *_CANGIE  |= ENERG_bm;  break;
  case toIntNum(Interrupt::CAN_TIMER_OVERRUN               ): *_CANGIE  |= ENOVRT_bm; break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE    ): *_SPCR    |= SPIE_bm;   break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE         ): *_UCSR0B  |= RXCIE0_bm; break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY ): *_UCSR0B  |= UDRIE0_bm; break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE        ): *_UCSR0B  |= TXCIE0_bm; break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR               ): *_ACSR    |= ACIE_bm;   break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER        ): *_ADCSRA  |= ADIE_bm;   break;
  case toIntNum(Interrupt::EEPROM_READY                    ): *_EECR    |= EERIE_bm;  break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                  ): *_TIMSK3  |= ICIE3_bm;  break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A                ): *_TIMSK3  |= OCIE3C_bm; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B                ): *_TIMSK3  |= OCIE3B_bm; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C                ): *_TIMSK3  |= OCIE3A_bm; break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                 ): *_TIMSK3  |= TOIE3_bm;  break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE         ): *_UCSR1B  |= RXCIE1_bm; break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY ): *_UCSR1B  |= UDRIE1_bm; break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE        ): *_UCSR1B  |= TXCIE1_bm; break;
  case toIntNum(Interrupt::TWO_WIRE_INT                    ): *_TWCR    |= TWIE_bm;   break;
  case toIntNum(Interrupt::SPM_READY                       ): *_SPMCSR  |= SPMIE_bm;  break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                          ): asm volatile("sei");    break;
#endif
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                   ): *_EIMSK   &= ~INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                   ): *_EIMSK   &= ~INT1_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT2                   ): *_EIMSK   &= ~INT2_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT3                   ): *_EIMSK   &= ~INT3_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT4                   ): *_EIMSK   &= ~INT4_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT5                   ): *_EIMSK   &= ~INT5_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT6                   ): *_EIMSK   &= ~INT6_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT7                   ): *_EIMSK   &= ~INT7_bm;   break;
  case toIntNum(Interrupt::TIMER2_COMPARE                  ): *_TIMSK2  &= ~OCIE2A_bm; break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                 ): *_TIMSK2  &= ~TOIE2_bm;  break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                  ): *_TIMSK1  &= ~ICIE1_bm;  break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A                ): *_TIMSK1  &= ~OCIE1C_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B                ): *_TIMSK1  &= ~OCIE1B_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C                ): *_TIMSK1  &= ~OCIE1A_bm; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                 ): *_TIMSK1  &= ~TOIE1_bm;  break;
  case toIntNum(Interrupt::TIMER0_COMPARE                  ): *_TIMSK0  &= ~OCIE0A_bm; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                 ): *_TIMSK0  &= ~TOIE0_bm;  break;
  case toIntNum(Interrupt::CAN_ALL                         ): *_CANGIE  &= ~ENIT_bm;   break;
  case toIntNum(Interrupt::CAN_BUS_OFF                     ): *_CANGIE  &= ~ENBOFF_bm; break;
  case toIntNum(Interrupt::CAN_RECEIVE                     ): *_CANGIE  &= ~ENRX_bm;   break;
  case toIntNum(Interrupt::CAN_TRANSMIT                    ): *_CANGIE  &= ~ENTX_bm;   break;
  case toIntNum(Interrupt::CAN_FRAME_BUFFER                ): *_CANGIE  &= ~ENBX_bm;   break;
  case toIntNum(Interrupt::CAN_GENERAL_ERROR               ): *_CANGIE  &= ~ENERG_bm;  break;
  case toIntNum(Interrupt::CAN_TIMER_OVERRUN               ): *_CANGIE  &= ~ENOVRT_bm; break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE    ): *_SPCR    &= ~SPIE_bm;   break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE         ): *_UCSR0B  &= ~RXCIE0_bm; break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY ): *_UCSR0B  &= ~UDRIE0_bm; break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE        ): *_UCSR0B  &= ~TXCIE0_bm; break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR               ): *_ACSR    &= ~ACIE_bm;   break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER        ): *_ADCSRA  &= ~ADIE_bm;   break;
  case toIntNum(Interrupt::EEPROM_READY                    ): *_EECR    &= ~EERIE_bm;  break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                  ): *_TIMSK3  &= ~ICIE3_bm;  break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A                ): *_TIMSK3  &= ~OCIE3C_bm; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B                ): *_TIMSK3  &= ~OCIE3B_bm; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C                ): *_TIMSK3  &= ~OCIE3A_bm; break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                 ): *_TIMSK3  &= ~TOIE3_bm;  break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE         ): *_UCSR1B  &= ~RXCIE1_bm; break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY ): *_UCSR1B  &= ~UDRIE1_bm; break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE        ): *_UCSR1B  &= ~TXCIE1_bm; break;
  case toIntNum(Interrupt::TWO_WIRE_INT                    ): *_TWCR    &= ~TWIE_bm;   break;
  case toIntNum(Interrupt::SPM_READY                       ): *_SPMCSR  &= ~SPMIE_bm;  break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                          ): asm volatile("cli");     break;
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
  case toIsrNum(InterruptServiceRoutine::TIMER2_COMPARE                 ): isr_timer2_compare                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_OVERFLOW                ): isr_timer2_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_CAPTURE                 ): isr_timer1_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_A               ): isr_timer1_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_B               ): isr_timer1_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_C               ): isr_timer1_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_OVERFLOW                ): isr_timer1_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE                 ): isr_timer0_compare                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_OVERFLOW                ): isr_timer0_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::CAN_ALL                        ): isr_can_all                         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::CAN_TIMER_OVERRUN              ): isr_can_timer_overrun               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPI_SERIAL_TRANSFER_COMPLETE   ): isr_spi_serial_transfer_complete    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_RECEIVE_COMPLETE        ): isr_usart0_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_UART_DATA_REGISTER_EMPTY): isr_usart0_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_TRANSMIT_COMPLETE       ): isr_usart0_transmit_complete        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_COMPARATOR              ): isr_analog_comparator               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_DIGITAL_CONVERTER       ): isr_analog_digital_converter        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EEPROM_READY                   ): isr_eeprom_ready                    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_CAPTURE                 ): isr_timer3_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_A               ): isr_timer3_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_B               ): isr_timer3_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_C               ): isr_timer3_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_OVERFLOW                ): isr_timer3_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_RECEIVE_COMPLETE        ): isr_usart1_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_UART_DATA_REGISTER_EMPTY): isr_usart1_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_TRANSMIT_COMPLETE       ): isr_usart1_transmit_complete        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TWO_WIRE_INT                   ): isr_two_wire_int                    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPM_READY                      ): isr_spm_ready                       = interrupt_callback; break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_at90can32) || defined(MCU_TYPE_at90can64) || defined(MCU_TYPE_at90can128) )

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::AT90CAN32_64_128;

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

ISR(TIMER2_COMP_vect)
{
  if(isr_timer2_compare) isr_timer2_compare->interruptServiceRoutine();
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

ISR(TIMER0_COMP_vect)
{
  if(isr_timer0_compare) isr_timer0_compare->interruptServiceRoutine();
}

ISR(TIMER0_OVF_vect)
{
  if(isr_timer0_overflow) isr_timer0_overflow->interruptServiceRoutine();
}

ISR(CANIT_vect)
{
  if(isr_can_all) isr_can_all->interruptServiceRoutine();
}

ISR(OVRIT_vect)
{
  if(isr_can_timer_overrun) isr_can_timer_overrun->interruptServiceRoutine();
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
  if(isr_analog_comparator) isr_analog_comparator->interruptServiceRoutine();
}

ISR(ADC_vect)
{
  if(isr_analog_digital_converter) isr_analog_digital_converter->interruptServiceRoutine();
}

ISR(EE_READY_vect)
{
  if(isr_eeprom_ready) isr_eeprom_ready->interruptServiceRoutine();
}

ISR(TIMER3_CAPT_vect)
{
  if(isr_timer3_capture) isr_timer3_capture->interruptServiceRoutine();
}

ISR(TIMER3_COMPA_vect)
{
  if(isr_timer3_compare_a) isr_timer3_compare_a->interruptServiceRoutine();
}

ISR(TIMER3_COMPB_vect)
{
  if(isr_timer3_compare_b) isr_timer3_compare_b->interruptServiceRoutine();
}

ISR(TIMER3_COMPC_vect)
{
  if(isr_timer3_compare_c) isr_timer3_compare_c->interruptServiceRoutine();
}

ISR(TIMER3_OVF_vect)
{
  if(isr_timer3_overflow) isr_timer3_overflow->interruptServiceRoutine();
}

ISR(USART1_RX_vect)
{
  if(isr_usart1_receive_complete) isr_usart1_receive_complete->interruptServiceRoutine();
}

ISR(USART1_UDRE_vect)
{
  if(isr_usart1_uart_data_register_empty) isr_usart1_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART1_TX_vect)
{
  if(isr_usart1_transmit_complete) isr_usart1_transmit_complete->interruptServiceRoutine();
}

ISR(TWI_vect)
{
  if(isr_two_wire_int) isr_two_wire_int->interruptServiceRoutine();
}

ISR(SPM_READY_vect)
{
  if(isr_spm_ready) isr_spm_ready->interruptServiceRoutine();
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_at90can32) || defined(MCU_TYPE_at90can64) || defined(MCU_TYPE_at90can128) ) */
