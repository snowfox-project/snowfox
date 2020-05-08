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
  util::setBit(_i2cx_control, util::bp(I2Cx_CONTROL::ENABLE));
  ackInterrupt();
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool I2cMasterBase::begin(uint8_t const address, bool const is_read_access)
{
  /* Write the address of the I2C slave to the transmit register */
  if (is_read_access) {
    *_i2cx_data = address | 0x01;
  } else {
    *_i2cx_data = address;
  }

  /* Generate a start condition for writing to a slave */
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::STA) | util::bm(I2Cx_COMMAND::WR);

  /* Wait for the I2C core to signal completion of operation */
  while (!isInterrupt()) { }
  ackInterrupt();
  if (isArbitrationLost()) return false;

  /* Check wether or not a ACK from the slave was received */
  if (!isAckBySlave())
  {
    stop();
    while(isBusy()) { }
    return false;  
  }

  return true;
}

void I2cMasterBase::end()
{
  stop();
  while(isBusy()) { }
}

bool I2cMasterBase::write(uint8_t const data)
{
  /* Set data and request transmission */
  *_i2cx_data = data;
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::WR);

  /* Wait for the I2C core to signal completion of operation */
  while (!isInterrupt()) { }
  ackInterrupt();
  if (isArbitrationLost()) return false;

  /* Check wether or not a ACK from the slave was received */
  if (!isAckBySlave())
  {
    stop();
    while(isBusy()) { }
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
    *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::RD);

    /* Wait for completion */
    while (!isInterrupt()) { }
    ackInterrupt();
    if (isArbitrationLost()) return false;

    /* Read Byte */
    data[b] = static_cast<uint8_t>((*_i2cx_data) & 0x0000'00FF);
  }

  /* R + NACK */
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::RD) | util::bm(I2Cx_COMMAND::ACK);

  /* Wait for completion */
  while(!isInterrupt()) { }
  ackInterrupt();
  if (isArbitrationLost()) return false;

  /* Read Byte */
  data[num_bytes - 1] = static_cast<uint8_t>((*_i2cx_data) & 0x0000'00FF);

  /* Stop operation */
  end();

  return true;
}

void I2cMasterBase::setI2cClock(hal::interface::I2cClock const i2c_clock)
{
  /* The value of the prescaler registers can only be changed then I2C is disabled */
  util::clrBit(_i2cx_control, util::bp(I2Cx_CONTROL::ENABLE));

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
  util::setBit(_i2cx_control, util::bp(I2Cx_CONTROL::ENABLE));
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void I2cMasterBase::ackInterrupt()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::IACK);
}

void I2cMasterBase::stop()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::STO);
}

bool I2cMasterBase::isBusy()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::Busy));
}

bool I2cMasterBase::isInterrupt()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::InterruptFlag));
}

bool I2cMasterBase::isAckBySlave()
{
  return util::isBitClr(_i2cx_cmd_status, util::bp(I2Cx_STATUS::RxACK));
}

bool I2cMasterBase::isArbitrationLost()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::ArbitrationLost));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */
