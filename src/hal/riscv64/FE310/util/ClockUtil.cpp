/**
 * Snowfox is a modular RTOS with extensive IO support.
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
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/riscv64/FE310/util/ClockUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace FE310
{

/**************************************************************************************
 * DEFINE
 **************************************************************************************/

/* PRCI_PLLCFG */
#define PRCI_PLLCFG_PLLQ_bm ((0x03) << 10)
#define PRCI_PLLCFG_PLLF_bm ((0x3F) << 4)
#define PRCI_PLLCFG_PLLR_bm ((0x03) << 0)

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool findPllParam(uint32_t const pllref_Hz, uint32_t const pllout_Hz, uint8_t & r, uint8_t & f, uint8_t & q)
{
  /* FIXME - Function only supported for HiFive1 board */
  if((pllref_Hz == 16000000UL) && (pllout_Hz == 200000000UL))
  {
    r = 2;  /* refr = pllref / r = XTAL (16 MHz) / 2 = 8 MHz */
    f = 50; /* vco = refr * f = 8 MHz * 50 = 400 MHz         */
    q = 2;  /* pllout = vco / q = 400 MHz / 2 = 200 MHz      */
    return true;
  }

  return false;
}

bool isValidPLLR(uint8_t const pllr)
{
  return ((pllr >= 1) && (pllr <= 4));
}

bool isValidPLLF(uint8_t const pllf)
{
  return ((pllf >= 2) && (pllf <= 128));
}

bool isValidPLLQ(uint8_t const pllq)
{
  return ((pllq == 2) || (pllq == 4) || (pllq == 8));
}

bool setPLLR(volatile uint32_t * PRCI_PLLCFG, uint8_t const pllr)
{
  if(isValidPLLR(pllr))
  {
    uint32_t const pllr_val = static_cast<uint32_t>(pllr & 0x07);
    *PRCI_PLLCFG &= ~PRCI_PLLCFG_PLLR_bm;
    *PRCI_PLLCFG |= (pllr_val << 0);
    return true;
  }
  else 
  {
    return false;
  }
}

bool setPLLF(volatile uint32_t * PRCI_PLLCFG, uint8_t const pllf)
{
  if(isValidPLLF(pllf))
  {
    uint32_t const pllf_val = static_cast<uint32_t>((pllf & 0x7F) >> 1);
    *PRCI_PLLCFG &= ~PRCI_PLLCFG_PLLF_bm;
    *PRCI_PLLCFG |= (pllf_val << 4);
    return true;
  }
  else
  {
    return false;
  }
}

bool setPLLQ(volatile uint32_t * PRCI_PLLCFG, uint8_t const pllq)
{
  if(isValidPLLQ(pllq))
  {
    *PRCI_PLLCFG &= ~PRCI_PLLCFG_PLLQ_bm;
    switch(pllq)
    {
      case 2: *PRCI_PLLCFG |= ((0x01) << 10); break;
      case 4: *PRCI_PLLCFG |= ((0x02) << 10); break;
      case 8: *PRCI_PLLCFG |= ((0x03) << 10); break;
    }
    return true;
  }
  else
  {
    return false;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
