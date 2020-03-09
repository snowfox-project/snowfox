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

#include <snowfox/hal/avr/common/ATxxxx/Delay.h>

#if defined(MCU_ARCH_avr)
#include <util/delay.h>
#elif defined(MCU_ARCH_host)
#include <chrono>
#include <thread>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Delay::Delay()
{

}

Delay::~Delay()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void Delay::delay_ms(uint32_t const ms)
{
#if defined(MCU_ARCH_avr)
  for(uint32_t i = 0; i < ms; i++)
  {
    _delay_ms(1);
  }
#elif defined(MCU_ARCH_host)
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
}

void Delay::delay_us(uint32_t const us)
{
#if defined(MCU_ARCH_avr)
  for(uint32_t i = 0; i < us; i++)
  {
    _delay_us(1);
  }
#elif defined(MCU_ARCH_host)
  std::this_thread::sleep_for(std::chrono::microseconds(us));
#endif
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* snowfox */
