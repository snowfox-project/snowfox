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

#include <snowfox/hal/avr/common/ATMEGA3209_4809/InterruptController.h>

#include <snowfox/util/BitUtil.h>

#include <snowfox/cpu/avr/io/common/ATMEGA3209_4809.h>

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
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t constexpr NUM_INTERRUPT_CALLBACKS = 48;

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

static interface::InterruptCallback * isr[NUM_INTERRUPT_CALLBACKS] = {0};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * crcscan_ctrla,
                                         volatile uint8_t * bod_intctrl,
                                         volatile uint8_t * rtc_intctrl,
                                         volatile uint8_t * rtc_pitintctrl,
                                         volatile uint8_t * tca0_intctrl,
                                         volatile uint8_t * tcb0_intctrl,
                                         volatile uint8_t * tcb1_intctrl,
                                         volatile uint8_t * tcb2_intctrl,
                                         volatile uint8_t * tcb3_intctrl,
                                         volatile uint8_t * usart0_ctrla,
                                         volatile uint8_t * usart1_ctrla,
                                         volatile uint8_t * usart2_ctrla,
                                         volatile uint8_t * usart3_ctrla,
                                         volatile uint8_t * twi_mctrla,
                                         volatile uint8_t * twi_sctrla,
                                         volatile uint8_t * spi_intctrl)
: _CRCSCAN_CTRLA (crcscan_ctrla ),
  _BOD_INTCTRL   (bod_intctrl   ),
  _RTC_INTCTRL   (rtc_intctrl   ),
  _RTC_PITINTCTRL(rtc_pitintctrl),
  _TCA0_INTCTRL  (tca0_intctrl  ),
  _TCB0_INTCTRL  (tcb0_intctrl  ),
  _TCB1_INTCTRL  (tcb1_intctrl  ),
  _TCB2_INTCTRL  (tcb2_intctrl  ),
  _TCB3_INTCTRL  (tcb3_intctrl  ),
  _USART0_CTRLA  (usart0_ctrla  ),
  _USART1_CTRLA  (usart1_ctrla  ),
  _USART2_CTRLA  (usart2_ctrla  ),
  _USART3_CTRLA  (usart3_ctrla  ),
  _TWI_MCTRLA    (twi_mctrla    ),
  _TWI_SCTRLA    (twi_sctrla    ),
  _SPI_INTCTRL   (spi_intctrl   )
{

}

