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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/AT45DBx/interface/AT45DBx_Control.h>

#include <snowfox/driver/memory/AT45DBx/interface/AT45DBx_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::AT45DBx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AT45DBx_Control final : public interface::AT45DBx_Control
{

public:

           AT45DBx_Control(interface::AT45DBx_Io & io);
  virtual ~AT45DBx_Control();


  virtual void erase(                                                                      ) override;
  virtual void erase(uint32_t const page, uint32_t const page_shift                        ) override;
  virtual void write(uint32_t const page, uint32_t const page_shift, uint8_t const * buffer) override;
  virtual void read (uint32_t const offset, uint8_t * buffer, uint16_t const num_bytes     ) override;


private:

  interface::AT45DBx_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::AT45DBx */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_CONTROL_H_ */
