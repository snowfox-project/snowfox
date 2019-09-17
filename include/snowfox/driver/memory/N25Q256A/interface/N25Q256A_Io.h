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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_INTERFACE_N25Q256A_IO_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_INTERFACE_N25Q256A_IO_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

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

namespace interface
{

/**************************************************************************************
 * DEFINE
 **************************************************************************************/

/* STATUS REGISTER */
#define N25Q256A_STATUS_REG_ADDRESSING_bp                 (7)
#define N25Q256A_STATUS_REG_WRITE_IN_PROG_bp              (0)

/* NON VOLATILE CONFIGURATION REGISTER */
#define N25Q256A_NON_VOLATILE_CONFIG_REG_ADDRESS_BYTE_bp  (0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Command : uint8_t
{
  WRITE_DISABLE                 = 0x04,
  READ_STATUS_REG               = 0x05,
  WRITE_ENABLE                  = 0x06,
  READ_NON_VOLATILE_CONFIG_REG  = 0xB5,
  WRITE_NON_VOLATILE_CONFIG_REG = 0xB1,
  SUBSECTOR_ERASE_4_BYTE_ADDR   = 0x21,
  PAGE_PROGRAM_4_BYTE_ADDR      = 0x12,
  READ_4_BYTE_ADDR              = 0x13,
  READ_DEVICE_ID                = 0x9E
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class N25Q256A_Io
{

public:

  virtual ~N25Q256A_Io() { }


  virtual void transfer(Command  const   cmd,
                        uint8_t  const * tx_buf,
                        uint32_t const   tx_num_bytes,
                        uint8_t  const   tx_fill_data,
                        uint8_t        * rx_buf,
                        uint32_t const   rx_num_bytes,
                        uint32_t const   rx_start_pos) = 0;

  virtual void transfer(Command  const   cmd,
                        uint8_t  const * tx_buf_1,
                        uint32_t const   tx_num_bytes_1,
                        uint8_t  const * tx_buf_2,
                        uint32_t const   tx_num_bytes_2) = 0;

  inline  void transfer(Command  const   cmd,
                        uint8_t  const * tx_buf,
                        uint32_t const   tx_num_bytes)
  {
    transfer(cmd, tx_buf, tx_num_bytes, 0, 0);
  }

  void     enableWrite     ();
  uint8_t  readStatusReg   ();
  uint16_t readNVConfigReg ();
  void     writeNVConfigReg(uint16_t const nv_config_reg);
  bool     isBusy          ();

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_INTERFACE_N25Q256A_IO_H_ */
