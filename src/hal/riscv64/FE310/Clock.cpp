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

#include <snowfox/hal/riscv64/FE310/Clock.h>

#include <snowfox/hal/riscv64/FE310/RegisterBits.h>

#include <snowfox/hal/riscv64/FE310/util/ClockUtil.h>

#include <snowfox/util/BitUtil.h>
#include <snowfox/util/EnumClassConv.hpp>

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

#define PRCI_PLLCFG_PLLQ_bm             ((0x03) << 10)
#define PRCI_PLLCFG_PLLF_bm             ((0x3F) << 4)
#define PRCI_PLLCFG_PLLR_bm             ((0x03) << 0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Clock::Clock(volatile uint32_t * prci_hfxosccfg,
             volatile uint32_t * prci_pllcfg,
             volatile uint32_t * prci_plloutdiv,
             uint32_t const      hfxoscin_freq_Hz)
: _PRCI_HFXOSCCFG  (prci_hfxosccfg  ),
  _PRCI_PLLCFG     (prci_pllcfg     ),
  _PRCI_PLLOUTDIV  (prci_plloutdiv  ),
  _hfxoscin_freq_Hz(hfxoscin_freq_Hz)
{

}

Clock::~Clock()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool Clock::setClockFreq(uint8_t const clk_id, uint32_t const clk_freq_hz)
{
  if(clk_id == static_cast<uint8_t>(ClockId::coreclk))
  {
    /* Enable HFXOSC and wait until it is ready */
    util::setBit(_PRCI_HFXOSCCFG, util::bp(PRCI_HFXOSCCFG::HFXOSCEN));
    while(!util::isBitSet(_PRCI_HFXOSCCFG, util::bp(PRCI_HFXOSCCFG::HFXOSCRDY))) { }

    /* Select HFXOSC as reference clock for the PLL */
    util::setBit(_PRCI_PLLCFG, util::bp(PRCI_PLLCFG::PLLREFSEL));

    /* Setup pllr, pllf, pllq to achieve the desired frequency
     *  refr = pllref / PLLR {1,2,3,4}
     *    6 MHz <= refr <= 12 MHz
     *  vco = refr * PLLF {2,4,8,...,256}
     *    384 <= vco <= 768 MHz
     *  pllout = vco / PLLQ {2,4,8}
     *    48 <= pllout <= 384 MHz
     */
    uint8_t r = 0, f = 0, q = 0;
    if(!findPllParam(16000000UL, clk_freq_hz, r, f, q)) return false;

    if(!setPLLR(_PRCI_PLLCFG, r)) return false;
    if(!setPLLF(_PRCI_PLLCFG, f)) return false;
    if(!setPLLQ(_PRCI_PLLCFG, q)) return false;

    /* Disable PLL bypass after configuration to activate PLL */
    util::clrBit(_PRCI_PLLCFG, util::bp(PRCI_PLLCFG::PLLBYPASS));

    /* Wait for PLL to achieve a lock */
    while(!util::isBitSet(_PRCI_PLLCFG, util::bp(PRCI_PLLCFG::PLLLOCK))) { }

    /* plloutdiv = 1 -> hfclk = pllout / 1  */
    util::setBit(_PRCI_PLLOUTDIV, util::bp(PRCI_PLLOUTDIV::PLLOUTDIVBY1));

    /* Select pllout as clock source -> hfclk = pllout */
    util::setBit(_PRCI_PLLCFG, util::bp(PRCI_PLLCFG::PLLSEL));

    return true;
  }

  return false;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
