/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/driver/memory/AT45DBx/AT45DBx.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* READ COMMANDS **********************************************************************/

#define AT45DB_RDMN          0xD2 /* Main Memory Page Read */
#define AT45DB_RDARRY        0xE8 /* Continuous Array Read (Legacy Command) */
#define AT45DB_RDARRAYLF     0x03 /* Continuous Array Read (Low Frequency) */
#define AT45DB_RDARRAYHF     0x0B /* Continuous Array Read (High Frequency) */
#define AT45DB_RDBF1LF       0xD1 /* Buffer 1 Read (Low Frequency) */
#define AT45DB_RDBF2LF       0xD3 /* Buffer 2 Read (Low Frequency) */
#define AT45DB_RDBF1         0xD4 /* Buffer 1 Read */
#define AT45DB_RDBF2         0xD6 /* Buffer 2 Read */

/* WRITE / ERASE COMMANDS **************************************************************/

#define AT45DB_WRBF1         0x84 /* Buffer 1 Write */
#define AT45DB_WRBF2         0x87 /* Buffer 2 Write */
#define AT45DB_BF1TOMNE      0x83 /* Buffer 1 to Main Memory Page Program with Built-in Erase */
#define AT45DB_BF2TOMNE      0x86 /* Buffer 2 to Main Memory Page Program with Built-in Erase */
#define AT45DB_BF1TOMN       0x88 /* Buffer 1 to Main Memory Page Program without Built-in Erase */
#define AT45DB_BF2TOMN       0x89 /* Buffer 2 to Main Memory Page Program without Built-in Erase  */
#define AT45DB_PGERASE       0x81 /* Page Erase */
#define AT45DB_BLKERASE      0x50 /* Block Erase */
#define AT45DB_SECTERASE     0x7C /* Sector Erase */
#define AT45DB_CHIPERASE_1   0xC7 /* Chip Erase - byte 1 */
#define AT45DB_CHIPERASE_2   0x94 /* Chip Erase - byte 2 */
#define AT45DB_CHIPERASE_3   0x80 /* Chip Erase - byte 3 */
#define AT45DB_CHIPERASE_4   0x9A /* Chip Erase - byte 4 */
#define AT45DB_MNTHRUBF1     0x82 /* Main Memory Page Program Through Buffer 1 */
#define AT45DB_MNTHRUBF2     0x85 /* Main Memory Page Program Through Buffer 2 */

/* PROTECTION / SECURITY COMMANDS ******************************************************/

#define AT45DB_ENABPROT1     0x3D /* Enable Sector Protection - byte 1 */
#define AT45DB_ENABPROT2     0x2A /* Enable Sector Protection - byte 2 */
#define AT45DB_ENABPROT3     0x7F /* Enable Sector Protection - byte 3 */
#define AT45DB_ENABPROT4     0xA9 /* Enable Sector Protection - byte 4 */
#define AT45DB_DISABPROT1    0x3D /* Disable Sector Protection - byte 1 */
#define AT45DB_DISABPROT2    0x2A /* Disable Sector Protection - byte 2 */
#define AT45DB_DISABPROT3    0x7F /* Disable Sector Protection - byte 3 */
#define AT45DB_DISABPROT4    0x9A /* Disable Sector Protection - byte 4 */
#define AT45DB_ERASEPROT1    0x3D /* Erase Sector Protection Register - byte 1 */
#define AT45DB_ERASEPROT2    0x2A /* Erase Sector Protection Register - byte 2 */
#define AT45DB_ERASEPROT3    0x7F /* Erase Sector Protection Register - byte 3 */
#define AT45DB_ERASEPROT4    0xCF /* Erase Sector Protection Register - byte 4 */
#define AT45DB_PROGPROT1     0x3D /* Program Sector Protection Register - byte 1 */
#define AT45DB_PROGPROT2     0x2A /* Program Sector Protection Register - byte 2 */
#define AT45DB_PROGPROT3     0x7F /* Program Sector Protection Register - byte 3 */
#define AT45DB_PROGPROT4     0xFC /* Program Sector Protection Register - byte 4 */
#define AT45DB_RDPROT        0x32 /* Read Sector Protection Register */
#define AT45DB_LOCKDOWN1     0x3D /* Sector Lockdown - byte 1 */
#define AT45DB_LOCKDOWN2     0x2A /* Sector Lockdown - byte 2 */
#define AT45DB_LOCKDOWN3     0x7F /* Sector Lockdown - byte 3 */
#define AT45DB_LOCKDOWN4     0x30 /* Sector Lockdown - byte 4 */
#define AT45DB_RDLOCKDOWN    0x35 /* Read Sector Lockdown Register  */
#define AT45DB_PROGSEC1      0x9B /* Program Security Register - byte 1 */
#define AT45DB_PROGSEC2      0x00 /* Program Security Register - byte 2 */
#define AT45DB_PROGSEC3      0x00 /* Program Security Register - byte 3 */
#define AT45DB_PROGSEC4      0x00 /* Program Security Register - byte 4 */
#define AT45DB_RDSEC         0x77 /* Read Security Register */

