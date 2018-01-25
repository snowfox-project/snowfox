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

#ifndef INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_IO_I2C_H_
#define INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_IO_I2C_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/haptic/DRV2605/interface/DRV2605_Io.h>

#include <spectre/hal/interface/i2c/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace haptic
{

namespace DRV2605
{

/**************************************************************************************
 * CLASS DECLARATION DRV2605
 **************************************************************************************/

class DRV2605_IoI2C : public interface::DRV2605_Io
{

public:

           DRV2605_IoI2C(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~DRV2605_IoI2C();


  virtual bool readSingleRegister (interface::RegisterSelect const reg_sel, uint8_t       * data) override;
  virtual bool writeSingleRegister(interface::RegisterSelect const reg_sel, uint8_t const   data) override;


private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_IO_I2C_H_ */
