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

#include <spectre/driver/ioexpander/MCP23017/MCP23017.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace ioexpander
{

namespace MCP23017
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MCP23017::MCP23017(interface::MCP23017_Configuration & config, interface::MCP23017_Control & control)
: _config (config ),
  _control(control)
{

}

MCP23017::~MCP23017()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool MCP23017::open()
{
  return true; /* Nothing to do */
}

ssize_t MCP23017::read(uint8_t * buffer, ssize_t const num_bytes)
{
  static ssize_t const READ_BUFFER_SIZE = 2;

  if(num_bytes < READ_BUFFER_SIZE) return -1;

  if(!_control.read(interface::Port::A, buffer + 0)) return -1;
  if(!_control.read(interface::Port::B, buffer + 1)) return -1;

  return READ_BUFFER_SIZE;
}

ssize_t MCP23017::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  static ssize_t const WRITE_BUFFER_SIZE = 2;

  if(num_bytes < WRITE_BUFFER_SIZE) return -1;

  if(!_control.write(interface::Port::A, buffer[0])) return -1;
  if(!_control.write(interface::Port::B, buffer[1])) return -1;

  return WRITE_BUFFER_SIZE;
}

bool MCP23017::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_CONFIG_INPUT ***************************************************************/
  case IOCTL_CONFIG_INPUT:
  {
    IoctlConfigInputArg const * arg_ptr = static_cast<IoctlConfigInputArg const *>(arg);
    return _config.configAsInput(arg_ptr->data.port, arg_ptr->data.pin, arg_ptr->data.pull_up_mode);
  }
  break;
  /* IOCTL_CONFIG_OUTPUT **************************************************************/
  case IOCTL_CONFIG_OUTPUT:
  {
    IoctlConfigOutputArg const * arg_ptr = static_cast<IoctlConfigOutputArg const *>(arg);
    return _config.configAsOutput(arg_ptr->data.port, arg_ptr->data.pin);
  }
  break;
  /* IOCTL_SET_OUTPUT_PIN *************************************************************/
  case IOCTL_SET_OUTPUT_PIN:
  {
    IoctlSetOutputPinArg const * arg_ptr = static_cast<IoctlSetOutputPinArg const *>(arg);
    if  (arg_ptr->data.set) return _control.set(arg_ptr->data.port, arg_ptr->data.pin);
    else                    return _control.clr(arg_ptr->data.port, arg_ptr->data.pin);
  }
  break;
  /* IOCTL_GET_INPUT_PIN **************************************************************/
  case IOCTL_GET_INPUT_PIN:
  {
    IoctlGetInputPinArg * arg_ptr = static_cast<IoctlGetInputPinArg *>(arg);
    return _control.isSet(arg_ptr->data.port, arg_ptr->data.pin, arg_ptr->data.is_set);
  }
  break;
  }

  return false;
}

void MCP23017::close()
{
  /* Nothing to do */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP23017 */

} /* ioexpander */

} /* driver */

} /* spectre */
