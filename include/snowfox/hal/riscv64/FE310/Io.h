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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_IO_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_IO_H_

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
 * DEFINE
 **************************************************************************************/

#define PLIC_BASE        (0x0C000000)

#define AON_BASE         (0x10000000)
#define AON_WDOGCFG      (*((volatile uint32_t *)(AON_BASE + 0x00)))
#define AON_WDOGCOUNT    (*((volatile uint32_t *)(AON_BASE + 0x08)))
#define AON_WDOGS        (*((volatile uint32_t *)(AON_BASE + 0x10)))
#define AON_WDOGFEED     (*((volatile uint32_t *)(AON_BASE + 0x18)))
#define AON_WDOGKEY      (*((volatile uint32_t *)(AON_BASE + 0x1C)))
#define AON_WDOGCMP      (*((volatile uint32_t *)(AON_BASE + 0x20)))
#define AON_RTCCFG       (*((volatile uint32_t *)(AON_BASE + 0x40)))
#define AON_RTCCOUNTLO   (*((volatile uint32_t *)(AON_BASE + 0x48)))
#define AON_RTCCOUNTHI   (*((volatile uint32_t *)(AON_BASE + 0x4C)))
#define AON_RTCS         (*((volatile uint32_t *)(AON_BASE + 0x50)))
#define AON_RTCCMP0      (*((volatile uint32_t *)(AON_BASE + 0x60)))
#define AON_LFROSCCFG    (*((volatile uint32_t *)(AON_BASE + 0x70)))
#define AON_LFCLKMUX     (*((volatile uint32_t *)(AON_BASE + 0x7C)))

#define PRCI_BASE        (0x10008000)
#define PRCI_HFROSCCFG   (*((volatile uint32_t *)(PRCI_BASE + 0x00)))
#define PRCI_HFXOSCCFG   (*((volatile uint32_t *)(PRCI_BASE + 0x04)))
#define PRCI_PLLCFG      (*((volatile uint32_t *)(PRCI_BASE + 0x08)))
#define PRCI_PLLOUTDIV   (*((volatile uint32_t *)(PRCI_BASE + 0x0C)))
#define PRCI_PROCMONCFG  (*((volatile uint32_t *)(PRCI_BASE + 0xF0)))

#define OTP_CONTROL_BASE (0x10010000)
#define OTP_LOCK         (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x00)))
#define OTP_CK           (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x04)))
#define OTP_OE           (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x08)))
#define OTP_SEL          (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x0C)))
#define OTP_WE           (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x10)))
#define OTP_MR           (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x14)))
#define OTP_MRR          (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x18)))
#define OTP_MPP          (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x1C)))
#define OTP_VRREN        (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x20)))
#define OTP_VPPEN        (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x24)))
#define OTP_ADR          (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x28)))
#define OTP_DATA_IN      (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x2C)))
#define OTP_DATA_OUT     (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x30)))
#define OTP_RSCTRL       (*((volatile uint32_t *)(OTP_CONTROL_BASE + 0x34)))

#define GPIO0_BASE       (0x10012000)
#define GPIO0_INPUT_VAL  (*((volatile uint32_t *)(GPIO0_BASE + 0x00)))
#define GPIO0_INPUT_EN   (*((volatile uint32_t *)(GPIO0_BASE + 0x04)))
#define GPIO0_OUTPUT_EN  (*((volatile uint32_t *)(GPIO0_BASE + 0x08)))
#define GPIO0_OUTPUT_VAL (*((volatile uint32_t *)(GPIO0_BASE + 0x0C)))
#define GPIO0_PUE        (*((volatile uint32_t *)(GPIO0_BASE + 0x10)))
#define GPIO0_IOF_EN     (*((volatile uint32_t *)(GPIO0_BASE + 0x38)))
#define GPIO0_IOF_SEL    (*((volatile uint32_t *)(GPIO0_BASE + 0x3C)))

#define UART0_BASE       (0x10013000)
#define UART0_TXDATA     (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_RXDATA     (*((volatile uint32_t *)(UART0_BASE + 0x04)))
#define UART0_TXCTRL     (*((volatile uint32_t *)(UART0_BASE + 0x08)))
#define UART0_RXCTRL     (*((volatile uint32_t *)(UART0_BASE + 0x0C)))
#define UART0_IE         (*((volatile uint32_t *)(UART0_BASE + 0x10)))
#define UART0_IP         (*((volatile uint32_t *)(UART0_BASE + 0x14)))
#define UART0_DIV        (*((volatile uint32_t *)(UART0_BASE + 0x18)))

