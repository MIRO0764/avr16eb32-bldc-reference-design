/**
 *  @file mc_analog.c
 *
 *  @ingroup mclib
 *
 *  @brief This Source File contains the implementation of the functions that
 *         are used to read the analog signals.
 *
 *  @version AVR® MCU Motor Control Library v1.2.0
 *
 *  @copyright © 2026 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. You're responsible
 *  for complying with 3rd party license terms applicable to your use of 3rd
 *  party software (including open source software) that may accompany
 *  Microchip software.
 *
 *  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 *  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
 *  NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
 *  RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID
 *  DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 **/


#include "../../system/clock.h"

#include <util/delay.h>
#include <avr/io.h>
#include <util/atomic.h>

#include "../mc_internal_defines.h"
#include "../mc_pins.h"
#include "../mc_control_analog.h"
#include "../mc_control_fault.h"


#define MC_ANALOG_FILTER    true


#define _MC_ANALOG_TEMPERATURE()    do { ADC0_ChannelSelect(ADC_MUXPOS_GND_gc); \
                                         measurement_id = AID_TEMPERATURE; \
                                         _delay_us(1); \
                                         ADC0_ChannelSelect(TEMP_ADC_PIN); \
                                         ADC0_ConversionStart(); \
                                    } while (0)

#define _MC_ANALOG_CURRENT()        do { ADC0_DiffChannelSelect(ADC_MUXPOS_GND_gc, ADC_MUXNEG_GND_gc); \
                                         measurement_id = AID_CURRENT; \
                                         _delay_us(1); \
                                         ADC0_DiffChannelSelect(CRT_SNS_ADC_PIN, CRT_REF_ADC_PIN); \
                                         ADC0_DiffConversionStart(); \
                                    } while (0)

#define _MC_ANALOG_VOLTAGE()        do { ADC0_ChannelSelect(ADC_MUXPOS_GND_gc); \
                                         measurement_id = AID_VOLTAGE; \
                                         _delay_us(1); \
                                         ADC0_ChannelSelect(VBUS_ADC_PIN); \
                                         ADC0_ConversionStart(); \
                                    } while (0)

#define _MC_ANALOG_POTENTIOMETER()  do { ADC0_ChannelSelect(ADC_MUXPOS_GND_gc); \
                                         measurement_id = AID_POTENTIOMETER; \
                                         _delay_us(1); \
                                         ADC0_ChannelSelect(POT_ADC_PIN); \
                                         ADC0_ConversionStart(); \
                                    } while (0)

#define _MC_ANALOG_INIT()           do { ADC0_Initialize(); } while (0)

#define _MC_ANALOG_RESRDY()         ADC0_IsConversionDone()

#define _MC_ANALOG_GET_RES()        ADC0_ConversionResultGet()


static mc_analog_id_t measurement_id;
static volatile mc_analog_data_t adc_filters[AID_MAX];

static inline void FilterClear(mc_analog_id_t id)     { adc_filters[id].W = 0; }
static inline uint16_t FilterRead (mc_analog_id_t id) { return adc_filters[id].H; }

#if (MC_ANALOG_FILTER == true)

static inline void FilterUnsigned(mc_analog_id_t id, adc_result_t data) { mc_analog_data_t x = adc_filters[id]; uint32_t y =           x.W;  uint16_t z =           x.H;  adc_filters[id].W =            y - z + (uint16_t)data; }
static inline void FilterSigned(mc_analog_id_t id,   adc_result_t data) { mc_analog_data_t x = adc_filters[id]; int32_t  y = (int32_t)(x.W);  int16_t z = (int16_t)(x.H); adc_filters[id].W = (uint32_t)(y - z +  (int16_t)data); }

#else

static inline void FilterUnsigned(mc_analog_id_t id, adc_result_t data) { adc_filters[id].H = data; }
static inline void FilterSigned(mc_analog_id_t id,   adc_result_t data) { adc_filters[id].H = data; }

#endif /* MC_ANALOG_FILTER */


