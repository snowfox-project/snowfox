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

#include <spectre/hal/avr/ATMEGA328P/ExternalInterruptController.h>

#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>
#include <spectre/hal/avr/common/ATxxxx/util/ExternalInterruptUtil.h>

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
  default                                           : /* PCINT trigger mode is Any */                    break;
  }
}

void ExternalInterruptController::enable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0   )); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1   )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT4 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT5 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT6 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT7 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT8 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT9 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT10)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT11)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT12)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT13)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT14)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT16)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT17)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT18)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT19)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT20)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT21)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT22)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT23)); break;
  }
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0   )); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1   )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT4 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT5 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT6 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT7 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT8 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT9 )); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT10)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT11)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT12)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT13)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT14)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT16)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT17)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT18)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT19)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT20)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT21)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT22)); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): _int_ctrl.disableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT23)); break;
  }
}

void ExternalInterruptController::registerInterruptCallback(uint8_t const ext_int_num, interface::InterruptCallback * interrupt_callback)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::EXTERNAL_INT0   ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::EXTERNAL_INT1   ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT0 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT1 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT2 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT3 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT4 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT5 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT6 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT7 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT8 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT9 ), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT10), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT11), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT12), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT13), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT14), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT16), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT17), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT18), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT19), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT20), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT21), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT22), interrupt_callback); break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): _int_ctrl.registerInterruptCallback(toIntNum(Interrupt::PIN_CHANGE_INT23), interrupt_callback); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */
