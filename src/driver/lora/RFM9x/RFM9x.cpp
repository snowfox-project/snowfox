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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/RFM9x.h>

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
 * CTOR/DTOR
 **************************************************************************************/

RFM9x::RFM9x(interface::RFM9x_Configuration & config,
             interface::RFM9x_Control       & control,
             interface::RFM9x_Status        & status,
             os::interface::EventConsumer   & rx_done_event,
             os::interface::EventConsumer   & rx_timeout_event,
             os::interface::EventConsumer   & tx_done_event)
: _config          (config          ),
  _control         (control         ),
  _status          (status          ),
  _rx_done_event   (rx_done_event   ),
  _rx_timeout_event(rx_timeout_event),
  _tx_done_event   (tx_done_event   )
{
  _event_group_rx_done_rx_timeout.addEvent(rx_done_event   );
  _event_group_rx_done_rx_timeout.addEvent(rx_timeout_event);
}

RFM9x::~RFM9x()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool RFM9x::open()
{
        _control.setOperatingMode     (interface::OperatingMode::SLEEP);
  while(_control.getOperatingMode() != interface::OperatingMode::SLEEP) { /* wait */ }

  _config.setLoRaMode           (interface::LoRaMode::LoRa              );
  _config.setHeaderMode         (interface::HeaderMode::Explicit        );
  _config.setPacketFormat       (interface::PacketFormat::VariableLength);
  _config.setTransceiverLocation(interface::TransceiverLocation::Static );

  return true;
}

ssize_t RFM9x::read(uint8_t * buffer, ssize_t const num_bytes)
{
  if(num_bytes < 1                                                    ) return static_cast<ssize_t>(RetCodeRead::ParameterError      );

  uint16_t const rx_fifo_size = _config.getRxFifoSize();
  if(static_cast<uint16_t>(num_bytes) > rx_fifo_size                  ) return static_cast<ssize_t>(RetCodeRead::RxFifoSizeExceeded  );

  if(_control.getOperatingMode() != interface::OperatingMode::SLEEP   ) return static_cast<ssize_t>(RetCodeRead::ModemBusy_NotSleep  );

        _control.setOperatingMode     (interface::OperatingMode::STDBY);
  while(_control.getOperatingMode() != interface::OperatingMode::STDBY) { /* wait */ }

  if(_control.getOperatingMode() != interface::OperatingMode::STDBY   ) return static_cast<ssize_t>(RetCodeRead::ModemBusy_NotStandby);

  _event_group_rx_done_rx_timeout.clearAllEvents();

  _control.setOperatingMode(interface::OperatingMode::RXSINGLE);

  os::waitAny(_event_group_rx_done_rx_timeout);

  uint8_t const bytes_read = _control.readFromReceiveFifo(buffer, static_cast<uint8_t>(num_bytes));

  return static_cast<ssize_t>(bytes_read);
}

ssize_t RFM9x::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* Check for parameter errors */

  if(num_bytes < 1                                                 ) return static_cast<ssize_t>(RetCodeWrite::ParameterError      );

  uint16_t const tx_fifo_size = _config.getTxFifoSize();
  if(static_cast<uint16_t>(num_bytes) > tx_fifo_size               ) return static_cast<ssize_t>(RetCodeWrite::TxFifoSizeExceeded  );

  /* Check if we are in operating mode SLEEP */

  if(_control.getOperatingMode() != interface::OperatingMode::SLEEP) return static_cast<ssize_t>(RetCodeWrite::ModemBusy_NotSleep  );

  /* Change to operating mode STDBY */

        _control.setOperatingMode     (interface::OperatingMode::STDBY);
  while(_control.getOperatingMode() != interface::OperatingMode::STDBY) { /* wait */ }

  if(_control.getOperatingMode() != interface::OperatingMode::STDBY) return static_cast<ssize_t>(RetCodeWrite::ModemBusy_NotStandby);

  /* Load message for transmission into FIFO */

  _control.writeToTransmitFifo(buffer, static_cast<uint8_t>(num_bytes));

  /* Clear the tx done event and setup TX DONE as event source for DIO0 */

  _tx_done_event.clear();

  _control.setDio0EventSource(interface::Dio0EventSource::TxDone);

  /* Initiate transmission */

  _control.setOperatingMode(interface::OperatingMode::TX);

  /* Wait for completion of the transmission */

  os::interface::wait(_tx_done_event);

  /* Change back to operating mode SLEEP */

        _control.setOperatingMode     (interface::OperatingMode::SLEEP);
  while(_control.getOperatingMode() != interface::OperatingMode::SLEEP) { /* wait */ }

  return num_bytes;
}

