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

#include <snowfox/hal/riscv64/FE310/Delay.h>

#ifdef MCU_ARCH_host
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

namespace FE310
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
#if defined(MCU_ARCH_riscv64)
  uint64_t const num_mcycle = static_cast<uint64_t>(ms * (F_CPU/1000UL));
  delay_mcycle(num_mcycle);
#elif defined(MCU_ARCH_host)
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
}

void Delay::delay_us(uint32_t const us)
{
#if defined(MCU_ARCH_riscv64)
  uint64_t const num_mcycle = static_cast<uint64_t>(us * (F_CPU/1000000UL));
  delay_mcycle(num_mcycle);
#elif defined(MCU_ARCH_host)
  std::this_thread::sleep_for(std::chrono::microseconds(us));
#endif
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void Delay::delay_mcycle(uint64_t const num_mcycle)
{
#ifdef MCU_ARCH_riscv64
  uint64_t const mcycle_start = getCycleCount();

  uint64_t current_num_mcycle = 0;
  while(current_num_mcycle < num_mcycle)
  {
    uint64_t const mcycle_now = getCycleCount();
    current_num_mcycle = mcycle_now - mcycle_start;
  }
#endif
}
#pragma GCC diagnostic pop

uint64_t Delay::getCycleCount()
{
#ifdef MCU_ARCH_riscv64
  uint32_t lo, hi, hi2;
  __asm__ __volatile__ ("1:\n\t"		        \
	    "csrr %0, mcycleh\n\t"                \
	    "csrr %1, mcycle\n\t"	                \
	    "csrr %2, mcycleh\n\t"                \
	    "bne  %0, %2, 1b\n\t"			            \
	    : "=r" (hi), "=r" (lo), "=r" (hi2)) ;
  return ((static_cast<uint64_t>(hi) << 32) | lo);
#else
  return 0;
#endif
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
