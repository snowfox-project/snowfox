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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTERBASE_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTERBASE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/i2c/I2cMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::FE310
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class I2cMasterBase : public hal::interface::I2cMaster
{

public:

           I2cMasterBase(volatile uint32_t * i2cx_prescaler_low,
                         volatile uint32_t * i2cx_prescaler_high,
                         volatile uint32_t * i2cx_control,
                         volatile uint32_t * i2cx_data,
                         volatile uint32_t * i2cx_cmd_status,
                         uint32_t const clock_Hz);
  virtual ~I2cMasterBase() { }


  virtual bool begin      (uint8_t const address, bool const is_read_access)                override;
  virtual void end        ()                                                                override;
  virtual bool write      (uint8_t const data)                                              override;
  virtual bool requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes) override;


  virtual void setI2cClock(hal::interface::I2cClock const i2c_clock) override;


private:

  volatile uint32_t * _i2cx_prescaler_low,
                    * _i2cx_prescaler_high,
                    * _i2cx_control,
                    * _i2cx_data,
                    * _i2cx_cmd_status;
  uint32_t const      _clock_Hz;

  void ll_enableI2c();
  void ll_disableI2c();

  void    ll_transmit(uint8_t const data);
  uint8_t ll_receive ();

  void ll_ackInterrupt();
  void ll_startAndWrite();
  void ll_write();
  void ll_readAndAck();
  void ll_readAndNack();
  void ll_stop();

  bool ll_isBusy();
  bool ll_isInterrupt();
  bool ll_isAckBySlave();
  bool ll_isArbitrationLost();

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_I2CMASTERBASE_H_ */
