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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_IOSPI_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_IOSPI_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/AT45DBx/interface/AT45DBx_Io.h>

#include <snowfox/hal/interface/gpio/DigitalOutPin.h>
#include <snowfox/hal/interface/spi/SpiMasterControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::AT45DBx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AT45DBx_IoSpi final : public interface::AT45DBx_Io
{

public:

           AT45DBx_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs);
  virtual ~AT45DBx_IoSpi();


  virtual void exchange(uint8_t const * buf_cmd_in                                                                ) override;
  virtual void exchange(uint8_t const * buf_cmd_in, uint8_t       * buf_cmd_out                                   ) override;
  virtual void exchange(uint8_t const * buf_cmd_in, uint8_t const * buf_data_in,  uint16_t const buf_data_in_size ) override;
  virtual void exchange(uint8_t const * buf_cmd_in, uint8_t       * buf_data_out, uint16_t const buf_data_out_size) override;


private:

  hal::interface::SpiMasterControl & _spi_master;
  hal::interface::DigitalOutPin    & _cs;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::AT45DBx */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_IOSPI_H_ */
