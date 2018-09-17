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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_SPIMASTER_ONSERIALTRANSFERCOMPLETECALLBACK_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_SPIMASTER_ONSERIALTRANSFERCOMPLETECALLBACK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/spi/events/SpiMaster_onSerialTransferCompleteCallback.h>

#include <spectre/hal/interface/interrupt/InterruptCallback.h>

#include <spectre/os/event/interface/EventProducer.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SpiMaster_onSerialTransferCompleteCallback : public interface::SpiMaster_onSerialTransferCompleteCallback
{

public:

           SpiMaster_onSerialTransferCompleteCallback(os::interface::EventProducer & spi_transfer_complete_event);
  virtual ~SpiMaster_onSerialTransferCompleteCallback();


  virtual void onSerialTransferComplete() override;


private:

  os::interface::EventProducer & _spi_transfer_complete_event;

};

/**************************************************************************************/

class SpiMaster_onSerialTransferCompleteCallbackAdapter : public interface::InterruptCallback
{

public:

           SpiMaster_onSerialTransferCompleteCallbackAdapter(SpiMaster_onSerialTransferCompleteCallback & on_serial_transfer_complete_callback) : _on_serial_transfer_complete_callback(on_serial_transfer_complete_callback) { }
  virtual ~SpiMaster_onSerialTransferCompleteCallbackAdapter() { }


  virtual void interruptServiceRoutine() override
  {
    _on_serial_transfer_complete_callback.onSerialTransferComplete();
  }

private:

  SpiMaster_onSerialTransferCompleteCallback & _on_serial_transfer_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_SPIMASTER_ONSERIALTRANSFERCOMPLETECALLBACK_H_ */
