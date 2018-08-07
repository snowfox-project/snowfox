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
  EINT0   =  0,
  EINT1   =  1,
  EINT2   =  2,
  PCINT0  =  3,
  PCINT1  =  4,
  PCINT2  =  5,
  PCINT3  =  6,
  PCINT4  =  7,
  PCINT5  =  8,
  PCINT6  =  9,
  PCINT7  = 10,
  PCINT8  = 11,
  PCINT9  = 12,
  PCINT10 = 13,
  PCINT11 = 14,
  PCINT12 = 15,
  PCINT13 = 16,
  PCINT14 = 17,
  PCINT15 = 18,
  PCINT16 = 19,
  PCINT17 = 20,
  PCINT18 = 21,
  PCINT19 = 22,
  PCINT20 = 23,
  PCINT21 = 24,
  PCINT22 = 25,
  PCINT23 = 26,
  PCINT24 = 27,
  PCINT25 = 28,
  PCINT26 = 29,
  PCINT27 = 30,
  PCINT28 = 31,
  PCINT29 = 32,
  PCINT30 = 33,
  PCINT31 = 34
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


  void setTriggerModeEint0(interface::TriggerMode const trigger_mode);
  void setTriggerModeEint1(interface::TriggerMode const trigger_mode);
  void setTriggerModeEint2(interface::TriggerMode const trigger_mode);

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
