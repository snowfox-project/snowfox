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

#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

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

namespace ATMEGA328P
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT0_bm   (1<<0)
#define INT1_bm   (1<<1)

/* PCICR */
#define PCIE0_bm  (1<<0)
#define PCIE1_bm  (1<<1)
#define PCIE2_bm  (1<<2)

/* WDTCSR */
#define WDIE_bm   (1<<6)

/* TIMSK2 */
#define TOIE2_bm  (1<<0)
#define OCIE2A_bm (1<<1)
#define OCIE2B_bm (1<<2)

/* TIMSK1 */
#define TOIE1_bm  (1<<0)
#define OCIE1A_bm (1<<1)
#define OCIE1B_bm (1<<2)
#define ICIE1_bm  (1<<5)

/* TIMSK0 */
#define TOIE0_bm  (1<<0)
#define OCIE0A_bm (1<<1)
#define OCIE0B_bm (1<<2)

/* SPCR */
#define SPIE_bm   (1<<7)

/* UCSR0B */
#define UDRIE0_bm (1<<5)
#define TXCIE0_bm (1<<6)
#define RXCIE0_bm (1<<7)

/* ADCSRA */
#define ADIE_bm   (1<<3)

/* EECR */
#define EERIE_bm  (1<<3)

/* ACSR */
#define ACIE_bm   (1<<3)

/* TWCR */
#define TWIE_bm   (1<<0)

/* SPMCSR */
#define SPMIE_bm  (1<<7)

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t constexpr NUMBER_OF_INTERRUPT_SERVICE_ROUTINES = 25;

static uint8_t constexpr EXTERNAL_INT0                  =  0;
static uint8_t constexpr EXTERNAL_INT1                  =  1;
static uint8_t constexpr PIN_CHANGE_INT0                =  2;
static uint8_t constexpr PIN_CHANGE_INT1                =  3;
static uint8_t constexpr PIN_CHANGE_INT2                =  4;
static uint8_t constexpr WATCHDOG_TIMER                 =  5;
static uint8_t constexpr TIMER2_COMPARE_A               =  6;
static uint8_t constexpr TIMER2_COMPARE_B               =  7;
static uint8_t constexpr TIMER2_OVERFLOW                =  8;
static uint8_t constexpr TIMER1_CAPTURE                 =  9;
static uint8_t constexpr TIMER1_COMPARE_A               = 10;
static uint8_t constexpr TIMER1_COMPARE_B               = 11;
static uint8_t constexpr TIMER1_OVERFLOW                = 12;
static uint8_t constexpr TIMER0_COMPARE_A               = 13;
static uint8_t constexpr TIMER0_COMPARE_B               = 14;
static uint8_t constexpr TIMER0_OVERFLOW                = 15;
static uint8_t constexpr SPI_SERIAL_TRANSFER_COMPLETE   = 16;
static uint8_t constexpr USART_RECEIVE_COMPLETE         = 17;
static uint8_t constexpr USART_UART_DATA_REGISTER_EMPTY = 18;
static uint8_t constexpr USART_TRANSMIT_COMPLETE        = 19;
static uint8_t constexpr ANALOG_DIGITAL_CONVERTER       = 20;
static uint8_t constexpr EEPROM_READY                   = 21;
static uint8_t constexpr ANALOG_COMPARATOR              = 22;
static uint8_t constexpr TWO_WIRE_INT                   = 23;
static uint8_t constexpr SPM_READY                      = 24;
static uint8_t constexpr GLOBAL                         = 25;
static uint8_t constexpr INVALID                        = 255;

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef struct
{
  interface::ISRFunc isr_func;
  interface::ISRArg  isr_arg;
} InterruptCallbackArrayEntry;

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

static InterruptController * _this = 0;
static InterruptCallbackArrayEntry _interrupt_callback_array[NUMBER_OF_INTERRUPT_SERVICE_ROUTINES];

/**************************************************************************************
 * GLOBAL FUNCTIONS
 **************************************************************************************/

