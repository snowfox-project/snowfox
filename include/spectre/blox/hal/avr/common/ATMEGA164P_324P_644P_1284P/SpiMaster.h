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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_SPIMASTER_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_SPIMASTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/locking/CriticalSection.h>
#include <spectre/hal/interface/interrupt/InterruptController.h>

#include <spectre/hal/avr/common/ATxxxx/SpiMaster.h>
#include <spectre/hal/avr/common/ATxxxx/SpiMaster_onSerialTransferCompleteCallback.h>

#include <spectre/os/event/Event.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

class SpiMaster
{

public:

  SpiMaster(volatile uint8_t                    * spcr,
            volatile uint8_t                    * spsr,
            volatile uint8_t                    * spdr,
            hal::interface::CriticalSection     & crit_sec,
            hal::interface::InterruptController & int_ctrl);

  SpiMaster(volatile uint8_t                          * spcr,
            volatile uint8_t                          * spsr,
            volatile uint8_t                          * spdr,
            hal::interface::CriticalSection           & crit_sec,
            hal::interface::InterruptController       & int_ctrl,
            hal::interface::SpiMode             const   spi_mode,
            hal::interface::SpiBitOrder         const   spi_bit_order,
            uint32_t                            const   spi_prescaler);

  hal::ATxxxx::SpiMaster & operator () () { return _spi_master; }

private:

  os::Event                                                      _serial_transfer_complete_event;
  hal::ATxxxx::SpiMaster                                         _spi_master;
  hal::ATxxxx::SpiMaster_onSerialTransferCompleteCallback        _spi_master_on_serial_transfer_complete_callback;
  hal::ATxxxx::SpiMaster_onSerialTransferCompleteCallbackAdapter _spi_master_on_serial_transfer_complete_callback_adapter;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA164P_324P_644P_1284P */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_SPIMASTER_H_ */
