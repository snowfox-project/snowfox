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

#include <snowfox/hal/riscv64/FE310/util/IoFuncUtil.h>

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
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void enableIoFunction(volatile uint32_t * gpio_iof_en, uint8_t const pin_number)
{
  util::setBit(gpio_iof_en, pin_number);
}

void disableIoFunction(volatile uint32_t * gpio_iof_en, uint8_t const pin_number)
{
  util::clrBit(gpio_iof_en, pin_number);
}

void setIoFunction(volatile uint32_t * gpio_iof_sel, uint8_t const pin_number, IoFunc const io_func)
{
  switch(io_func)
  {
  case IoFunc::IOF0: util::clrBit(gpio_iof_sel, pin_number); break;
  case IoFunc::IOF1: util::setBit(gpio_iof_sel, pin_number); break;
  default          :                                         break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
