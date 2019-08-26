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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_NORDRIVER_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_NORDRIVER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef struct
{
  /* Different NOR flash types support different API's. Some may support chip/sector/
   * subsector-level erase, others might only support chip/sector-level erase. It's
   * the same with write and read access. Viewed from the point-of-view of using this
   * generic NOR driver as interface for an overlying embedded flash filesystem there
   * are actually only 6 parameter that count:
   * - What's the smallest erase block size and how many erase blocks are available?
   * - What's the smallest write block size and how many write blocks are available?
   * - What's the smallest read block size and how many read blocks are available?
   * In any case the statement
   *   erase_block_size * erase_block_size_num ==
   *   write_block_size * write_block_size_num ==
   *   read_block_size * read_block_size_num
   * should hold true.
   */
  uint32_t erase_block_size;
  uint32_t erase_block_size_num;
  uint32_t write_block_size;
  uint32_t write_block_size_num;
  uint32_t read_block_size;
  uint32_t read_block_size_num;
} NorDriverCapabilities;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_GET_CAPABILITIES = 0; /* Arg: NorDriverCapabilities * capabilities */
static uint32_t constexpr IOCTL_ERASE            = 1; /* Arg: uint32_t * erase_block_num           */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class NorDriver : public interface::Driver
{

public:

           NorDriver() { }
  virtual ~NorDriver() { }


  virtual bool    open (                                                  ) = 0;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) = 0;

protected:

  virtual ssize_t read                  (uint32_t const read_addr,  uint8_t       * buffer, ssize_t const num_bytes) = 0;
  virtual ssize_t write                 (uint32_t const write_addr, uint8_t const * buffer, ssize_t const num_bytes) = 0;
  virtual bool    ioctl_get_capabilities(NorDriverCapabilities * capabilities)                                       = 0;
  virtual bool    ioctl_erase           (uint32_t const erase_block_num)                                             = 0;

private:

  static unsigned int constexpr READ_ADDR_SIZE  = sizeof(uint32_t);
  static unsigned int constexpr WRITE_ADDR_SIZE = sizeof(uint32_t);

  static uint32_t          toReadAddr     (uint8_t       * buffer);
  static uint32_t          toWriteAddr    (uint8_t const * buffer);
  static uint8_t        *  toReadBuffer   (uint8_t       * buffer);
  static uint8_t  const *  toWriteBuffer  (uint8_t const * buffer);
  static ssize_t           toReadNumBytes (ssize_t const   num_bytes);
  static ssize_t           toWriteNumBytes(ssize_t const   num_bytes);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_NORDRIVER_H_ */
