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

#include <snowfox/hal/avr/ATMEGA328P/AnalogDigitalConverter.h>

#include <snowfox/util/BitUtil.h>

#include <snowfox/cpu/avr/io/ATMEGA328P.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class AdcPrescaler : uint8_t
{
  P_2   =                       ADPS0_bm,
  P_4   =            ADPS1_bm,
  P_8   =            ADPS1_bm | ADPS0_bm,
  P_16  = ADPS2_bm,
  P_32  = ADPS2_bm |            ADPS0_bm,
  P_64  = ADPS2_bm | ADPS1_bm,
  P_128 = ADPS2_bm | ADPS1_bm | ADPS0_bm
};

enum class AdcReferenceVoltage : uint8_t
{
  AREF          = 0,
  AVCC          =            REFS0_bm,
  BANDGAP_1_1V  = REFS1_bm | REFS0_bm
};

enum class AdcChannel : uint8_t
{
  CH_0  = 0,
  CH_1 =                     MUX0_bm,
  CH_2 =           MUX1_bm,
  CH_3 =           MUX1_bm | MUX0_bm,
  CH_4 = MUX2_bm,
  CH_5 = MUX2_bm |           MUX0_bm,
  CH_6 = MUX2_bm | MUX1_bm,
  CH_7 = MUX2_bm | MUX1_bm | MUX0_bm
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AnalogDigitalConverter::AnalogDigitalConverter(volatile uint8_t * adcsra, volatile uint8_t * admux, volatile uint8_t * didr0, volatile uint16_t * adc)
: _ADCSRA(adcsra),
  _ADMUX (admux ),
  _DIDR0 (didr0 ),
  _ADC   (adc   )
{
  enableAdc();
}

AnalogDigitalConverter::~AnalogDigitalConverter()
{
  disableAdc();
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void AnalogDigitalConverter::setAnalogChannel(uint8_t const adc_channel)
{
  *_ADMUX &= ~(MUX3_bm | MUX2_bm | MUX1_bm | MUX0_bm);
  *_DIDR0 &= ~(ADC5D_bm | ADC4D_bm | ADC3D_bm | ADC2D_bm | ADC1D_bm | ADC0D_bm);

  switch(adc_channel)
  {
  case 0 : { *_ADMUX |= static_cast<uint8_t>(AdcChannel::CH_0); util::setBit(_DIDR0, ADC0D_bp); } break;
  case 1 : { *_ADMUX |= static_cast<uint8_t>(AdcChannel::CH_1); util::setBit(_DIDR0, ADC1D_bp); } break;
  case 2 : { *_ADMUX |= static_cast<uint8_t>(AdcChannel::CH_2); util::setBit(_DIDR0, ADC2D_bp); } break;
  case 3 : { *_ADMUX |= static_cast<uint8_t>(AdcChannel::CH_3); util::setBit(_DIDR0, ADC3D_bp); } break;
  case 4 : { *_ADMUX |= static_cast<uint8_t>(AdcChannel::CH_4); util::setBit(_DIDR0, ADC4D_bp); } break;
  case 5 : { *_ADMUX |= static_cast<uint8_t>(AdcChannel::CH_5); util::setBit(_DIDR0, ADC5D_bp); } break;
  case 6 : { *_ADMUX |= static_cast<uint8_t>(AdcChannel::CH_6);                                 } break;
  case 7 : { *_ADMUX |= static_cast<uint8_t>(AdcChannel::CH_7);                                 } break;
  default:                                                                                        break;
  }
}

void AnalogDigitalConverter::startConversion()
{
  util::setBit(_ADCSRA, ADSC_bp);
}

bool AnalogDigitalConverter::isConversionComplete()
{
  return ((*_ADCSRA & ADSC_bm) == 0);
}

uint32_t AnalogDigitalConverter::getConversionResult()
{
  return static_cast<uint32_t>(*_ADC);
}

void AnalogDigitalConverter::setPrescaler(uint32_t const prescaler)
{
  *_ADCSRA &= ~(ADPS2_bm | ADPS1_bm | ADPS0_bm);

  switch(prescaler)
  {
  case 2  : *_ADCSRA |= static_cast<uint8_t>(AdcPrescaler::P_2  ); break;
  case 4  : *_ADCSRA |= static_cast<uint8_t>(AdcPrescaler::P_4  ); break;
  case 8  : *_ADCSRA |= static_cast<uint8_t>(AdcPrescaler::P_8  ); break;
  case 16 : *_ADCSRA |= static_cast<uint8_t>(AdcPrescaler::P_16 ); break;
  case 32 : *_ADCSRA |= static_cast<uint8_t>(AdcPrescaler::P_32 ); break;
  case 64 : *_ADCSRA |= static_cast<uint8_t>(AdcPrescaler::P_64 ); break;
  case 128: *_ADCSRA |= static_cast<uint8_t>(AdcPrescaler::P_128); break;
  default :                                                                break;
  }
}

void AnalogDigitalConverter::setReferenceVoltage(uint8_t const v_ref_num)
{
  *_ADMUX &= ~(REFS1_bm | REFS0_bm);

  switch(v_ref_num)
  {
  case toVRefNum(VRef::AREF        ): *_ADMUX |= static_cast<uint8_t>(AdcReferenceVoltage::AREF        ); break;
  case toVRefNum(VRef::AVCC        ): *_ADMUX |= static_cast<uint8_t>(AdcReferenceVoltage::AVCC        ); break;
  case toVRefNum(VRef::BANDGAP_1_1V): *_ADMUX |= static_cast<uint8_t>(AdcReferenceVoltage::BANDGAP_1_1V); break;
  default                           :                                                                     break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void AnalogDigitalConverter::enableAdc()
{
  util::setBit(_ADCSRA, ADEN_bp);
}

void AnalogDigitalConverter::disableAdc()
{
  util::clrBit(_ADCSRA, ADEN_bp);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* snowfox */
