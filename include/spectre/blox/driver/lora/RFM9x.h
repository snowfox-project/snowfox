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

#ifndef INCLUDE_SPECTRE_BLOX_DRIVER_LORA_RFM9X_H_
#define INCLUDE_SPECTRE_BLOX_DRIVER_LORA_RFM9X_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/locking/CriticalSection.h>
#include <spectre/hal/interface/extint/ExternalInterruptAssembly.h>

#include <spectre/driver/lora/RFM9x/interface/RFM9x_Io.h>

#include <spectre/driver/lora/RFM9x/RFM9x.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Status.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Control.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Configuration.h>

#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_Dio0EventCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_onTxDoneCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_onRxDoneCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_onCadDoneCallback.h>

#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_Dio1EventCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_onRxTimeoutCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_onCadDetectedCallback.h>
#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_onFhssChangeChannelCallback.h>

#include <spectre/os/event/Event.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x
{

public:

  RFM9x(hal::interface::CriticalSection                & crit_sec,
        hal::interface::ExternalInterruptAssembly      & ext_int_ctrl,
        uint8_t                                  const   dio0_ext_int_num,
        uint8_t                                  const   dio1_ext_int_num,
        driver::lora::RFM9x::interface::RFM9x_Io       & rfm9x_io,
        uint32_t                                 const   rfm9x_f_xosc_hz);

  RFM9x(hal::interface::CriticalSection                        & crit_sec,
        hal::interface::ExternalInterruptAssembly              & ext_int_ctrl,
        uint8_t                                          const   dio0_ext_int_num,
        uint8_t                                          const   dio1_ext_int_num,
        driver::lora::RFM9x::interface::RFM9x_Io               & rfm9x_io,
        uint32_t                                         const   rfm9x_f_xosc_hz,
        uint32_t                                         const   frequency_hz,
        driver::lora::RFM9x::interface::SignalBandwidth  const   signal_bandwidth,
        driver::lora::RFM9x::interface::CodingRate       const   coding_rate,
        driver::lora::RFM9x::interface::SpreadingFactor  const   spreading_factor,
        uint16_t                                         const   preamble_length,
        uint16_t                                         const   tx_fifo_size,
        uint16_t                                         const   rx_fifo_size);

  ~RFM9x();

  driver::lora::RFM9x::RFM9x & operator () () { return _rfm9x; }


private:

  driver::lora::RFM9x::RFM9x_Configuration               _rfm9x_config;
  driver::lora::RFM9x::RFM9x_Control                     _rfm9x_control;
  driver::lora::RFM9x::RFM9x_Status                      _rfm9x_status;

  os::Event                                              _rfm9x_tx_done_event;
  os::Event                                              _rfm9x_rx_done_event;
  os::Event                                              _rfm9x_rx_timeout_event;

  driver::lora::RFM9x::RFM9x_onTxDoneCallback            _rfm9x_on_tx_done_callback;
  driver::lora::RFM9x::RFM9x_onRxDoneCallback            _rfm9x_on_rx_done_callback;
  driver::lora::RFM9x::RFM9x_onCadDoneCallback           _rfm9x_on_cad_done_callback;
  driver::lora::RFM9x::RFM9x_Dio0EventCallback           _rfm9x_dio0_event_callback;

  driver::lora::RFM9x::RFM9x_onRxTimeoutCallback         _rfm9x_on_rx_timeout_callback;
  driver::lora::RFM9x::RFM9x_onFhssChangeChannelCallback _rfm9x_on_fhss_change_channel_callback;
  driver::lora::RFM9x::RFM9x_onCadDetectedCallback       _rfm9x_on_cad_detected_callback;
  driver::lora::RFM9x::RFM9x_Dio1EventCallback           _rfm9x_dio1_event_callback;

  driver::lora::RFM9x::RFM9x                             _rfm9x;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_DRIVER_LORA_RFM9X_H_ */