void MC_Analog_Initialize(void)
{
    _MC_ANALOG_INIT();
    FilterClear(AID_CURRENT);
    FilterClear(AID_VOLTAGE);
    FilterClear(AID_TEMPERATURE);
    FilterClear(AID_POTENTIOMETER);
    _MC_ANALOG_CURRENT();
}

/* Called from interrupt context */
void MC_Analog_Run(void)
{
    if (_MC_ANALOG_RESRDY())
    {
        mc_analog_id_t prev_id = measurement_id;
        uint16_t res = _MC_ANALOG_GET_RES();

        switch(measurement_id)
        {
            case AID_CURRENT:       FilterSigned(measurement_id, res);   _MC_ANALOG_VOLTAGE();        break;
            case AID_VOLTAGE:       FilterUnsigned(measurement_id, res); _MC_ANALOG_POTENTIOMETER();  break;
            case AID_POTENTIOMETER: FilterUnsigned(measurement_id, res); _MC_ANALOG_TEMPERATURE();    break;
            case AID_TEMPERATURE:   FilterUnsigned(measurement_id, res); _MC_ANALOG_CURRENT();        break;
            default: break;
        }
        MC_Fault_LimitsCheck(prev_id, FilterRead(prev_id));
    }
}

uint16_t MC_Analog_Read(mc_analog_id_t index)
{
    uint16_t retVal;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        retVal = FilterRead(index);
    }
    return retVal;
}


// Temporary APIs - These will be removed in the future

void ADC0_Initialize(void)
{
    // PRESC System clock divided by 2;
    ADC0.CTRLB = 0x0;

    // CHOPPING ENABLE; FREERUN disabled; LEFTADJ disabled; SAMPNUM 16 samples accumulated;
    ADC0.CTRLF = 0x44;

    // REFSEL VDD;
    ADC0.CTRLC = 0x0;

    // WINCM No Window Comparison; WINSRC RESULT;
    ADC0.CTRLD = 0x0;

    // SAMPDUR 11;
    ADC0.CTRLE = 0xB;

    // GAIN 1x gain; PGABIASSEL 100% BIAS current.; PGAEN disabled;
    ADC0.PGACTRL = 0x0;

    // DBGRUN disabled;
    ADC0.DBGCTRL = 0x0;

    // DIFF disabled; MODE BURST; START Stop an ongoing conversion;
    ADC0.COMMAND = 0x40;

    // RESOVR disabled; RESRDY disabled; SAMPOVR disabled; SAMPRDY disabled; TRIGOVR disabled; WCMP disabled;
    ADC0.INTCTRL = 0x0;

    // MUXPOS Ground; VIA Inputs connected directly to ADC;
    ADC0.MUXPOS = 0x30;

    // MUXNEG Ground; VIA Inputs connected directly to ADC;
    ADC0.MUXNEG = 0x30;

    // Window Comparator High Threshold
    ADC0.WINHT = 0x0;

    // Window Comparator Low Threshold
    ADC0.WINLT = 0x0;

    // ENABLE enabled; LOWLAT disabled; RUNSTDBY disabled;
    ADC0.CTRLA = 0x1;
}

void ADC0_ChannelSelect(adc_channel_t const channel)
{
    ADC0.MUXPOS = channel;
}

void ADC0_DiffChannelSelect(adc_pos_channel_t const posChannel, adc_neg_channel_t const negChannel)
{
    ADC0.MUXPOS = posChannel;
    ADC0.MUXNEG = negChannel;
}

void ADC0_ConversionStart(void)
{
    ADC0.COMMAND &= ~ADC_DIFF_bm;
    ADC0.COMMAND |= ADC_START_IMMEDIATE_gc;
}

void ADC0_DiffConversionStart(void)
{
    ADC0.COMMAND |= ADC_START_IMMEDIATE_gc | ADC_DIFF_bm;
}

bool ADC0_IsConversionDone(void)
{
    return (ADC0.INTFLAGS & ADC_RESRDY_bm);
}

adc_result_t ADC0_ConversionResultGet(void)
{
    return ( (adc_result_t) ADC0.RESULT );
}

adc_diff_result_t ADC0_DiffConversionResultGet(void)
{
    return ( (adc_diff_result_t) ADC0.RESULT );
}
