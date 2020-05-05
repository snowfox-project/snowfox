/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_UART2_H_
#define INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_UART2_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/uart/Uart.h>

#include <snowfox/hal/interface/interrupt/InterruptCallback.h>
#include <snowfox/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATxxxx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART2 : public interface::Uart
{

public:


           UART2(volatile uint8_t                     * udr2,
                 volatile uint8_t                     * ucsr2a,
                 volatile uint8_t                     * ucsr2b,
                 volatile uint8_t                     * ucsr2c,
                 volatile uint16_t                    * ubrr2,
                 interface::InterruptController       & int_ctrl,
                 uint32_t                       const   f_cpu);
  virtual ~UART2();


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

  volatile uint8_t  * _UDR2,
                    * _UCSR2A,
                    * _UCSR2B,
                    * _UCSR2C;
  volatile uint16_t * _UBRR2;

  interface::InterruptController         & _int_ctrl;
  uint32_t                         const   _f_cpu;
  interface::UART_onRxDoneCallback       * _on_rx_done_callback;
  interface::UART_onTxDoneCallback       * _on_tx_done_callback;

};

/**************************************************************************************/

class UART2_TransmitRegisterEmptyCallback : public interface::InterruptCallback
{

public:

           UART2_TransmitRegisterEmptyCallback(UART2 & uart2) : _uart2(uart2) { }
  virtual ~UART2_TransmitRegisterEmptyCallback() { }


  virtual void onInterrupt() override
  {
    _uart2.ISR_onTransmitRegisterEmpty();
  }

private:

  UART2 & _uart2;

};

/**************************************************************************************/

class UART2_ReceiveCompleteCallback : public interface::InterruptCallback
{

public:

           UART2_ReceiveCompleteCallback(UART2 & uart2) : _uart2(uart2) { }
  virtual ~UART2_ReceiveCompleteCallback() { }


  virtual void onInterrupt() override
  {
    _uart2.ISR_onReceiveComplete();
  }

private:

  UART2 & _uart2;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATxxxx */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_UART2_H_ */
