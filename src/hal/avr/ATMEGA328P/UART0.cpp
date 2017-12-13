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

#include <spectre/hal/avr/ATMEGA328P/UART0.h>

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
#define UCPHA0_bm   (1<<1)
#define UCSZ01_bm   (1<<2)
#define UDORD0_bm   (1<<2)
#define USBS0_bm    (1<<3)
#define UPM00_bm    (1<<4)
#define UPM01_bm    (1<<5)
#define UMSEL00_bm  (1<<6)
#define UMSEL01_bm  (1<<7)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef void(*onTransmitCompleteCallback)(UART0 * _this);
typedef void(*onReceiveCompleteCallback )(UART0 * _this);

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

static UART0 * _this = 0;

static onTransmitCompleteCallback on_transmit_complete = 0;
static onReceiveCompleteCallback  on_receive_complete  = 0;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART0::UART0(volatile uint8_t * UDR0, volatile uint8_t * UCSR0A, volatile uint8_t * UCSR0B, volatile uint8_t * UCSR0C, volatile uint16_t * UBRR0)
: _UDR0                   (UDR0  ),
  _UCSR0A                 (UCSR0A),
  _UCSR0B                 (UCSR0B),
  _UCSR0C                 (UCSR0C),
  _UBRR0                  (UBRR0 ),
  _uart_callback_interface(0     )
{
  _this = this;

  on_transmit_complete = &UART0::onTransmitCompleteFunc;
  on_receive_complete  = &UART0::onReceiveCompleteFunc;

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

void UART0::setBaudRate(eBaudRate const baud_rate)
{
  *_UCSR0A |= U2X0_bm;

  switch(baud_rate)
  {
  case B115200: *_UBRR0 = calcBaudRate(F_CPU, 115200);  break;
  default:                                              break;
  }
}

void UART0::setParity(eParity const parity)
{
  *_UCSR0C &= ~(UPM01_bm | UPM00_bm);

  switch(parity)
  {
  case None:                                    break;
  case Even:  *_UCSR0C |= UPM01_bm;             break;
  case Odd:   *_UCSR0C |= UPM01_bm | UPM00_bm;  break;
  default:                                      break;
  }
}

void UART0::setStopBit(eStopBit const stop_bit)
{
  *_UCSR0C &= ~USBS0_bm;

  switch(stop_bit)
  {
  case _1:                        break;
  case _2: *_UCSR0C |= USBS0_bm;  break;
  default:                        break;
  }
}

void UART0::registerUARTCallbackInterface(interface::UARTCallback * uart_callback_interface)
{
  _uart_callback_interface = uart_callback_interface;
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

uint16_t UART0::calcBaudRate(uint32_t const f_cpu, uint32_t const baud_rate)
{
  return (static_cast<uint16_t>(f_cpu/(8*baud_rate)) - 1);
}

void UART0::onTransmitCompleteFunc(UART0 * _this)
{
  _this->_uart_callback_interface->onTransmitCompleteCallback();
}

void UART0::onReceiveCompleteFunc(UART0 * _this)
{
  _this->_uart_callback_interface->onReceiveCompleteCallback();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

/**************************************************************************************
 * ISR
 **************************************************************************************/

using namespace spectre::hal::ATMEGA328P;

//ISR(USART_UDRE_vect)
//{
//  if(on_transmit_complete && _this) on_transmit_complete(_this);
//}
//
//ISR(USART_RX_vect)
//{
//  if(on_receive_complete && _this) on_receive_complete(_this);
//}