#define QSPI0_BASE       (0x10014000)
#define QSPI0_SCKDIV     (*((volatile uint32_t *)(QSPI0_BASE + 0x00)))
#define QSPI0_SCKMODE    (*((volatile uint32_t *)(QSPI0_BASE + 0x04)))
#define QSPI0_CSID       (*((volatile uint32_t *)(QSPI0_BASE + 0x10)))
#define QSPI0_CSDEF      (*((volatile uint32_t *)(QSPI0_BASE + 0x14)))
#define QSPI0_CSMODE     (*((volatile uint32_t *)(QSPI0_BASE + 0x18)))
#define QSPI0_DELAY0     (*((volatile uint32_t *)(QSPI0_BASE + 0x28)))
#define QSPI0_DELAY1     (*((volatile uint32_t *)(QSPI0_BASE + 0x2C)))
#define QSPI0_FMT        (*((volatile uint32_t *)(QSPI0_BASE + 0x40)))
#define QSPI0_TXDATA     (*((volatile uint32_t *)(QSPI0_BASE + 0x48)))
#define QSPI0_RXDATA     (*((volatile uint32_t *)(QSPI0_BASE + 0x4C)))
#define QSPI0_TXMARK     (*((volatile uint32_t *)(QSPI0_BASE + 0x50)))
#define QSPI0_RXMARK     (*((volatile uint32_t *)(QSPI0_BASE + 0x54)))

#define PWM0_BASE        (0x10015000)
#define PWM0_PWMCFG      (*((volatile uint32_t *)(PWM0_BASE + 0x00)))
#define PWM0_PWMCOUNT    (*((volatile uint32_t *)(PWM0_BASE + 0x08)))
#define PWM0_PWMS        (*((volatile uint32_t *)(PWM0_BASE + 0x10)))
#define PWM0_PWMCMP0     (*((volatile uint32_t *)(PWM0_BASE + 0x20)))
#define PWM0_PWMCMP1     (*((volatile uint32_t *)(PWM0_BASE + 0x24)))
#define PWM0_PWMCMP2     (*((volatile uint32_t *)(PWM0_BASE + 0x28)))
#define PWM0_PWMCMP3     (*((volatile uint32_t *)(PWM0_BASE + 0x2C)))

#define I2C0_BASE        (0x10016000)
#define I2C0_PRESC_LOW   (*((volatile uint32_t *)(PWM0_BASE + 0x00)))
#define I2C0_PRESC_HIGH  (*((volatile uint32_t *)(PWM0_BASE + 0x04)))
#define I2C0_CONTROL     (*((volatile uint32_t *)(PWM0_BASE + 0x08)))
#define I2C0_DATA        (*((volatile uint32_t *)(PWM0_BASE + 0x0C)))
#define I2C0_CMD_STATUS  (*((volatile uint32_t *)(PWM0_BASE + 0x10)))

#define UART1_BASE       (0x10023000)
#define UART1_TXDATA     (*((volatile uint32_t *)(UART1_BASE + 0x00)))
#define UART1_RXDATA     (*((volatile uint32_t *)(UART1_BASE + 0x04)))
#define UART1_TXCTRL     (*((volatile uint32_t *)(UART1_BASE + 0x08)))
#define UART1_RXCTRL     (*((volatile uint32_t *)(UART1_BASE + 0x0C)))
#define UART1_IE         (*((volatile uint32_t *)(UART1_BASE + 0x10)))
#define UART1_IP         (*((volatile uint32_t *)(UART1_BASE + 0x14)))
#define UART1_DIV        (*((volatile uint32_t *)(UART1_BASE + 0x18)))

