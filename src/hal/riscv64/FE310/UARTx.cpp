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

#include <snowfox/hal/riscv64/FE310/UARTx.h>

#include <snowfox/util/BitUtil.h>

#include <snowfox/hal/riscv64/FE310/util/UartUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace FE310
{

/**************************************************************************************
 * DEFINE
 **************************************************************************************/

/* TXCTRL */
#define TXCTRL_TXEN_bp  (0)
#define TXCTRL_NSTOP_bp (0)

/* RXCTRL */
#define RXCTRL_RXEN_bp  (0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UARTx::UARTx(volatile uint32_t * uartx_txdata,
             volatile uint32_t * uartx_rxdata,
             volatile uint32_t * uartx_txctrl,
             volatile uint32_t * uartx_rxctrl,
             volatile uint32_t * uartx_div,
             uint32_t const      tlclk_Hz)
: _uartx_txdata       (uartx_txdata),
  _uartx_rxdata       (uartx_rxdata),
  _uartx_txctrl       (uartx_txctrl),
  _uartx_rxctrl       (uartx_rxctrl),
  _uartx_div          (uartx_div   ),
  _tlclk_Hz           (tlclk_Hz    ),
  _on_rx_done_callback(0),
  _on_tx_done_callback(0)
{

}

UARTx::~UARTx()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UARTx::transmit(uint8_t const data)
{
  *_uartx_txdata = static_cast<uint32_t>(data);
}

void UARTx::receive(uint8_t & data)
{
  data = static_cast<uint8_t>(*_uartx_rxdata & 0x000000FF);
}

void UARTx::enableTx()
{
  util::setBit(_uartx_txctrl, TXCTRL_TXEN_bp);
}

void UARTx::enableRx()
{
  util::setBit(_uartx_rxctrl, RXCTRL_RXEN_bp);
}

void UARTx::disableTx()
{
  util::clrBit(_uartx_rxctrl, RXCTRL_RXEN_bp);
}

bool UARTx::setBaudRate(interface::UartBaudRate const baud_rate)
{
  switch(baud_rate)
  {
  case interface::UartBaudRate::B115200: *_uartx_div = static_cast<uint32_t>(calcUartBaudRate(_tlclk_Hz, 115200)); return true; break;
  }

  return false;
}

bool UARTx::setParity(interface::UartParity const parity)
{
  /* The FE310 UART only supports no parity */
  switch(parity)
  {
  case interface::UartParity::None: return true;  break;
  case interface::UartParity::Even: return false; break;
  case interface::UartParity::Odd:  return false; break;
  default:                          return false; break;
  }
}

bool UARTx::setStopBit(interface::UartStopBit const stop_bit)
{
  switch(stop_bit)
  {
  case interface::UartStopBit::_1: util::clrBit(_uartx_txctrl, TXCTRL_NSTOP_bp); return true; break;
  case interface::UartStopBit::_2: util::setBit(_uartx_txctrl, TXCTRL_NSTOP_bp); return true; break;
  }

  return false;
}

void UARTx::register_onRxDoneCallback(interface::UART_onRxDoneCallback * on_rx_done_callback)
{
  _on_rx_done_callback = on_rx_done_callback;
}

void UARTx::register_onTxDoneCallback(interface::UART_onTxDoneCallback * on_tx_done_callback)
{
  _on_tx_done_callback = on_tx_done_callback;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
