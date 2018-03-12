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

#include <spectre/driver/sensor/BMG160/BMG160.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace BMG160
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

BMG160::BMG160(interface::BMG160_Control & ctrl)
: _ctrl(ctrl)
{

}

BMG160::~BMG160()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool BMG160::open()
{
  /* TODO */
  return false;
}

ssize_t BMG160::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

ssize_t BMG160::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

bool BMG160::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_OUTPUT_DATA_RATE_AND_BANDWIDTH *****************************************/
  case IOCTL_SET_OUTPUT_DATA_RATE_AND_BANDWIDTH:
  {
    uint8_t                                    const * arg_ptr                        = static_cast<uint8_t *>                                 (arg     );
    interface::OutputDataRateAndBandwithSelect const   output_data_rate_and_bandwidth = static_cast<interface::OutputDataRateAndBandwithSelect>(*arg_ptr);
    return _ctrl.setOutputDataRateAndBandwith(output_data_rate_and_bandwidth);
  }
  break;
  /* IOCTL_SET_FULL_SCALE_RANGE *******************************************************/
  case IOCTL_SET_FULL_SCALE_RANGE:
  {
    uint8_t                         const * arg_ptr          = static_cast<uint8_t *>                      (arg     );
    interface::FullScaleRangeSelect const   full_scale_range = static_cast<interface::FullScaleRangeSelect>(*arg_ptr);
    return _ctrl.setFullScaleRange(full_scale_range);
  }
  break;
  }

  return false;
}

void BMG160::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMG160 */

} /* sensor */

} /* driver */

} /* spectre */
