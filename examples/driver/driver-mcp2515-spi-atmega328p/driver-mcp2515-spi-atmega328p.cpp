/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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
 * This example programm is tailored for usage with Arduino Uno
 * and Seedstudio CAN Bus Shield V2.0
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/SPIMaster.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>

#include <spectre/driver/can/Can.h>

#include <spectre/driver/can/MCP2515/MCP2515_IoSpi.h>
#include <spectre/driver/can/MCP2515/MCP2515_Control.h>
#include <spectre/driver/can/MCP2515/MCP2515_CanController.h>
#include <spectre/driver/can/MCP2515/MCP2515_CanReceiveBuffer.h>
#include <spectre/driver/can/MCP2515/MCP2515_CanTransmitBuffer.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static hal::interface::SpiMode     const MCP2515_SPI_MODE      = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const MCP2515_SPI_BIT_ORDER = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const MCP2515_SPI_PRESCALER = 16; /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz                     */
static uint8_t                     const F_MCP2515_MHz         = 16; /* Seedstudio CAN Bus Shield V2.0 is clocked with a 16 MHz crystal */

static uint16_t                    const CAN_RX_BUFFER_SIZE    = 8;
static uint16_t                    const CAN_TX_BUFFER_SIZE    = 8;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::SPIMaster spi_master(&SPCR, &SPSR, &SPDR);

  spi_master.setSpiMode     (MCP2515_SPI_MODE     );
  spi_master.setSpiBitOrder (MCP2515_SPI_BIT_ORDER);
  spi_master.setSpiPrescaler(MCP2515_SPI_PRESCALER);

  ATMEGA328P::DigitalOutPin cs(&DDRB, &PORTB, 1); /* D9 = PB1 */

  /* DRIVER ***************************************************************************/

  can::MCP2515::MCP2515_IoSpi             mcp2515_io_spi    (spi_master, cs);
  can::MCP2515::MCP2515_Control           mcp2515_control   (mcp2515_io_spi);
  can::MCP2515::MCP2515_CanController     mcp2515_can_ctrl  (mcp2515_control, F_MCP2515_MHz);
  can::MCP2515::MCP2515_CanReceiveBuffer  mcp2515_can_rx_buf(CAN_RX_BUFFER_SIZE);
  can::MCP2515::MCP2515_CanTransmitBuffer mcp2515_can_tx_buf(CAN_TX_BUFFER_SIZE);

  can::Can                                can               (mcp2515_can_ctrl, mcp2515_can_tx_buf, mcp2515_can_rx_buf);

  uint8_t bitrate = static_cast<uint8_t>(can::MCP2515::interface::CanBitRate::BR_250kBPS);

  /* APPLICATION **********************************************************************/

  can.open();
  can.ioctl(can::IOCTL_SET_BITRATE, static_cast<void *>(&bitrate));

  for(;;) { }

  can.close();

  return 0;
}
