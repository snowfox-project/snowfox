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

#ifndef INCLUDE_SPECTRE_DRIVER_MEMORY_PCF8570_H_
#define INCLUDE_SPECTRE_DRIVER_MEMORY_PCF8570_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <spectre/debug/interface/Debug.h>
#include <spectre/hal/interface/i2c/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace PCF8570
{

/**************************************************************************************
 * CLASS DECLARATION Interface
 **************************************************************************************/

class Interface
{

public:

           Interface() { }
  virtual ~Interface() { }


  virtual bool write(uint8_t const address, uint8_t const   data) = 0;
  virtual bool read (uint8_t const address, uint8_t       * data) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION PCF8570
 **************************************************************************************/

class PCF8570 : public Interface
{

public:

           PCF8570(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~PCF8570();


  /* PCF8570 Interface */

  virtual bool write(uint8_t const address, uint8_t const   data) override;
  virtual bool read (uint8_t const address, uint8_t       * data) override;

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCF8570 */

} /* memory */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_MEMORY_PCF8570_H_ */