/* Additional commands */

#define AT45DB_MNTOBF1XFR    0x53 /* Main Memory Page to Buffer 1 Transfer */
#define AT45DB_MNTOBF2XFR    0x55 /* Main Memory Page to Buffer 2 Transfer */
#define AT45DB_MNBF1CMP      0x60 /* Main Memory Page to Buffer 1 Compare  */
#define AT45DB_MNBF2CMP      0x61 /* Main Memory Page to Buffer 2 Compare */
#define AT45DB_AUTOWRBF1     0x58 /* Auto Page Rewrite through Buffer 1 */
#define AT45DB_AUTOWRBF2     0x59 /* Auto Page Rewrite through Buffer 2 */
#define AT45DB_PWRDOWN       0xB9 /* Deep Power-down */
#define AT45DB_RESUME        0xAB /* Resume from Deep Power-down */
#define AT45DB_RDSR          0xD7 /* Status Register Read */
#define AT45DB_RDDEVID       0x9F /* Manufacturer and Device ID Read */

#define AT45DB_MANUFACTURER  0x1F /* Manufacturer ID: Atmel */
#define AT45DB_DEVID1_CAPMSK 0x1F /* Bits 0-4: Capacity */
#define AT45DB_DEVID1_1MBIT  0x02 /* xxx0 0010 = 1Mbit AT45DB011 */
#define AT45DB_DEVID1_2MBIT  0x03 /* xxx0 0012 = 2Mbit AT45DB021 */
#define AT45DB_DEVID1_4MBIT  0x04 /* xxx0 0100 = 4Mbit AT45DB041 */
#define AT45DB_DEVID1_8MBIT  0x05 /* xxx0 0101 = 8Mbit AT45DB081 */
#define AT45DB_DEVID1_16MBIT 0x06 /* xxx0 0110 = 16Mbit AT45DB161 */
#define AT45DB_DEVID1_32MBIT 0x07 /* xxx0 0111 = 32Mbit AT45DB321 */
#define AT45DB_DEVID1_64MBIT 0x08 /* xxx0 1000 = 32Mbit AT45DB641 */
#define AT45DB_DEVID1_FAMMSK 0xE0 /* Bits 5-7: Family */
#define AT45DB_DEVID1_DFLASH 0x20 /* 001x xxxx = Dataflash */
#define AT45DB_DEVID1_AT26DF 0x40 /* 010x xxxx = AT26DFxxx series (Not supported) */
#define AT45DB_DEVID2_VERMSK 0x1F /* Bits 0-4: MLC mask */
#define AT45DB_DEVID2_MLCMSK 0xE0 /* Bits 5-7: MLC mask */

/* Status register bit definitions */

#define AT45DB_SR_RDY_bm       (1 << 7) /* Bit 7: RDY/ Not BUSY */
#define AT45DB_SR_COMP_bm      (1 << 6) /* Bit 6: COMP */
#define AT45DB_SR_PROTECT_bm   (1 << 1) /* Bit 1: PROTECT */
#define AT45DB_SR_PGSIZE_bm    (1 << 0) /* Bit 0: PAGE_SIZE */

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AT45DBx::AT45DBx(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master(spi_master),
  _cs        (cs        ),
  _page_shift(0         ),
  _num_pages (0         )
{
   _cs.set();
}

AT45DBx::~AT45DBx()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void AT45DBx::eraseChip()
{
  _cs.clr();

  _spi_master.exchange(AT45DB_CHIPERASE_1);
  _spi_master.exchange(AT45DB_CHIPERASE_2);
  _spi_master.exchange(AT45DB_CHIPERASE_3);
  _spi_master.exchange(AT45DB_CHIPERASE_4);

  _cs.set();
}

void AT45DBx::erasePage(uint16_t const page)
{
  uint32_t const offset = static_cast<uint32_t>(page) << _page_shift;

  _cs.clr();

  _spi_master.exchange(AT45DB_PGERASE);
  _spi_master.exchange(static_cast<uint8_t>((offset >> 16) & 0xFF));
  _spi_master.exchange(static_cast<uint8_t>((offset >>  8) & 0xFF));
  _spi_master.exchange(static_cast<uint8_t>((offset >>  0) & 0xFF));

  _cs.set();
}

void AT45DBx::writePage(uint16_t const page, uint8_t const * buffer)
{
  uint32_t const offset = static_cast<uint32_t>(page) << _page_shift;

  _cs.clr();

  _spi_master.exchange(AT45DB_MNTHRUBF1);
  _spi_master.exchange(static_cast<uint8_t>((offset >> 16) & 0xFF));
  _spi_master.exchange(static_cast<uint8_t>((offset >>  8) & 0xFF));
  _spi_master.exchange(static_cast<uint8_t>((offset >>  0) & 0xFF));

  for(uint16_t b = 0; b < getPageSize(); b++)
  {
    _spi_master.exchange(buffer[b]);
  }

  _cs.set();
}

void AT45DBx::read(uint32_t const offset, uint8_t * buffer, uint16_t const num_bytes)
{
  _cs.clr();

  _spi_master.exchange(AT45DB_RDARRAYHF);
  _spi_master.exchange(static_cast<uint8_t>((offset >> 16) & 0xFF));
  _spi_master.exchange(static_cast<uint8_t>((offset >>  8) & 0xFF));
  _spi_master.exchange(static_cast<uint8_t>((offset >>  0) & 0xFF));

  for(uint16_t b = 0; b < num_bytes; b++)
  {
    buffer[b] = _spi_master.exchange(0x00);
  }

  _cs.set();
}

void AT45DBx::readDeviceId(uint8_t * dev_id)
{
  _cs.clr();

  _spi_master.exchange(AT45DB_RDDEVID);

  dev_id[0] = _spi_master.exchange(0x00);
  dev_id[1] = _spi_master.exchange(0x00);
  dev_id[2] = _spi_master.exchange(0x00);

  _cs.set();
}

uint32_t AT45DBx::getPageShift(uint8_t const * dev_id)
{
  uint8_t const capacity = dev_id[1] & AT45DB_DEVID1_CAPMSK;

  uint32_t page_shift = 0;

  switch (capacity)
  {
    case AT45DB_DEVID1_1MBIT : page_shift = 8;  break;
    case AT45DB_DEVID1_2MBIT : page_shift = 8;  break;
    case AT45DB_DEVID1_4MBIT : page_shift = 8;  break;
    case AT45DB_DEVID1_8MBIT : page_shift = 8;  break;
    case AT45DB_DEVID1_16MBIT: page_shift = 9;  break;
    case AT45DB_DEVID1_32MBIT: page_shift = 9;  break;
    case AT45DB_DEVID1_64MBIT: page_shift = 10; break;
  }

  return page_shift;
}

uint32_t AT45DBx::getNumPages(uint8_t const * dev_id)
{
  uint8_t const capacity = dev_id[1] & AT45DB_DEVID1_CAPMSK;

  uint32_t num_pages = 0;

  switch (capacity)
  {
    case AT45DB_DEVID1_1MBIT : num_pages  = 512;  break;
    case AT45DB_DEVID1_2MBIT : num_pages  = 1024; break;
    case AT45DB_DEVID1_4MBIT : num_pages  = 2048; break;
    case AT45DB_DEVID1_8MBIT : num_pages  = 4096; break;
    case AT45DB_DEVID1_16MBIT: num_pages  = 4096; break;
    case AT45DB_DEVID1_32MBIT: num_pages  = 8192; break;
    case AT45DB_DEVID1_64MBIT: num_pages  = 8192; break;
  }

  return num_pages;
}


/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* spectre */
