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

#include <snowfox/hal/riscv64/FE310/Spi1Master.h>

#include <snowfox/util/BitUtil.h>

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

#define GPIO_IOF_SEL_SPI1_DQ0_bp  (3) /* MOSI */
#define GPIO_IOF_SEL_SPI1_DQ1_bp  (4) /* MISO */
#define GPIO_IOF_SEL_SPI1_SCK_bp  (5)

#define GPIO_IOF_EN_SPI1_DQ0_bp   (GPIO_IOF_SEL_SPI1_DQ0_bp)
#define GPIO_IOF_EN_SPI1_DQ1_bp   (GPIO_IOF_SEL_SPI1_DQ1_bp)
#define GPIO_IOF_EN_SPI1_SCK_bp   (GPIO_IOF_SEL_SPI1_SCK_bp)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Spi1Master::Spi1Master(volatile uint32_t * spi1_sckmode,
                       volatile uint32_t * spi1_fmt,
                       volatile uint32_t * gpio_iof_en,
                       volatile uint32_t * gpio_iof_sel)
: SpiMaster(spi1_sckmode, spi1_fmt)
{
  enableGpioAccess(gpio_iof_en, gpio_iof_sel);
}

Spi1Master::~Spi1Master()
{

}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void Spi1Master::enableGpioAccess(volatile uint32_t * gpio_iof_en, volatile uint32_t * gpio_iof_sel)
{
  util::clrBit(gpio_iof_sel, GPIO_IOF_SEL_SPI1_DQ0_bp);
  util::clrBit(gpio_iof_sel, GPIO_IOF_SEL_SPI1_DQ1_bp);
  util::clrBit(gpio_iof_sel, GPIO_IOF_SEL_SPI1_SCK_bp);
  util::setBit(gpio_iof_en,  GPIO_IOF_EN_SPI1_DQ0_bp);
  util::setBit(gpio_iof_en,  GPIO_IOF_EN_SPI1_DQ1_bp);
  util::setBit(gpio_iof_en,  GPIO_IOF_SEL_SPI1_SCK_bp);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
