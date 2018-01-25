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

#include <spectre/driver/haptic/DRV2605/DRV2605.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace haptic
{

namespace DRV2605
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DRV2605::DRV2605(interface::DRV2605_ControlInterface & ctrl)
: _ctrl(ctrl)
{
  _ctrl.reset();
}

DRV2605::~DRV2605()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool DRV2605::open()
{
  return _ctrl.clrStandby();
}

bool DRV2605::read(uint8_t * buffer, uint32_t const num_bytes)
{
  return false; /* Not supported for this driver */
}

bool DRV2605::write(uint8_t const * buffer, uint32_t const num_bytes)
{
  return false; /* Not supported for this driver */
}

bool DRV2605::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* SET_MODE *************************************************************************/
  case IOCTL_SET_MODE:
  {
    uint8_t               const * arg_ptr     = static_cast<uint8_t *>            (arg     );
    interface::ModeSelect const   mode_select = static_cast<interface::ModeSelect>(*arg_ptr);
    return _ctrl.setMode(mode_select);
  }
  break;
  /* SET_WAVEFORM_LIBRARY *************************************************************/
  case IOCTL_SET_WAVEFORM_LIBRARY:
  {
    uint8_t                          const * arg_ptr             = static_cast<uint8_t *>                       (arg     );
    interface::WaveformLibrarySelect const   waveform_lib_select = static_cast<interface::WaveformLibrarySelect>(*arg_ptr);
    return _ctrl.setWaveformLibrary(waveform_lib_select);
  }
  break;
  /* SET_WAVEFORM ********************************************************************/
  case IOCTL_SET_WAVEFORM:
  {
    IoctlSetWaveFormArg const * arg_ptr = static_cast<IoctlSetWaveFormArg const *>(arg);
    return _ctrl.setWaveform(arg_ptr->waveform_sequencer_select, arg_ptr->waveform);
  }
  break;
  /* SET_ACTUATOR *********************************************************************/
  case IOCTL_SET_ACTUATOR:
  {
    uint8_t                   const * arg_ptr         = static_cast<uint8_t *>                (arg     );
    interface::ActuatorSelect const   actuator_select = static_cast<interface::ActuatorSelect>(*arg_ptr);
    return _ctrl.setActuator(actuator_select);
  }
  break;
  /* SET_GO ***************************************************************************/
  case IOCTL_SET_GO:
  {
    return _ctrl.setGo();
  }
  break;
  /* CLR_GO ***************************************************************************/
  case IOCTL_CLR_GO:
  {
    return _ctrl.clrGo();
  }
  break;
  }

  return false;
}

bool DRV2605::close()
{
  return _ctrl.setStandby();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */
