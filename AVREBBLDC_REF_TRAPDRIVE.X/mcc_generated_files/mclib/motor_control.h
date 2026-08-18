/**
 *  @defgroup mclib AVR® MCU Motor Control Library
 *
 *  @brief The AVR® MCU Motor Control Library is a library for the AVR® EB family
 *         of devices with support for spinning a BLDC/PMSM motor using either a
 *         sensored or sensorless setup. The library interface offers motor-specific
 *         and power board customizations, MCU settings, and pinout functionality.
 *         The drive algorithm takes advantage of the MCU peripherals that ensure
 *         the CPU doesn't have a large overhead and optimizes memory usage and
 *         resource consumption. User layer APIs are generated for a simple
 *         run-time configuration and control.
 **/

/**
 *  @file motor_control.h
 *
 *  @ingroup mclib
 *
 *  @brief This header file contains the declarations of the functions public to
 *         the user.
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


#ifndef MC_CONTROL_H
#define MC_CONTROL_H


#include "mc_config.h"
#include "mc_public_types.h"


#if PWM_FREQUENCY > 20000UL

#define HIGH_FREQUENCY                      true
#define MC_F_SAMPLING                       ( PWM_FREQUENCY / 2.0 )

#else

#define HIGH_FREQUENCY                      false
#define MC_F_SAMPLING                       PWM_FREQUENCY

#endif /* PWM_FREQUENCY */

/* These macros must not be called with variable arguments within interrupt context */
#define MC_RPM_TO_MCSPEED(RPM)               (mc_speed_t) (((float) (RPM) * 65536.0 * (float) (MC_MOTOR_PAIR_POLES)) / ((float)(MC_F_SAMPLING) * 60.0) + 0.5)
#define MC_MCSPEED_TO_RPM(MCSPEED)           (float) (MC_F_SAMPLING) * (float) (MCSPEED) * 60.0 / ( 65536.0 * (float) (MC_MOTOR_PAIR_POLES) )

#define MC_HZ_TO_MCSPEED(HZ)                 (mc_speed_t) (((float)(HZ) * 65536.0) / ((float)(MC_F_SAMPLING)) + 0.5)
#define MC_MCSPEED_TO_HZ(MCSPEED)            (float) (MC_F_SAMPLING) * (float)(MCSPEED) / 65536.0

#define MC_DELAY_MS    MC_DelayMs


/**
 * @ingroup mclib
 * @brief Initializes the AVR® MCU Motor Control Library.
 * @note Call this function from normal context, not from interrupt context.
 *       This function must be called before any other function in the library.
 * @param None.
 * @return None.
 */
void MC_Initialize(void);


/**
 * @ingroup mclib
 * @brief Performs a delay using a timer in the background.
 * @note Call this function from normal context, not from interrupt context.
 *       It is recommended to use the MC_DELAY_MS macro instead of a direct call.
 *       Use this in the application to create delays instead of long loops or
 *       other system delays.
 * @param[in] delayMs The number of milliseconds of delay
 * @return None.
 */
void MC_DelayMs(uint32_t delayMs);


/**
 * @ingroup mclib
 * @brief Sets the reference point. When the speed regulator is enabled, it sets
 *        the reference for the speed control loop. When the speed regulator
 *        is disabled, it sets the drive amplitude, and the speed will vary depending
 *        on the power supply voltage and mechanical load.
 * @note Call this function from normal context, not from interrupt context.
 * @param[in] reference The reference value to be set
 * @return None.
 */
void MC_ReferenceSet(uint16_t reference);


/**
 * @ingroup mclib
 * @brief Returns the potentiometer value in percentage.
 * @note Call this function from normal context, not from interrupt context.
 * @param None.
 * @return Value of the potentiometer in percentage
 */
uint8_t MC_PotentiometerRead(void);


/**
 * @ingroup mclib
 * @brief Returns the potentiometer value in uint16_t format.
 * @note Call this function from normal context, not from interrupt context.
 * @param None.
 * @return Value of the potentiometer
 */
uint16_t MC_FastPotentiometerRead(void);


/**
 * @ingroup mclib
 * @brief Returns the bus voltage.
 * @note Call this function from normal context, not from interrupt context.
 * @param None.
 * @return Value of the bus voltage
 */
uint16_t MC_VoltageBusRead(void);


/**
 * @ingroup mclib
 * @brief Returns the temperature of the MOSFETs in degrees Celsius.
 * @note Call this function from normal context, not from interrupt context.
 * @param None.
 * @return Value of the temperature
 */
uint8_t MC_TemperatureRead(void);


/**
 * @ingroup mclib
 * @brief Returns the mean current value in milliamperes (mA).
 * @note Call this function from normal context, not from interrupt context.
 * @param None.
 * @return Value of the mean current
 */
int16_t MC_CurrentRead(void);


/**
 * @ingroup mclib
 * @brief Returns the motor's the rotational speed.
 * @note Call this function from normal context, not from interrupt context.
 * @param None.
 * @return The data type is mc_speed_t, which can be converted to RPM using the macro MC_MCSPEED_TO_RPM.
 */
mc_speed_t MC_SpeedGet(void);


/**
 * @ingroup mclib
 * @brief Registers a user's function as a callback.
 *        The user's function must have the prototype: @code{.c}void function(void) @endcode
 * @note Call this function from normal context, not from interrupt context.
 * @param[in] pHandler The user's function to be called
 * @return None.
 */
void MC_PeriodicHandlerRegister(mc_status_handler_t pHandler);


/**
 * @ingroup mclib
 * @brief Returns the status of the motor.
 * @note Call this function from normal context, not from interrupt context.
 * @param None.
 * @return Motor status. The data type mc_status_t is described in @ref mc_public_types.h.
 */
mc_status_t MC_StatusGet(void);


/**
 * @ingroup mclib
 * @brief Starts or stops the motor when a start or stop event is received.
 * @note Call this function from normal context, not from interrupt context.
 * @param[in] direction Direction of the motor rotation
 * @return None.
 */
void MC_StartStop(mc_direction_t direction);


#endif  /* MC_CONTROL_H */
