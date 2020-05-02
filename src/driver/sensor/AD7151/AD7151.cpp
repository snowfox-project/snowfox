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

#include <snowfox/driver/sensor/AD7151/AD7151.h>

#include <string.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::AD7151
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AD7151::AD7151(interface::AD7151_Control & ctrl)
: _ctrl(ctrl)
{

}

AD7151::~AD7151()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool AD7151::open()
{
  return true; /* Do nothing */
}

ssize_t AD7151::read(uint8_t * buffer, ssize_t const num_bytes)
{
  uint16_t raw_data = 0;

  if(num_bytes < static_cast<ssize_t>(sizeof(raw_data))) return -1;
  if(!_ctrl.readConversionResult(&raw_data))             return -2;

  memcpy(buffer, &raw_data, sizeof(raw_data));

  return sizeof(raw_data);
}

ssize_t AD7151::write(uint8_t const * /* buffer */, ssize_t const /* num_bytes */)
{
  return -1; /* Not supported */
}

bool AD7151::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_CAPACITIVE_INPUT_RANGE *************************************************/
  case IOCTL_SET_CAPACITIVE_INPUT_RANGE:
  {
    uint8_t                         const * arg_ptr                = static_cast<uint8_t *>                      (arg     );
    interface::CapacitiveInputRange const   capacitive_input_range = static_cast<interface::CapacitiveInputRange>(*arg_ptr);
    return _ctrl.setCapacitiveInputRange(capacitive_input_range);
  }
  break;
  /* IOCTL_START_CONVERSION ***********************************************************/
  case IOCTL_START_CONVERSION:
  {
    return _ctrl.startSingleConversion();
  }
  break;
  /* IOCTL_CHECK_IF_CONVERSION_IS_COMPLETE ********************************************/
  case IOCTL_CHECK_IF_CONVERSION_IS_COMPLETE:
  {
    bool * arg_ptr = static_cast<bool *>(arg);
    return _ctrl.checkIfConversionIsComplete(arg_ptr);
  }
  break;
  }

  return false;
}

void AD7151::close()
{
  /* Do nothing */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::AD7151 */
