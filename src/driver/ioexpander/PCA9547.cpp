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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/ioexpander/PCA9547.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace haptic
{

namespace PCA9547
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

PCA9547::PCA9547(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master )
{
  setChannel(I2C_CHANNEL_0);
}

PCA9547::~PCA9547()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool PCA9547::setChannel(I2CChannelSelect const sel)
{
  uint8_t const data = static_cast<uint8_t>(sel);

  return writeControlRegister(data);
}

bool PCA9547::getChannel(I2CChannelSelect * sel)
{
  uint8_t data = 0;

  if(!readControlRegister(&data)) return false;

  *sel = static_cast<I2CChannelSelect>(data);

  return true;
}

void PCA9547::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  uint8_t control_reg_content = 0;

  readControlRegister   (&control_reg_content);

  debug_interface.print("REG_CONTROL = %X\n", control_reg_content);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

bool PCA9547::readControlRegister(uint8_t * data)
{
  return _i2c_master.requestFrom(_i2c_address, data, 1);
}

bool PCA9547::writeControlRegister(uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCA9547 */

} /* haptic */

} /* driver */

} /* spectre */
