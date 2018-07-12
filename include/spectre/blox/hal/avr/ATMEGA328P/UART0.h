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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA328P_UART0_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA328P_UART0_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/ATMEGA328P/UART0.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA328P
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

class UART0
{

public:

  typedef struct
  {
    volatile uint8_t                          * udr0,
                                              * ucsr0a,
                                              * ucsr0b,
                                              * ucsr0c,
                                              * ubrr0;
    hal::interface::InterruptController       & int_ctrl;
    uint32_t                            const   f_cpu;
  } ParamIn;

  typedef struct
  {
    hal::ATMEGA328P::UART0 & uart0;
  } ParamOut;


  UART0(ParamIn & in, ParamOut & out);

private:

  hal::ATMEGA328P::UART0                                _uart0;
  hal::ATMEGA328P::UART0_TransmitRegisterEmptyCallback  _uart0_uart_data_register_empty_callback;
  hal::ATMEGA328P::UART0_ReceiveCompleteCallback        _uart0_receive_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA328P_UART0_H_ */
