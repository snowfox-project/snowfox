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

RFM9x::RFM9x(interface::RFM9x_Control & ctrl)
: _ctrl(ctrl)
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
  /* TODO*/
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
  /* IOCTL_SET_OPERATING_MODE *********************************************************/
  case IOCTL_SET_OPERATING_MODE:
  {
    uint8_t                  const * arg_ptr        = static_cast<uint8_t *>               (arg     );
    interface::OperatingMode const   operating_mode = static_cast<interface::OperatingMode>(*arg_ptr);
    _ctrl.setOperatingMode(operating_mode);
    return true;
  }
  break;
  /* IOCTL_SET_LORA_MODE **************************************************************/
  case IOCTL_SET_LORA_MODE:
  {
    uint8_t             const * arg_ptr   = static_cast<uint8_t *>          (arg     );
    interface::LoRaMode const   lora_mode = static_cast<interface::LoRaMode>(*arg_ptr);
    _ctrl.setLoRaMode(lora_mode);
    return true;
  }
  break;
  /* IOCTL_SET_MODULATION_TYPE ********************************************************/
  case IOCTL_SET_MODULATION_TYPE:
  {
    uint8_t                   const * arg_ptr         = static_cast<uint8_t *>                (arg     );
    interface::ModulationType const   modulation_type = static_cast<interface::ModulationType>(*arg_ptr);
    _ctrl.setModulationType(modulation_type);
    return true;
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
