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

#ifndef INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_H_
#define INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <spectre/hal/interface/spi/SpiMaster.h>
#include <spectre/hal/interface/gpio/DigitalOutPin.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * CLASS DECLARATION Interface
 **************************************************************************************/

class Interface
{

public:

           Interface() { }
  virtual ~Interface() { }


  virtual void eraseChip   (                                                                       ) = 0;
  virtual void erasePage   (uint16_t const page                                                    ) = 0;
  virtual void writePage   (uint16_t const page,   uint8_t const * buffer                          ) = 0;
  virtual void read        (uint32_t const offset, uint8_t       * buffer, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class ConfigurationInterface
{

public:

           ConfigurationInterface() { }
  virtual ~ConfigurationInterface() { }


  virtual void readDeviceId (uint8_t * dev_id) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION AT45DBx
 **************************************************************************************/

class AT45DBx : public Interface,
                public ConfigurationInterface
{

public:

           AT45DBx(hal::interface::SpiMaster & spi_master, hal::interface::DigitalOutPin & cs);
  virtual ~AT45DBx();


  /* AD45DBx Interface */

  virtual void eraseChip   (                                                                       ) override;
  virtual void erasePage   (uint16_t const page                                                    ) override;
  virtual void writePage   (uint16_t const page,   uint8_t const * buffer                          ) override;
  virtual void read        (uint32_t const offset, uint8_t       * buffer, uint16_t const num_bytes) override;


  /* AT45DBx Configuration Interface */

  virtual void readDeviceId (uint8_t * dev_id) override;


  static uint32_t getPageShift(uint8_t  const * dev_id);
  static uint32_t getNumPages (uint8_t  const * dev_id);

  inline void     setPageShift(uint32_t const   page_shift) { _page_shift = page_shift; }
  inline void     setNumPages (uint32_t const   num_pages ) { _num_pages  = num_pages;  }

private:

  hal::interface::SpiMaster     & _spi_master;
  hal::interface::DigitalOutPin & _cs;

  uint32_t                        _page_shift;
  uint32_t                        _num_pages;

  inline uint16_t getPageSize () const { return static_cast<uint16_t>(1 << _page_shift); }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_H_ */
