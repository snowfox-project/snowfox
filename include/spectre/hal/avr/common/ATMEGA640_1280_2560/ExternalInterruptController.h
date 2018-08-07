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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_EXTERNALINTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_EXTERNALINTERRUPTCONTROLLER_H_

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

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class ExternalInterrupt : uint8_t
{
  EINT0   =  0,
  EINT1   =  1,
  EINT2   =  2,
  EINT3   =  3,
  EINT4   =  4,
  EINT5   =  5,
  EINT6   =  6,
  EINT7   =  7,
  EINT8   =  8,
  PCINT0  =  9,
  PCINT1  = 10,
  PCINT2  = 11,
  PCINT3  = 12,
  PCINT4  = 13,
  PCINT5  = 14,
  PCINT6  = 15,
  PCINT7  = 16,
  PCINT8  = 17,
  PCINT9  = 18,
  PCINT10 = 19,
  PCINT11 = 20,
  PCINT12 = 21,
  PCINT13 = 22,
  PCINT14 = 23,
  PCINT15 = 24,
  PCINT16 = 25,
  PCINT17 = 26,
  PCINT18 = 27,
  PCINT19 = 28,
  PCINT20 = 29,
  PCINT21 = 30,
  PCINT22 = 31,
  PCINT23 = 32,
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
                                       volatile uint8_t            * pcmsk1,
                                       volatile uint8_t            * pcmsk2,
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
  void ISR_onEint4Event     ();
  void ISR_onEint5Event     ();
  void ISR_onEint6Event     ();
  void ISR_onEint7Event     ();
  void ISR_onPinChange0Event();
  void ISR_onPinChange1Event();
  void ISR_onPinChange2Event();


private:

  static uint8_t constexpr NUM_EXTERNAL_INTERRUPTS = 33;


  volatile uint8_t                     * _EICRA,
                                       * _EICRB,
                                       * _PCMSK0,
                                       * _PCMSK1,
                                       * _PCMSK2;
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

class EINT4_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           EINT4_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~EINT4_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onEint4Event(); }

private:
  ExternalInterruptController & _ext_int_ctrl;
};

/**************************************************************************************/

class EINT5_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:
           EINT5_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~EINT5_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onEint5Event(); }

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

class EINT7_ExternalInterruptEventCallback : public interface::InterruptCallback
{
public:

           EINT7_ExternalInterruptEventCallback(ExternalInterruptController & ext_int_ctrl) : _ext_int_ctrl(ext_int_ctrl) { }
  virtual ~EINT7_ExternalInterruptEventCallback() { }
  virtual void interruptServiceRoutine() override { _ext_int_ctrl.ISR_onEint7Event(); }

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

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_EXTERNALINTERRUPTCONTROLLER_H_ */
