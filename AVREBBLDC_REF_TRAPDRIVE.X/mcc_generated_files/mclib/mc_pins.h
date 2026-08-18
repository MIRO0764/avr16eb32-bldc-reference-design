/**
 *  @file mc_pins.h
 *
 *  @ingroup mclib
 *
 *  @brief This Header File contains the defifinitions of the used pins.
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


#ifndef MC_PINS_H
#define MC_PINS_H


#include <avr/io.h>


/* BEMF Ports and Pins */
#define PHASE_A_AC_PIN    AC_MUXPOS_AINP0_gc
#define PHASE_B_AC_PIN    AC_MUXPOS_AINP0_gc
#define PHASE_C_AC_PIN    AC_MUXPOS_AINP0_gc
#define PHASE_N_AC_PIN    AC_MUXNEG_AINN0_gc


/* Analog Parameters Ports and Pins */
#define VBUS_ADC_PIN       ADC_MUXPOS_AIN20_gc
#define POT_ADC_PIN        ADC_MUXPOS_AIN1_gc
#define TEMP_ADC_PIN       ADC_MUXPOS_AIN28_gc
#define CRT_SNS_ADC_PIN    ADC_MUXPOS_AIN3_gc
#define CRT_REF_ADC_PIN    ADC_MUXNEG_GND_gc


#endif /* MC_PINS_H */
