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

#ifndef INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATXXXX_SPIMASTER_HPP_
#define INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATXXXX_SPIMASTER_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/hal/interface/locking/CriticalSection.h>
#include <snowfox/hal/interface/interrupt/InterruptController.h>

#include <snowfox/hal/avr/common/ATxxxx/SpiMaster.h>
#include <snowfox/hal/avr/common/ATxxxx/SpiMaster_onSerialTransferCompleteCallback.h>

#include <snowfox/os/event/Event.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace blox
{

namespace ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <uint8_t SERIAL_TRANSFER_COMPLETE_INTERRUPT_NUMBER>
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

  os::Event                                               _serial_transfer_complete_event;
  hal::ATxxxx::SpiMaster                                  _spi_master;
  hal::ATxxxx::SpiMaster_onSerialTransferCompleteCallback _spi_master_on_serial_transfer_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* blox */

} /* snowfox */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "SpiMaster.ipp"

#endif /* INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATXXXX_SPIMASTER_HPP_ */
