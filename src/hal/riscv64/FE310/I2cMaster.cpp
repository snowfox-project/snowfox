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

#include <snowfox/hal/riscv64/FE310/I2cMaster.h>

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

I2cMaster::I2cMaster(volatile uint32_t * i2cx_prescaler_low,
                     volatile uint32_t * i2cx_prescaler_high,
                     volatile uint32_t * i2cx_control,
                     volatile uint32_t * i2cx_data,
                     volatile uint32_t * i2cx_cmd_status,
                     volatile uint32_t * gpio_iof_en,
                     volatile uint32_t * gpio_iof_sel,
                     uint32_t const clock_Hz)
: I2cMasterBase{i2cx_prescaler_low, i2cx_prescaler_high, i2cx_control, i2cx_data, i2cx_cmd_status, clock_Hz}
{
  enableGpioAccess(gpio_iof_en, gpio_iof_sel);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void I2cMaster::enableGpioAccess(volatile uint32_t * gpio_iof_en, volatile uint32_t * gpio_iof_sel)
{
  util::setBit(gpio_iof_en,  util::bp(GPIO0_IOF_EN::I2C0_SDA));
  util::setBit(gpio_iof_en,  util::bp(GPIO0_IOF_EN::I2C0_SCL));
  util::clrBit(gpio_iof_sel, util::bp(GPIO0_IOF_SEL::I2C0_SDA));
  util::clrBit(gpio_iof_sel, util::bp(GPIO0_IOF_SEL::I2C0_SCL));
}
  
/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */
