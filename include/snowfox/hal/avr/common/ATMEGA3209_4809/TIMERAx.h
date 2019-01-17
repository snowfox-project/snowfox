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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA3209_4809_TIMERAX_H_
#define INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA3209_4809_TIMERAX_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/hal/interface/timer/Timer.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA3209_4809
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TIMERAx : public interface::Timer<uint16_t>
{

public:

           TIMERAx(volatile uint8_t  * tcax_ctrla,
                   volatile uint16_t * tcax_cnt,
                   volatile uint16_t * tcax_cmp0,
                   volatile uint16_t * tcax_cmp1,
                   volatile uint16_t * tcax_cmp2);
  virtual ~TIMERAx();


  static uint8_t const COMPARE_CHANNEL_0 = 0;
  static uint8_t const COMPARE_CHANNEL_1 = 1;
  static uint8_t const COMPARE_CHANNEL_2 = 2;


  /* Timer Interface */

  virtual void     start             (                  ) override;
  virtual void     stop              (                  ) override;
  virtual void     set               (uint16_t const val) override;
  virtual uint16_t get               (                  ) override;

  virtual void     setCompareRegister(uint8_t const reg_sel, uint16_t const reg_val) override;


  /* Timer Configuration Interface */

  virtual void setPrescaler(uint32_t const prescaler) override;


private:

  volatile uint8_t  * _TCAx_CTRLA;
  volatile uint16_t * _TCAx_CNT,
                    * _TCAx_CMP0,
                    * _TCAx_CMP1,
                    * _TCAx_CMP2;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA3209_4809 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA3209_4809_TIMERAX_H_ */
