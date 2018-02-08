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

#include <spectre/hal/avr/AT90CAN128/InterruptController.h>

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

namespace AT90CAN128
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t constexpr NUMBER_OF_INTERRUPT_SERVICE_ROUTINES = 36;

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
  /* todo */
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  /* todo */
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

} /* AT90CAN128 */

} /* hal */

} /* spectre */

/**************************************************************************************/

#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_at90can128)

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::interface;
using namespace spectre::hal::AT90CAN128;

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

ISR(INT2_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EXTERNAL_INT2].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EXTERNAL_INT2].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(INT3_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EXTERNAL_INT3].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EXTERNAL_INT3].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(INT4_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EXTERNAL_INT4].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EXTERNAL_INT4].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(INT5_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EXTERNAL_INT5].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EXTERNAL_INT5].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(INT6_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EXTERNAL_INT6].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EXTERNAL_INT6].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(INT7_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EXTERNAL_INT7].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EXTERNAL_INT7].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

ISR(TIMER2_COMP_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER2_COMPARE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER2_COMPARE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER2_OVF_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER2_OVERFLOW].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER2_OVERFLOW].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER1_CAPT_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_CAPTURE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_CAPTURE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER1_COMPA_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_COMPARE_A].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_COMPARE_A].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER1_COMPB_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_COMPARE_B].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_COMPARE_B].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER1_COMPC_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_COMPARE_C].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_COMPARE_C].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER1_OVF_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER1_OVERFLOW].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER1_OVERFLOW].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER0_COMP_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER0_COMPARE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER0_COMPARE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER0_OVF_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER0_OVERFLOW].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER0_OVERFLOW].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(CANIT_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[CAN_INT].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[CAN_INT].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(OVRIT_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[CAN_TIMER_OVERRUN].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[CAN_TIMER_OVERRUN].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(SPI_STC_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[SPI_SERIAL_TRANSFER_COMPLETE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[SPI_SERIAL_TRANSFER_COMPLETE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(USART0_RX_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART0_RECEIVE_COMPLETE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART0_RECEIVE_COMPLETE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(USART0_UDRE_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART0_UART_DATA_REGISTER_EMPTY].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART0_UART_DATA_REGISTER_EMPTY].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(USART0_TX_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART0_TRANSMIT_COMPLETE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART0_TRANSMIT_COMPLETE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(ANALOG_COMP_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[ANALOG_COMPARATOR].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[ANALOG_COMPARATOR].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(ADC_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[ANALOG_DIGITAL_CONVERTER].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[ANALOG_DIGITAL_CONVERTER].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(EE_READY_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[EEPROM_READY].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[EEPROM_READY].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER3_CAPT_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER3_CAPTURE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER3_CAPTURE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER3_COMPA_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER3_COMPARE_A].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER3_COMPARE_A].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER3_COMPB_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER3_COMPARE_B].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER3_COMPARE_B].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER3_COMPC_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER3_COMPARE_C].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER3_COMPARE_C].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TIMER3_OVF_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TIMER3_OVERFLOW].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TIMER3_OVERFLOW].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(USART1_RX_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART1_RECEIVE_COMPLETE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART1_RECEIVE_COMPLETE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(USART1_UDRE_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART1_UART_DATA_REGISTER_EMPTY].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART1_UART_DATA_REGISTER_EMPTY].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(USART1_TX_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[USART1_TRANSMIT_COMPLETE].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[USART1_TRANSMIT_COMPLETE].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(TWI_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[TWO_WIRE_INT].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[TWO_WIRE_INT].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

ISR(SPM_READY_vect)
{
  ISRFunc isr_func = _interrupt_callback_array[SPM_READY].isr_func;
  ISRArg  isr_arg  = _interrupt_callback_array[SPM_READY].isr_arg;

  if(isr_func) isr_func(isr_arg);
}

/**************************************************************************************/

#endif /* defined(MCU_ARCH_avr) && defined(MCU_TYPE_at90can128) */

/**************************************************************************************/