#define SPI1_BASE        (0x10024000)
#define SPI1_SCKDIV      (*((volatile uint32_t *)(SPI1_BASE + 0x00)))
#define SPI1_SCKMODE     (*((volatile uint32_t *)(SPI1_BASE + 0x04)))
#define SPI1_CSID        (*((volatile uint32_t *)(SPI1_BASE + 0x10)))
#define SPI1_CSDEF       (*((volatile uint32_t *)(SPI1_BASE + 0x14)))
#define SPI1_CSMODE      (*((volatile uint32_t *)(SPI1_BASE + 0x18)))
#define SPI1_DELAY0      (*((volatile uint32_t *)(SPI1_BASE + 0x28)))
#define SPI1_DELAY1      (*((volatile uint32_t *)(SPI1_BASE + 0x2C)))
#define SPI1_FMT         (*((volatile uint32_t *)(SPI1_BASE + 0x40)))
#define SPI1_TXDATA      (*((volatile uint32_t *)(SPI1_BASE + 0x48)))
#define SPI1_RXDATA      (*((volatile uint32_t *)(SPI1_BASE + 0x4C)))
#define SPI1_TXMARK      (*((volatile uint32_t *)(SPI1_BASE + 0x50)))
#define SPI1_RXMARK      (*((volatile uint32_t *)(SPI1_BASE + 0x54)))

#define PWM1_BASE        (0x10025000)
#define PWM1_PWMCFG      (*((volatile uint32_t *)(PWM1_BASE + 0x00)))
#define PWM1_PWMCOUNT    (*((volatile uint32_t *)(PWM1_BASE + 0x08)))
#define PWM1_PWMS        (*((volatile uint32_t *)(PWM1_BASE + 0x10)))
#define PWM1_PWMCMP0     (*((volatile uint32_t *)(PWM1_BASE + 0x20)))
#define PWM1_PWMCMP1     (*((volatile uint32_t *)(PWM1_BASE + 0x24)))
#define PWM1_PWMCMP2     (*((volatile uint32_t *)(PWM1_BASE + 0x28)))
#define PWM1_PWMCMP3     (*((volatile uint32_t *)(PWM1_BASE + 0x2C)))

#define SPI2_BASE        (0x10034000)
#define SPI2_SCKDIV      (*((volatile uint32_t *)(SPI2_BASE + 0x00)))
#define SPI2_SCKMODE     (*((volatile uint32_t *)(SPI2_BASE + 0x04)))
#define SPI2_CSID        (*((volatile uint32_t *)(SPI2_BASE + 0x10)))
#define SPI2_CSDEF       (*((volatile uint32_t *)(SPI2_BASE + 0x14)))
#define SPI2_CSMODE      (*((volatile uint32_t *)(SPI2_BASE + 0x18)))
#define SPI2_DELAY0      (*((volatile uint32_t *)(SPI2_BASE + 0x28)))
#define SPI2_DELAY1      (*((volatile uint32_t *)(SPI2_BASE + 0x2C)))
#define SPI2_FMT         (*((volatile uint32_t *)(SPI2_BASE + 0x40)))
#define SPI2_TXDATA      (*((volatile uint32_t *)(SPI2_BASE + 0x48)))
#define SPI2_RXDATA      (*((volatile uint32_t *)(SPI2_BASE + 0x4C)))
#define SPI2_TXMARK      (*((volatile uint32_t *)(SPI2_BASE + 0x50)))
#define SPI2_RXMARK      (*((volatile uint32_t *)(SPI2_BASE + 0x54)))

#define PWM2_BASE        (0x10035000)
#define PWM2_PWMCFG      (*((volatile uint32_t *)(PWM2_BASE + 0x00)))
#define PWM2_PWMCOUNT    (*((volatile uint32_t *)(PWM2_BASE + 0x08)))
#define PWM2_PWMS        (*((volatile uint32_t *)(PWM2_BASE + 0x10)))
#define PWM2_PWMCMP0     (*((volatile uint32_t *)(PWM2_BASE + 0x20)))
#define PWM2_PWMCMP1     (*((volatile uint32_t *)(PWM2_BASE + 0x24)))
#define PWM2_PWMCMP2     (*((volatile uint32_t *)(PWM2_BASE + 0x28)))
#define PWM2_PWMCMP3     (*((volatile uint32_t *)(PWM2_BASE + 0x2C)))

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class HFXOSCCFG : uint32_t
{
  HFXOSCRDY = 31,
  HFXOSCEN  = 30
};

enum class PLLCFG : uint32_t
{
  PLLLOCK   = 31,
  PLLBYPASS = 18,
  PLLREFSEL = 17,
  PLLSEL    = 16
};

enum class PLLOUTDIV : uint32_t
{
  PLLOUTDIVBY1 = 8
};

enum class MSTATUS : uint32_t
{
  MACHINE_INTERRUPT_ENABLE = INT32_C(3)
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_IO_H_ */
