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

#include <snowfox/hal/riscv64/FE310/Spi1Master.h>

#include <snowfox/hal/riscv64/FE310/RegisterBits.h>

#include <snowfox/util/BitUtil.h>
#include <snowfox/util/EnumClassConv.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::FE310
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Spi1Master::Spi1Master(volatile uint32_t * spi1_sckmode,
                       volatile uint32_t * spi1_fmt,
                       volatile uint32_t * spi1_csmode,
                       volatile uint32_t * gpio_iof_en,
                       volatile uint32_t * gpio_iof_sel)
: SpiMasterBase(spi1_sckmode, spi1_fmt, spi1_csmode)
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
  util::clrBit(gpio_iof_sel, util::bp(GPIO0_IOF_SEL::SPI1_DQ0));
  util::clrBit(gpio_iof_sel, util::bp(GPIO0_IOF_SEL::SPI1_DQ1));
  util::clrBit(gpio_iof_sel, util::bp(GPIO0_IOF_SEL::SPI1_SCK));
  util::setBit(gpio_iof_en,  util::bp(GPIO0_IOF_EN::SPI1_DQ0));
  util::setBit(gpio_iof_en,  util::bp(GPIO0_IOF_EN::SPI1_DQ1));
  util::setBit(gpio_iof_en,  util::bp(GPIO0_IOF_EN::SPI1_SCK));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */
