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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTER_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/riscv64/FE310/I2cMasterBase.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::FE310
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class I2cMaster : public I2cMasterBase
{

public:

           I2cMaster(volatile uint32_t * i2cx_prescaler_low,
                     volatile uint32_t * i2cx_prescaler_high,
                     volatile uint32_t * i2cx_control,
                     volatile uint32_t * i2cx_data,
                     volatile uint32_t * i2cx_cmd_status,
                     volatile uint32_t * gpio_iof_en,
                     volatile uint32_t * gpio_iof_sel,
                     uint32_t const clock_Hz);
  virtual ~I2cMaster() { }


private:

  static void enableGpioAccess(volatile uint32_t * gpio_iof_en, volatile uint32_t * gpio_iof_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTER_H_ */
