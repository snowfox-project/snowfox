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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/UART2.h>

#include <spectre/hal/avr/common/ATxxxx/util/UartUtil.h>

#if   defined(MCU_TYPE_atmega328p)
  #include <spectre/hal/avr/ATMEGA328P/InterruptController.h>
#elif defined(MCU_TYPE_at90can32)
  #include <spectre/hal/avr/AT90CAN32/InterruptController.h>
#elif defined(MCU_TYPE_at90can64)
  #include <spectre/hal/avr/AT90CAN64/InterruptController.h>
#elif defined(MCU_TYPE_at90can128)
  #include <spectre/hal/avr/AT90CAN128/InterruptController.h>
#elif defined(MCU_TYPE_atmega164p)
  #include <spectre/hal/avr/ATMEGA164P/InterruptController.h>
#elif defined(MCU_TYPE_atmega324p)
  #include <spectre/hal/avr/ATMEGA324P/InterruptController.h>
#elif defined(MCU_TYPE_atmega644p)
  #include <spectre/hal/avr/ATMEGA644P/InterruptController.h>
#elif defined(MCU_TYPE_atmega1284p)
  #include <spectre/hal/avr/ATMEGA1284P/InterruptController.h>
#elif defined(MCU_TYPE_atmega640)
  #include <spectre/hal/avr/ATMEGA640/InterruptController.h>
#elif defined(MCU_TYPE_atmega1280)
  #include <spectre/hal/avr/ATMEGA1280/InterruptController.h>
#elif defined(MCU_TYPE_atmega2560)
  #include <spectre/hal/avr/ATMEGA2560/InterruptController.h>
#else
  #include <spectre/hal/interface/interrupt/InterruptController.h>
#endif

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
 * DEFINES
 **************************************************************************************/

/* UCSR2A */
#define RXC2_bm     (1<<7)
#define TXC2_bm     (1<<6)
#define UDRE2_bm    (1<<5)
#define FE2_bm      (1<<4)
#define DOR2_bm     (1<<3)
#define UPE2_bm     (1<<2)
#define U2X2_bm     (1<<1)
#define MPCM2_bm    (1<<0)

/* UCSR2B */
#define RXCIE2_bm   (1<<7)
#define TXCIE2_bm   (1<<6)
#define UDRIE2_bm   (1<<5)
#define RXEN2_bm    (1<<4)
#define TXEN2_bm    (1<<3)
#define UCSZ22_bm   (1<<2)
#define RXB82_bm    (1<<1)
#define TXB82_bm    (1<<0)

/* UCSR2C */
#define UMSEL21_bm  (1<<7)
#define UMSEL20_bm  (1<<6)
#define UPM21_bm    (1<<5)
#define UPM20_bm    (1<<4)
#define USBS2_bm    (1<<3)
#define UCSZ21_bm   (1<<2)
#define UCSZ20_bm   (1<<1)
#define UCPOL2_bm   (1<<0)

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
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum(ATMEGA640::Interrupt::USART2_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum(ATMEGA640::Interrupt::USART2_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_atmega1280)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum(ATMEGA1280::Interrupt::USART2_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum(ATMEGA1280::Interrupt::USART2_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega2560)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum(ATMEGA2560::Interrupt::USART2_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum(ATMEGA2560::Interrupt::USART2_RECEIVE_COMPLETE         );
#else
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#endif

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART2::UART2(volatile uint8_t * udr2, volatile uint8_t * ucsr2a, volatile uint8_t * ucsr2b, volatile uint8_t * ucsr2c, volatile uint16_t * ubrr2, interface::InterruptController & int_ctrl, uint32_t const f_cpu)
: _UDR2               (udr2    ),
  _UCSR2A             (ucsr2a  ),
  _UCSR2B             (ucsr2b  ),
  _UCSR2C             (ucsr2c  ),
  _UBRR2              (ubrr2   ),
  _int_ctrl           (int_ctrl),
  _f_cpu              (f_cpu   ),
  _on_rx_done_callback(0       ),
  _on_tx_done_callback(0       )
{

}

UART2::~UART2()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART2::transmit(uint8_t const data)
{
  *_UDR2 = data;
}

void UART2::receive(uint8_t & data)
{
  data = *_UDR2;
}

void UART2::enableTx()
{
  *_UCSR2B |= TXEN2_bm;
  _int_ctrl.enableInterrupt(INT_NUM_UART_DATA_REGISTER_EMPTY);
}

void UART2::enableRx()
{
  _int_ctrl.enableInterrupt(INT_NUM_RECEIVE_COMPLETE);
  *_UCSR2B |= RXEN2_bm;
}

void UART2::disableTx()
{
  _int_ctrl.disableInterrupt(INT_NUM_UART_DATA_REGISTER_EMPTY);
  *_UCSR2B &= ~TXEN2_bm;
}

void UART2::setBaudRate(interface::UartBaudRate const baud_rate)
{
  *_UCSR2A |= U2X2_bm;

  switch(baud_rate)
  {
  case interface::UartBaudRate::B115200: *_UBRR2 = calcUartBaudRate(_f_cpu, 115200); break;
  }
}

void UART2::setParity(interface::UartParity const parity)
{
  *_UCSR2C &= ~(UPM21_bm | UPM20_bm);

  switch(parity)
  {
  case interface::UartParity::None:                                  break;
  case interface::UartParity::Even: *_UCSR2C |= UPM21_bm;            break;
  case interface::UartParity::Odd : *_UCSR2C |= UPM21_bm | UPM20_bm; break;
  }
}

void UART2::setStopBit(interface::UartStopBit const stop_bit)
{
  *_UCSR2C &= ~USBS2_bm;

  switch(stop_bit)
  {
  case interface::UartStopBit::_1:                       break;
  case interface::UartStopBit::_2: *_UCSR2C |= USBS2_bm; break;
  }
}

void UART2::register_onRxDoneCallback(interface::UART_onRxDoneCallback * on_rx_done_callback)
{
  _on_rx_done_callback = on_rx_done_callback;
}

void UART2::register_onTxDoneCallback(interface::UART_onTxDoneCallback * on_tx_done_callback)
{
  _on_tx_done_callback = on_tx_done_callback;
}

void UART2::ISR_onTransmitRegisterEmpty()
{
  if(_on_tx_done_callback) _on_tx_done_callback->onTxDone();
}

void UART2::ISR_onReceiveComplete()
{
  if(_on_rx_done_callback) _on_rx_done_callback->onRxDone();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
