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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART0_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART0_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/uart/UartControl.h>
#include <spectre/hal/interface/uart/UartAssembly.h>
#include <spectre/hal/interface/uart/UartConfiguration.h>

#include <spectre/hal/interface/interrupt/InterruptCallback.h>
#include <spectre/hal/interface/interrupt/InterruptController.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class UART0 : public interface::UartControl,
              public interface::UartConfiguration,
              public interface::UartAssembly
{

public:


           UART0(volatile uint8_t                     * udr0,
                 volatile uint8_t                     * ucsr0a,
                 volatile uint8_t                     * ucsr0b,
                 volatile uint8_t                     * ucsr0c,
                 volatile uint16_t                    * ubrr0,
                 interface::InterruptController       & int_ctrl,
                 uint32_t                       const   f_cpu);
  virtual ~UART0();


  /* UART Control Interface */

  virtual void transmit         (uint8_t  const    data) override;
  virtual void receive          (uint8_t         & data) override;
  virtual void enableTx         (                      ) override;
  virtual void enableRx         (                      ) override;
  virtual void disableTx        (                      ) override;


  /* UART Configuration Interface */

  virtual void setBaudRate      (interface::UartBaudRate const   baud_rate) override;
  virtual void setParity        (interface::UartParity   const   parity   ) override;
  virtual void setStopBit       (interface::UartStopBit  const   stop_bit ) override;


  /* UART Assembly */

  virtual void register_onRxDoneCallback(interface::UART_onRxDoneCallback * on_rx_done_callback) override;
  virtual void register_onTxDoneCallback(interface::UART_onTxDoneCallback * on_tx_done_callback) override;

  /* Functions to be called upon execution of a interrupt service routine */

  void ISR_onTransmitRegisterEmpty();
  void ISR_onReceiveComplete      ();

private:

  volatile uint8_t  * _UDR0,
                    * _UCSR0A,
                    * _UCSR0B,
                    * _UCSR0C;
  volatile uint16_t * _UBRR0;

  interface::InterruptController         & _int_ctrl;
  uint32_t                         const   _f_cpu;
  interface::UART_onRxDoneCallback       * _on_rx_done_callback;
  interface::UART_onTxDoneCallback       * _on_tx_done_callback;

};

/**************************************************************************************/

class UART0_TransmitRegisterEmptyCallback : public interface::InterruptCallback
{

public:

           UART0_TransmitRegisterEmptyCallback(UART0 & uart0) : _uart0(uart0) { }
  virtual ~UART0_TransmitRegisterEmptyCallback() { }


  virtual void interruptServiceRoutine() override
  {
    _uart0.ISR_onTransmitRegisterEmpty();
  }

private:

  UART0 & _uart0;

};

/**************************************************************************************/

class UART0_ReceiveCompleteCallback : public interface::InterruptCallback
{

public:

           UART0_ReceiveCompleteCallback(UART0 & uart0) : _uart0(uart0) { }
  virtual ~UART0_ReceiveCompleteCallback() { }


  virtual void interruptServiceRoutine() override
  {
    _uart0.ISR_onReceiveComplete();
  }

private:

  UART0 & _uart0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART0_H_ */