InterruptController::~InterruptController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void InterruptController::enableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::CRC_NMI                        ): { util::setBit(_CRCSCAN_CTRLA,  CRCSCAN_NMIEN_bp); } break;
  case toIntNum(Interrupt::VOLTAGE_LEVEL_MONITOR          ): { util::setBit(_BOD_INTCTRL,    BOD_VLMIE_bp    ); } break;
  /* RTC */
  case toIntNum(Interrupt::RTC_OVERFLOW                   ): { util::setBit(_RTC_INTCTRL,    RTC_OVF_bp      ); } break;
  case toIntNum(Interrupt::RTC_COMPARE                    ): { util::setBit(_RTC_INTCTRL,    RTC_CMP_bp      ); } break;
  case toIntNum(Interrupt::RTC_PERIODIC_INTERRUPT         ): { util::setBit(_RTC_PITINTCTRL, RTC_PI_bp       ); } break;
  /* TIMER A0 */
  case toIntNum(Interrupt::TIMERA0_OVERFLOW               ): { util::setBit(_TCA0_INTCTRL,   TCAx_OVF_bp     ); } break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_0              ): { util::setBit(_TCA0_INTCTRL,   TCAx_CMP0_bp    ); } break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_1              ): { util::setBit(_TCA0_INTCTRL,   TCAx_CMP1_bp    ); } break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_2              ): { util::setBit(_TCA0_INTCTRL,   TCAx_CMP2_bp    ); } break;
  /* TIMER B0/1/2/3 */
  case toIntNum(Interrupt::TIMERB0_CAPTURE                ): { util::setBit(_TCB0_INTCTRL,   TCBx_CAPT_bp    ); } break;
  case toIntNum(Interrupt::TIMERB1_CAPTURE                ): { util::setBit(_TCB1_INTCTRL,   TCBx_CAPT_bp    ); } break;
  case toIntNum(Interrupt::TIMERB2_CAPTURE                ): { util::setBit(_TCB2_INTCTRL,   TCBx_CAPT_bp    ); } break;
  case toIntNum(Interrupt::TIMERB3_CAPTURE                ): { util::setBit(_TCB3_INTCTRL,   TCBx_CAPT_bp    ); } break;
  /* USART0 */
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): { util::setBit(_USART0_CTRLA,   USARTx_RXCIE_bp ); } break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): { util::setBit(_USART0_CTRLA,   USARTx_TXCIE_bp ); } break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): { util::setBit(_USART0_CTRLA,   USARTx_DREIE_bp ); } break;
  case toIntNum(Interrupt::USART0_RECEIVER_START_OF_FRAME ): { util::setBit(_USART0_CTRLA,   USARTx_RXSIE_bp ); } break;
  /* USART1 */
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): { util::setBit(_USART1_CTRLA,   USARTx_RXCIE_bp ); } break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): { util::setBit(_USART1_CTRLA,   USARTx_TXCIE_bp ); } break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): { util::setBit(_USART1_CTRLA,   USARTx_DREIE_bp ); } break;
  case toIntNum(Interrupt::USART1_RECEIVER_START_OF_FRAME ): { util::setBit(_USART1_CTRLA,   USARTx_RXSIE_bp ); } break;
  /* USART2 */
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): { util::setBit(_USART2_CTRLA,   USARTx_RXCIE_bp ); } break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): { util::setBit(_USART2_CTRLA,   USARTx_TXCIE_bp ); } break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): { util::setBit(_USART2_CTRLA,   USARTx_DREIE_bp ); } break;
  case toIntNum(Interrupt::USART2_RECEIVER_START_OF_FRAME ): { util::setBit(_USART2_CTRLA,   USARTx_RXSIE_bp ); } break;
  /* USART3 */
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): { util::setBit(_USART3_CTRLA,   USARTx_RXCIE_bp ); } break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): { util::setBit(_USART3_CTRLA,   USARTx_TXCIE_bp ); } break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): { util::setBit(_USART3_CTRLA,   USARTx_DREIE_bp ); } break;
  case toIntNum(Interrupt::USART3_RECEIVER_START_OF_FRAME ): { util::setBit(_USART3_CTRLA,   USARTx_RXSIE_bp ); } break;
  /* TWI0_MASTER/SLAVE */
  case toIntNum(Interrupt::TWI0_MASTER_READ               ): { util::setBit(_TWI_MCTRLA,     TWI_RIEN_bp     ); } break;
  case toIntNum(Interrupt::TWI0_MASTER_WRITE              ): { util::setBit(_TWI_MCTRLA,     TWI_WIEN_bp     ); } break;
  case toIntNum(Interrupt::TWI0_SLAVE_DATA                ): { util::setBit(_TWI_SCTRLA,     TWI_DIEN_bp     ); } break;
  case toIntNum(Interrupt::TWI0_SLAVE_ADDRESS             ): { util::setBit(_TWI_SCTRLA,     TWI_APIEN_bp    ); } break;
  case toIntNum(Interrupt::TWI0_SLAVE_STOP                ): { util::setBit(_TWI_SCTRLA,     TWI_APIEN_bp    ); util::setBit(_TWI_SCTRLA,  TWI_PIEN_bp  ); } break;
  /* SPI */
  case toIntNum(Interrupt::SPI0_TRANFER_COMPLETE          ): { util::setBit(_SPI_INTCTRL,    SPIx_IE_bp      ); util::setBit(_SPI_INTCTRL, SPIx_TXCIE_bp); } break;
  case toIntNum(Interrupt::SPI0_WRITE_COLLISION           ): { util::setBit(_SPI_INTCTRL,    SPIx_IE_bp      );                                            } break;
  /* GLOBAL */
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("sei");                             break;
#endif
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::CRC_NMI                        ): { util::clrBit(_CRCSCAN_CTRLA,  CRCSCAN_NMIEN_bp); } break;
  case toIntNum(Interrupt::VOLTAGE_LEVEL_MONITOR          ): { util::clrBit(_BOD_INTCTRL,    BOD_VLMIE_bp    ); } break;
  /* RTC */
  case toIntNum(Interrupt::RTC_OVERFLOW                   ): { util::clrBit(_RTC_INTCTRL,    RTC_OVF_bp      ); } break;
  case toIntNum(Interrupt::RTC_COMPARE                    ): { util::clrBit(_RTC_INTCTRL,    RTC_CMP_bp      ); } break;
  case toIntNum(Interrupt::RTC_PERIODIC_INTERRUPT         ): { util::clrBit(_RTC_PITINTCTRL, RTC_PI_bp       ); } break;
  /* TIMER A0 */
  case toIntNum(Interrupt::TIMERA0_OVERFLOW               ): { util::clrBit(_TCA0_INTCTRL,   TCAx_OVF_bp     ); } break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_0              ): { util::clrBit(_TCA0_INTCTRL,   TCAx_CMP0_bp    ); } break;
  case toIntNum(Interrupt::TIMERA0_COMPARE_1              ): { util::clrBit(_TCA0_INTCTRL,   TCAx_CMP1_bp    ); } break;
  /* TIMER B0/1/2/3 */
  case toIntNum(Interrupt::TIMERB0_CAPTURE                ): { util::clrBit(_TCB0_INTCTRL,   TCBx_CAPT_bp    ); } break;
  case toIntNum(Interrupt::TIMERB1_CAPTURE                ): { util::clrBit(_TCB1_INTCTRL,   TCBx_CAPT_bp    ); } break;
  case toIntNum(Interrupt::TIMERB2_CAPTURE                ): { util::clrBit(_TCB2_INTCTRL,   TCBx_CAPT_bp    ); } break;
  case toIntNum(Interrupt::TIMERB3_CAPTURE                ): { util::clrBit(_TCB3_INTCTRL,   TCBx_CAPT_bp    ); } break;
  /* USART0 */
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): { util::clrBit(_USART0_CTRLA,   USARTx_RXCIE_bp ); } break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): { util::clrBit(_USART0_CTRLA,   USARTx_TXCIE_bp ); } break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): { util::clrBit(_USART0_CTRLA,   USARTx_DREIE_bp ); } break;
  case toIntNum(Interrupt::USART0_RECEIVER_START_OF_FRAME ): { util::clrBit(_USART0_CTRLA,   USARTx_RXSIE_bp ); } break;
  /* USART1 */
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): { util::clrBit(_USART1_CTRLA,   USARTx_RXCIE_bp ); } break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): { util::clrBit(_USART1_CTRLA,   USARTx_TXCIE_bp ); } break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): { util::clrBit(_USART1_CTRLA,   USARTx_DREIE_bp ); } break;
  case toIntNum(Interrupt::USART1_RECEIVER_START_OF_FRAME ): { util::clrBit(_USART1_CTRLA,   USARTx_RXSIE_bp ); } break;
  /* USART2 */
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): { util::clrBit(_USART2_CTRLA,   USARTx_RXCIE_bp ); } break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): { util::clrBit(_USART2_CTRLA,   USARTx_TXCIE_bp ); } break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): { util::clrBit(_USART2_CTRLA,   USARTx_DREIE_bp ); } break;
  case toIntNum(Interrupt::USART2_RECEIVER_START_OF_FRAME ): { util::clrBit(_USART2_CTRLA,   USARTx_RXSIE_bp ); } break;
  /* USART3 */
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): { util::clrBit(_USART3_CTRLA,   USARTx_RXCIE_bp ); } break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): { util::clrBit(_USART3_CTRLA,   USARTx_TXCIE_bp ); } break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): { util::clrBit(_USART3_CTRLA,   USARTx_DREIE_bp ); } break;
  case toIntNum(Interrupt::USART3_RECEIVER_START_OF_FRAME ): { util::clrBit(_USART3_CTRLA,   USARTx_RXSIE_bp ); } break;
  /* TWI0_MASTER/SLAVE */
  case toIntNum(Interrupt::TWI0_MASTER_READ               ): { util::clrBit(_TWI_MCTRLA,     TWI_RIEN_bp     ); } break;
  case toIntNum(Interrupt::TWI0_MASTER_WRITE              ): { util::clrBit(_TWI_MCTRLA,     TWI_WIEN_bp     ); } break;
  case toIntNum(Interrupt::TWI0_SLAVE_DATA                ): { util::clrBit(_TWI_SCTRLA,     TWI_DIEN_bp     ); } break;
  case toIntNum(Interrupt::TWI0_SLAVE_ADDRESS             ): { util::clrBit(_TWI_SCTRLA,     TWI_APIEN_bp    ); } break;
  case toIntNum(Interrupt::TWI0_SLAVE_STOP                ): { util::clrBit(_TWI_SCTRLA,     TWI_PIEN_bp     ); } break;
  /* SPI */
  case toIntNum(Interrupt::SPI0_TRANFER_COMPLETE          ): { util::clrBit(_SPI_INTCTRL,    SPIx_TXCIE_bp   ); } break;
  case toIntNum(Interrupt::SPI0_WRITE_COLLISION           ): {                                                  } break;
  /* GLOBAL */
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("cli");                             break;
#endif
  }
}