bool RFM9x::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_FREQUENCY_HZ ***********************************************************/
  case IOCTL_SET_FREQUENCY_HZ:
  {
    uint32_t const * frequency_hz = static_cast<uint32_t *>(arg);
    _config.setFrequency(*frequency_hz);
    return true;
  }
  break;
  /* IOCTL_SET_SIGNAL_BANDWIDTH *******************************************************/
  case IOCTL_SET_SIGNAL_BANDWIDTH:
  {
    uint8_t                    const * arg_ptr          = static_cast<uint8_t *>                 (arg     );
    interface::SignalBandwidth const   signal_bandwidth = static_cast<interface::SignalBandwidth>(*arg_ptr);
    _config.setSignalBandwidth(signal_bandwidth);
    return true;
  }
  break;
  /* IOCTL_SET_CODING_RATE ************************************************************/
  case IOCTL_SET_CODING_RATE:
  {
    uint8_t               const * arg_ptr     = static_cast<uint8_t *>            (arg     );
    interface::CodingRate const   coding_rate = static_cast<interface::CodingRate>(*arg_ptr);
    _config.setCodingRate(coding_rate);
    return true;
  }
  break;
  /* IOCTL_SET_SPREADING_FACTOR *******************************************************/
  case IOCTL_SET_SPREADING_FACTOR:
  {
    uint8_t                    const * arg_ptr          = static_cast<uint8_t *>                 (arg     );
    interface::SpreadingFactor const   spreading_factor = static_cast<interface::SpreadingFactor>(*arg_ptr);
    _config.setSpreadingFactor(spreading_factor);
    return true;
  }
  break;
  /* IOCTL_SET_PREAMBLE_LENGTH ********************************************************/
  case IOCTL_SET_PREAMBLE_LENGTH:
  {
    uint16_t const * preamble_length = static_cast<uint16_t *>(arg);
    _config.setPreambleLength(*preamble_length);
    return true;
  }
  break;
  /* IOCTL_SET_TX_FIFO_SIZE ***********************************************************/
  case IOCTL_SET_TX_FIFO_SIZE:
  {
    uint16_t const * tx_fifo_size = static_cast<uint16_t *>(arg);
    return _config.setTxFifoSize(*tx_fifo_size);
  }
  break;
  /* IOCTL_SET_RX_FIFO_SIZE ***********************************************************/
  case IOCTL_SET_RX_FIFO_SIZE:
  {
    uint16_t const * rx_fifo_size = static_cast<uint16_t *>(arg);
    return _config.setRxFifoSize(*rx_fifo_size);
  }
  break;
  /* IOCTL_GET_CURRENT_RSSI ***********************************************************/
  case IOCTL_GET_CURRENT_RSSI:
  {
    int16_t * current_rssi_dbm = static_cast<int16_t *>(arg);
    *current_rssi_dbm = _status.getCurrentRssi();
    return true;
  }
  break;
  /* IOCTL_GET_LAST_PACKET_RSSI *******************************************************/
  case IOCTL_GET_LAST_PACKET_RSSI:
  {
    int16_t * last_packet_rssi_dbm = static_cast<int16_t *>(arg);
    *last_packet_rssi_dbm = _status.getLastPacketRssi();
    return true;
  }
  break;
  /* IOCTL_GET_LAST_PACKET_SNR ********************************************************/
  case IOCTL_GET_LAST_PACKET_SNR:
  {
    int8_t * last_packet_rssi_snr = static_cast<int8_t *>(arg);
    *last_packet_rssi_snr = _status.getLastPacketSnr();
    return true;
  }
  break;
  }

  return false;
}

void RFM9x::close()
{
        _control.setOperatingMode     (interface::OperatingMode::SLEEP);
  while(_control.getOperatingMode() != interface::OperatingMode::SLEEP) { /* wait */ }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
