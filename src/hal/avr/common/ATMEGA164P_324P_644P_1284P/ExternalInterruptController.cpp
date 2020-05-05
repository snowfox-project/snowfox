/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/hal/avr/common/ATMEGA164P_324P_644P_1284P/ExternalInterruptController.h>

#include <snowfox/hal/avr/common/ATMEGA164P_324P_644P_1284P/InterruptController.h>
#include <snowfox/hal/avr/common/ATxxxx/util/ExternalInterruptUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

ExternalInterruptController::ExternalInterruptController(volatile uint8_t               * eicra,
                                                         interface::InterruptController & int_ctrl)
: _EICRA   (eicra   ),
  _int_ctrl(int_ctrl)
{

}

ExternalInterruptController::~ExternalInterruptController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void ExternalInterruptController::setTriggerMode(uint8_t const ext_int_num, interface::TriggerMode const trigger_mode)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0): ATxxxx::setTriggerModeEint0(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1): ATxxxx::setTriggerModeEint1(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2): ATxxxx::setTriggerModeEint2(trigger_mode, _EICRA); break;
  default                                           : /* PCINT trigger mode is Any */                    break;
  }
}

void ExternalInterruptController::enable(uint8_t const ext_int_num)
{
  uint8_t const int_num = converToIntNum(ext_int_num);
  if(int_num != interface::InterruptController::INVALID_INT_NUM)
  {
    _int_ctrl.enableInterrupt(int_num);
  }
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  uint8_t const int_num = converToIntNum(ext_int_num);
  if(int_num != interface::InterruptController::INVALID_INT_NUM)
  {
    _int_ctrl.disableInterrupt(int_num);
  }
}

void ExternalInterruptController::registerInterruptCallback(uint8_t const ext_int_num, interface::ExternalInterruptCallback * external_interrupt_callback)
{
  uint8_t const int_num = converToIntNum(ext_int_num);
  if(int_num != interface::InterruptController::INVALID_INT_NUM)
  {
    _int_ctrl.registerInterruptCallback(int_num, external_interrupt_callback);
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t ExternalInterruptController::converToIntNum(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): return toIntNum(Interrupt::EXTERNAL_INT0   );           break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): return toIntNum(Interrupt::EXTERNAL_INT1   );           break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2   ): return toIntNum(Interrupt::EXTERNAL_INT2   );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): return toIntNum(Interrupt::PIN_CHANGE_INT0 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): return toIntNum(Interrupt::PIN_CHANGE_INT1 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): return toIntNum(Interrupt::PIN_CHANGE_INT2 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): return toIntNum(Interrupt::PIN_CHANGE_INT3 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): return toIntNum(Interrupt::PIN_CHANGE_INT4 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): return toIntNum(Interrupt::PIN_CHANGE_INT5 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): return toIntNum(Interrupt::PIN_CHANGE_INT6 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): return toIntNum(Interrupt::PIN_CHANGE_INT7 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): return toIntNum(Interrupt::PIN_CHANGE_INT8 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): return toIntNum(Interrupt::PIN_CHANGE_INT9 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): return toIntNum(Interrupt::PIN_CHANGE_INT10);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): return toIntNum(Interrupt::PIN_CHANGE_INT11);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): return toIntNum(Interrupt::PIN_CHANGE_INT12);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): return toIntNum(Interrupt::PIN_CHANGE_INT13);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): return toIntNum(Interrupt::PIN_CHANGE_INT14);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT15): return toIntNum(Interrupt::PIN_CHANGE_INT15);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): return toIntNum(Interrupt::PIN_CHANGE_INT16);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): return toIntNum(Interrupt::PIN_CHANGE_INT17);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): return toIntNum(Interrupt::PIN_CHANGE_INT18);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): return toIntNum(Interrupt::PIN_CHANGE_INT19);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): return toIntNum(Interrupt::PIN_CHANGE_INT20);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): return toIntNum(Interrupt::PIN_CHANGE_INT21);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): return toIntNum(Interrupt::PIN_CHANGE_INT22);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): return toIntNum(Interrupt::PIN_CHANGE_INT23);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT24): return toIntNum(Interrupt::PIN_CHANGE_INT24);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT25): return toIntNum(Interrupt::PIN_CHANGE_INT25);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT26): return toIntNum(Interrupt::PIN_CHANGE_INT26);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT27): return toIntNum(Interrupt::PIN_CHANGE_INT27);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT28): return toIntNum(Interrupt::PIN_CHANGE_INT28);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT29): return toIntNum(Interrupt::PIN_CHANGE_INT29);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT30): return toIntNum(Interrupt::PIN_CHANGE_INT30);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT31): return toIntNum(Interrupt::PIN_CHANGE_INT31);           break;
  default                                              : return interface::InterruptController::INVALID_INT_NUM; break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATMEGA164P_324P_644P_1284P */