void InterruptController::registerInterruptCallback(uint8_t const int_num, interface::InterruptCallback * interrupt_callback)
{
  if(int_num < NUM_INTERRUPT_CALLBACKS)
  {
    isr[int_num] = interrupt_callback;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA3209_4809 */

} /* hal */

} /* snowfox */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega3209) || defined(MCU_TYPE_atmega4809) )

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace snowfox::hal::ATMEGA3209_4809;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(CRCSCAN_NMI_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::CRC_NMI)]);
}

ISR(BOD_VLM_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::VOLTAGE_LEVEL_MONITOR)]);
}

ISR(RTC_CNT_vect)
{
  bool const is_overflow      = (RTC_INTFLAGS & RTC_OVF_bm) == RTC_OVF_bm;
  bool const is_compare_match = (RTC_INTFLAGS & RTC_CMP_bm) == RTC_CMP_bm;

  if(is_overflow)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::RTC_OVERFLOW)]);
    RTC_INTFLAGS |= RTC_OVF_bm;
  }

  if(is_compare_match)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::RTC_COMPARE)]);
    RTC_INTFLAGS |= RTC_CMP_bm;
  }
}

ISR(RTC_PIT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::RTC_PERIODIC_INTERRUPT)]);
}

ISR(CCL_CCL_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::CONFIGURABLE_CUSTOM_LOGIC)]);
}

