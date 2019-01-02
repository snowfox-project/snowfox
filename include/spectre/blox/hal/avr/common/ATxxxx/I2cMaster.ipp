/**
 * Spectre is a modular RTOS with extensive IO support.
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
I2cMaster<I2C_TRANSFER_COMPLETE_INTERRUPT_NUMBER>::I2cMaster(volatile uint8_t                    * twcr,
                                                             volatile uint8_t                    * twdr,
                                                             volatile uint8_t                    * twsr,
                                                             volatile uint8_t                    * twbr,
                                                             hal::interface::CriticalSection     & crit_sec,
                                                             hal::interface::InterruptController & int_ctrl)
: _i2c_transfer_complete_event                 (crit_sec                                            ),
  _i2c_master_low_level                        (twcr, twdr, twsr, twbr, _i2c_transfer_complete_event),
  _i2c_master                                  (_i2c_master_low_level                               ),
  _i2c_master_on_i2c_transfer_complete_callback(_i2c_transfer_complete_event                        )
{
  int_ctrl.registerInterruptCallback(I2C_TRANSFER_COMPLETE_INTERRUPT_NUMBER, &_i2c_master_on_i2c_transfer_complete_callback);
  int_ctrl.enableInterrupt          (I2C_TRANSFER_COMPLETE_INTERRUPT_NUMBER);
}

template <uint8_t I2C_TRANSFER_COMPLETE_INTERRUPT_NUMBER>
I2cMaster<I2C_TRANSFER_COMPLETE_INTERRUPT_NUMBER>::I2cMaster(volatile uint8_t                          * twcr,
                                                             volatile uint8_t                          * twdr,
                                                             volatile uint8_t                          * twsr,
                                                             volatile uint8_t                          * twbr,
                                                             hal::interface::CriticalSection           & crit_sec,
                                                             hal::interface::InterruptController       & int_ctrl,
                                                             hal::interface::I2cClock            const   i2c_clock)
: I2cMaster<I2C_TRANSFER_COMPLETE_INTERRUPT_NUMBER>(twcr, twdr, twsr, twbr, crit_sec, int_ctrl)
{
  _i2c_master.setI2cClock(i2c_clock);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* blox */

} /* spectre */
