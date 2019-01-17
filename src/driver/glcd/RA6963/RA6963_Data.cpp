/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/driver/glcd/RA6963/RA6963_Data.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace glcd
{

namespace RA6963
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

#define STATUS_BYTE_STA3_bm  (1<<3) /* Check auto mode data write capability */
#define STATUS_BYTE_STA2_bm  (1<<2) /* Check auto mode data read capability  */
#define STATUS_BYTE_STA1_bm  (1<<1) /* Check data read/write capability      */
#define STATUS_BYTE_STA0_bm  (1<<0) /* Check command execution capability    */

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RA6963_Data::RA6963_Data(interface::RA6963_Io & io)
: _io(io)
{
  _io.reset();
}

RA6963_Data::~RA6963_Data()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t RA6963_Data::readData(interface::OpMode const mode)
{
  waitForReady(mode);

  return _io.readData();
}

void RA6963_Data::writeData(interface::OpMode const mode, uint8_t const data_val)
{
  waitForReady(mode);

  _io.writeData(data_val);
}

void RA6963_Data::writeCommand(interface::OpMode const mode, uint8_t const cmd_val)
{
  waitForReady(mode);

  _io.writeCommand(cmd_val);
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void RA6963_Data::waitForReady(interface::OpMode const mode) const
{
  uint8_t status = 0;
  do
  {
    status = _io.readStatus();
  } while(!isReady(mode, status));
}

bool RA6963_Data::isReady(interface::OpMode const mode, uint8_t const status) const
{
  bool is_ready = false;

  switch(mode)
  {
  case interface::OpMode::NORMAL: is_ready = isReadyNormalMode(status); break;
  case interface::OpMode::AUTO  : is_ready = isReadyAutoMode  (status); break;
  }

  return is_ready;
}

bool RA6963_Data::isReadyNormalMode(uint8_t const status) const
{
  return ((status & (STATUS_BYTE_STA1_bm | STATUS_BYTE_STA0_bm)) == (STATUS_BYTE_STA1_bm | STATUS_BYTE_STA0_bm));
}

bool RA6963_Data::isReadyAutoMode(uint8_t const status) const
{
  return (
         ((status & STATUS_BYTE_STA3_bm) ==  STATUS_BYTE_STA3_bm)
         ||
         ((status & STATUS_BYTE_STA2_bm) ==  STATUS_BYTE_STA2_bm)
         );
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RA6963 */

} /* glcd */

} /* driver */

} /* snowfox */