ISR(PORTA_PORT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INTERRUPT_PORT_A)]);
}

ISR(TCA0_OVF_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMERA0_OVERFLOW)]);
}

ISR(TCA0_HUNF_vect)
{
  /* Not implemented */
}

ISR(TCA0_CMP0_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMERA0_COMPARE_0)]);
}

ISR(TCA0_CMP1_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMERA0_COMPARE_1)]);
}

ISR(TCA0_CMP2_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMERA0_COMPARE_2)]);
}

ISR(TCB0_INT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMERB0_CAPTURE)]);
}

ISR(TCB1_INT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMERB1_CAPTURE)]);
}

ISR(TWI0_TWIS_vect)
{
  bool const is_slave_data    = (TWI0_SSTATUS & TWI_DIF_bm) == TWI_DIF_bm;
  /* TWI.SSTATUS
   *   Bit 0 – AP Address or Stop
   *
   *   When the TWI slave address or Stop Interrupt Flag (APIF) is set, this bit
   *   determines whether the interrupt is due to address detection or a Stop condition.
   *
   *   Value | Name | Description
   *   0     | STOP | A Stop condition generated the interrupt on APIF
   *   1     | ADR  | Address detection generated the interrupt on APIF
   */
  bool const is_slave_address = (TWI0_SSTATUS & TWI_AP_bm ) == TWI_AP_bm;
  bool const is_slave_stop    = (TWI0_SSTATUS & TWI_AP_bm ) == 0;

  if(is_slave_data)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::TWI0_SLAVE_DATA)]);
  }

  if(is_slave_address)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::TWI0_SLAVE_ADDRESS)]);
  }

  if(is_slave_stop)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::TWI0_SLAVE_STOP)]);
  }
}

ISR(TWI0_TWIM_vect)
{
  bool const is_master_read  = (TWI0_MSTATUS & TWI_RIF_bm) == TWI_RIF_bm;
  bool const is_master_write = (TWI0_MSTATUS & TWI_WIF_bm) == TWI_WIF_bm;

  if(is_master_read)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::TWI0_MASTER_READ)]);
    TWI0_MSTATUS |= TWI_RIF_bm; /* Clearing interrupt flag - TODO: is this necessary? */
  }

  if(is_master_write)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::TWI0_MASTER_WRITE)]);
    TWI0_MSTATUS |= TWI_WIF_bm; /* Clearing interrupt flag - TODO: is this necessary? */
  }
}

