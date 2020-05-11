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

#include <snowfox/hal/riscv64/FE310/I2cMasterLowLevel.h>

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

I2cMasterLowLevel::I2cMasterLowLevel(volatile uint32_t * i2cx_control,
                                     volatile uint32_t * i2cx_data,
                                     volatile uint32_t * i2cx_cmd_status)
: _i2cx_control{i2cx_control}
, _i2cx_data{i2cx_data}
, _i2cx_cmd_status{i2cx_cmd_status}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void I2cMasterLowLevel::enable()
{
  util::setBit(_i2cx_control, util::bp(I2Cx_CONTROL::ENABLE));
}

void I2cMasterLowLevel::disable()
{
  util::clrBit(_i2cx_control, util::bp(I2Cx_CONTROL::ENABLE));
}

void I2cMasterLowLevel::transmit(uint8_t const data)
{
  *_i2cx_data = static_cast<uint32_t>(data);
}

uint8_t I2cMasterLowLevel::receive()
{
  return static_cast<uint8_t>((*_i2cx_data) & 0x0000'00FF);
}

void I2cMasterLowLevel::startAndWrite()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::STA) | util::bm(I2Cx_COMMAND::WR);
}

void I2cMasterLowLevel::write()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::WR);
}

void I2cMasterLowLevel::readAndAck()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::RD);
}

void I2cMasterLowLevel::readAndNack()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::RD) | util::bm(I2Cx_COMMAND::ACK);
}

void I2cMasterLowLevel::stop()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::STO);
}

bool I2cMasterLowLevel::isBusy()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::Busy));
}

bool I2cMasterLowLevel::isInterrupt()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::InterruptFlag));
}

bool I2cMasterLowLevel::isAckBySlave()
{
  return util::isBitClr(_i2cx_cmd_status, util::bp(I2Cx_STATUS::RxACK));
}

bool I2cMasterLowLevel::isArbitrationLost()
{
  return util::isBitSet(_i2cx_cmd_status, util::bp(I2Cx_STATUS::ArbitrationLost));
}

void I2cMasterLowLevel::ackInterrupt()
{
  *_i2cx_cmd_status = util::bm(I2Cx_COMMAND::IACK);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */
