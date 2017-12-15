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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/interrupt/InterruptController.h>
#include <spectre/hal/interface/interrupt/InterruptControllerAssembly.h>

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
 * CONSTANTS
 **************************************************************************************/

namespace interrupt
{

static uint8_t const EXTERNAL_INT0                  =  0;
static uint8_t const EXTERNAL_INT1                  =  1;
static uint8_t const PIN_CHANGE_INT0                =  2;
static uint8_t const PIN_CHANGE_INT1                =  3;
static uint8_t const PIN_CHANGE_INT2                =  4;
static uint8_t const WATCHDOG_TIMER                 =  5;
static uint8_t const TIMER2_COMPARE_A               =  6;
static uint8_t const TIMER2_COMPARE_B               =  7;
static uint8_t const TIMER2_OVERFLOW                =  8;
static uint8_t const TIMER1_CAPTURE                 =  9;
static uint8_t const TIMER1_COMPARE_A               = 10;
static uint8_t const TIMER1_COMPARE_B               = 11;
static uint8_t const TIMER1_OVERFLOW                = 12;
static uint8_t const TIMER0_COMPARE_A               = 13;
static uint8_t const TIMER0_COMPARE_B               = 14;
static uint8_t const TIMER0_OVERFLOW                = 15;
static uint8_t const SPI_SERIAL_TRANSFER_COMPLETE   = 16;
static uint8_t const USART_RECEIVE_COMPLETE         = 17;
static uint8_t const USART_UART_DATA_REGISTER_EMPTY = 18;
static uint8_t const USART_TRANSMIT_COMPLETE        = 19;
static uint8_t const ANALOG_DIGITAL_CONVERTER       = 20;
static uint8_t const EEPROM_READY                   = 21;
static uint8_t const ANALOG_COMPARATOR              = 22;
static uint8_t const TWO_WIRE_INT                   = 23;
static uint8_t const SPM_READY                      = 24;
static uint8_t const GLOBAL                         = 25;

} /* interrupt */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class InterruptController : public interface::InterruptController,
                            public interface::InterruptControllerAssembly
{

public:

           InterruptController();
  virtual ~InterruptController();


  /* Interrupt Controller Interface */

  virtual void enableInterrupt (uint8_t const int_num) override;
  virtual void disableInterrupt(uint8_t const int_num) override;


  /* Interrupt Controller Assembly Interface */

  virtual void registerInterruptCallback(uint8_t const int_num, InterruptCallbackFunc callback) override;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_ */