ISR(SPI0_INT_vect)
{
  bool const is_transfer_complete = (SPI0_INTFLAGS & SPI_IF_bm   ) == SPI_IF_bm;
  bool const is_write_collision   = (SPI0_INTFLAGS & SPI_WRCOL_bm) == SPI_WRCOL_bm;

  if(is_transfer_complete)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::SPI0_TRANFER_COMPLETE)]);
  }

  if(is_write_collision)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::SPI0_WRITE_COLLISION)]);
  }
}

ISR(USART0_RXC_vect)
{
  bool const is_usart0_receive_start    = (USART0_STATUS & USART_RXSIF_bm) == USART_RXSIF_bm;
  bool const is_usart0_receive_complete = (USART0_STATUS & USART_RXCIF_bm) == USART_RXCIF_bm;

  if(is_usart0_receive_start)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::USART0_RECEIVER_START_OF_FRAME)]);
  }

  if(is_usart0_receive_complete)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::USART0_RECEIVE_COMPLETE)]);
    USART0_STATUS |= USART_RXSIF_bm; /* Clearing flag by writing a '1' to it */
  }
}

ISR(USART0_DRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART0_TXC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE)]);
}

ISR(PORTD_PORT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INTERRUPT_PORT_D)]);
}

ISR(AC0_AC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::ANALOG_COMPARATOR)]);
}

ISR(ADC0_RESRDY_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::ADC_RESULT_READY)]);
}

ISR(ADC0_WCOMP_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::ADC_WINDOW_COMPARE)]);
}

ISR(PORTC_PORT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INTERRUPT_PORT_C)]);
}

ISR(TCB2_INT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMERB2_CAPTURE)]);
}

ISR(USART1_RXC_vect)
{
  bool const is_usart1_receive_start    = (USART1_STATUS & USART_RXSIF_bm) == USART_RXSIF_bm;
  bool const is_usart1_receive_complete = (USART1_STATUS & USART_RXCIF_bm) == USART_RXCIF_bm;

  if(is_usart1_receive_start)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::USART1_RECEIVER_START_OF_FRAME)]);
  }

  if(is_usart1_receive_complete)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::USART1_RECEIVE_COMPLETE)]);
    USART1_STATUS |= USART_RXSIF_bm; /* Clearing flag by writing a '1' to it */
  }
}

ISR(USART1_DRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART1_TXC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE)]);
}

ISR(PORTF_PORT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INTERRUPT_PORT_F)]);
}

ISR(NVMCTRL_EE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EEPROM_READY)]);
}

ISR(USART2_RXC_vect)
{
  bool const is_usart2_receive_start    = (USART2_STATUS & USART_RXSIF_bm) == USART_RXSIF_bm;
  bool const is_usart2_receive_complete = (USART2_STATUS & USART_RXCIF_bm) == USART_RXCIF_bm;

  if(is_usart2_receive_start)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::USART2_RECEIVER_START_OF_FRAME)]);
  }

  if(is_usart2_receive_complete)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::USART2_RECEIVE_COMPLETE)]);
    USART2_STATUS |= USART_RXSIF_bm; /* Clearing flag by writing a '1' to it */
  }
}

ISR(USART2_DRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART2_TXC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE)]);
}

ISR(PORTB_PORT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INTERRUPT_PORT_B)]);
}

ISR(PORTE_PORT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INTERRUPT_PORT_E)]);
}

ISR(TCB3_INT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMERB3_CAPTURE)]);
}

ISR(USART3_RXC_vect)
{
  bool const is_usart3_receive_start    = (USART3_STATUS & USART_RXSIF_bm) == USART_RXSIF_bm;
  bool const is_usart3_receive_complete = (USART3_STATUS & USART_RXCIF_bm) == USART_RXCIF_bm;

  if(is_usart3_receive_start)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::USART3_RECEIVER_START_OF_FRAME)]);
  }

  if(is_usart3_receive_complete)
  {
    executeCallbackIfValid(isr[toIntNum(Interrupt::USART3_RECEIVE_COMPLETE)]);
    USART3_STATUS |= USART_RXSIF_bm; /* Clearing flag by writing a '1' to it */
  }
}

ISR(USART3_DRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART3_TXC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE)]);
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega3209) || defined(MCU_TYPE_atmega4809) ) */
