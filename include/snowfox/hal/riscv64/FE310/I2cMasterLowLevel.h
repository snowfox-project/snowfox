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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTERLOWLEVEL_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTERLOWLEVEL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::FE310
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class I2cMasterLowLevel
{

public:

    I2cMasterLowLevel(volatile uint32_t * i2cx_control,
                      volatile uint32_t * i2cx_data,
                      volatile uint32_t * i2cx_cmd_status);


    void    enable();
    void    disable();

    void    transmit(uint8_t const data);
    uint8_t receive ();

    void    startAndWrite();
    void    write();
    void    readAndAck();
    void    readAndNack();
    void    stop();

    bool    isBusy();
    bool    isInterrupt();
    bool    isAckBySlave();
    bool    isArbitrationLost();

    void    ackInterrupt();

private:

  volatile uint32_t * _i2cx_control,
                    * _i2cx_data,
                    * _i2cx_cmd_status;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTERLOWLEVEL_H_ */
