/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_I2CMASTER_ONI2CTRANSFERCOMPLETECALLBACK_H_
#define INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_I2CMASTER_ONI2CTRANSFERCOMPLETECALLBACK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/interrupt/InterruptCallback.h>

#include <snowfox/os/event/interface/EventProducer.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATxxxx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class I2cMaster_onI2cTransferCompleteCallback : public hal::interface::InterruptCallback
{

public:

           I2cMaster_onI2cTransferCompleteCallback(os::interface::EventProducer & i2c_transfer_complete_event);
  virtual ~I2cMaster_onI2cTransferCompleteCallback();


  virtual void onInterrupt() override;

private:

  os::interface::EventProducer & _i2c_transfer_complete_event;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATxxxx */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATXXXX_I2CMASTER_ONI2CTRANSFERCOMPLETECALLBACK_H_ */
