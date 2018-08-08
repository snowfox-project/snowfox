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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/ATMEGA328P/ExternalInterruptController.h>

#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>
#include <spectre/hal/avr/common/ATxxxx/util/ExternalInterruptTriggerModeConfig.h>

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
 * DEFINES
 **************************************************************************************/

/* PCMSK0 */
#define PCINT7_bm  (1<<7)
#define PCINT6_bm  (1<<6)
#define PCINT5_bm  (1<<5)
#define PCINT4_bm  (1<<4)
#define PCINT3_bm  (1<<3)
#define PCINT2_bm  (1<<2)
#define PCINT1_bm  (1<<1)
#define PCINT0_bm  (1<<0)

/* PCMSK1 */
#define PCINT14_bm (1<<6)
#define PCINT13_bm (1<<5)
#define PCINT12_bm (1<<4)
#define PCINT11_bm (1<<3)
#define PCINT10_bm (1<<2)
#define PCINT9_bm  (1<<1)
#define PCINT8_bm  (1<<0)

/* PCMSK2 */
#define PCINT23_bm (1<<7)
#define PCINT22_bm (1<<6)
#define PCINT21_bm (1<<5)
#define PCINT20_bm (1<<4)
#define PCINT19_bm (1<<3)
#define PCINT18_bm (1<<2)
#define PCINT17_bm (1<<1)
#define PCINT16_bm (1<<0)

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
  case toExtIntNum(ExternalInterrupt::EINT0): ATxxxx::ExternalInterruptTriggerModeConfig::setTriggerModeEint0(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EINT1): ATxxxx::ExternalInterruptTriggerModeConfig::setTriggerModeEint1(trigger_mode, _EICRA); break;
  default                                   : /* PCINT trigger mode is Any */                                                        break;
  }
}

void ExternalInterruptController::enable(uint8_t const ext_int_num)
{
  /* TODO */
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  /* TODO */
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
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT0)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT0)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint1Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT1)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT1)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onPinChange0Event()
{
  for(uint8_t ext_int_num = toExtIntNum(ExternalInterrupt::PCINT0);
      ext_int_num <= toExtIntNum(ExternalInterrupt::PCINT7);
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
  for(uint8_t ext_int_num = toExtIntNum(ExternalInterrupt::PCINT8);
      ext_int_num <= toExtIntNum(ExternalInterrupt::PCINT14);
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
  for(uint8_t ext_int_num = toExtIntNum(ExternalInterrupt::PCINT16);
      ext_int_num <= toExtIntNum(ExternalInterrupt::PCINT23);
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
