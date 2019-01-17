/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#include <snowfox/hal/avr/common/AT90CAN32_64_128/ExternalInterruptController.h>

#include <snowfox/hal/avr/common/AT90CAN32_64_128/InterruptController.h>
#include <snowfox/hal/avr/common/ATxxxx/util/ExternalInterruptUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace AT90CAN32_64_128
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
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT4): ATxxxx::setTriggerModeEint4(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT5): ATxxxx::setTriggerModeEint5(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT6): ATxxxx::setTriggerModeEint6(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT7): ATxxxx::setTriggerModeEint7(trigger_mode, _EICRB); break;
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
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0): return toIntNum(Interrupt::EXTERNAL_INT0);              break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1): return toIntNum(Interrupt::EXTERNAL_INT1);              break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2): return toIntNum(Interrupt::EXTERNAL_INT2);              break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT3): return toIntNum(Interrupt::EXTERNAL_INT3);              break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT4): return toIntNum(Interrupt::EXTERNAL_INT4);              break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT5): return toIntNum(Interrupt::EXTERNAL_INT5);              break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT6): return toIntNum(Interrupt::EXTERNAL_INT6);              break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT7): return toIntNum(Interrupt::EXTERNAL_INT7);              break;
  default                                           : return interface::InterruptController::INVALID_INT_NUM; break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* hal */

} /* snowfox */
