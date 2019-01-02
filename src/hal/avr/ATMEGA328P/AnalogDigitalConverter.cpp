/**
 * Spectre is a modular RTOS with extensive IO support.
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

#include <spectre/hal/avr/ATMEGA328P/AnalogDigitalConverter.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* ADCSRA */
#define ADPS0_bm  (1<<0)
#define ADPS1_bm  (1<<1)
#define ADPS2_bm  (1<<2)
#define ADIE_bm   (1<<3)
#define ADIF_bm   (1<<4)
#define ADATE_bm  (1<<5)
#define ADSC_bm   (1<<6)
#define ADEN_bm   (1<<7)

/* ADMUX */
#define MUX0_bm   (1<<0)
#define MUX1_bm   (1<<1)
#define MUX2_bm   (1<<2)
#define MUX3_bm   (1<<3)
#define ADLAR_bm  (1<<5)
#define REFS0_bm  (1<<6)
#define REFS1_bm  (1<<7)

/* DIDR0 */
#define ADC0D_bm  (1<<0)
#define ADC1D_bm  (1<<1)
#define ADC2D_bm  (1<<2)
#define ADC3D_bm  (1<<3)
#define ADC4D_bm  (1<<4)
#define ADC5D_bm  (1<<5)

/* VREF NUMBERS */

#define VREF_AREF           0
#define VREF_AVCC           1
#define VREF_BANDGAP_1_1V   2
#define VREF_INVALID      255

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef enum
{
  Prescaler_2   =                       ADPS0_bm,
  Prescaler_4   =            ADPS1_bm,
  Prescaler_8   =            ADPS1_bm | ADPS0_bm,
  Prescaler_16  = ADPS2_bm,
  Prescaler_32  = ADPS2_bm |            ADPS0_bm,
  Prescaler_64  = ADPS2_bm | ADPS1_bm,
  Prescaler_128 = ADPS2_bm | ADPS1_bm | ADPS0_bm
} AdcPrescalerSelect;

typedef enum
{
  AREF          = 0,
  AVCC          =            REFS0_bm,
  BANDGAP_1_1V  = REFS1_bm | REFS0_bm
} AdcReferenceVoltageSelect;

typedef enum
{
  ADC_CH_0  = 0,
  ADC_CH_1 =                     MUX0_bm,
  ADC_CH_2 =           MUX1_bm,
  ADC_CH_3 =           MUX1_bm | MUX0_bm,
  ADC_CH_4 = MUX2_bm,
  ADC_CH_5 = MUX2_bm |           MUX0_bm,
  ADC_CH_6 = MUX2_bm | MUX1_bm,
  ADC_CH_7 = MUX2_bm | MUX1_bm | MUX0_bm
} AdcChannelSelect;


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
  case 0 : { *_ADMUX |= static_cast<uint8_t>(ADC_CH_0); *_DIDR0 |= ADC0D_bm; } break;
  case 1 : { *_ADMUX |= static_cast<uint8_t>(ADC_CH_1); *_DIDR0 |= ADC1D_bm; } break;
  case 2 : { *_ADMUX |= static_cast<uint8_t>(ADC_CH_2); *_DIDR0 |= ADC2D_bm; } break;
  case 3 : { *_ADMUX |= static_cast<uint8_t>(ADC_CH_3); *_DIDR0 |= ADC3D_bm; } break;
  case 4 : { *_ADMUX |= static_cast<uint8_t>(ADC_CH_4); *_DIDR0 |= ADC4D_bm; } break;
  case 5 : { *_ADMUX |= static_cast<uint8_t>(ADC_CH_5); *_DIDR0 |= ADC5D_bm; } break;
  case 6 : { *_ADMUX |= static_cast<uint8_t>(ADC_CH_6);                      } break;
  case 7 : { *_ADMUX |= static_cast<uint8_t>(ADC_CH_7);                      } break;
  default:                                                                     break;
  }
}

void AnalogDigitalConverter::startConversion()
{
  *_ADCSRA |= ADSC_bm;
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
  case 2  : *_ADCSRA |= static_cast<uint8_t>(Prescaler_2  ); break;
  case 4  : *_ADCSRA |= static_cast<uint8_t>(Prescaler_4  ); break;
  case 8  : *_ADCSRA |= static_cast<uint8_t>(Prescaler_8  ); break;
  case 16 : *_ADCSRA |= static_cast<uint8_t>(Prescaler_16 ); break;
  case 32 : *_ADCSRA |= static_cast<uint8_t>(Prescaler_32 ); break;
  case 64 : *_ADCSRA |= static_cast<uint8_t>(Prescaler_64 ); break;
  case 128: *_ADCSRA |= static_cast<uint8_t>(Prescaler_128); break;
  default :                                                  break;
  }
}

void AnalogDigitalConverter::setReferenceVoltage(uint8_t const v_ref)
{
  *_ADMUX &= ~(REFS1_bm | REFS0_bm);

  switch(v_ref)
  {
  case VREF_AREF        : *_ADMUX |= static_cast<uint8_t>(AREF);         break;
  case VREF_AVCC        : *_ADMUX |= static_cast<uint8_t>(AVCC);         break;
  case VREF_BANDGAP_1_1V: *_ADMUX |= static_cast<uint8_t>(BANDGAP_1_1V); break;
  default               :                                                break;
  }
}

uint8_t AnalogDigitalConverter::toVRefNum(VRef const vref)
{
  switch(vref)
  {
  case VRef::AREF        : return VREF_AREF;         break;
  case VRef::AVCC        : return VREF_AVCC;         break;
  case VRef::BANDGAP_1_1V: return VREF_BANDGAP_1_1V; break;
  default                : return VREF_INVALID;      break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void AnalogDigitalConverter::enableAdc()
{
  *_ADCSRA |= ADEN_bm;
}

void AnalogDigitalConverter::disableAdc()
{
  *_ADCSRA &= ~ADEN_bm;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */
