/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

#ifndef ATMEGA328P_UART_H_
#define ATMEGA328P_UART_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/uart/UART.h>
#include <spectre/hal/interface/uart/UARTAssembly.h>
#include <spectre/hal/interface/uart/UARTCallback.h>
#include <spectre/hal/interface/uart/UARTConfiguration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART0 : public interface::UART,
              public interface::UARTConfiguration,
              public interface::UARTAssembly
{

public:

           UART0(volatile uint8_t * UDR0, volatile uint8_t * UCSR0A, volatile uint8_t * UCSR0B, volatile uint8_t * UCSR0C, volatile uint16_t * UBRR0);
  virtual ~UART0();


  /* UART Interface */

  virtual void transmit       (uint8_t const   data) override;
  virtual void receive        (uint8_t       & data) override;
  
  /* UART Configuration Interface */

  virtual void setBaudRate  (eBaudRate const    baud_rate) override;
  virtual void setParity    (eParity   const    parity   ) override;
  virtual void setStopBit   (eStopBit  const    stop_bit ) override;


  /* UART Assembly */

  virtual void registerUARTCallbackInterface(interface::UARTCallback * uart_callback_interface) override;

private:

  volatile uint8_t  * _UDR0,
                    * _UCSR0A,
                    * _UCSR0B,
                    * _UCSR0C;
  volatile uint16_t * _UBRR0;

  interface::UARTCallback * _uart_callback_interface;

  /* Member functions */

         void     enableTransmit();
         void     enableReceive ();

  static uint16_t calcBaudRate  (uint32_t const f_cpu, uint32_t const baud_rate);

  /* ISR Functions */

  static void onTransmitCompleteFunc(UART0 * _this);
  static void onReceiveCompleteFunc (UART0 * _this);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

#endif /* ATMEGA328P_UART_H_*/