uint8_t toIntNum(Interrupt const interrupt)
{
  switch(interrupt)
  {
  case Interrupt::EXTERNAL_INT0                  : return EXTERNAL_INT0;                  break;
  case Interrupt::EXTERNAL_INT1                  : return EXTERNAL_INT1;                  break;
  case Interrupt::PIN_CHANGE_INT0                : return PIN_CHANGE_INT0;                break;
  case Interrupt::PIN_CHANGE_INT1                : return PIN_CHANGE_INT1;                break;
  case Interrupt::PIN_CHANGE_INT2                : return PIN_CHANGE_INT2;                break;
  case Interrupt::WATCHDOG_TIMER                 : return WATCHDOG_TIMER;                 break;
  case Interrupt::TIMER2_COMPARE_A               : return TIMER2_COMPARE_A;               break;
  case Interrupt::TIMER2_COMPARE_B               : return TIMER2_COMPARE_B;               break;
  case Interrupt::TIMER2_OVERFLOW                : return TIMER2_OVERFLOW;                break;
  case Interrupt::TIMER1_CAPTURE                 : return TIMER1_CAPTURE;                 break;
  case Interrupt::TIMER1_COMPARE_A               : return TIMER1_COMPARE_A;               break;
  case Interrupt::TIMER1_COMPARE_B               : return TIMER1_COMPARE_B;               break;
  case Interrupt::TIMER1_OVERFLOW                : return TIMER1_OVERFLOW;                break;
  case Interrupt::TIMER0_COMPARE_A               : return TIMER0_COMPARE_A;               break;
  case Interrupt::TIMER0_COMPARE_B               : return TIMER0_COMPARE_B;               break;
  case Interrupt::TIMER0_OVERFLOW                : return TIMER0_OVERFLOW;                break;
  case Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   : return SPI_SERIAL_TRANSFER_COMPLETE;   break;
  case Interrupt::USART_RECEIVE_COMPLETE         : return USART_RECEIVE_COMPLETE;         break;
  case Interrupt::USART_UART_DATA_REGISTER_EMPTY : return USART_UART_DATA_REGISTER_EMPTY; break;
  case Interrupt::USART_TRANSMIT_COMPLETE        : return USART_TRANSMIT_COMPLETE;        break;
  case Interrupt::ANALOG_DIGITAL_CONVERTER       : return ANALOG_DIGITAL_CONVERTER;       break;
  case Interrupt::EEPROM_READY                   : return EEPROM_READY;                   break;
  case Interrupt::ANALOG_COMPARATOR              : return ANALOG_COMPARATOR;              break;
  case Interrupt::TWO_WIRE_INT                   : return TWO_WIRE_INT;                   break;
  case Interrupt::SPM_READY                      : return SPM_READY;                      break;
  case Interrupt::GLOBAL                         : return GLOBAL;                         break;
  default                                        : return INVALID;                        break;
  }
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
                                         volatile uint8_t * pcicr,
                                         volatile uint8_t * wdtcsr,
                                         volatile uint8_t * timsk2,
                                         volatile uint8_t * timsk1,
                                         volatile uint8_t * timsk0,
                                         volatile uint8_t * spcr,
                                         volatile uint8_t * ucsr0b,
                                         volatile uint8_t * adcsra,
                                         volatile uint8_t * eecr,
                                         volatile uint8_t * acsr,
                                         volatile uint8_t * twcr,
                                         volatile uint8_t * spmcsr)
