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

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/ExternalInterruptController.h>

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>
#include <spectre/hal/avr/common/ATxxxx/util/ExternalInterruptTriggerModeConfig.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA640_1280_2560
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
#define PCINT15_bm (1<<7)
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
                                                         volatile uint8_t            * eicrb,
                                                         volatile uint8_t            * pcmsk0,
                                                         volatile uint8_t            * pcmsk1,
                                                         volatile uint8_t            * pcmsk2,
                                                         interface::InterruptControl & int_ctrl)
: _EICRA   (eicra   ),
  _EICRB   (eicrb   ),
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
  case toExtIntNum(ExternalInterrupt::EINT2): ATxxxx::ExternalInterruptTriggerModeConfig::setTriggerModeEint2(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EINT3): ATxxxx::ExternalInterruptTriggerModeConfig::setTriggerModeEint3(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EINT4): ATxxxx::ExternalInterruptTriggerModeConfig::setTriggerModeEint4(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EINT5): ATxxxx::ExternalInterruptTriggerModeConfig::setTriggerModeEint5(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EINT6): ATxxxx::ExternalInterruptTriggerModeConfig::setTriggerModeEint6(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EINT7): ATxxxx::ExternalInterruptTriggerModeConfig::setTriggerModeEint7(trigger_mode, _EICRB); break;
  default                                   : /* PCINT trigger mode is Any */                                                        break;
  }
}

void ExternalInterruptController::enable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EINT0  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT1  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT2  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT2  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT3  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT3  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT4  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT4  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT5  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT5  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT6  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT6  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT7  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT7  ));                         } break;
  case toExtIntNum(ExternalInterrupt::PCINT0 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT0_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT1 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT1_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT2 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT2_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT3 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT3_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT4 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT4_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT5 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT5_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT6 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT6_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT7 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT7_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT8 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT8_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT9 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT9_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT10): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT10_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT11): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT11_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT12): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT12_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT13): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT13_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT14): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT14_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT15): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT15_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT16): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT16_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT17): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT17_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT18): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT18_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT19): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT19_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT20): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT20_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT21): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT21_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT22): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT22_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT23): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT23_bm; } break;
  }
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EINT0  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT1  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT2  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT2  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT3  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT3  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT4  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT4  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT5  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT5  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT6  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT6  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT7  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT7  ));                          } break;
  case toExtIntNum(ExternalInterrupt::PCINT0 ): {                                                                  *_PCMSK0 &= ~PCINT0_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT1 ): {                                                                  *_PCMSK0 &= ~PCINT1_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT2 ): {                                                                  *_PCMSK0 &= ~PCINT2_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT3 ): {                                                                  *_PCMSK0 &= ~PCINT3_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT4 ): {                                                                  *_PCMSK0 &= ~PCINT4_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT5 ): {                                                                  *_PCMSK0 &= ~PCINT5_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT6 ): {                                                                  *_PCMSK0 &= ~PCINT6_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT7 ): {                                                                  *_PCMSK0 &= ~PCINT7_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT8 ): {                                                                  *_PCMSK1 &= ~PCINT8_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT9 ): {                                                                  *_PCMSK1 &= ~PCINT9_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PCINT10): {                                                                  *_PCMSK1 &= ~PCINT10_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT11): {                                                                  *_PCMSK1 &= ~PCINT11_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT12): {                                                                  *_PCMSK1 &= ~PCINT12_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT13): {                                                                  *_PCMSK1 &= ~PCINT13_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT14): {                                                                  *_PCMSK1 &= ~PCINT14_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT15): {                                                                  *_PCMSK1 &= ~PCINT15_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT16): {                                                                  *_PCMSK2 &= ~PCINT16_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT17): {                                                                  *_PCMSK2 &= ~PCINT17_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT18): {                                                                  *_PCMSK2 &= ~PCINT18_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT19): {                                                                  *_PCMSK2 &= ~PCINT19_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT20): {                                                                  *_PCMSK2 &= ~PCINT20_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT21): {                                                                  *_PCMSK2 &= ~PCINT21_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT22): {                                                                  *_PCMSK2 &= ~PCINT22_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT23): {                                                                  *_PCMSK2 &= ~PCINT23_bm; } break;
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

void ExternalInterruptController::ISR_onEint2Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT2)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT2)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint3Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT3)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT3)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint4Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT4)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT4)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint5Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT5)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT5)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint6Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT6)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT6)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint7Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT7)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EINT7)]->onExternalEventCallback();
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
      ext_int_num <= toExtIntNum(ExternalInterrupt::PCINT15);
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

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* spectre */
