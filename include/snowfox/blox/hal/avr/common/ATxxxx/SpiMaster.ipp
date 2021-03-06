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
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::blox::ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <uint8_t SERIAL_TRANSFER_COMPLETE_INTERRUPT_NUMBER>
SpiMaster<SERIAL_TRANSFER_COMPLETE_INTERRUPT_NUMBER>::SpiMaster(volatile uint8_t                    * spcr,
                                                                volatile uint8_t                    * spsr,
                                                                volatile uint8_t                    * spdr,
                                                                hal::interface::InterruptController & int_ctrl)
: _serial_transfer_complete_event                 (                                                 ),
  _spi_master                                     (spcr, spsr, spdr, _serial_transfer_complete_event),
  _spi_master_on_serial_transfer_complete_callback(_serial_transfer_complete_event                  )
{
  int_ctrl.registerInterruptCallback(SERIAL_TRANSFER_COMPLETE_INTERRUPT_NUMBER, &_spi_master_on_serial_transfer_complete_callback);
  int_ctrl.enableInterrupt          (SERIAL_TRANSFER_COMPLETE_INTERRUPT_NUMBER);
}

template <uint8_t SERIAL_TRANSFER_COMPLETE_INTERRUPT_NUMBER>
SpiMaster<SERIAL_TRANSFER_COMPLETE_INTERRUPT_NUMBER>::SpiMaster(volatile uint8_t                          * spcr,
                                                                volatile uint8_t                          * spsr,
                                                                volatile uint8_t                          * spdr,
                                                                hal::interface::InterruptController       & int_ctrl,
                                                                hal::interface::SpiMode             const   spi_mode,
                                                                hal::interface::SpiBitOrder         const   spi_bit_order,
                                                                uint32_t                            const   spi_prescaler)
: SpiMaster<SERIAL_TRANSFER_COMPLETE_INTERRUPT_NUMBER>(spcr, spsr, spdr, int_ctrl)
{
  _spi_master.setSpiMode     (spi_mode     );
  _spi_master.setSpiBitOrder (spi_bit_order);
  _spi_master.setSpiPrescaler(spi_prescaler);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::blox::ATxxxx */