: _EIMSK  (eimsk ),
  _PCICR  (pcicr ),
  _WDTCSR (wdtcsr),
  _TIMSK2 (timsk2),
  _TIMSK1 (timsk1),
  _TIMSK0 (timsk0),
  _SPCR   (spcr  ),
  _UCSR0B (ucsr0b),
  _ADCSRA (adcsra),
  _EECR   (eecr  ),
  _ACSR   (acsr  ),
  _TWCR   (twcr  ),
  _SPMCSR (spmcsr)
{
  _this = this;

  for(uint8_t i = 0; i < NUMBER_OF_INTERRUPT_SERVICE_ROUTINES; i++)
  {
    _interrupt_callback_array[i].isr_func = 0;
    _interrupt_callback_array[i].isr_arg  = 0;
  }
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
  case EXTERNAL_INT0                  : *_EIMSK   |= INT0_bm;   break;
  case EXTERNAL_INT1                  : *_EIMSK   |= INT1_bm;   break;
  case PIN_CHANGE_INT0                : *_PCICR   |= PCIE0_bm;  break;
  case PIN_CHANGE_INT1                : *_PCICR   |= PCIE1_bm;  break;
  case PIN_CHANGE_INT2                : *_PCICR   |= PCIE2_bm;  break;
  case WATCHDOG_TIMER                 : *_WDTCSR  |= WDIE_bm;   break;
  case TIMER2_COMPARE_A               : *_TIMSK2  |= OCIE2A_bm; break;
  case TIMER2_COMPARE_B               : *_TIMSK2  |= OCIE2B_bm; break;
  case TIMER2_OVERFLOW                : *_TIMSK2  |= TOIE2_bm;  break;
  case TIMER1_CAPTURE                 : *_TIMSK1  |= ICIE1_bm;  break;
  case TIMER1_COMPARE_A               : *_TIMSK1  |= OCIE1A_bm; break;
  case TIMER1_COMPARE_B               : *_TIMSK1  |= OCIE1B_bm; break;
  case TIMER1_OVERFLOW                : *_TIMSK1  |= TOIE1_bm;  break;
  case TIMER0_COMPARE_A               : *_TIMSK0  |= OCIE0A_bm; break;
  case TIMER0_COMPARE_B               : *_TIMSK0  |= OCIE0B_bm; break;
  case TIMER0_OVERFLOW                : *_TIMSK0  |= TOIE0_bm;  break;
  case SPI_SERIAL_TRANSFER_COMPLETE   : *_SPCR    |= SPIE_bm;   break;
  case USART_RECEIVE_COMPLETE         : *_UCSR0B  |= RXCIE0_bm; break;
  case USART_UART_DATA_REGISTER_EMPTY : *_UCSR0B  |= UDRIE0_bm; break;
  case USART_TRANSMIT_COMPLETE        : *_UCSR0B  |= TXCIE0_bm; break;
  case ANALOG_DIGITAL_CONVERTER       : *_ADCSRA  |= ADIE_bm;   break;
  case EEPROM_READY                   : *_EECR    |= EERIE_bm;  break;
  case ANALOG_COMPARATOR              : *_ACSR    |= ACIE_bm;   break;
  case TWO_WIRE_INT                   : *_TWCR    |= TWIE_bm;   break;
  case SPM_READY                      : *_SPMCSR  |= SPMIE_bm;  break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case GLOBAL                         : asm volatile("sei");    break;
#endif
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case EXTERNAL_INT0                  : *_EIMSK   &= ~INT0_bm;   break;
  case EXTERNAL_INT1                  : *_EIMSK   &= ~INT1_bm;   break;
  case PIN_CHANGE_INT0                : *_PCICR   &= ~PCIE0_bm;  break;
  case PIN_CHANGE_INT1                : *_PCICR   &= ~PCIE1_bm;  break;
  case PIN_CHANGE_INT2                : *_PCICR   &= ~PCIE2_bm;  break;
  case WATCHDOG_TIMER                 : *_WDTCSR  &= ~WDIE_bm;   break;
  case TIMER2_COMPARE_A               : *_TIMSK2  &= ~OCIE2A_bm; break;
  case TIMER2_COMPARE_B               : *_TIMSK2  &= ~OCIE2B_bm; break;
  case TIMER2_OVERFLOW                : *_TIMSK2  &= ~TOIE2_bm;  break;
  case TIMER1_CAPTURE                 : *_TIMSK1  &= ~ICIE1_bm;  break;
  case TIMER1_COMPARE_A               : *_TIMSK1  &= ~OCIE1A_bm; break;
  case TIMER1_COMPARE_B               : *_TIMSK1  &= ~OCIE1B_bm; break;
  case TIMER1_OVERFLOW                : *_TIMSK1  &= ~TOIE1_bm;  break;
  case TIMER0_COMPARE_A               : *_TIMSK0  &= ~OCIE0A_bm; break;
  case TIMER0_COMPARE_B               : *_TIMSK0  &= ~OCIE0B_bm; break;
  case TIMER0_OVERFLOW                : *_TIMSK0  &= ~TOIE0_bm;  break;
  case SPI_SERIAL_TRANSFER_COMPLETE   : *_SPCR    &= ~SPIE_bm;   break;
  case USART_RECEIVE_COMPLETE         : *_UCSR0B  &= ~RXCIE0_bm; break;
  case USART_UART_DATA_REGISTER_EMPTY : *_UCSR0B  &= ~UDRIE0_bm; break;
  case USART_TRANSMIT_COMPLETE        : *_UCSR0B  &= ~TXCIE0_bm; break;
  case ANALOG_DIGITAL_CONVERTER       : *_ADCSRA  &= ~ADIE_bm;   break;
  case EEPROM_READY                   : *_EECR    &= ~EERIE_bm;  break;
  case ANALOG_COMPARATOR              : *_ACSR    &= ~ACIE_bm;   break;
  case TWO_WIRE_INT                   : *_TWCR    &= ~TWIE_bm;   break;
  case SPM_READY                      : *_SPMCSR  &= ~SPMIE_bm;  break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case GLOBAL                         : asm volatile("cli");     break;
#endif
  }
}

void InterruptController::registerISR(uint8_t const int_num, interface::ISRFunc isr_func, interface::ISRArg isr_arg)
{
  assert(int_num < NUMBER_OF_INTERRUPT_SERVICE_ROUTINES);

  _interrupt_callback_array[int_num].isr_func = isr_func;
  _interrupt_callback_array[int_num].isr_arg  = isr_arg;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

/**************************************************************************************/

#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::interface;
using namespace spectre::hal::ATMEGA328P;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(INT0_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EXTERNAL_INT0].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EXTERNAL_INT0].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(INT1_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EXTERNAL_INT1].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EXTERNAL_INT1].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(PCINT0_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[PIN_CHANGE_INT0].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[PIN_CHANGE_INT0].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(PCINT1_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[PIN_CHANGE_INT1].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[PIN_CHANGE_INT1].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(PCINT2_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[PIN_CHANGE_INT2].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[PIN_CHANGE_INT2].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(WDT_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[WATCHDOG_TIMER].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[WATCHDOG_TIMER].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER2_COMPA_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER2_COMPARE_A].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER2_COMPARE_A].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER2_COMPB_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER2_COMPARE_B].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER2_COMPARE_B].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER2_OVF_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER2_OVERFLOW].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER2_OVERFLOW].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/
ISR(TIMER1_CAPT_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_CAPTURE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_CAPTURE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER1_COMPA_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_COMPARE_A].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_COMPARE_A].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER1_COMPB_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_COMPARE_B].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_COMPARE_B].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER1_OVF_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_OVERFLOW].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_OVERFLOW].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER0_COMPA_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER0_COMPARE_A].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER0_COMPARE_A].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER0_COMPB_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER0_COMPARE_B].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER0_COMPARE_B].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER0_OVF_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER0_OVERFLOW].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER0_OVERFLOW].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(SPI_STC_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[SPI_SERIAL_TRANSFER_COMPLETE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[SPI_SERIAL_TRANSFER_COMPLETE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(USART_RX_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART_RECEIVE_COMPLETE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART_RECEIVE_COMPLETE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(USART_UDRE_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART_UART_DATA_REGISTER_EMPTY].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART_UART_DATA_REGISTER_EMPTY].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(USART_TX_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART_TRANSMIT_COMPLETE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART_TRANSMIT_COMPLETE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(ADC_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[ANALOG_DIGITAL_CONVERTER].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[ANALOG_DIGITAL_CONVERTER].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(EE_READY_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EEPROM_READY].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EEPROM_READY].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(ANALOG_COMP_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[ANALOG_COMPARATOR].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[ANALOG_COMPARATOR].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TWI_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TWO_WIRE_INT].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TWO_WIRE_INT].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(SPM_READY_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[SPM_READY].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[SPM_READY].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

#endif /* defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p) */

/**************************************************************************************/
