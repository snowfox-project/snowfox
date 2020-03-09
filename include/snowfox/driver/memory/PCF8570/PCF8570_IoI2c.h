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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_PCF8570_PCF8570_IO_I2C_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_PCF8570_PCF8570_IO_I2C_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/PCF8570/interface/PCF8570_Io.h>

#include <snowfox/hal/interface/i2c/I2cMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace PCF8570
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class PCF8570_IoI2c final : public interface::PCF8570_Io
{

public:

           PCF8570_IoI2c(uint8_t const i2c_address, hal::interface::I2cMaster & i2c_master);
  virtual ~PCF8570_IoI2c();


  virtual bool writeByte(uint8_t const address, uint8_t const   data) override;
  virtual bool readByte (uint8_t const address, uint8_t       * data) override;

private:

  uint8_t                     _i2c_address;
  hal::interface::I2cMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCF8570 */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_PCF8570_PCF8570_IO_I2C_H_ */
