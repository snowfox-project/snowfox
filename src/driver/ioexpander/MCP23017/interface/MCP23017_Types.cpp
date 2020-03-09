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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/ioexpander/MCP23017/interface/MCP23017_Types.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace ioexpander
{

namespace MCP23017
{

namespace interface
{

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

Register toReg_GPPU(Port const port)
{
  if  (port == Port::A) return Register::GPPU_A;
  else                  return Register::GPPU_B;
}

Register toReg_GPIO (Port const port)
{
  if  (port == Port::A) return Register::GPIO_A;
  else                  return Register::GPIO_B;
}

Register toReg_IODIR(Port const port)
{
  if  (port == Port::A) return Register::IODIR_A;
  else                  return Register::IODIR_B;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* snowfox */
