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

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/ExternalInterruptController.h>

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/InterruptController.h>
#include <spectre/hal/avr/common/ATxxxx/util/ExternalInterruptUtil.h>

#include <spectre/util/BitManip.h>

#include <spectre/cpu/avr/io/common/ATMEGA16U4_32U4.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA16U4_32U4
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

ExternalInterruptController::ExternalInterruptController(volatile uint8_t               * eicra,
                                                         volatile uint8_t               * eicrb,
                                                         interface::InterruptController & int_ctrl)
: _EICRA   (eicra   ),
  _EICRB   (eicrb   ),
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
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT3): ATxxxx::setTriggerModeEint3(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT6): ATxxxx::setTriggerModeEint6(trigger_mode, _EICRB); break;
  default                                           : /* PCINT trigger mode is Any */                    break;
  }
}

void ExternalInterruptController::enable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT2  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT3   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT3  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT6   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT6  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT0_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT1_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT2_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT3_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT4_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT5_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT6_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT7_bp); } break;
  }
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT2  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT3   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT3  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT6   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT6  ));                                   } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): {                                                                  util::clrBit(_PCMSK0, PCINT0_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): {                                                                  util::clrBit(_PCMSK0, PCINT1_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): {                                                                  util::clrBit(_PCMSK0, PCINT2_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): {                                                                  util::clrBit(_PCMSK0, PCINT3_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): {                                                                  util::clrBit(_PCMSK0, PCINT4_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): {                                                                  util::clrBit(_PCMSK0, PCINT5_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): {                                                                  util::clrBit(_PCMSK0, PCINT6_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): {                                                                  util::clrBit(_PCMSK0, PCINT7_bp); } break;
  }
}

void ExternalInterruptController::registerInterruptCallback(uint8_t const ext_int_num, interface::InterruptCallback * interrupt_callback)
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* spectre */
