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
#define INT0_bm (1<<0)
#define INT1_bm (1<<1)

/* PCICR */
#define PCIE0_bm (1<<0)
#define PCIE1_bm (1<<1)
#define PCIE2_bm (1<<2)

/* WDTCSR */
#define WDIE_bm  (1<<6)

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
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * EIMSK,
                                         volatile uint8_t * PCICR,
                                         volatile uint8_t * WDTCSR,
                                         volatile uint8_t * TIMSK2,
                                         volatile uint8_t * TIMSK1,
                                         volatile uint8_t * TIMSK0,
                                         volatile uint8_t * SPCR,
                                         volatile uint8_t * UCSR0B,
                                         volatile uint8_t * ADCSRA,
                                         volatile uint8_t * EECR,
                                         volatile uint8_t * ACSR,
                                         volatile uint8_t * TWCR,
                                         volatile uint8_t * SPMCSR)
: _EIMSK  (EIMSK ),
  _PCICR  (PCICR ),
  _WDTCSR (WDTCSR),
  _TIMSK2 (TIMSK2),
  _TIMSK1 (TIMSK1),
  _TIMSK0 (TIMSK0),
  _SPCR   (SPCR  ),
  _UCSR0B (UCSR0B),
  _ADCSRA (ADCSRA),
  _EECR   (EECR  ),
  _ACSR   (ACSR  ),
  _TWCR   (TWCR  ),
  _SPMCSR (SPMCSR)
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
  case USART_RECEIVE_COMPLETE         : *_UCSR0B  |= UDRIE0_bm; break;
  case USART_UART_DATA_REGISTER_EMPTY : *_UCSR0B  |= RXCIE0_bm; break;
  case USART_TRANSMIT_COMPLETE        : *_UCSR0B  |= TXCIE0_bm; break;
  case ANALOG_DIGITAL_CONVERTER       : *_ADCSRA  |= ADIE_bm;   break;
  case EEPROM_READY                   : *_EECR    |= EERIE_bm;  break;
  case ANALOG_COMPARATOR              : *_ACSR    |= ACIE_bm;   break;
  case TWO_WIRE_INT                   : *_TWCR    |= TWIE_bm;   break;
  case SPM_READY                      : *_SPMCSR  |= SPMIE_bm; break;
  case GLOBAL                         :
#if (MCU_TYPE == atmega328p)
    asm volatile("sei");
#endif
  break;
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
  case USART_RECEIVE_COMPLETE         : *_UCSR0B  &= ~UDRIE0_bm; break;
  case USART_UART_DATA_REGISTER_EMPTY : *_UCSR0B  &= ~RXCIE0_bm; break;
  case USART_TRANSMIT_COMPLETE        : *_UCSR0B  &= ~TXCIE0_bm; break;
  case ANALOG_DIGITAL_CONVERTER       : *_ADCSRA  &= ~ADIE_bm;   break;
  case EEPROM_READY                   : *_EECR    &= ~EERIE_bm;  break;
  case ANALOG_COMPARATOR              : *_ACSR    &= ~ACIE_bm;   break;
  case TWO_WIRE_INT                   : *_TWCR    &= ~TWIE_bm;   break;
  case SPM_READY                      : *_SPMCSR  |= SPMIE_bm;   break;
  case GLOBAL                         :
#if (MCU_TYPE == atmega328p)
    asm volatile("cli");
#endif
break;
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

#if (MCU_TYPE == atmega328p)

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

#endif /* (MCU_TYPE == atmega328p) */

/**************************************************************************************/
