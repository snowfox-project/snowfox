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

#include <spectre/driver/sensor/TPA81/TPA81.h>

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
 * CTOR/DTOR
 **************************************************************************************/

TPA81::TPA81(TPA81_IO_Interface & io)
: _io(io)
{

}

TPA81::~TPA81()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool TPA81::readSoftwareRevision(uint8_t * software_revision)
{
  bool success = false;

  /* TODO */

  return success;
}

bool TPA81::readAmbientTemperature(uint8_t * ambient_temperature)
{
  bool success = false;

  /* TODO */

  return success;
}

bool TPA81::readThermophileArray(ThermophileData * thermo_data)
{
  bool success = false;

  /* TODO */

  return success;
}

void TPA81::debug_dumpAllRegs(driver::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_COMMAND             = ", REG_COMMAND            );
  debug_dumpSingleReg(debug_interface, "REG_AMBIENT_TEMPERATURE = ", REG_AMBIENT_TEMPERATURE);
  debug_dumpSingleReg(debug_interface, "REG_PIXEL_1             = ", REG_PIXEL_1            );
  debug_dumpSingleReg(debug_interface, "REG_PIXEL_2             = ", REG_PIXEL_2            );
  debug_dumpSingleReg(debug_interface, "REG_PIXEL_3             = ", REG_PIXEL_3            );
  debug_dumpSingleReg(debug_interface, "REG_PIXEL_4             = ", REG_PIXEL_4            );
  debug_dumpSingleReg(debug_interface, "REG_PIXEL_5             = ", REG_PIXEL_5            );
  debug_dumpSingleReg(debug_interface, "REG_PIXEL_6             = ", REG_PIXEL_6            );
  debug_dumpSingleReg(debug_interface, "REG_PIXEL_7             = ", REG_PIXEL_7            );
  debug_dumpSingleReg(debug_interface, "REG_PIXEL_8             = ", REG_PIXEL_8            );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool TPA81::readSingleRegister(RegisterSelect const reg_sel, uint8_t * data)
{
  return _io.readMultipleRegister(reg_sel, data, 1);
}

bool TPA81::writeSingleRegister(RegisterSelect const reg_sel, uint8_t const data)
{
  return _io.writeMultipleRegister(reg_sel, &data, 1);
}

void TPA81::debug_dumpSingleReg(driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* TPA81 */

} /* sensor */

} /* driver */

} /* spectre */
