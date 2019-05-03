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

#include <snowfox/hal/riscv64/FE310/Clock.h>

#include <snowfox/hal/riscv64/FE310/util/ClockUtil.h>

#include <snowfox/util/BitUtil.h>

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

/* PRCI_HFXOSCCFG */
#define PRCI_HFXOSCCFG_HFXOSCRDY_bp    (31)
#define PRCI_HFXOSCCFG_HFXOSCEN_bp     (30)

/* PRCI_PLLCFG */
#define PRCI_PLLCFG_PLLLOCK_bp         (31)
#define PRCI_PLLCFG_PLLBYPASS_bp       (18)
#define PRCI_PLLCFG_PLLREFSEL_bp       (17)
#define PRCI_PLLCFG_PLLSEL_bp          (16)

#define PRCI_PLLCFG_PLLQ_bm             ((0x03) << 10)
#define PRCI_PLLCFG_PLLF_bm             ((0x3F) << 4)
#define PRCI_PLLCFG_PLLR_bm             ((0x03) << 0)

/* PRCI_PLLOUTDIV */
#define PRCI_PLLOUTDIV_PLLOUTDIVBY1_bp (8)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Clock::Clock(volatile uint32_t * PRCI_HFXOSCCFG,
             volatile uint32_t * PRCI_PLLCFG,
             volatile uint32_t * PRCI_PLLOUTDIV,
             uint32_t const      hfxoscin_freq_Hz)
: _PRCI_HFXOSCCFG  (PRCI_HFXOSCCFG  ),
  _PRCI_PLLCFG     (PRCI_PLLCFG     ),
  _PRCI_PLLOUTDIV  (PRCI_PLLOUTDIV  ),
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
    util::setBit(_PRCI_HFXOSCCFG, PRCI_HFXOSCCFG_HFXOSCEN_bp);
    while(!util::isBitSet(_PRCI_HFXOSCCFG, PRCI_HFXOSCCFG_HFXOSCRDY_bp)) { }

    /* Select HFXOSC as reference clock for the PLL */
    util::setBit(_PRCI_PLLCFG, PRCI_PLLCFG_PLLREFSEL_bp);

    /* Setup pllr, pllf, pllq to achieve the desired frequency
     *  refr = pllref / PLLR {1,2,3,4}
     *    6 MHz <= refr <= 12 MHz
     *  vco = refr * PLLF {2,4,8,...,256}
     *    384 <= vco <= 768 MHz
     *  pllout = vco / PLLQ {2,4,8}
     *    48 <= pllout <= 384 MHz
     */

    if(!setPLLR(_PRCI_PLLCFG, 2)) return false;
    /* HiFive1 = XTAL = 16 MHz -> refr = 16 MHz / 2 = 8 MHz */
    /* vco = refr * 50 = 400 MHz */
    if(!setPLLF(_PRCI_PLLCFG, 50)) return false;
    /* pllout = vco / 2 = 200 MHz */
    if(!setPLLQ(_PRCI_PLLCFG, 2)) return false;

    /* Wait for PLL to achieve a lock */
    while(!util::isBitSet(_PRCI_PLLCFG, PRCI_PLLCFG_PLLLOCK_bp)) { }

    /* plloutdiv = 1 -> hfclk = pllout / 1  */
    util::setBit(_PRCI_PLLOUTDIV, PRCI_PLLOUTDIV_PLLOUTDIVBY1_bp);

    /* Disable bypass and select pllout as clock source -> hfclk = pllout */
    util::setBit(_PRCI_PLLCFG, PRCI_PLLCFG_PLLSEL_bp);
    util::setBit(_PRCI_PLLCFG, PRCI_PLLCFG_PLLBYPASS_bp);

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
