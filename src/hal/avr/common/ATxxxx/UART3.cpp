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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/avr/common/ATxxxx/UART3.h>

#include <snowfox/hal/avr/common/ATxxxx/util/UartUtil.h>

#if   defined(MCU_TYPE_atmega328p)
  #include <snowfox/hal/avr/ATMEGA328P/InterruptController.h>
#elif defined(MCU_TYPE_at90can32)
  #include <snowfox/hal/avr/AT90CAN32/InterruptController.h>
#elif defined(MCU_TYPE_at90can64)
  #include <snowfox/hal/avr/AT90CAN64/InterruptController.h>
#elif defined(MCU_TYPE_at90can128)
  #include <snowfox/hal/avr/AT90CAN128/InterruptController.h>
#elif defined(MCU_TYPE_atmega164p)
  #include <snowfox/hal/avr/ATMEGA164P/InterruptController.h>
#elif defined(MCU_TYPE_atmega324p)
  #include <snowfox/hal/avr/ATMEGA324P/InterruptController.h>
#elif defined(MCU_TYPE_atmega644p)
  #include <snowfox/hal/avr/ATMEGA644P/InterruptController.h>
#elif defined(MCU_TYPE_atmega1284p)
  #include <snowfox/hal/avr/ATMEGA1284P/InterruptController.h>
#elif defined(MCU_TYPE_atmega640)
  #include <snowfox/hal/avr/ATMEGA640/InterruptController.h>
#elif defined(MCU_TYPE_atmega1280)
  #include <snowfox/hal/avr/ATMEGA1280/InterruptController.h>
#elif defined(MCU_TYPE_atmega2560)
  #include <snowfox/hal/avr/ATMEGA2560/InterruptController.h>
#elif defined(MCU_TYPE_atmega16u4)
  #include <snowfox/hal/avr/ATMEGA16U4/InterruptController.h>
#elif defined(MCU_TYPE_atmega32u4)
  #include <snowfox/hal/avr/ATMEGA32U4/InterruptController.h>
#else
  #include <snowfox/hal/interface/interrupt/InterruptController.h>
#endif

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
 * DEFINES
 **************************************************************************************/

/* UCSR3A */
#define RXC3_bm     (1<<7)
#define TXC3_bm     (1<<6)
#define UDRE3_bm    (1<<5)
#define FE3_bm      (1<<4)
#define DOR3_bm     (1<<3)
#define UPE3_bm     (1<<2)
#define U2X3_bm     (1<<1)
#define MPCM3_bm    (1<<0)

/* UCSR3B */
#define RXCIE3_bm   (1<<7)
#define TXCIE3_bm   (1<<6)
#define UDRIE3_bm   (1<<5)
#define RXEN3_bm    (1<<4)
#define TXEN3_bm    (1<<3)
#define UCSZ32_bm   (1<<2)
#define RXB83_bm    (1<<1)
#define TXB83_bm    (1<<0)

/* UCSR3C */
#define UMSEL31_bm  (1<<7)
#define UMSEL30_bm  (1<<6)
#define UPM31_bm    (1<<5)
#define UPM30_bm    (1<<4)
#define USBS3_bm    (1<<3)
#define UCSZ31_bm   (1<<2)
#define UCSZ30_bm   (1<<1)
#define UCPOL3_bm   (1<<0)

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

#if   defined(MCU_TYPE_atmega328p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_at90can32)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_at90can64)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_at90can128)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_atmega164p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_atmega324p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_atmega644p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_atmega1284p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_atmega640)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum(ATMEGA640::Interrupt::USART3_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum(ATMEGA640::Interrupt::USART3_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_atmega1280)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum(ATMEGA1280::Interrupt::USART3_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum(ATMEGA1280::Interrupt::USART3_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega2560)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum(ATMEGA2560::Interrupt::USART3_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum(ATMEGA2560::Interrupt::USART3_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega16u4)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_atmega32u4)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#else
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#endif

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART3::UART3(volatile uint8_t * udr3, volatile uint8_t * ucsr3a, volatile uint8_t * ucsr3b, volatile uint8_t * ucsr3c, volatile uint16_t * ubrr3, interface::InterruptController & int_ctrl, uint32_t const f_cpu)
: _UDR3               (udr3    ),
  _UCSR3A             (ucsr3a  ),
  _UCSR3B             (ucsr3b  ),
  _UCSR3C             (ucsr3c  ),
  _UBRR3              (ubrr3   ),
  _int_ctrl           (int_ctrl),
  _f_cpu              (f_cpu   ),
  _on_rx_done_callback(0       ),
  _on_tx_done_callback(0       )
{

}

UART3::~UART3()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART3::transmit(uint8_t const data)
{
  *_UDR3 = data;
}

void UART3::receive(uint8_t & data)
{
  data = *_UDR3;
}

void UART3::enableTx()
{
  *_UCSR3B |= TXEN3_bm;
  _int_ctrl.enableInterrupt(INT_NUM_UART_DATA_REGISTER_EMPTY);
}

void UART3::enableRx()
{
  _int_ctrl.enableInterrupt(INT_NUM_RECEIVE_COMPLETE);
  *_UCSR3B |= RXEN3_bm;
}

void UART3::disableTx()
{
  _int_ctrl.disableInterrupt(INT_NUM_UART_DATA_REGISTER_EMPTY);
  *_UCSR3B &= ~TXEN3_bm;
}

bool UART3::setBaudRate(interface::UartBaudRate const baud_rate)
{
  *_UCSR3A |= U2X3_bm;

  switch(baud_rate)
  {
  case interface::UartBaudRate::B115200: *_UBRR3 = calcUartBaudRate(_f_cpu, 115200); return true;  break;
  default:                                                                           return false; break;
  }
}

bool UART3::setParity(interface::UartParity const parity)
{
  *_UCSR3C &= ~(UPM31_bm | UPM30_bm);

  switch(parity)
  {
  case interface::UartParity::None:                                  return true;  break;
  case interface::UartParity::Even: *_UCSR3C |= UPM31_bm;            return true;  break;
  case interface::UartParity::Odd:  *_UCSR3C |= UPM31_bm | UPM30_bm; return true;  break;
  default:                                                           return false; break;
  }
}

bool UART3::setStopBit(interface::UartStopBit const stop_bit)
{
  *_UCSR3C &= ~USBS3_bm;

  switch(stop_bit)
  {
  case interface::UartStopBit::_1:                       return true;  break;
  case interface::UartStopBit::_2: *_UCSR3C |= USBS3_bm; return true;  break;
  default:                                               return false; break;
  }
}

void UART3::register_onRxDoneCallback(interface::UART_onRxDoneCallback * on_rx_done_callback)
{
  _on_rx_done_callback = on_rx_done_callback;
}

void UART3::register_onTxDoneCallback(interface::UART_onTxDoneCallback * on_tx_done_callback)
{
  _on_tx_done_callback = on_tx_done_callback;
}

void UART3::ISR_onTransmitRegisterEmpty()
{
  if(_on_tx_done_callback) _on_tx_done_callback->onTxDone();
}

void UART3::ISR_onReceiveComplete()
{
  if(_on_rx_done_callback) _on_rx_done_callback->onRxDone();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* snowfox */
