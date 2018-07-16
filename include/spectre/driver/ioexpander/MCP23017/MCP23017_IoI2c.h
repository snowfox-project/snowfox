/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_IOI2C_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_IOI2C_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/ioexpander/MCP23017/interface/MCP23017_Io.h>

#include <spectre/hal/interface/i2c/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace ioexpander
{

namespace MCP23017
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP23017_IoI2c : public interface::MCP23017_Io
{

public:

           MCP23017_IoI2c(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~MCP23017_IoI2c();


  virtual bool readRegister (interface::Register const reg, uint8_t       * data) override;
  virtual bool writeRegister(interface::Register const reg, uint8_t const   data) override;


private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_MCP23017_MCP23017_IOI2C_H_ */
