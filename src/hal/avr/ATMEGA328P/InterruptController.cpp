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
  case interrupt::GLOBAL                         : sei(); break;
  case interrupt::EXTERNAL_INT0                  : break;
  case interrupt::EXTERNAL_INT1                  : break;
  case interrupt::PIN_CHANGE_INT0                : break;
  case interrupt::PIN_CHANGE_INT1                : break;
  case interrupt::PIN_CHANGE_INT2                : break;
  case interrupt::WATCHDOG_TIMER                 : break;
  case interrupt::TIMER2_COMPARE_A               : break;
  case interrupt::TIMER2_COMPARE_B               : break;
  case interrupt::TIMER2_OVERFLOW                : break;
  case interrupt::TIMER1_CAPTURE                 : break;
  case interrupt::TIMER1_COMPARE_A               : break;
  case interrupt::TIMER1_COMPARE_B               : break;
  case interrupt::TIMER1_OVERFLOW                : break;
  case interrupt::TIMER0_COMPARE_A               : break;
  case interrupt::TIMER0_COMPARE_B               : break;
  case interrupt::TIMER0_OVERFLOW                : break;
  case interrupt::SPI_SERIAL_TRANSFER_COMPLETE   : break;
  case interrupt::USART_RECEIVE_COMPLETE         : break;
  case interrupt::USART_UART_DATA_REGISTER_EMPTY : break;
  case interrupt::USART_TRANSMIT_COMPLETE        : break;
  case interrupt::ANALOG_DIGITAL_CONVERTER       : break;
  case interrupt::EEPROM_READY                   : break;
  case interrupt::ANALOG_COMPARATOR              : break;
  case interrupt::TWO_WIRE_INT                   : break;
  case interrupt::SPM_READY                      : break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case interrupt::GLOBAL                         : cli(); break;
  case interrupt::EXTERNAL_INT0                  : break;
  case interrupt::EXTERNAL_INT1                  : break;
  case interrupt::PIN_CHANGE_INT0                : break;
  case interrupt::PIN_CHANGE_INT1                : break;
  case interrupt::PIN_CHANGE_INT2                : break;
  case interrupt::WATCHDOG_TIMER                 : break;
  case interrupt::TIMER2_COMPARE_A               : break;
  case interrupt::TIMER2_COMPARE_B               : break;
  case interrupt::TIMER2_OVERFLOW                : break;
  case interrupt::TIMER1_CAPTURE                 : break;
  case interrupt::TIMER1_COMPARE_A               : break;
  case interrupt::TIMER1_COMPARE_B               : break;
  case interrupt::TIMER1_OVERFLOW                : break;
  case interrupt::TIMER0_COMPARE_A               : break;
  case interrupt::TIMER0_COMPARE_B               : break;
  case interrupt::TIMER0_OVERFLOW                : break;
  case interrupt::SPI_SERIAL_TRANSFER_COMPLETE   : break;
  case interrupt::USART_RECEIVE_COMPLETE         : break;
  case interrupt::USART_UART_DATA_REGISTER_EMPTY : break;
  case interrupt::USART_TRANSMIT_COMPLETE        : break;
  case interrupt::ANALOG_DIGITAL_CONVERTER       : break;
  case interrupt::EEPROM_READY                   : break;
  case interrupt::ANALOG_COMPARATOR              : break;
  case interrupt::TWO_WIRE_INT                   : break;
  case interrupt::SPM_READY                      : break;
  }
}

void InterruptController::registerInterruptCallback(uint8_t const int_num, InterruptCallbackFunc callback)
{
  switch(int_num)
  {
  case interrupt::GLOBAL                         : break;
  case interrupt::EXTERNAL_INT0                  : break;
  case interrupt::EXTERNAL_INT1                  : break;
  case interrupt::PIN_CHANGE_INT0                : break;
  case interrupt::PIN_CHANGE_INT1                : break;
  case interrupt::PIN_CHANGE_INT2                : break;
  case interrupt::WATCHDOG_TIMER                 : break;
  case interrupt::TIMER2_COMPARE_A               : break;
  case interrupt::TIMER2_COMPARE_B               : break;
  case interrupt::TIMER2_OVERFLOW                : break;
  case interrupt::TIMER1_CAPTURE                 : break;
  case interrupt::TIMER1_COMPARE_A               : break;
  case interrupt::TIMER1_COMPARE_B               : break;
  case interrupt::TIMER1_OVERFLOW                : break;
  case interrupt::TIMER0_COMPARE_A               : break;
  case interrupt::TIMER0_COMPARE_B               : break;
  case interrupt::TIMER0_OVERFLOW                : break;
  case interrupt::SPI_SERIAL_TRANSFER_COMPLETE   : break;
  case interrupt::USART_RECEIVE_COMPLETE         : break;
  case interrupt::USART_UART_DATA_REGISTER_EMPTY : break;
  case interrupt::USART_TRANSMIT_COMPLETE        : break;
  case interrupt::ANALOG_DIGITAL_CONVERTER       : break;
  case interrupt::EEPROM_READY                   : break;
  case interrupt::ANALOG_COMPARATOR              : break;
  case interrupt::TWO_WIRE_INT                   : break;
  case interrupt::SPM_READY                      : break;
  }
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

ISR(INT0_vect)
{

}

ISR(INT1_vect)
{

}

ISR(PCINT0_vect)
{

}

ISR(PCINT1_vect)
{

}

ISR(PCINT2_vect)
{

}

ISR(WDT_vect)
{

}

ISR(TIMER2_COMPA_vect)
{

}

ISR(TIMER2_COMPB_vect)
{

}

ISR(TIMER2_OVF_vect)
{

}

ISR(TIMER1_CAPT_vect)
{

}

ISR(TIMER1_COMPA_vect)
{

}

ISR(TIMER1_COMPB_vect)
{

}

ISR(TIMER1_OVF_vect)
{

}

ISR(TIMER0_COMPA_vect)
{

}

ISR(TIMER0_COMPB_vect)
{

}

ISR(TIMER0_OVF_vect)
{

}

ISR(SPI_STC_vect)
{

}

ISR(USART_RX_vect)
{

}

ISR(USART_UDRE_vect)
{

}

ISR(USART_TX_vect)
{

}

ISR(ADC_vect)
{

}

ISR(EE_READY_vect)
{

}

ISR(ANALOG_COMP_vect)
{

}

ISR(TWI_vect)
{

}

ISR(SPM_READY_vect)
{

}

#endif
