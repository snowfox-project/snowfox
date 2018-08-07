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

#include <spectre/hal/avr/common/ATMEGA164P_324P_644P_1284P/ExternalInterruptController.h>

#include <spectre/hal/avr/common/ATMEGA164P_324P_644P_1284P/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EICRA */
#define ISC21_bm   (1<<5)
#define ISC20_bm   (1<<4)
#define ISC11_bm   (1<<3)
#define ISC10_bm   (1<<2)
#define ISC01_bm   (1<<1)
#define ISC00_bm   (1<<0)

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

/* PCMSK3 */
#define PCINT31_bm (1<<7)
#define PCINT30_bm (1<<6)
#define PCINT29_bm (1<<5)
#define PCINT28_bm (1<<4)
#define PCINT27_bm (1<<3)
#define PCINT26_bm (1<<2)
#define PCINT25_bm (1<<1)
#define PCINT24_bm (1<<0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

ExternalInterruptController::ExternalInterruptController(volatile uint8_t            * eicra,
                                                         volatile uint8_t            * pcmsk0,
                                                         volatile uint8_t            * pcmsk1,
                                                         volatile uint8_t            * pcmsk2,
                                                         volatile uint8_t            * pcmsk3,
                                                         interface::InterruptControl & int_ctrl)
: _EICRA   (eicra   ),
  _PCMSK0  (pcmsk0  ),
  _PCMSK1  (pcmsk1  ),
  _PCMSK2  (pcmsk2  ),
  _PCMSK3  (pcmsk3  ),
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
  case toExtIntNum(ExternalInterrupt::EINT0): setTriggerModeEint0(trigger_mode); break;
  case toExtIntNum(ExternalInterrupt::EINT1): setTriggerModeEint1(trigger_mode); break;
  case toExtIntNum(ExternalInterrupt::EINT2): setTriggerModeEint2(trigger_mode); break;
  default                                   : /* PCINT trigger mode is Any */    break;
  }
}

void ExternalInterruptController::enable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EINT0  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT1  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                         } break;
  case toExtIntNum(ExternalInterrupt::EINT2  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT2  ));                         } break;
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
  case toExtIntNum(ExternalInterrupt::PCINT24): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3)); *_PCMSK3 |= PCINT24_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT25): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3)); *_PCMSK3 |= PCINT25_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT26): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3)); *_PCMSK3 |= PCINT26_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT27): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3)); *_PCMSK3 |= PCINT27_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT28): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3)); *_PCMSK3 |= PCINT28_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT29): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3)); *_PCMSK3 |= PCINT29_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT30): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3)); *_PCMSK3 |= PCINT30_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT31): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::PIN_CHANGE_INT3)); *_PCMSK3 |= PCINT31_bm; } break;
  }
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EINT0  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT0  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT1  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT1  ));                          } break;
  case toExtIntNum(ExternalInterrupt::EINT2  ): { _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT2  ));                          } break;
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
  case toExtIntNum(ExternalInterrupt::PCINT24): {                                                                  *_PCMSK3 &= ~PCINT24_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT25): {                                                                  *_PCMSK3 &= ~PCINT25_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT26): {                                                                  *_PCMSK3 &= ~PCINT26_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT27): {                                                                  *_PCMSK3 &= ~PCINT27_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT28): {                                                                  *_PCMSK3 &= ~PCINT28_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT29): {                                                                  *_PCMSK3 &= ~PCINT29_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT30): {                                                                  *_PCMSK3 &= ~PCINT30_bm; } break;
  case toExtIntNum(ExternalInterrupt::PCINT31): {                                                                  *_PCMSK3 &= ~PCINT31_bm; } break;
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

void ExternalInterruptController::ISR_onPinChange3Event()
{
  for(uint8_t ext_int_num = toExtIntNum(ExternalInterrupt::PCINT24);
      ext_int_num <= toExtIntNum(ExternalInterrupt::PCINT31);
      ext_int_num++)
  {
    if(_external_interrupt_callback[ext_int_num])
    {
      _external_interrupt_callback[ext_int_num]->onExternalEventCallback();
    }
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void ExternalInterruptController::setTriggerModeEint0(interface::TriggerMode const trigger_mode)
{
  *_EICRA &= ~(ISC01_bm | ISC00_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *_EICRA |=            ISC00_bm; break;
  case interface::TriggerMode::Low        : *_EICRA |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */             break;
  case interface::TriggerMode::RisingEdge : *_EICRA |= ISC01_bm | ISC00_bm; break;
  case interface::TriggerMode::FallingEdge: *_EICRA |= ISC01_bm;            break;
  }
}

void ExternalInterruptController::setTriggerModeEint1(interface::TriggerMode const trigger_mode)
{
  *_EICRA &= ~(ISC11_bm | ISC10_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *_EICRA |=            ISC10_bm; break;
  case interface::TriggerMode::Low        : *_EICRA |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */             break;
  case interface::TriggerMode::RisingEdge : *_EICRA |= ISC11_bm | ISC10_bm; break;
  case interface::TriggerMode::FallingEdge: *_EICRA |= ISC11_bm;            break;
  }
}

void ExternalInterruptController::setTriggerModeEint2(interface::TriggerMode const trigger_mode)
{
  *_EICRA &= ~(ISC21_bm | ISC20_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *_EICRA |=            ISC20_bm; break;
  case interface::TriggerMode::Low        : *_EICRA |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */             break;
  case interface::TriggerMode::RisingEdge : *_EICRA |= ISC21_bm | ISC20_bm; break;
  case interface::TriggerMode::FallingEdge: *_EICRA |= ISC21_bm;            break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA164P_324P_644P_1284P */

} /* hal */

} /* spectre */
