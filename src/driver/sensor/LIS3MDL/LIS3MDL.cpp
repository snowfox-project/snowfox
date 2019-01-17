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

#include <snowfox/driver/sensor/LIS3MDL/LIS3MDL.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace LIS3MDL
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LIS3MDL::LIS3MDL(interface::LIS3MDL_Control & ctrl)
: _ctrl(ctrl)
{

}

LIS3MDL::~LIS3MDL()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool LIS3MDL::open()
{
  /* TODO */
  return false;
}

ssize_t LIS3MDL::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

ssize_t LIS3MDL::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

bool LIS3MDL::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_OPERATION_MODE_XY ******************************************************/
  case IOCTL_SET_OPERATION_MODE_XY:
  {
    uint8_t                     const * arg_ptr           = static_cast<uint8_t *>                  (arg     );
    interface::OperationMode_XY const   operating_mode_xy = static_cast<interface::OperationMode_XY>(*arg_ptr);
    return _ctrl.setOperationMode_XY(operating_mode_xy);
  }
  break;
  /* IOCTL_SET_OPERATION_MODE_Z *******************************************************/
  case IOCTL_SET_OPERATION_MODE_Z:
  {
    uint8_t                    const * arg_ptr          = static_cast<uint8_t *>                  (arg     );
    interface::OperationMode_Z const   operating_mode_z = static_cast<interface::OperationMode_Z>(*arg_ptr);
    return _ctrl.setOperationMode_Z(operating_mode_z);
  }
  break;
  /* IOCTL_SET_OUTPUT_DATA_RATE *******************************************************/
  case IOCTL_SET_OUTPUT_DATA_RATE:
  {
    uint8_t                   const * arg_ptr          = static_cast<uint8_t *>                (arg     );
    interface::OutputDataRate const   output_data_rate = static_cast<interface::OutputDataRate>(*arg_ptr);
    return _ctrl.setOutputDataRate(output_data_rate);
  }
  break;
  /* IOCTL_SET_FULL_SCALE_RANGE *******************************************************/
  case IOCTL_SET_FULL_SCALE_RANGE:
  {
    uint8_t                   const * arg_ptr          = static_cast<uint8_t *>                (arg     );
    interface::FullScaleRange const   full_scale_range = static_cast<interface::FullScaleRange>(*arg_ptr);
    return _ctrl.setFullScaleRange(full_scale_range);
  }
  break;
  /* IOCTL_SET_CONVERSION_MODE ********************************************************/
  case IOCTL_SET_CONVERSION_MODE:
  {
    uint8_t                   const * arg_ptr         = static_cast<uint8_t *>                (arg     );
    interface::ConversionMode const   conversion_mode = static_cast<interface::ConversionMode>(*arg_ptr);
    return _ctrl.setConversionMode(conversion_mode);
  }
  break;
  }

  return false;
}

void LIS3MDL::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* snowfox */
