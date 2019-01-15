/**
 * Spectre is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART3_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART3_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/uart/Uart.h>

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

class UART3 : public interface::Uart
{

public:


           UART3(volatile uint8_t                     * udr3,
                 volatile uint8_t                     * ucsr3a,
                 volatile uint8_t                     * ucsr3b,
                 volatile uint8_t                     * ucsr3c,
                 volatile uint16_t                    * ubrr3,
                 interface::InterruptController       & int_ctrl,
                 uint32_t                       const   f_cpu);
  virtual ~UART3();


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

  volatile uint8_t  * _UDR3,
                    * _UCSR3A,
                    * _UCSR3B,
                    * _UCSR3C;
  volatile uint16_t * _UBRR3;

  interface::InterruptController         & _int_ctrl;
  uint32_t                         const   _f_cpu;
  interface::UART_onRxDoneCallback       * _on_rx_done_callback;
  interface::UART_onTxDoneCallback       * _on_tx_done_callback;

};

/**************************************************************************************/

class UART3_TransmitRegisterEmptyCallback : public interface::InterruptCallback
{

public:

           UART3_TransmitRegisterEmptyCallback(UART3 & uart3) : _uart3(uart3) { }
  virtual ~UART3_TransmitRegisterEmptyCallback() { }


  virtual void onInterrupt() override
  {
    _uart3.ISR_onTransmitRegisterEmpty();
  }

private:

  UART3 & _uart3;

};

/**************************************************************************************/

class UART3_ReceiveCompleteCallback : public interface::InterruptCallback
{

public:

           UART3_ReceiveCompleteCallback(UART3 & uart3) : _uart3(uart3) { }
  virtual ~UART3_ReceiveCompleteCallback() { }


  virtual void onInterrupt() override
  {
    _uart3.ISR_onReceiveComplete();
  }

private:

  UART3 & _uart3;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_UART3_H_ */
