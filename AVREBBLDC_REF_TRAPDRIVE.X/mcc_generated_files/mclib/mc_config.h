/**
 *  @file mc_config.h
 *
 *  @ingroup mclib
 *
 *  @brief This Header File contains the general configuration parameters for the library.
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


#ifndef MC_CONFIG_H
#define MC_CONFIG_H


#define MC_SENSORED_MODE      ( 0 )
#define MC_SENSORLESS_MODE    ( 1 )

#define MC_STEPPED_MODE       ( 0 )
#define MC_CONTINUOUS_MODE    ( 1 )

#define MC_WAVE_SINE      ( 0 )
#define MC_WAVE_SVM       ( 1 )
#define MC_WAVE_SADDLE    ( 2 )

#define MC_SCALE_CENTER    ( 0 )
#define MC_SCALE_BOTTOM    ( 1 )

#define MC_COMM_OFF       ( 0 )
#define MC_COMM_PRINTF    ( 1 )
#define MC_COMM_DVRT      ( 2 )


/* General Settings */
#define MC_CONTROL_MODE    MC_SENSORLESS_MODE
#define MC_DRIVE_MODE      MC_STEPPED_MODE
#define MC_WAVE_PROFILE    MC_WAVE_SINE
#define MC_SCALE_MODE      MC_SCALE_BOTTOM


/* Motor Specific Settings */
#define MOTOR_PHASE_ADVANCE                ( 20.000f )  // Degrees
#define MC_MOTOR_PAIR_POLES                ( 4 )  // Pole Pairs
#define MC_MOTOR_PHASE_PHASE_RESISTANCE    ( 0.400f )  // Ohms
#define MC_MOTOR_KV                        ( 0.006f )  // V/RPM
#define MC_RAMP_UP_DURATION                ( 500 )  // Milliseconds
#define MC_RAMP_DOWN_DURATION              ( 500 )  // Milliseconds
#define MC_STARTUP_CURRENT                 ( 0.500f )  // Amperes
#define MC_STARTUP_SPEED                   ( 700 )  // RPM


/* PWM Drive Settings */
#define PWM_FREQUENCY    ( 20000 )  // Hertz
#define PWM_PERIOD       ( 50 )  // Microseconds
#define PWM_DTH          ( 100 )  // Nanoseconds
#define PWM_DTL          ( 100 )  // Nanoseconds


/* Board Specific Settings */
#define MC_SHUNT_RESISTANCE       ( 0.003f )  // Ohms
#define MC_CURR_AMPLIFIER_GAIN    ( 16.000f )  // Dimensionless
#define MC_VBUS_DIVIDER           ( 16.000f )  // Dimensionless
#define MC_ADC_REFERENCE          ( 5.000f )  // Volts
#define MC_TEMP_K1                ( 500.000f )  // mV
#define MC_TEMP_K2                ( 10.000f )  // mV/°C


/* Control Functionality Settings */
#define MC_SPEED_REGULATOR_MIN       ( 800.000f )  // RPM
#define MC_SPEED_REGULATOR_MAX       ( 3500.000f )  // RPM
#define MC_SPEED_REGULATOR_EN        ( true )
#define MC_SYNCHRONIZED              ( true )
#define MC_FAULT_ENABLED             ( false )


/* Application Settings */
#define MC_COMM_SUPPORT                 MC_COMM_PRINTF
#define MC_PRINTOUT_REFRESH_INTERVAL    ( 1000UL )  // Milliseconds

#if (MC_COMM_SUPPORT == MC_COMM_PRINTF)

#define MC_DVRT_ENABLED        ( false )
#define MC_PRINTOUT_ENABLED    ( true )

#elif (MC_COMM_SUPPORT == MC_COMM_DVRT)

#define MC_DVRT_ENABLED        ( true )
#define MC_PRINTOUT_ENABLED    ( false )

#else

#define MC_DVRT_ENABLED        ( false )
#define MC_PRINTOUT_ENABLED    ( false )

#endif


#endif /* MC_CONFIG_H */
