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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/N25Q256A/interface/N25Q256A_Control.h>

#include <snowfox/driver/memory/N25Q256A/interface/N25Q256A_Io.h>
#include <snowfox/hal/interface/delay/Delay.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace N25Q256A
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class N25Q256A_Control final : public interface::N25Q256A_Control
{

public:

           N25Q256A_Control(interface::N25Q256A_Io & io, hal::interface::Delay & delay);
  virtual ~N25Q256A_Control();


  virtual void reset          ()                                                                            override final;
  virtual void read           (uint32_t const read_addr,  uint8_t       * buffer, uint32_t const num_bytes) override final;
  virtual void write          (uint32_t const write_addr, uint8_t const * buffer, uint32_t const num_bytes) override final;
  virtual void eraseSubsector (uint32_t const subsector_num)                                                override final;

private:

  interface::N25Q256A_Io & _io;
  hal::interface::Delay  & _delay;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_CONTROL_H_ */
