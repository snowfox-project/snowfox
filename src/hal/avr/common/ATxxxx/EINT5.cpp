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

#include <spectre/hal/avr/common/ATxxxx/EINT5.h>

#if   defined(MCU_TYPE_atmega328p)
  #include <spectre/hal/avr/ATMEGA328P/InterruptController.h>
#elif defined(MCU_TYPE_at90can32)
  #include <spectre/hal/avr/AT90CAN32/InterruptController.h>
#elif defined(MCU_TYPE_at90can64)
  #include <spectre/hal/avr/AT90CAN64/InterruptController.h>
#elif defined(MCU_TYPE_at90can128)
  #include <spectre/hal/avr/AT90CAN128/InterruptController.h>
#elif defined(MCU_TYPE_atmega640)
  #include <spectre/hal/avr/AT90CAN640/InterruptController.h>
#elif defined(MCU_TYPE_atmega1280)
  #include <spectre/hal/avr/AT90CAN1280/InterruptController.h>
#elif defined(MCU_TYPE_atmega2560)
  #include <spectre/hal/avr/AT90CAN2560/InterruptController.h>
#else
  #include <spectre/hal/interface/interrupt/InterruptController.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EICRA */
#define ISC51_bm (1<<3)
#define ISC50_bm (1<<2)

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

#if   defined(MCU_TYPE_atmega328p)
  static uint8_t const INT_NUM = ATMEGA328P::toIntNum         (ATMEGA328P::Interrupt::EXTERNAL_INT5);
#elif defined(MCU_TYPE_at90can32)
  static uint8_t const INT_NUM = AT90CAN32_64_128::toIntNum   (AT90CAN32::Interrupt::EXTERNAL_INT5 );
#elif defined(MCU_TYPE_at90can64)
  static uint8_t const INT_NUM = AT90CAN32_64_128::toIntNum   (AT90CAN64::Interrupt::EXTERNAL_INT5 );
#elif defined(MCU_TYPE_at90can128)
  static uint8_t const INT_NUM = AT90CAN32_64_128::toIntNum   (AT90CAN128::Interrupt::EXTERNAL_INT5);
#elif defined(MCU_TYPE_atmega640)
  static uint8_t const INT_NUM = ATMEGA640_1280_2560::toIntNum(ATMEGA640::Interrupt::EXTERNAL_INT5 );
#elif defined(MCU_TYPE_atmega1280)
  static uint8_t const INT_NUM = ATMEGA640_1280_2560::toIntNum(ATMEGA1280::Interrupt::EXTERNAL_INT5);
#elif defined(MCU_TYPE_atmega2560)
  static uint8_t const INT_NUM = ATMEGA640_1280_2560::toIntNum(ATMEG2560::Interrupt::EXTERNAL_INT5 );
#else
  static uint8_t const INT_NUM = interface::InterruptController::INVALID_INT_NUM;
#endif

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

EINT5::EINT5(volatile uint8_t * eicrb, interface::InterruptController & int_ctrl)
: _EICRB                      (eicrb   ),
  _int_ctrl                   (int_ctrl),
  _external_interrupt_callback(0       )
{

}

EINT5::~EINT5()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void EINT5::setTriggerMode(interface::TriggerMode const trigger_mode)
{
  *_EICRB &= ~(ISC51_bm | ISC50_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *_EICRB |=            ISC50_bm; break;
  case interface::TriggerMode::Low        : *_EICRB |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */             break;
  case interface::TriggerMode::RisingEdge : *_EICRB |= ISC51_bm | ISC50_bm; break;
  case interface::TriggerMode::FallingEdge: *_EICRB |= ISC51_bm;            break;
  }
}

void EINT5::enable()
{
  _int_ctrl.enableInterrupt(INT_NUM);
}

void EINT5::disable()
{
  _int_ctrl.disableInterrupt(INT_NUM);
}

void EINT5::registerExternalInterruptCallback(interface::ExternalInterruptCallback * external_interrupt_callback)
{
  _external_interrupt_callback = external_interrupt_callback;
}

void EINT5::ISR_onExternalInterruptEvent()
{
  if(_external_interrupt_callback)
  {
    _external_interrupt_callback->onExternalEventCallback();
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
