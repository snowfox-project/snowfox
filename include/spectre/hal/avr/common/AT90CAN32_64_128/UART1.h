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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_64_128_UART1_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_64_128_UART1_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/uart/UART.h>
#include <spectre/hal/interface/uart/UARTAssembly.h>
#include <spectre/hal/interface/uart/UARTCallback.h>
#include <spectre/hal/interface/uart/UARTConfiguration.h>

#include <spectre/hal/interface/interrupt/InterruptCallback.h>
#include <spectre/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN32_64_128
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART1 : public interface::UART,
              public interface::UARTConfiguration,
              public interface::UARTAssembly
{

public:


           UART1(volatile uint8_t * udr1, volatile uint8_t * ucsr1a, volatile uint8_t * ucsr1b, volatile uint8_t * ucsr1c, volatile uint16_t * ubrr1, interface::InterruptController & int_ctrl, uint32_t const f_cpu);
  virtual ~UART1();


  /* UART Interface */

  virtual void transmit         (uint8_t  const    data) override;
  virtual void receive          (uint8_t         & data) override;


  /* UART Configuration Interface */

  virtual void enableTx         () override;
  virtual void enableRx         () override;
  virtual void disableTx        () override;
  virtual void disableRx        () override;

  virtual void setBaudRate      (interface::UartBaudRate const   baud_rate) override;
  virtual void setParity        (interface::UartParity   const   parity   ) override;
  virtual void setStopBit       (interface::UartStopBit  const   stop_bit ) override;


  /* UART Assembly */

  virtual void registerUARTCallback(interface::UARTCallback * uart_callback) override;


  /* Functions to be called upon execution of a interrupt service routine */

  void ISR_onTransmitRegisterEmpty();
  void ISR_onReceiveComplete      ();


private:

  volatile uint8_t  * _UDR1,
                    * _UCSR1A,
                    * _UCSR1B,
                    * _UCSR1C;
  volatile uint16_t * _UBRR1;

  interface::InterruptController       & _int_ctrl;
  interface::UARTCallback              * _uart_callback;
  uint32_t                       const   _f_cpu;


  static uint16_t calcBaudRate(uint32_t const f_cpu, uint32_t const baud_rate);

};

/**************************************************************************************/

class UART1_TransmitRegisterEmptyCallback : public interface::InterruptCallback
{

public:

           UART1_TransmitRegisterEmptyCallback(UART1 & uart1) : _uart1(uart1) { }
  virtual ~UART1_TransmitRegisterEmptyCallback() { }


  virtual void interruptServiceRoutine() override
  {
    _uart1.ISR_onTransmitRegisterEmpty();
  }

private:

  UART1 & _uart1;

};

/**************************************************************************************/

class UART1_ReceiveCompleteCallback : public interface::InterruptCallback
{

public:

           UART1_ReceiveCompleteCallback(UART1 & uart1) : _uart1(uart1) { }
  virtual ~UART1_ReceiveCompleteCallback() { }


  virtual void interruptServiceRoutine() override
  {
    _uart1.ISR_onReceiveComplete();
  }

private:

  UART1 & _uart1;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_64_128_UART1_H_ */
