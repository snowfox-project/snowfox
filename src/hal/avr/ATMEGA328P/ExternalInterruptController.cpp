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

#include <spectre/util/BitManip.h>

#include <spectre/cpu/avr/io/ATMEGA328P.h>

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

ExternalInterruptController::ExternalInterruptController(volatile uint8_t            * eicra,
                                                         volatile uint8_t            * pcmsk0,
                                                         volatile uint8_t            * pcmsk1,
                                                         volatile uint8_t            * pcmsk2,
                                                         interface::InterruptControl & int_ctrl)
: _EICRA   (eicra   ),
  _PCMSK0  (pcmsk0  ),
  _PCMSK1  (pcmsk1  ),
  _PCMSK2  (pcmsk2  ),
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
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                                    } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                                    } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT0_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT1_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT2_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT3_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT4_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT5_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT6_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); util::setBit(_PCMSK0, PCINT7_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); util::setBit(_PCMSK1, PCINT8_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); util::setBit(_PCMSK1, PCINT9_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); util::setBit(_PCMSK1, PCINT10_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); util::setBit(_PCMSK1, PCINT11_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); util::setBit(_PCMSK1, PCINT12_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); util::setBit(_PCMSK1, PCINT13_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); util::setBit(_PCMSK1, PCINT14_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); util::setBit(_PCMSK2, PCINT16_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); util::setBit(_PCMSK2, PCINT17_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); util::setBit(_PCMSK2, PCINT18_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); util::setBit(_PCMSK2, PCINT19_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); util::setBit(_PCMSK2, PCINT20_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); util::setBit(_PCMSK2, PCINT21_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); util::setBit(_PCMSK2, PCINT22_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); util::setBit(_PCMSK2, PCINT23_bp); } break;
  }
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                                    } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                                    } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): {                                                                  util::clrBit(_PCMSK0, PCINT0_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): {                                                                  util::clrBit(_PCMSK0, PCINT1_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): {                                                                  util::clrBit(_PCMSK0, PCINT2_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): {                                                                  util::clrBit(_PCMSK0, PCINT3_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): {                                                                  util::clrBit(_PCMSK0, PCINT4_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): {                                                                  util::clrBit(_PCMSK0, PCINT5_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): {                                                                  util::clrBit(_PCMSK0, PCINT6_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): {                                                                  util::clrBit(_PCMSK0, PCINT7_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): {                                                                  util::clrBit(_PCMSK1, PCINT8_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): {                                                                  util::clrBit(_PCMSK1, PCINT9_bp ); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): {                                                                  util::clrBit(_PCMSK1, PCINT10_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): {                                                                  util::clrBit(_PCMSK1, PCINT11_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): {                                                                  util::clrBit(_PCMSK1, PCINT12_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): {                                                                  util::clrBit(_PCMSK1, PCINT13_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): {                                                                  util::clrBit(_PCMSK1, PCINT14_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): {                                                                  util::clrBit(_PCMSK2, PCINT16_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): {                                                                  util::clrBit(_PCMSK2, PCINT17_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): {                                                                  util::clrBit(_PCMSK2, PCINT18_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): {                                                                  util::clrBit(_PCMSK2, PCINT19_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): {                                                                  util::clrBit(_PCMSK2, PCINT20_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): {                                                                  util::clrBit(_PCMSK2, PCINT21_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): {                                                                  util::clrBit(_PCMSK2, PCINT22_bp); } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): {                                                                  util::clrBit(_PCMSK2, PCINT23_bp); } break;
  }
}

void ExternalInterruptController::registerExternalInterruptCallback(uint8_t const ext_int_num, interface::ExternalInterruptCallback * external_interrupt_callback)
{
  if(ext_int_num < NUM_EXTERNAL_INTERRUPTS)
  {
    _external_interrupt_callback[ext_int_num] = external_interrupt_callback;
  }
}

void ExternalInterruptController::ISR_onEint0Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT0)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT0)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint1Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT1)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT1)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onPinChange0Event()
{
  for(uint8_t ext_int_num = toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0);
      ext_int_num <= toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7);
      ext_int_num++)
  {
    if(_external_interrupt_callback[ext_int_num])
    {
      _external_interrupt_callback[ext_int_num]->onExternalEventCallback();
    }
  }
}

void ExternalInterruptController::ISR_onPinChange1Event()
{
  for(uint8_t ext_int_num = toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8);
      ext_int_num <= toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14);
      ext_int_num++)
  {
    if(_external_interrupt_callback[ext_int_num])
    {
      _external_interrupt_callback[ext_int_num]->onExternalEventCallback();
    }
  }
}

void ExternalInterruptController::ISR_onPinChange2Event()
{
  for(uint8_t ext_int_num = toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16);
      ext_int_num <= toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23);
      ext_int_num++)
  {
    if(_external_interrupt_callback[ext_int_num])
    {
      _external_interrupt_callback[ext_int_num]->onExternalEventCallback();
    }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */
