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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/blox/driver/lora/RFM9x.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace blox
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x::RFM9x(hal::interface::CriticalSection                & crit_sec,
             hal::interface::ExternalInterruptAssembly      & ext_int_ctrl,
             uint8_t                                  const   dio0_ext_int_num,
             uint8_t                                  const   dio1_ext_int_num,
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
  ext_int_ctrl.registerInterruptCallback(dio0_ext_int_num, &_rfm9x_dio0_event_callback);
  ext_int_ctrl.registerInterruptCallback(dio1_ext_int_num, &_rfm9x_dio1_event_callback);

  _rfm9x.open();
}

RFM9x::RFM9x(hal::interface::CriticalSection                        & crit_sec,
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
             uint16_t                                         const   rx_fifo_size)
: RFM9x(crit_sec, ext_int_ctrl, dio0_ext_int_num, dio1_ext_int_num, rfm9x_io, rfm9x_f_xosc_hz)
{
  uint32_t ioctl_frequenzy_Hz     = frequency_hz;
  uint8_t  ioctl_signal_bandwidth = static_cast<uint8_t>(signal_bandwidth);
  uint8_t  ioctl_coding_rate      = static_cast<uint8_t>(coding_rate);
  uint8_t  ioctl_spreading_factor = static_cast<uint8_t>(spreading_factor);
  uint16_t ioctl_preamble_length  = preamble_length;
  uint16_t ioctl_tx_fifo_size     = tx_fifo_size;
  uint16_t ioctl_rx_fifo_size     = rx_fifo_size;

  _rfm9x.ioctl(driver::lora::RFM9x::IOCTL_SET_FREQUENCY_HZ,     static_cast<void *>(&ioctl_frequenzy_Hz    ));
  _rfm9x.ioctl(driver::lora::RFM9x::IOCTL_SET_SIGNAL_BANDWIDTH, static_cast<void *>(&ioctl_signal_bandwidth));
  _rfm9x.ioctl(driver::lora::RFM9x::IOCTL_SET_CODING_RATE,      static_cast<void *>(&ioctl_coding_rate     ));
  _rfm9x.ioctl(driver::lora::RFM9x::IOCTL_SET_SPREADING_FACTOR, static_cast<void *>(&ioctl_spreading_factor));
  _rfm9x.ioctl(driver::lora::RFM9x::IOCTL_SET_PREAMBLE_LENGTH,  static_cast<void *>(&ioctl_preamble_length ));
  _rfm9x.ioctl(driver::lora::RFM9x::IOCTL_SET_TX_FIFO_SIZE,     static_cast<void *>(&ioctl_tx_fifo_size    ));
  _rfm9x.ioctl(driver::lora::RFM9x::IOCTL_SET_RX_FIFO_SIZE,     static_cast<void *>(&ioctl_rx_fifo_size    ));
}

RFM9x::~RFM9x()
{
  _rfm9x.close();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* blox */

} /* snowfox */
