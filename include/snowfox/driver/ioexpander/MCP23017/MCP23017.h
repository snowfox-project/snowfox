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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_MCP23017_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_MCP23017_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/ioexpander/MCP23017/interface/control/MCP23017_Control.h>
#include <snowfox/driver/ioexpander/MCP23017/interface/config/MCP23017_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::ioexpander::MCP23017
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

class IoctlConfigInputArg
{

public:

  IoctlConfigInputArg(interface::Port const port, interface::Pin const pin, interface::PullUpMode const pull_up_mode)
  {
    data.port         = port;
    data.pin          = pin;
    data.pull_up_mode = pull_up_mode;
  }

  struct
  {
    interface::Port       port;
    interface::Pin        pin;
    interface::PullUpMode pull_up_mode;
  } data;
};

/**************************************************************************************/

class IoctlConfigOutputArg
{

public:

  IoctlConfigOutputArg(interface::Port const port, interface::Pin const pin)
  {
    data.port = port;
    data.pin  = pin;
  }

  struct
  {
    interface::Port       port;
    interface::Pin        pin;
  } data;
};

/**************************************************************************************/

class IoctlSetOutputPinArg
{

public:

  IoctlSetOutputPinArg(interface::Port const port, interface::Pin const pin, bool const set)
  {
    data.port = port;
    data.pin  = pin;
    data.set  = set;
  }

  struct
  {
    interface::Port port;
    interface::Pin  pin;
    bool            set;
  } data;
};

/**************************************************************************************/

class IoctlGetInputPinArg
{

public:

  IoctlGetInputPinArg(interface::Port const port, interface::Pin const pin, bool * is_set)
  {
    data.port   = port;
    data.pin    = pin;
    data.is_set = is_set;
  }

  struct
  {
    interface::Port   port;
    interface::Pin    pin;
    bool            * is_set;
  } data;
};

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_CONFIG_INPUT   = 0; /* Arg: ConfigInputArg  *  */
static uint32_t constexpr IOCTL_CONFIG_OUTPUT  = 1; /* Arg: ConfigOutputArg *  */
static uint32_t constexpr IOCTL_SET_OUTPUT_PIN = 2; /* Arg: SetOutputPinArg *  */
static uint32_t constexpr IOCTL_GET_INPUT_PIN = 3;  /* Arg: GetInputPinArg  *  */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP23017 final : public driver::interface::Driver
{

public:

           MCP23017(interface::MCP23017_Configuration & config,
                    interface::MCP23017_Control       & control);
  virtual ~MCP23017();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;


private:

  interface::MCP23017_Configuration & _config;
  interface::MCP23017_Control       & _control;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::ioexpander::MCP23017 */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MCP23017_MCP23017_H_ */
