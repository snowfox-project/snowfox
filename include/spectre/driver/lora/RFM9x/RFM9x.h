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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/interface/Driver.h>

#include <spectre/driver/lora/RFM9x/interface/RFM9x_FifoControl.h>
#include <spectre/driver/lora/RFM9x/interface/RFM9x_Configuration.h>

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
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_FREQUENCY_HZ      = 0; /* Arg: uint32_t *                                 */
static uint32_t constexpr IOCTL_SET_SIGNAL_BANDWIDTH  = 1; /* Arg: interface::SignalBandwidth * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_CODING_RATE       = 2; /* Arg: interface::CodingRate *      -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_SPREADING_FACTOR  = 3; /* Arg: interface::SpreadingFactor * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_PREAMBLE_LENGTH   = 4; /* Arg: uint16_t *                                 */
static uint32_t constexpr IOCTL_SET_TX_FIFO_SIZE      = 5; /* Arg: uint16_t *                                 */
static uint32_t constexpr IOCTL_SET_RX_FIFO_SIZE      = 6; /* Arg: uint16_t *                                 */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x : public driver::interface::Driver
{

public:

           RFM9x(interface::RFM9x_Configuration & config,
                 interface::RFM9x_FifoControl   & fifo_ctrl);
  virtual ~RFM9x();


  bool    open (                                                  ) override;
  ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  void    close(                                                  ) override;


private:

  interface::RFM9x_Configuration & _config;
  interface::RFM9x_FifoControl   & _fifo_ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_H_ */
