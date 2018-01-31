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

#include <spectre/driver/glcd/RA6963/RA6963_Control.h>

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint8_t const RA6963_CMD_SET_ADDRESS_POINTER   = 0x24;
static uint8_t const RA6963_CMD_SET_GFX_HOME_ADDRESS  = 0x42;
static uint8_t const RA6963_CMD_SET_GFX_AREA          = 0x43;
static uint8_t const RA6963_CMD_SET_DATA_AUTO_WRITE   = 0xB0;
static uint8_t const RA6963_CMD_RESET_AUTO_READ_WRITE = 0xB1;
static uint8_t const RA6963_CMD_SET_BIT_WITHIN_BYTE   = 0xF8;
static uint8_t const RA6963_CMD_CLR_BIT_WITHIN_BYTE   = 0xF0;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace glcd
{

namespace RA6963
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RA6963_Control::RA6963_Control(interface::RA6963_Data & data)
: _data(data                     ),
  _mode(interface::OpMode::NORMAL)
{
  setOperationMode(interface::OpMode::NORMAL);
}

RA6963_Control::~RA6963_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RA6963_Control::setGfxHomeAddress(uint16_t const gfx_home_address)
{

}

void RA6963_Control::setGfxArea(uint8_t const gfx_columns)
{

}

void RA6963_Control::setAddressPointer(uint16_t const address_pointer)
{

}

void RA6963_Control::write(uint8_t const * data, uint32_t const num_bytes)
{

}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void RA6963_Control::setOperationMode(interface::OpMode const mode)
{
  switch(mode)
  {
  case interface::OpMode::NORMAL: _data.writeCommand(_mode, RA6963_CMD_RESET_AUTO_READ_WRITE); break;
  case interface::OpMode::AUTO  : _data.writeCommand(_mode, RA6963_CMD_SET_DATA_AUTO_WRITE  ); break;
  }

  _mode = mode;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RA6963 */

} /* glcd */

} /* driver */

} /* spectre */
