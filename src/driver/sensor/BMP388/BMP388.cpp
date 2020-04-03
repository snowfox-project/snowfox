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

#include <snowfox/driver/sensor/BMP388/BMP388.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

BMP388::BMP388(interface::BMP388_Configuration & config)
: _config{config}
{

}

BMP388::~BMP388()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool BMP388::open()
{
  /* TODO */ return false;
}

ssize_t BMP388::read(uint8_t * /* buffer */, ssize_t const /* num_bytes */)
{
  /* TODO */ return -1;
}

ssize_t BMP388::write(uint8_t const * /* buffer */, ssize_t const /* num_bytes */)
{
  /* TODO */ return -1;
}

bool BMP388::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_PRESSURE_OVERSAMPLING **************************************************/
  case IOCTL_SET_PRESSURE_OVERSAMPLING:
  {
    uint8_t                         const * arg_ptr               = static_cast<uint8_t *>                      (arg     );
    interface::PressureOversampling const   pressure_oversampling = static_cast<interface::PressureOversampling>(*arg_ptr);
    _config.configPressureOversampling(pressure_oversampling);
    return true;
  }
  break;
  /* IOCTL_SET_TEMPERATURE_OVERSAMPLING ***********************************************/
  case IOCTL_SET_TEMPERATURE_OVERSAMPLING:
  {
    uint8_t                            const * arg_ptr                  = static_cast<uint8_t *>                         (arg     );
    interface::TemperatureOversampling const   temperature_oversampling = static_cast<interface::TemperatureOversampling>(*arg_ptr);
    _config.configTemperatureOversampling(temperature_oversampling);
    return true;
  }
  break;
  /* IOCTL_SET_OUTPUT_DATA_RATE *******************************************************/
  case IOCTL_SET_OUTPUT_DATA_RATE:
  {
    uint8_t                   const * arg_ptr          = static_cast<uint8_t *>                (arg     );
    interface::OutputDataRate const   output_data_rate = static_cast<interface::OutputDataRate>(*arg_ptr);
    _config.configOutputDataRate(output_data_rate);
    return true;
  }
  break;
  }

  return false;
}

void BMP388::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */
