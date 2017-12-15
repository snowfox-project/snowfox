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

#include <avr/io.h>
#include <avr/interrupt.h>

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

InterruptController::InterruptController()
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
  case EXTERNAL_INT0                  : break;
  case EXTERNAL_INT1                  : break;
  case PIN_CHANGE_INT0                : break;
  case PIN_CHANGE_INT1                : break;
  case PIN_CHANGE_INT2                : break;
  case WATCHDOG_TIMER                 : break;
  case TIMER2_COMPARE_A               : break;
  case TIMER2_COMPARE_B               : break;
  case TIMER2_OVERFLOW                : break;
  case TIMER1_CAPTURE                 : break;
  case TIMER1_COMPARE_A               : break;
  case TIMER1_COMPARE_B               : break;
  case TIMER1_OVERFLOW                : break;
  case TIMER0_COMPARE_A               : break;
  case TIMER0_COMPARE_B               : break;
  case TIMER0_OVERFLOW                : break;
  case SPI_SERIAL_TRANSFER_COMPLETE   : break;
  case USART_RECEIVE_COMPLETE         : break;
  case USART_UART_DATA_REGISTER_EMPTY : break;
  case USART_TRANSMIT_COMPLETE        : break;
  case ANALOG_DIGITAL_CONVERTER       : break;
  case EEPROM_READY                   : break;
  case ANALOG_COMPARATOR              : break;
  case TWO_WIRE_INT                   : break;
  case SPM_READY                      : break;
  case GLOBAL                         : sei(); break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case EXTERNAL_INT0                  : break;
  case EXTERNAL_INT1                  : break;
  case PIN_CHANGE_INT0                : break;
  case PIN_CHANGE_INT1                : break;
  case PIN_CHANGE_INT2                : break;
  case WATCHDOG_TIMER                 : break;
  case TIMER2_COMPARE_A               : break;
  case TIMER2_COMPARE_B               : break;
  case TIMER2_OVERFLOW                : break;
  case TIMER1_CAPTURE                 : break;
  case TIMER1_COMPARE_A               : break;
  case TIMER1_COMPARE_B               : break;
  case TIMER1_OVERFLOW                : break;
  case TIMER0_COMPARE_A               : break;
  case TIMER0_COMPARE_B               : break;
  case TIMER0_OVERFLOW                : break;
  case SPI_SERIAL_TRANSFER_COMPLETE   : break;
  case USART_RECEIVE_COMPLETE         : break;
  case USART_UART_DATA_REGISTER_EMPTY : break;
  case USART_TRANSMIT_COMPLETE        : break;
  case ANALOG_DIGITAL_CONVERTER       : break;
  case EEPROM_READY                   : break;
  case ANALOG_COMPARATOR              : break;
  case TWO_WIRE_INT                   : break;
  case SPM_READY                      : break;
  case GLOBAL                         : cli(); break;
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

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if (MCU_TYPE == atmega328p)

using namespace spectre::hal::interface;
using namespace spectre::hal::ATMEGA328P;

/**************************************************************************************/

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
