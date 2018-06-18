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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/LIS3DSH/LIS3DSH.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace LIS3DSH
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LIS3DSH::LIS3DSH(interface::LIS3DSH_Control & ctrl)
: _ctrl(ctrl)
{

}

LIS3DSH::~LIS3DSH()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool LIS3DSH::open()
{
  /* TODO */
  return false;
}

ssize_t LIS3DSH::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

ssize_t LIS3DSH::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

bool LIS3DSH::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
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
  /* IOCTL_SET_FILTER_BANDWIDTH *******************************************************/
  case IOCTL_SET_FILTER_BANDWIDTH:
  {
    uint8_t                    const * arg_ptr          = static_cast<uint8_t *>                 (arg     );
    interface::FilterBandwidth const   filter_bandwidth = static_cast<interface::FilterBandwidth>(*arg_ptr);
    return _ctrl.setFilterBandwidth(filter_bandwidth);
  }
  break;
  /* IOCTL_ENABLE_XYZ *****************************************************************/
  case IOCTL_ENABLE_XYZ:
  {
    return _ctrl.enableXYZAxis();
  }
  break;
  /* IOCTL_ENABLE_X *******************************************************************/
  case IOCTL_ENABLE_X:
  {
    return _ctrl.enableXAxis();
  }
  break;
  /* IOCTL_ENABLE_Y *******************************************************************/
  case IOCTL_ENABLE_Y:
  {
    return _ctrl.enableYAxis();
  }
  break;
  /* IOCTL_ENABLE_Z *******************************************************************/
  case IOCTL_ENABLE_Z:
  {
    return _ctrl.enableZAxis();
  }
  break;
  }

  return false;
}

void LIS3DSH::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* spectre */
