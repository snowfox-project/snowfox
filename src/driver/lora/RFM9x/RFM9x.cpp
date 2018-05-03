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

#include <spectre/driver/lora/RFM9x/RFM9x.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace lora
{

namespace RFM9x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x::RFM9x(interface::RFM9x_Configuration & config)
: _config(config)
{

}

RFM9x::~RFM9x()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool RFM9x::open()
{
  _config.setOperatingMode(interface::OperatingMode::SLEEP);
  _config.setLoRaMode     (interface::LoRaMode::LoRa      );

  return false;
}

ssize_t RFM9x::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO*/
  return -1;
}

ssize_t RFM9x::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO*/
  return -1;
}

bool RFM9x::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_FREQUENCY_HZ ***********************************************************/
  case IOCTL_SET_FREQUENCY_HZ:
  {
    uint32_t const * frequency_hz = static_cast<uint32_t *>(arg);
    _config.setFrequency(*frequency_hz);
    return true;
  }
  break;
  /* IOCTL_SET_SIGNAL_BANDWIDTH *******************************************************/
  case IOCTL_SET_SIGNAL_BANDWIDTH:
  {
    uint8_t                    const * arg_ptr          = static_cast<uint8_t *>                 (arg     );
    interface::SignalBandwidth const   signal_bandwidth = static_cast<interface::SignalBandwidth>(*arg_ptr);
    _config.setSignalBandwidth(signal_bandwidth);
  }
  break;
  /* IOCTL_SET_CODING_RATE ************************************************************/
  case IOCTL_SET_CODING_RATE:
  {
    uint8_t               const * arg_ptr     = static_cast<uint8_t *>            (arg     );
    interface::CodingRate const   coding_rate = static_cast<interface::CodingRate>(*arg_ptr);
    _config.setCodingRate(coding_rate);
  }
  break;
  /* IOCTL_SET_SPREADING_FACTOR *******************************************************/
  case IOCTL_SET_SPREADING_FACTOR:
  {
    uint8_t                    const * arg_ptr          = static_cast<uint8_t *>                 (arg     );
    interface::SpreadingFactor const   spreading_factor = static_cast<interface::SpreadingFactor>(*arg_ptr);
    _config.setSpreadingFactor(spreading_factor);
  }
  break;
  }


  return false;
}

void RFM9x::close()
{
  /* TODO*/
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
