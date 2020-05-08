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
, _i2cx_control{i2cx_control}
, _i2cx_data{i2cx_data}
, _i2cx_cmd_status{i2cx_cmd_status}
, _clock_Hz{clock_Hz}
{
  ll_enableI2c();
  ll_ackInterrupt();
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool I2cMasterBase::begin(uint8_t const address, bool const is_read_access)
{
  /* Write the address of the I2C slave to the transmit register */
  if (is_read_access) {
    ll_write(address | 0x01);
  } else {
    ll_write(address);
  }

  /* Generate a start condition for writing to a slave */
  ll_startAndWrite();

  /* Wait for the I2C core to signal completion of operation */
  while (!ll_isInterrupt()) { }
  ll_ackInterrupt();
  if (ll_isArbitrationLost()) return false;

  /* Check wether or not a ACK from the slave was received */
  if (!ll_isAckBySlave())
  {
    ll_stop();
    while(ll_isBusy()) { }
    return false;  
  }

  return true;
}

void I2cMasterBase::end()
{
  ll_stop();
  while(ll_isBusy()) { }
}

bool I2cMasterBase::write(uint8_t const data)
{
  /* Set data and request transmission */
  ll_write(data);
  ll_write();

  /* Wait for the I2C core to signal completion of operation */
  while (!ll_isInterrupt()) { }
  ll_ackInterrupt();
  if (ll_isArbitrationLost()) return false;

  /* Check wether or not a ACK from the slave was received */
  if (!ll_isAckBySlave())
  {
    ll_stop();
    while(ll_isBusy()) { }
    return false;  
  }

  return true;
}

bool I2cMasterBase::requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes)
{
  /* Address the slave for reading */
  if (!begin(address, true)) {
    return false;
  }

  /* Read the bytes except the last one */
  for(uint16_t b = 0; b < (num_bytes - 1); b++)
  {
    /* R + ACK */
    ll_readAndAck();

    /* Wait for completion */
    while (!ll_isInterrupt()) { }
    ll_ackInterrupt();
    if (ll_isArbitrationLost()) return false;

    /* Read Byte */
    data[b] = ll_read();
  }

  /* R + NACK */
  ll_readAndNack();

  /* Wait for completion */
  while(!ll_isInterrupt()) { }
  ll_ackInterrupt();
  if (ll_isArbitrationLost()) return false;

  /* Read Byte */
  data[num_bytes - 1] = ll_read();

  /* Stop operation */
  end();

  return true;
}

void I2cMasterBase::setI2cClock(hal::interface::I2cClock const i2c_clock)
{
  /* The value of the prescaler registers can only be changed then I2C is disabled */
  ll_disableI2c();

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
  ll_enableI2c();
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void I2cMasterBase::ll_enableI2c()
{
  util::setBit(_i2cx_control, util::bp(I2Cx_CONTROL::ENABLE));
}

void I2cMasterBase::ll_disableI2c()
{
  util::clrBit(_i2cx_control, util::bp(I2Cx_CONTROL::ENABLE));
}

void I2cMasterBase::ll_write(uint8_t const data)
{
  *_i2cx_data = static_cast<uint32_t>(data);
}

uint8_t I2cMasterBase::ll_read()
{
  return static_cast<uint8_t>((*_i2cx_data) & 0x0000'00FF);
}

void I2cMasterBase::ll_ackInterrupt()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::IACK);
}

void I2cMasterBase::ll_startAndWrite()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::STA) | util::bm(I2Cx_COMMAND::WR);
}

void I2cMasterBase::ll_write()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::WR);
}

void I2cMasterBase::ll_readAndAck()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::RD);
}

void I2cMasterBase::ll_readAndNack()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::RD) | util::bm(I2Cx_COMMAND::ACK);
}

void I2cMasterBase::ll_stop()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::STO);
}

bool I2cMasterBase::ll_isBusy()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::Busy));
}

bool I2cMasterBase::ll_isInterrupt()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::InterruptFlag));
}

bool I2cMasterBase::ll_isAckBySlave()
{
  return util::isBitClr(_i2cx_cmd_status, util::bp(I2Cx_STATUS::RxACK));
}

bool I2cMasterBase::ll_isArbitrationLost()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::ArbitrationLost));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */
