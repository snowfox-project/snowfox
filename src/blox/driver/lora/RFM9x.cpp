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

#include <spectre/blox/driver/lora/RFM9x.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x::RFM9x(hal::interface::CriticalSection                & crit_sec,
             driver::lora::RFM9x::interface::RFM9x_Io       & rfm9x_io,
             uint32_t                                 const   rfm9x_f_xosc_hz)
: _rfm9x_config                          (rfm9x_io, rfm9x_f_xosc_hz),
  _rfm9x_control                         (rfm9x_io),
  _rfm9x_status                          (rfm9x_io),

  _rfm9x_tx_done_event                   (crit_sec),
  _rfm9x_rx_done_event                   (crit_sec),
  _rfm9x_rx_timeout_event                (crit_sec),

  _rfm9x_on_tx_done_callback             (_rfm9x_tx_done_event),
  _rfm9x_on_rx_done_callback             (_rfm9x_rx_done_event),
  _rfm9x_on_cad_done_callback            (),
  _rfm9x_dio0_event_callback             (_rfm9x_control, _rfm9x_on_tx_done_callback, _rfm9x_on_rx_done_callback, _rfm9x_on_cad_done_callback),

  _rfm9x_on_rx_timeout_callback          (_rfm9x_rx_timeout_event),
  _rfm9x_on_fhss_change_channel_callback (),
  _rfm9x_on_cad_detected_callback        (),
  _rfm9x_dio1_event_callback             (_rfm9x_control, _rfm9x_on_rx_timeout_callback, _rfm9x_on_fhss_change_channel_callback, _rfm9x_on_cad_detected_callback),

  _rfm9x                                 (_rfm9x_config, _rfm9x_control, _rfm9x_status, _rfm9x_rx_done_event, _rfm9x_rx_timeout_event, _rfm9x_tx_done_event)
{

}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* blox */

} /* spectre */
