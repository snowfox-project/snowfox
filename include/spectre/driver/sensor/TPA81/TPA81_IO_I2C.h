/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_TPA81_IO_I2C_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_TPA81_IO_I2C_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/TPA81/interface/TPA81_IO_Interface.h>

#include <spectre/hal/interface/i2c/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace TPA81
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TPA81_IO_I2C : public TPA81_IO_Interface
{

public:

           TPA81_IO_I2C(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~TPA81_IO_I2C();


  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const  * data, uint16_t const num_bytes) override;
  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t        * data, uint16_t const num_bytes) override;

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* TPA81 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_TPA81_IO_I2C_H_ */
