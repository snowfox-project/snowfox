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

#include <spectre/hal/avr/common/ATxxxx/EINT1.h>

#if   defined(MCU_TYPE_atmega328p)
  #include <spectre/hal/avr/ATMEGA328P/InterruptController.h>
#elif defined(MCU_TYPE_at90can32)
  #include <spectre/hal/avr/AT90CAN32/InterruptController.h>
#elif defined(MCU_TYPE_at90can64)
  #include <spectre/hal/avr/AT90CAN64/InterruptController.h>
#elif defined(MCU_TYPE_at90can128)
  #include <spectre/hal/avr/AT90CAN128/InterruptController.h>
#elif defined(MCU_TYPE_atmega164p)
  #include <spectre/hal/avr/ATMEGA164P/InterruptController.h>
#elif defined(MCU_TYPE_atmega324p)
  #include <spectre/hal/avr/ATMEGA324P/InterruptController.h>
#elif defined(MCU_TYPE_atmega644p)
  #include <spectre/hal/avr/ATMEGA644P/InterruptController.h>
#elif defined(MCU_TYPE_atmega1284p)
  #include <spectre/hal/avr/ATMEGA1284P/InterruptController.h>
#elif defined(MCU_TYPE_atmega640)
  #include <spectre/hal/avr/ATMEGA640/InterruptController.h>
#elif defined(MCU_TYPE_atmega1280)
  #include <spectre/hal/avr/ATMEGA1280/InterruptController.h>
#elif defined(MCU_TYPE_atmega2560)
  #include <spectre/hal/avr/ATMEGA2560/InterruptController.h>
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
#define ISC11_bm (1<<3)
#define ISC10_bm (1<<2)

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

#if   defined(MCU_TYPE_atmega328p)
  static uint8_t const INT_NUM = ATMEGA328P::toIntNum                 (ATMEGA328P::Interrupt::EXTERNAL_INT1 );
#elif defined(MCU_TYPE_at90can32)
  static uint8_t const INT_NUM = AT90CAN32_64_128::toIntNum           (AT90CAN32::Interrupt::EXTERNAL_INT1  );
#elif defined(MCU_TYPE_at90can64)
  static uint8_t const INT_NUM = AT90CAN32_64_128::toIntNum           (AT90CAN64::Interrupt::EXTERNAL_INT1  );
#elif defined(MCU_TYPE_at90can128)
  static uint8_t const INT_NUM = AT90CAN32_64_128::toIntNum           (AT90CAN128::Interrupt::EXTERNAL_INT1 );
#elif defined(MCU_TYPE_atmega164p)
  static uint8_t const INT_NUM = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA164P::Interrupt::EXTERNAL_INT1 );
#elif defined(MCU_TYPE_atmega324p)
  static uint8_t const INT_NUM = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA324P::Interrupt::EXTERNAL_INT1 );
#elif defined(MCU_TYPE_atmega644p)
  static uint8_t const INT_NUM = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA644P::Interrupt::EXTERNAL_INT1 );
#elif defined(MCU_TYPE_atmega1284p)
  static uint8_t const INT_NUM = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA1284P::Interrupt::EXTERNAL_INT1);
#elif defined(MCU_TYPE_atmega640)
  static uint8_t const INT_NUM = ATMEGA640_1280_2560::toIntNum        (ATMEGA640::Interrupt::EXTERNAL_INT1  );
#elif defined(MCU_TYPE_atmega1280)
  static uint8_t const INT_NUM = ATMEGA640_1280_2560::toIntNum        (ATMEGA1280::Interrupt::EXTERNAL_INT1 );
#elif defined(MCU_TYPE_atmega2560)
  static uint8_t const INT_NUM = ATMEGA640_1280_2560::toIntNum        (ATMEGA2560::Interrupt::EXTERNAL_INT1 );
#else
  static uint8_t const INT_NUM = interface::InterruptController::INVALID_INT_NUM;
#endif

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

EINT1::EINT1(volatile uint8_t * eicra, interface::InterruptController & int_ctrl)
: _EICRA                      (eicra   ),
  _int_ctrl                   (int_ctrl),
  _external_interrupt_callback(0       )
{

}

EINT1::~EINT1()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void EINT1::setTriggerMode(interface::TriggerMode const trigger_mode)
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

void EINT1::enable()
{
  _int_ctrl.enableInterrupt(INT_NUM);
}

void EINT1::disable()
{
  _int_ctrl.disableInterrupt(INT_NUM);
}

void EINT1::registerExternalInterruptCallback(interface::ExternalInterruptCallback * external_interrupt_callback)
{
  _external_interrupt_callback = external_interrupt_callback;
}

void EINT1::ISR_onExternalInterruptEvent()
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
