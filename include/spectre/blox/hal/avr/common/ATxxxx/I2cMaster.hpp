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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATXXXX_I2CMASTER_HPP_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATXXXX_I2CMASTER_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <spectre/hal/interface/locking/CriticalSection.h>
#include <spectre/hal/interface/interrupt/InterruptController.h>

#include <spectre/hal/avr/common/ATxxxx/I2cMaster.h>
#include <spectre/hal/avr/common/ATxxxx/I2cMasterLowLevel.h>
#include <spectre/hal/avr/common/ATxxxx/I2cMaster_onI2cTransferCompleteCallback.h>

#include <spectre/os/event/Event.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <uint8_t I2C_TRANSFER_COMPLETE_INTERRUPT_NUMBER>
class I2cMaster
{

public:

  I2cMaster(volatile uint8_t                    * twcr,
            volatile uint8_t                    * twdr,
            volatile uint8_t                    * twsr,
            volatile uint8_t                    * twbr,
            hal::interface::CriticalSection     & crit_sec,
            hal::interface::InterruptController & int_ctrl);

  hal::ATxxxx::I2cMaster & operator () () { return _i2c_master; }

private:

  os::Event                                            _i2c_transfer_complete_event;
  hal::ATxxxx::I2cMasterLowLevel                       _i2c_master_low_level;
  hal::ATxxxx::I2cMaster                               _i2c_master;
  hal::ATxxxx::I2cMaster_onI2cTransferCompleteCallback _i2c_master_on_i2c_transfer_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* blox */

} /* spectre */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "I2cMaster.ipp"

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATXXXX_I2CMASTER_HPP_ */
