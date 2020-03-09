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

#include <snowfox/hal/avr/common/ATxxxx/util/ExternalInterruptUtil.h>

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
 * DEFINES
 **************************************************************************************/

/* EICRA */
#define ISC31_bm   (1<<7)
#define ISC30_bm   (1<<6)
#define ISC21_bm   (1<<5)
#define ISC20_bm   (1<<4)
#define ISC11_bm   (1<<3)
#define ISC10_bm   (1<<2)
#define ISC01_bm   (1<<1)
#define ISC00_bm   (1<<0)

/* EICRB */
#define ISC71_bm   (1<<7)
#define ISC70_bm   (1<<6)
#define ISC61_bm   (1<<5)
#define ISC60_bm   (1<<4)
#define ISC51_bm   (1<<3)
#define ISC50_bm   (1<<2)
#define ISC41_bm   (1<<1)
#define ISC40_bm   (1<<0)

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void setTriggerModeEint0(interface::TriggerMode const trigger_mode, volatile uint8_t * eicra)
{
  *eicra &= ~(ISC01_bm | ISC00_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *eicra |=            ISC00_bm; break;
  case interface::TriggerMode::Low        : *eicra |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */            break;
  case interface::TriggerMode::RisingEdge : *eicra |= ISC01_bm | ISC00_bm; break;
  case interface::TriggerMode::FallingEdge: *eicra |= ISC01_bm;            break;
  }
}

void setTriggerModeEint1(interface::TriggerMode const trigger_mode, volatile uint8_t * eicra)
{
  *eicra &= ~(ISC11_bm | ISC10_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *eicra |=            ISC10_bm; break;
  case interface::TriggerMode::Low        : *eicra |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */            break;
  case interface::TriggerMode::RisingEdge : *eicra |= ISC11_bm | ISC10_bm; break;
  case interface::TriggerMode::FallingEdge: *eicra |= ISC11_bm;            break;
  }
}

void setTriggerModeEint2(interface::TriggerMode const trigger_mode, volatile uint8_t * eicra)
{
  *eicra &= ~(ISC21_bm | ISC20_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *eicra |=            ISC20_bm; break;
  case interface::TriggerMode::Low        : *eicra |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */            break;
  case interface::TriggerMode::RisingEdge : *eicra |= ISC21_bm | ISC20_bm; break;
  case interface::TriggerMode::FallingEdge: *eicra |= ISC21_bm;            break;
  }
}

void setTriggerModeEint3(interface::TriggerMode const trigger_mode, volatile uint8_t * eicra)
{
  *eicra &= ~(ISC31_bm | ISC30_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *eicra |=            ISC30_bm; break;
  case interface::TriggerMode::Low        : *eicra |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */            break;
  case interface::TriggerMode::RisingEdge : *eicra |= ISC31_bm | ISC30_bm; break;
  case interface::TriggerMode::FallingEdge: *eicra |= ISC31_bm;            break;
  }
}

void setTriggerModeEint4(interface::TriggerMode const trigger_mode, volatile uint8_t * eicrb)
{
  *eicrb &= ~(ISC41_bm | ISC40_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *eicrb |=            ISC40_bm; break;
  case interface::TriggerMode::Low        : *eicrb |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */            break;
  case interface::TriggerMode::RisingEdge : *eicrb |= ISC41_bm | ISC40_bm; break;
  case interface::TriggerMode::FallingEdge: *eicrb |= ISC41_bm;            break;
  }
}

void setTriggerModeEint5(interface::TriggerMode const trigger_mode, volatile uint8_t * eicrb)
{
  *eicrb &= ~(ISC51_bm | ISC50_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *eicrb |=            ISC50_bm; break;
  case interface::TriggerMode::Low        : *eicrb |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */            break;
  case interface::TriggerMode::RisingEdge : *eicrb |= ISC51_bm | ISC50_bm; break;
  case interface::TriggerMode::FallingEdge: *eicrb |= ISC51_bm;            break;
  }
}

void setTriggerModeEint6(interface::TriggerMode const trigger_mode, volatile uint8_t * eicrb)
{
  *eicrb &= ~(ISC61_bm | ISC60_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *eicrb |=            ISC60_bm; break;
  case interface::TriggerMode::Low        : *eicrb |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */            break;
  case interface::TriggerMode::RisingEdge : *eicrb |= ISC61_bm | ISC60_bm; break;
  case interface::TriggerMode::FallingEdge: *eicrb |= ISC61_bm;            break;
  }
}

void setTriggerModeEint7(interface::TriggerMode const trigger_mode, volatile uint8_t * eicrb)
{
  *eicrb &= ~(ISC71_bm | ISC70_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *eicrb |=            ISC70_bm; break;
  case interface::TriggerMode::Low        : *eicrb |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */            break;
  case interface::TriggerMode::RisingEdge : *eicrb |= ISC71_bm | ISC70_bm; break;
  case interface::TriggerMode::FallingEdge: *eicrb |= ISC71_bm;            break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* snowfox */
