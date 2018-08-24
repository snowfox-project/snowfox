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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA16U4_32U4_EXTERNALINTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA16U4_32U4_EXTERNALINTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/extint/ExternalInterruptAssembly.h>
#include <spectre/hal/interface/extint/ExternalInterruptCallback.h>
#include <spectre/hal/interface/extint/ExternalInterruptConfiguration.h>

#include <spectre/hal/interface/interrupt/InterruptControl.h>
#include <spectre/hal/interface/interrupt/InterruptCallback.h>

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
 * TYPEDEF
 **************************************************************************************/

enum class ExternalInterrupt : uint8_t
{
  EXTERNAL_INT0    =  0,
  EXTERNAL_INT1    =  1,
  EXTERNAL_INT2    =  2,
  EXTERNAL_INT3    =  3,
  EXTERNAL_INT6    =  4,
  PIN_CHANGE_INT0  =  5,
  PIN_CHANGE_INT1  =  6,
  PIN_CHANGE_INT2  =  7,
  PIN_CHANGE_INT3  =  8,
  PIN_CHANGE_INT4  =  9,
  PIN_CHANGE_INT5  = 10,
  PIN_CHANGE_INT6  = 11,
  PIN_CHANGE_INT7  = 12
};

/**************************************************************************************
 * CONSTEXPR FUNCTIONS
 **************************************************************************************/

constexpr uint8_t toExtIntNum(ExternalInterrupt const external_interrupt)
{
  return static_cast<uint8_t>(external_interrupt);
}

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ExternalInterruptController : public interface::ExternalInterruptConfiguration,
                                    public interface::ExternalInterruptAssembly
{

public:

           ExternalInterruptController(volatile uint8_t            * eicra,
                                       volatile uint8_t            * eicrb,
                                       volatile uint8_t            * pcmsk0,
                                       interface::InterruptControl & int_ctrl);
  virtual ~ExternalInterruptController();


  /* External Interrupt Configuration */

  virtual void setTriggerMode(uint8_t const ext_int_num, interface::TriggerMode const trigger_mode) override;
  virtual void enable        (uint8_t const ext_int_num                                           ) override;
  virtual void disable       (uint8_t const ext_int_num                                           ) override;


  /* External Interrupt Assembly */

  virtual void registerExternalInterruptCallback(uint8_t const ext_int_num, interface::ExternalInterruptCallback * external_interrupt_callback) override;


  /* Functions to be called upon execution of a interrupt service routine */

  void ISR_onEint0Event     ();
  void ISR_onEint1Event     ();
  void ISR_onEint2Event     ();
  void ISR_onEint3Event     ();
  void ISR_onEint6Event     ();
  void ISR_onPinChange0Event();


private:

  static uint8_t constexpr NUM_EXTERNAL_INTERRUPTS = 12;


  volatile uint8_t                     * _EICRA,
                                       * _EICRB,
                                       * _PCMSK0;
  interface::InterruptControl          & _int_ctrl;
  interface::ExternalInterruptCallback * _external_interrupt_callback[NUM_EXTERNAL_INTERRUPTS];

};

/**************************************************************************************/

class EINT0_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           EINT0_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~EINT0_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onEint0Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class EINT1_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           EINT1_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~EINT1_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onEint1Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class EINT2_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           EINT2_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~EINT2_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onEint2Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class EINT3_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           EINT3_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~EINT3_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onEint3Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class EINT6_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           EINT6_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~EINT6_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onEint6Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class PinChange0_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           PinChange0_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~PinChange0_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onPinChange0Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA16U4_32U4_EXTERNALINTERRUPTCONTROLLER_H_ */
