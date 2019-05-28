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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_SPI1MASTER_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_SPI1MASTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/riscv64/FE310/SpiMasterBase.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class Spi1Master : public SpiMasterBase
{

public:

           Spi1Master(volatile uint32_t * spi1_sckmode,
                      volatile uint32_t * spi1_fmt,
                      volatile uint32_t * gpio_iof_en,
                      volatile uint32_t * gpio_iof_sel);
  virtual ~Spi1Master();


private:

  static void enableGpioAccess(volatile uint32_t * gpio_iof_en, volatile uint32_t * gpio_iof_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_SPI1MASTER_H_ */
