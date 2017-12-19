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

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

#include <spectre/debug/interface/Debug.h>

#include <spectre/hal/interface/delay/Delay.h>
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

namespace PCA9547
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  I2C_CHANNEL_0   = 0x08,
  I2C_CHANNEL_1   = 0x09,
  I2C_CHANNEL_2   = 0x0A,
  I2C_CHANNEL_3   = 0x0B,
  I2C_CHANNEL_4   = 0x0C,
  I2C_CHANNEL_5   = 0x0D,
  I2C_CHANNEL_6   = 0x0E,
  I2C_CHANNEL_7   = 0x0F,
  I2C_NO_CHANNEL  = 0x00
} I2CChannelSelect;

/**************************************************************************************
 * CLASS DECLARATION Interface
 **************************************************************************************/

class Interface
{

public:

           Interface() { }
  virtual ~Interface() { }


  virtual bool setChannel(I2CChannelSelect const   sel) = 0;
  virtual bool getChannel(I2CChannelSelect       * sel) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION PCA9547
 **************************************************************************************/

class PCA9547 : public Interface
{

public:

           PCA9547(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~PCA9547();


  /* PCA9547 Interface */

  virtual bool setChannel(I2CChannelSelect const   sel) override;
  virtual bool getChannel(I2CChannelSelect       * sel) override;


          void debug_dumpAllRegs(debug::interface::Debug & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

  bool readControlRegister   (uint8_t        * data);
  bool writeControlRegister  (uint8_t const    data);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCA9547 */

} /* ioexpander */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_H_ */
