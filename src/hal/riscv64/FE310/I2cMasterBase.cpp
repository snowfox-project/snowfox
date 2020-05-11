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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/riscv64/FE310/I2cMasterBase.h>

#include <snowfox/hal/riscv64/FE310/RegisterBits.h>

#include <snowfox/util/BitUtil.h>
#include <snowfox/util/EnumClassConv.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::FE310
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

I2cMasterBase::I2cMasterBase(volatile uint32_t * i2cx_prescaler_low,
                             volatile uint32_t * i2cx_prescaler_high,
                             volatile uint32_t * i2cx_control,
                             volatile uint32_t * i2cx_data,
                             volatile uint32_t * i2cx_cmd_status,
                             uint32_t const clock_Hz)
: _i2cx_prescaler_low{i2cx_prescaler_low}
, _i2cx_prescaler_high{i2cx_prescaler_high}
, _clock_Hz{clock_Hz}
, _i2c_low_level{i2cx_control, i2cx_data, i2cx_cmd_status}
{
  _i2c_low_level.enable();
  _i2c_low_level.ackInterrupt();
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool I2cMasterBase::begin(uint8_t const address, bool const is_read_access)
{
  _i2c_low_level.transmit(convertI2cAddress(address, is_read_access));
  _i2c_low_level.startAndWrite();

  waitForInterrupt();
  if (_i2c_low_level.isArbitrationLost()) return false;

  if (!_i2c_low_level.isAckBySlave()) {
    end();
    return false;  
  }

  return true;
}

void I2cMasterBase::end()
{
  _i2c_low_level.stop();
  while(_i2c_low_level.isBusy()) { }
}

bool I2cMasterBase::write(uint8_t const data)
{
  _i2c_low_level.transmit(data);
  _i2c_low_level.write();

  waitForInterrupt();
  if (_i2c_low_level.isArbitrationLost()) return false;

  if (!_i2c_low_level.isAckBySlave()) {
    end();
    return false;  
  }

  return true;
}

bool I2cMasterBase::requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes)
{
  if (!begin(address, true)) {
    return false;
  }

  /* Read up to (num_bytes - 1) */
  for(uint16_t b = 0; b < (num_bytes - 1); b++)
  {
    _i2c_low_level.readAndAck();
    waitForInterrupt();
    if (_i2c_low_level.isArbitrationLost()) return false;
    data[b] = _i2c_low_level.receive();
  }

  /* Read the last byte */
  _i2c_low_level.readAndNack();
  waitForInterrupt();
  if (_i2c_low_level.isArbitrationLost()) return false;
  data[num_bytes - 1] = _i2c_low_level.receive();

  /* Stop operation */
  end();

  return true;
}

void I2cMasterBase::setI2cClock(hal::interface::I2cClock const i2c_clock)
{
  /* The value of the prescaler registers can only be changed then I2C is disabled */
  _i2c_low_level.disable();

  /* Calculate the value of the I2C prescalers */
  uint32_t prescaler = 0;
  switch(i2c_clock)
  {
  default:
  case interface::I2cClock::F_100_kHz: prescaler = (_clock_Hz / (5 * 100'000UL)) - 1; break;
  case interface::I2cClock::F_400_kHz: prescaler = (_clock_Hz / (5 * 400'000UL)) - 1; break;
  }

  /* Set the prescaler registers */
  *_i2cx_prescaler_low  = (prescaler & 0x0000'00FF);
  *_i2cx_prescaler_high = (prescaler & 0x0000'FF00) / 256; /* >> 8 creates a SRLI and it just doesn't work */

  /* Re-enable I2C */
  _i2c_low_level.enable();
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void I2cMasterBase::waitForInterrupt()
{
  while(!_i2c_low_level.isInterrupt()) { }
  _i2c_low_level.ackInterrupt();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */
