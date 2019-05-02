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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_CLOCK_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_CLOCK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/clock/Clock.h>

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
 * TYPEDEF
 **************************************************************************************/

enum class ClockId : uint8_t
{
  coreclk = 0
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Clock : public interface::Clock
{

public:

           Clock(volatile uint32_t * PRCI_HFXOSCCFG,
                 volatile uint32_t * PRCI_PLLCFG,
                 volatile uint32_t * PRCI_PLLOUTDIV,
                 uint32_t const      hfxoscin_freq_Hz);
  virtual ~Clock();


  virtual bool setClockFreq(uint8_t const clk_id, uint32_t const clk_freq_hz) override;


private:

  volatile uint32_t * _PRCI_HFXOSCCFG,
                    * _PRCI_PLLCFG,
                    * _PRCI_PLLOUTDIV;
  uint32_t const      _hfxoscin_freq_Hz;


  static bool isValidPLLR(uint8_t const pllr);
  static bool isValidPLLF(uint8_t const pllf);
  static bool isValidPLLQ(uint8_t const pllq);
  static bool setPLLR(volatile uint32_t * PRCI_PLLCFG, uint8_t const pllr);
  static bool setPLLF(volatile uint32_t * PRCI_PLLCFG, uint8_t const pllf);
  static bool setPLLQ(volatile uint32_t * PRCI_PLLCFG, uint8_t const pllq);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_CLOCK_H_ */