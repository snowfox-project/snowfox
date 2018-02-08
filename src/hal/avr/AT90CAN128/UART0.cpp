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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/AT90CAN128/UART0.h>

#include <spectre/hal/avr/AT90CAN128/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* UXSR0A */
#define MPCM0_bm    (1<<0)
#define U2X0_bm     (1<<1)
#define UPE0_bm     (1<<2)
#define DOR0_bm     (1<<3)
#define FE0_bm      (1<<4)
#define UDRE0_bm    (1<<5)
#define TXC0_bm     (1<<6)
#define RXC0_bm     (1<<7)

/* UXSR0B */
#define TXB80_bm    (1<<0)
#define RXB80_bm    (1<<1)
#define UCSZ02_bm   (1<<2)
#define TXEN0_bm    (1<<3)
#define RXEN0_bm    (1<<4)
#define UDRIE0_bm   (1<<5)
#define TXCIE0_bm   (1<<6)
#define RXCIE0_bm   (1<<7)

/* UCSR0C */
#define UCPOL0_bm   (1<<0)
#define UCSZ00_bm   (1<<1)
#define UCSZ01_bm   (1<<2)
#define USBS0_bm    (1<<3)
#define UPM00_bm    (1<<4)
#define UPM01_bm    (1<<5)
#define UMSEL0_bm   (1<<6)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART0::UART0(volatile uint8_t * udr0, volatile uint8_t * ucsr0a, volatile uint8_t * ucsr0b, volatile uint8_t * ucsr0c, volatile uint16_t * ubrr0, interface::InterruptController & int_ctrl, uint32_t const f_cpu)
: _UDR0                   (udr0    ),
  _UCSR0A                 (ucsr0a  ),
  _UCSR0B                 (ucsr0b  ),
  _UCSR0C                 (ucsr0c  ),
  _UBRR0                  (ubrr0   ),
  _int_ctrl               (int_ctrl),
  _uart_callback_interface(0       ),
  _f_cpu                  (f_cpu   )
{
  enableTransmit();
  enableReceive ();
}

UART0::~UART0()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART0::transmit(uint8_t const data)
{
  *_UDR0 = data;
}

void UART0::receive(uint8_t & data)
{
  data = *_UDR0;
}

void UART0::setBaudRate(interface::UartBaudRate const baud_rate)
{
  *_UCSR0A |= U2X0_bm;

  switch(baud_rate)
  {
  case interface::UartBaudRate::B115200: *_UBRR0 = calcBaudRate(_f_cpu, 115200); break;
  }
}

void UART0::setParity(interface::UartParity const parity)
{
  *_UCSR0C &= ~(UPM01_bm | UPM00_bm);

  switch(parity)
  {
  case interface::UartParity::None:                                  break;
  case interface::UartParity::Even: *_UCSR0C |= UPM01_bm;            break;
  case interface::UartParity::Odd : *_UCSR0C |= UPM01_bm | UPM00_bm; break;
  }
}

void UART0::setStopBit(interface::UartStopBit const stop_bit)
{
  *_UCSR0C &= ~USBS0_bm;

  switch(stop_bit)
  {
  case interface::UartStopBit::_1:                       break;
  case interface::UartStopBit::_2: *_UCSR0C |= USBS0_bm; break;
  }
}

void UART0::enableInterrupt(interface::UartInt const uart_int)
{
  switch(uart_int)
  {
  case interface::UartInt::TxComplete: _int_ctrl.enableInterrupt(/* TODO */ 0); break;
  case interface::UartInt::RxComplete: _int_ctrl.enableInterrupt(/* TODO */ 0); break;
  }
}

void UART0::disableInterrupt(interface::UartInt const uart_int)
{
  switch(uart_int)
  {
  case interface::UartInt::TxComplete: _int_ctrl.disableInterrupt(/* TODO */ 0); break;
  case interface::UartInt::RxComplete: _int_ctrl.disableInterrupt(/* TODO */ 0); break;
  }
}

void UART0::registerUARTCallbackInterface(interface::UARTCallback * uart_callback_interface)
{
  _uart_callback_interface = uart_callback_interface;
}

void UART0::ISR_onTransmitComplete(void * arg)
{
  reinterpret_cast<UART0 *>(arg)->ISR_onTransmitComplete();
}

void UART0::ISR_onReceiveComplete (void * arg)
{
  reinterpret_cast<UART0 *>(arg)->ISR_onReceiveComplete();
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void UART0::enableTransmit()
{
  *_UCSR0B |= TXEN0_bm;
}

void UART0::enableReceive()
{
  *_UCSR0B |= RXEN0_bm;
}

void UART0::ISR_onTransmitComplete()
{
  if(_uart_callback_interface) _uart_callback_interface->onTransmitCompleteCallback();
}

void UART0::ISR_onReceiveComplete()
{
  if(_uart_callback_interface) _uart_callback_interface->onReceiveCompleteCallback();
}

uint16_t UART0::calcBaudRate(uint32_t const f_cpu, uint32_t const baud_rate)
{
  return (static_cast<uint16_t>(f_cpu/(8*baud_rate)) - 1);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */
