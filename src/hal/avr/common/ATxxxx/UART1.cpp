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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/UART1.h>

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
#elif defined(MCU_TYPE_atmega16u4)
  #include <spectre/hal/avr/ATMEGA16U4/InterruptController.h>
#elif defined(MCU_TYPE_atmega32u4)
  #include <spectre/hal/avr/ATMEGA32U4/InterruptController.h>
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

/* UCSR1A */
#define RXC1_bm     (1<<7)
#define TXC1_bm     (1<<6)
#define UDRE1_bm    (1<<5)
#define FE1_bm      (1<<4)
#define DOR1_bm     (1<<3)
#define UPE1_bm     (1<<2)
#define U2X1_bm     (1<<1)
#define MPCM1_bm    (1<<0)

/* UCSR1B */
#define RXCIE1_bm   (1<<7)
#define TXCIE1_bm   (1<<6)
#define UDRIE1_bm   (1<<5)
#define RXEN1_bm    (1<<4)
#define TXEN1_bm    (1<<3)
#define UCSZ12_bm   (1<<2)
#define RXB81_bm    (1<<1)
#define TXB81_bm    (1<<0)

/* UCSR1C */
#define UMSEL11_bm  (1<<7)
#define UMSEL10_bm  (1<<6)
#define UPM11_bm    (1<<5)
#define UPM10_bm    (1<<4)
#define USBS1_bm    (1<<3)
#define UCSZ11_bm   (1<<2)
#define UCSZ10_bm   (1<<1)
#define UCPOL1_bm   (1<<0)

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

#if   defined(MCU_TYPE_atmega328p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_at90can32)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = AT90CAN32_64_128::toIntNum           (AT90CAN32::Interrupt::USART1_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = AT90CAN32_64_128::toIntNum           (AT90CAN32::Interrupt::USART1_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_at90can64)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = AT90CAN32_64_128::toIntNum           (AT90CAN64::Interrupt::USART1_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = AT90CAN32_64_128::toIntNum           (AT90CAN64::Interrupt::USART1_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_at90can128)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = AT90CAN32_64_128::toIntNum           (AT90CAN128::Interrupt::USART1_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = AT90CAN32_64_128::toIntNum           (AT90CAN128::Interrupt::USART1_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega164p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA164P::Interrupt::USART1_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA164P::Interrupt::USART1_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega324p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA324P::Interrupt::USART1_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA324P::Interrupt::USART1_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega644p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA644P::Interrupt::USART1_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA644P::Interrupt::USART1_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega1284p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA1284P::Interrupt::USART1_UART_DATA_REGISTER_EMPTY);
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA1284P::Interrupt::USART1_RECEIVE_COMPLETE        );
#elif defined(MCU_TYPE_atmega640)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum        (ATMEGA640::Interrupt::USART1_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum        (ATMEGA640::Interrupt::USART1_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_atmega1280)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum        (ATMEGA1280::Interrupt::USART1_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum        (ATMEGA1280::Interrupt::USART1_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega2560)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum        (ATMEGA2560::Interrupt::USART1_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum        (ATMEGA2560::Interrupt::USART1_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega16u4)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA16U4_32U4::toIntNum            (ATMEGA16U4::Interrupt::USART1_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA16U4_32U4::toIntNum            (ATMEGA16U4::Interrupt::USART1_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega32u4)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA16U4_32U4::toIntNum            (ATMEGA32U4::Interrupt::USART1_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA16U4_32U4::toIntNum            (ATMEGA32U4::Interrupt::USART1_RECEIVE_COMPLETE         );
#else
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#endif

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART1::UART1(volatile uint8_t * udr1, volatile uint8_t * ucsr1a, volatile uint8_t * ucsr1b, volatile uint8_t * ucsr1c, volatile uint16_t * ubrr1, interface::InterruptController & int_ctrl, uint32_t const f_cpu)
: _UDR1               (udr1    ),
  _UCSR1A             (ucsr1a  ),
  _UCSR1B             (ucsr1b  ),
  _UCSR1C             (ucsr1c  ),
  _UBRR1              (ubrr1   ),
  _int_ctrl           (int_ctrl),
  _f_cpu              (f_cpu   ),
  _on_rx_done_callback(0       ),
  _on_tx_done_callback(0       )
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
  _int_ctrl.enableInterrupt(INT_NUM_UART_DATA_REGISTER_EMPTY);
}

void UART1::enableRx()
{
  _int_ctrl.enableInterrupt(INT_NUM_RECEIVE_COMPLETE);
  *_UCSR1B |= RXEN1_bm;
}

void UART1::disableTx()
{
  _int_ctrl.disableInterrupt(INT_NUM_UART_DATA_REGISTER_EMPTY);
  *_UCSR1B &= ~TXEN1_bm;
}

void UART1::setBaudRate(interface::UartBaudRate const baud_rate)
{
  *_UCSR1A |= U2X1_bm;

  switch(baud_rate)
  {
  case interface::UartBaudRate::B115200: *_UBRR1 = calcUartBaudRate(_f_cpu, 115200); break;
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

void UART1::register_onRxDoneCallback(interface::UART_onRxDoneCallback * on_rx_done_callback)
{
  _on_rx_done_callback = on_rx_done_callback;
}

void UART1::register_onTxDoneCallback(interface::UART_onTxDoneCallback * on_tx_done_callback)
{
  _on_tx_done_callback = on_tx_done_callback;
}

void UART1::ISR_onTransmitRegisterEmpty()
{
  if(_on_tx_done_callback) _on_tx_done_callback->onTxDone();
}

void UART1::ISR_onReceiveComplete()
{
  if(_on_rx_done_callback) _on_rx_done_callback->onRxDone();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
