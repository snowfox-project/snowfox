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

#include <spectre/hal/avr/AT90CAN128/UART1.h>

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

/* UXSR1A */
#define MPCM1_bm    (1<<0)
#define U2X1_bm     (1<<1)
#define UPE1_bm     (1<<2)
#define DOR1_bm     (1<<3)
#define FE1_bm      (1<<4)
#define UDRE1_bm    (1<<5)
#define TXC1_bm     (1<<6)
#define RXC1_bm     (1<<7)

/* UXSR1B */
#define TXB81_bm    (1<<0)
#define RXB81_bm    (1<<1)
#define UCSZ12_bm   (1<<2)
#define TXEN1_bm    (1<<3)
#define RXEN1_bm    (1<<4)
#define UDRIE1_bm   (1<<5)
#define TXCIE1_bm   (1<<6)
#define RXCIE1_bm   (1<<7)

/* UCSR1C */
#define UCPOL1_bm   (1<<0)
#define UCSZ10_bm   (1<<1)
#define UCSZ11_bm   (1<<2)
#define USBS1_bm    (1<<3)
#define UPM10_bm    (1<<4)
#define UPM11_bm    (1<<5)
#define UMSEL1_bm   (1<<6)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART1::UART1(volatile uint8_t * udr1, volatile uint8_t * ucsr1a, volatile uint8_t * ucsr1b, volatile uint8_t * ucsr1c, volatile uint16_t * ubrr1, interface::InterruptController & int_ctrl, uint32_t const f_cpu)
: _UDR1                   (udr1    ),
  _UCSR1A                 (ucsr1a  ),
  _UCSR1B                 (ucsr1b  ),
  _UCSR1C                 (ucsr1c  ),
  _UBRR1                  (ubrr1   ),
  _int_ctrl               (int_ctrl),
  _uart_callback_interface(0       ),
  _f_cpu                  (f_cpu   )
{

}

UART1::~UART1()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART1::transmit(uint8_t const data)
{
  *_UDR1 = data;
}

void UART1::receive(uint8_t & data)
{
  data = *_UDR1;
}

void UART1::enableTx()
{
  *_UCSR1B |= TXEN1_bm;
  _int_ctrl.enableInterrupt(toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY));
}

void UART1::enableRx()
{
  _int_ctrl.enableInterrupt(toIntNum(Interrupt::USART1_RECEIVE_COMPLETE));
  *_UCSR1B |= RXEN1_bm;
}

void UART1::disableTx()
{
  _int_ctrl.disableInterrupt(toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY));
  *_UCSR1B &= ~TXEN1_bm;
}

void UART1::disableRx()
{
  *_UCSR1B &= ~RXEN1_bm;
  _int_ctrl.disableInterrupt(toIntNum(Interrupt::USART1_RECEIVE_COMPLETE));
}

void UART1::setBaudRate(interface::UartBaudRate const baud_rate)
{
  *_UCSR1A |= U2X1_bm;

  switch(baud_rate)
  {
  case interface::UartBaudRate::B115200: *_UBRR1 = calcBaudRate(_f_cpu, 115200); break;
  }
}

void UART1::setParity(interface::UartParity const parity)
{
  *_UCSR1C &= ~(UPM11_bm | UPM10_bm);

  switch(parity)
  {
  case interface::UartParity::None:                                  break;
  case interface::UartParity::Even: *_UCSR1C |= UPM11_bm;            break;
  case interface::UartParity::Odd : *_UCSR1C |= UPM11_bm | UPM10_bm; break;
  }
}

void UART1::setStopBit(interface::UartStopBit const stop_bit)
{
  *_UCSR1C &= ~USBS1_bm;

  switch(stop_bit)
  {
  case interface::UartStopBit::_1:                       break;
  case interface::UartStopBit::_2: *_UCSR1C |= USBS1_bm; break;
  }
}

void UART1::registerUARTCallbackInterface(interface::UARTCallback * uart_callback_interface)
{
  _uart_callback_interface = uart_callback_interface;
}

void UART1::ISR_onTransmitRegisterEmpty()
{
  if(_uart_callback_interface) _uart_callback_interface->onTransmitRegisterEmptyCallback();
}

void UART1::ISR_onReceiveComplete()
{
  if(_uart_callback_interface)
  {
    uint8_t data = 0;
    receive(data);
    _uart_callback_interface->onReceiveCompleteCallback(data);
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

uint16_t UART1::calcBaudRate(uint32_t const f_cpu, uint32_t const baud_rate)
{
  return (static_cast<uint16_t>(f_cpu/(8*baud_rate)) - 1);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */
