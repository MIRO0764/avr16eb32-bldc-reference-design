/**
 *  @file mc_limits.h
 *
 *  @ingroup mclib
 *
 *  @brief This Header File contains the events limits.
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


#ifndef MC_LIMITS_H
#define	MC_LIMITS_H


#define MC_OVER_VOLTAGE_EVENT_LEVEL          ( 50.000f ) // Volts
#define MC_OVER_VOLTAGE_RESTORE_LEVEL        ( 49.000f ) // Volts
#define MC_UNDER_VOLTAGE_EVENT_LEVEL         ( 6.000f ) // Volts
#define MC_UNDER_VOLTAGE_RESTORE_LEVEL       ( 7.000f ) // Volts
#define MC_OVER_TEMPERATURE_EVENT_LEVEL      ( 60.000f ) // Degrees Celsius
#define MC_OVER_TEMPERATURE_RESTORE_LEVEL    ( 50.000f ) // Degrees Celsius
#define MC_OVER_CURRENT_PEAK_EVENT_LEVEL     ( 44.000f ) // Amperes
#define MC_OVER_CURRENT_AVG_EVENT_LEVEL      ( 10.000f ) // Amperes


#endif	/* MC_LIMITS_H */
