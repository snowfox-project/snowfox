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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_REGISTER_BITS_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_REGISTER_BITS_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::FE310
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class PRCI_HFXOSCCFG : uint32_t
{
  HFXOSCRDY = 31,
  HFXOSCEN  = 30
};

enum class PRCI_PLLCFG : uint32_t
{
  PLLLOCK   = 31,
  PLLBYPASS = 18,
  PLLREFSEL = 17,
  PLLSEL    = 16
};

enum class PRCI_PLLOUTDIV : uint32_t
{
  PLLOUTDIVBY1 = 8
};

enum class GPIO0_IOF_EN : uint32_t
{
  SPI1_DQ0 = 3,  /* SPI1 MOSI */
  SPI1_DQ1 = 4,  /* SPI1 MISO */
  SPI1_SCK = 5,  /* SPI1 SCK  */
  I2C0_SDA = 12, /* I2C0 SDA */
  I2C0_SCL = 13, /* I2C0 SCL */
  UART0_RX = 16,
  UART0_TX = 17,
  UART1_RX = 18,
  UART1_TX = 23,
  SPI2_DQ0 = 27, /* SPI2 MOSI */
  SPI2_DQ1 = 28, /* SPI2 MISO */
  SPI2_SCK = 29, /* SPI2 SCK  */
};

enum class GPIO0_IOF_SEL : uint32_t
{
  SPI1_DQ0 = 3,  /* SPI1 MOSI */
  SPI1_DQ1 = 4,  /* SPI1 MISO */
  SPI1_SCK = 5,  /* SPI1 SCK  */
  I2C0_SDA = 12, /* I2C0 SDA */
  I2C0_SCL = 13, /* I2C0 SCL */
  UART0_RX = 16,
  UART0_TX = 17,
  UART1_RX = 18,
  UART1_TX = 23,
  SPI2_DQ0 = 27, /* SPI2 MOSI */
  SPI2_DQ1 = 28, /* SPI2 MISO */
  SPI2_SCK = 29, /* SPI2 SCK  */
};

enum class UARTx_TXCTRL : uint32_t
{
  TXEN  = 0,
  NSTOP = 1,
};

enum class UARTx_RXCTRL : uint32_t
{
  RXEN = 0,
};

enum class SPIx_SCKMODE : uint32_t
{
  POL = 1,
  PHA = 0,
};

enum class SPIx_CSMODE : uint32_t
{
  MODE_1 = 1,
  MODE_0 = 0,
};

enum class SPIx_FMT : uint32_t
{
  LEN_3   = 19,
  LEN_2   = 18,
  LEN_1   = 17,
  LEN_0   = 16,
  ENDIAN  = 2,
  PROTO_1 = 1,
  PROTO_0 = 0,
};

enum class MSTATUS : uint32_t
{
  MACHINE_INTERRUPT_ENABLE = INT32_C(3)
};

enum class I2Cx_CONTROL : uint32_t
{
  ENABLE           = 7,
  INTERRUPT_ENABLE = 6
};

enum class I2Cx_COMMAND : uint32_t
{
  STA  = 7,
  STO  = 6,
  RD   = 5,
  WR   = 4,
  ACK  = 3,
  IACK = 0
};

enum class I2Cx_STATUS : uint32_t
{
  RxACK             = 7,
  Busy              = 6,
  ArbitrationLost   = 5,
  TransferInProgres = 1,
  InterruptFlag     = 0
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_REGISTER_BITS_H_ */
