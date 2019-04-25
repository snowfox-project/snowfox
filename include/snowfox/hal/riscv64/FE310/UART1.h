/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#include <snowfox/hal/riscv64/FE310/UART1.h>

#include <snowfox/util/BitManip.h>

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

#define GPIO_IOF_SEL_UART1_RX_bp (18)
#define GPIO_IOF_SEL_UART1_TX_bp (23)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART1::UART1(volatile uint32_t * uartx_txdata,
             volatile uint32_t * uartx_rxdata,
             volatile uint32_t * uartx_txctrl,
             volatile uint32_t * uartx_rxctrl,
             volatile uint32_t * uartx_div,
             uint32_t const      tlclk_Hz,
             volatile uint32_t * gpio_iof_en,
             volatile uint32_t * gpio_iof_sel)
: UARTx(uartx_txdata,
        uartx_rxdata,
        uartx_txctrl,
        uartx_rxctrl,
        uartx_div,
        tlclk_Hz)
{
  enableGpioAccess(gpio_iof_en, gpio_iof_sel);
}

UART1::~UART1()
{

}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void UART1::enableGpioAccess(volatile uint32_t * gpio_iof_en, volatile uint32_t * gpio_iof_sel)
{
  util::clrBit(gpio_iof_sel, GPIO_IOF_SEL_UART1_RX_bp);
  util::clrBit(gpio_iof_sel, GPIO_IOF_SEL_UART1_TX_bp);
  util::setBit(gpio_iof_en,  GPIO_IOF_SEL_UART1_RX_bp);
  util::setBit(gpio_iof_en,  GPIO_IOF_SEL_UART1_TX_bp);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
