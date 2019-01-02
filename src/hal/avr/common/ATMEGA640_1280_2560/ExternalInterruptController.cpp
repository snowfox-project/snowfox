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

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/ExternalInterruptController.h>

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>
#include <spectre/hal/avr/common/ATxxxx/util/ExternalInterruptUtil.h>

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
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT2  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT3   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT3  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT4   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT4  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT5   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT5  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT6   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT6  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT7   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT7  ));                         } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT0_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT1_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT2_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT3_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT4_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT5_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT6_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT0)); *_PCMSK0 |= PCINT7_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT8_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT9_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT10_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT11_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT12_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT13_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT14_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT15): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT1)); *_PCMSK1 |= PCINT15_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT16_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT17_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT18_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT19_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT20_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT21_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT22_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT2)); *_PCMSK2 |= PCINT23_bm; } break;
  }
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT2  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT3   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT3  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT4   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT4  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT5   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT5  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT6   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT6  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT7   ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT7  ));                          } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): {                                                                  *_PCMSK0 &= ~PCINT0_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): {                                                                  *_PCMSK0 &= ~PCINT1_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): {                                                                  *_PCMSK0 &= ~PCINT2_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): {                                                                  *_PCMSK0 &= ~PCINT3_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): {                                                                  *_PCMSK0 &= ~PCINT4_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): {                                                                  *_PCMSK0 &= ~PCINT5_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): {                                                                  *_PCMSK0 &= ~PCINT6_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): {                                                                  *_PCMSK0 &= ~PCINT7_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): {                                                                  *_PCMSK1 &= ~PCINT8_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): {                                                                  *_PCMSK1 &= ~PCINT9_bm;  } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): {                                                                  *_PCMSK1 &= ~PCINT10_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): {                                                                  *_PCMSK1 &= ~PCINT11_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): {                                                                  *_PCMSK1 &= ~PCINT12_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): {                                                                  *_PCMSK1 &= ~PCINT13_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): {                                                                  *_PCMSK1 &= ~PCINT14_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT15): {                                                                  *_PCMSK1 &= ~PCINT15_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): {                                                                  *_PCMSK2 &= ~PCINT16_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): {                                                                  *_PCMSK2 &= ~PCINT17_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): {                                                                  *_PCMSK2 &= ~PCINT18_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): {                                                                  *_PCMSK2 &= ~PCINT19_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): {                                                                  *_PCMSK2 &= ~PCINT20_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): {                                                                  *_PCMSK2 &= ~PCINT21_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): {                                                                  *_PCMSK2 &= ~PCINT22_bm; } break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): {                                                                  *_PCMSK2 &= ~PCINT23_bm; } break;
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

void ExternalInterruptController::ISR_onEint2Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT2)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT2)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint3Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT3)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT3)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint4Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT4)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT4)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint5Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT5)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT5)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint6Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT6)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT6)]->onExternalEventCallback();
  }
}

void ExternalInterruptController::ISR_onEint7Event()
{
  if(_external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT7)])
  {
    _external_interrupt_callback[toExtIntNum(ExternalInterrupt::EXTERNAL_INT7)]->onExternalEventCallback();
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
      ext_int_num <= toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT15);
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

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* spectre */
