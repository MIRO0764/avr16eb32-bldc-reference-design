/**
 *  @file mc_control_analog.h
 *
 *  @ingroup mclib
 *
 *  @brief This Header File contains the declarations of the functions that are
 *         used to read the analog signals.
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


#ifndef MC_CONTROL_ANALOG_H
#define MC_CONTROL_ANALOG_H


#include "mc_internal_types.h"


void MC_Analog_Initialize(void);
void MC_Analog_Run(void);
uint16_t MC_Analog_Read(mc_analog_id_t);


// Temporary APIs - These will be removed in the future

typedef uint32_t adc_result_t;
typedef int32_t adc_diff_result_t;
typedef ADC_MUXPOS_t adc_channel_t;
typedef ADC_MUXPOS_t adc_pos_channel_t;
typedef ADC_MUXNEG_t adc_neg_channel_t;

void ADC0_Initialize(void);
void ADC0_ChannelSelect(adc_channel_t const channel);
void ADC0_DiffChannelSelect(adc_pos_channel_t const posChannel, adc_neg_channel_t const negChannel);
void ADC0_ConversionStart(void);
void ADC0_DiffConversionStart(void);
bool ADC0_IsConversionDone(void);
adc_result_t ADC0_ConversionResultGet(void);
adc_diff_result_t ADC0_DiffConversionResultGet(void);


#endif  /* MC_CONTROL_ANALOG_H */
