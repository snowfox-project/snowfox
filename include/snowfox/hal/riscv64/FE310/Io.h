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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_IO_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_IO_H_

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

#define GPIO0_BASE       (0x10012000)
#define GPIO0_INPUT_VAL  (*((volatile uint32_t *)(GPIO0_BASE + 0x00)))
#define GPIO0_INPUT_EN   (*((volatile uint32_t *)(GPIO0_BASE + 0x04)))
#define GPIO0_OUTPUT_EN  (*((volatile uint32_t *)(GPIO0_BASE + 0x08)))
#define GPIO0_OUTPUT_VAL (*((volatile uint32_t *)(GPIO0_BASE + 0x0C)))
#define GPIO0_PUE        (*((volatile uint32_t *)(GPIO0_BASE + 0x10)))
#define GPIO0_IOF_EN     (*((volatile uint32_t *)(GPIO0_BASE + 0x38)))
#define GPIO0_IOF_SEL    (*((volatile uint32_t *)(GPIO0_BASE + 0x3C)))

#define PRCI_BASE        (0x10008000)
#define PRCI_HFROSCCFG   (*((volatile uint32_t *)(PRCI_BASE + 0x00)))
#define PRCI_HFXOSCCFG   (*((volatile uint32_t *)(PRCI_BASE + 0x04)))
#define PRCI_PLLCFG      (*((volatile uint32_t *)(PRCI_BASE + 0x08)))
#define PRCI_PLLOUTDIV   (*((volatile uint32_t *)(PRCI_BASE + 0x0C)))
#define PRCI_PROCMONCFG  (*((volatile uint32_t *)(PRCI_BASE + 0xF0)))

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_IO_H_ */
