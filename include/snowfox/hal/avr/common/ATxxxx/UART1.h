/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_UART1_H_
#define INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_UART1_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/uart/Uart.h>

#include <snowfox/hal/interface/interrupt/InterruptCallback.h>
#include <snowfox/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART1 : public interface::Uart
{

public:


           UART1(volatile uint8_t                     * udr1,
                 volatile uint8_t                     * ucsr1a,
                 volatile uint8_t                     * ucsr1b,
                 volatile uint8_t                     * ucsr1c,
                 volatile uint16_t                    * ubrr1,
                 interface::InterruptController       & int_ctrl,
                 uint32_t                       const   f_cpu);
  virtual ~UART1();


  /* UART Control Interface */

  virtual void transmit         (uint8_t  const    data) override;
  virtual void receive          (uint8_t         & data) override;
  virtual void enableTx         (                      ) override;
  virtual void enableRx         (                      ) override;
  virtual void disableTx        (                      ) override;


  /* UART Configuration Interface */

  virtual bool setBaudRate      (interface::UartBaudRate const baud_rate) override;
  virtual bool setParity        (interface::UartParity   const parity   ) override;
  virtual bool setStopBit       (interface::UartStopBit  const stop_bit ) override;


  /* UART Assembly */

  virtual void register_onRxDoneCallback(interface::UART_onRxDoneCallback * on_rx_done_callback) override;
  virtual void register_onTxDoneCallback(interface::UART_onTxDoneCallback * on_tx_done_callback) override;


  /* Functions to be called upon execution of a interrupt service routine */

  void ISR_onTransmitRegisterEmpty();
  void ISR_onReceiveComplete      ();


private:

  volatile uint8_t  * _UDR1,
                    * _UCSR1A,
                    * _UCSR1B,
                    * _UCSR1C;
  volatile uint16_t * _UBRR1;

  interface::InterruptController         & _int_ctrl;
  uint32_t                         const   _f_cpu;
  interface::UART_onRxDoneCallback       * _on_rx_done_callback;
  interface::UART_onTxDoneCallback       * _on_tx_done_callback;

};

/**************************************************************************************/

class UART1_TransmitRegisterEmptyCallback : public interface::InterruptCallback
{

public:

           UART1_TransmitRegisterEmptyCallback(UART1 & uart1) : _uart1(uart1) { }
  virtual ~UART1_TransmitRegisterEmptyCallback() { }


  virtual void onInterrupt() override
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


  virtual void onInterrupt() override
  {
    _uart1.ISR_onReceiveComplete();
  }

private:

  UART1 & _uart1;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_UART1_H_ */
