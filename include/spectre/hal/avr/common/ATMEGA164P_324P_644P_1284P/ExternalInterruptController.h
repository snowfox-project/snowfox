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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_EXTERNALINTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_EXTERNALINTERRUPTCONTROLLER_H_

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

namespace ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class ExternalInterrupt : uint8_t
{
  EXTERNAL_INT0    =  0,
  EXTERNAL_INT1    =  1,
  EXTERNAL_INT2    =  2,
  PIN_CHANGE_INT0  =  3,
  PIN_CHANGE_INT1  =  4,
  PIN_CHANGE_INT2  =  5,
  PIN_CHANGE_INT3  =  6,
  PIN_CHANGE_INT4  =  7,
  PIN_CHANGE_INT5  =  8,
  PIN_CHANGE_INT6  =  9,
  PIN_CHANGE_INT7  = 10,
  PIN_CHANGE_INT8  = 11,
  PIN_CHANGE_INT9  = 12,
  PIN_CHANGE_INT10 = 13,
  PIN_CHANGE_INT11 = 14,
  PIN_CHANGE_INT12 = 15,
  PIN_CHANGE_INT13 = 16,
  PIN_CHANGE_INT14 = 17,
  PIN_CHANGE_INT15 = 18,
  PIN_CHANGE_INT16 = 19,
  PIN_CHANGE_INT17 = 20,
  PIN_CHANGE_INT18 = 21,
  PIN_CHANGE_INT19 = 22,
  PIN_CHANGE_INT20 = 23,
  PIN_CHANGE_INT21 = 24,
  PIN_CHANGE_INT22 = 25,
  PIN_CHANGE_INT23 = 26,
  PIN_CHANGE_INT24 = 27,
  PIN_CHANGE_INT25 = 28,
  PIN_CHANGE_INT26 = 29,
  PIN_CHANGE_INT27 = 30,
  PIN_CHANGE_INT28 = 31,
  PIN_CHANGE_INT29 = 32,
  PIN_CHANGE_INT30 = 33,
  PIN_CHANGE_INT31 = 34
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
                                       volatile uint8_t            * pcmsk0,
                                       volatile uint8_t            * pcmsk1,
                                       volatile uint8_t            * pcmsk2,
                                       volatile uint8_t            * pcmsk3,
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
  void ISR_onPinChange0Event();
  void ISR_onPinChange1Event();
  void ISR_onPinChange2Event();
  void ISR_onPinChange3Event();


private:

  static uint8_t constexpr NUM_EXTERNAL_INTERRUPTS = 35;


  volatile uint8_t                     * _EICRA,
                                       * _PCMSK0,
                                       * _PCMSK1,
                                       * _PCMSK2,
                                       * _PCMSK3;
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

class PinChange0_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           PinChange0_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~PinChange0_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onPinChange0Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class PinChange1_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           PinChange1_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~PinChange1_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onPinChange1Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class PinChange2_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           PinChange2_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~PinChange2_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onPinChange2Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class PinChange3_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           PinChange3_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~PinChange3_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onPinChange3Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA164P_324P_644P_1284P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_EXTERNALINTERRUPTCONTROLLER_H_ */
