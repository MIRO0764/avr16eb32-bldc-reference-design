/**
 *  @file mc_public_types.h
 *
 *  @ingroup mclib
 *
 *  @brief This header file contains the declarations of the functions related
 *         to ramp generation.
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


#ifndef MC_PUBLIC_TYPES_H
#define	MC_PUBLIC_TYPES_H


#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


/**
 * @ingroup mclib
 * @brief Describes the motor direction.
 */
typedef enum
{
    MC_DIR_CW,  /**< Clockwise direction */
    MC_DIR_CCW, /**< Counterclockwise direction */
}
mc_direction_t;

/**
 * @ingroup mclib
 * @brief Describes the fault events.
 */
typedef enum
{
    MC_FAULT_STALL_MASK        = (1 << 0), /**< Stall fault */
    MC_FAULT_OVERCURRENT_MASK  = (1 << 1), /**< Overcurrent fault */
    MC_FAULT_UNDERVOLTAGE_MASK = (1 << 2), /**< Undervoltage fault */
    MC_FAULT_OVERHEAT_MASK     = (1 << 3), /**< Overtemperature fault */
    MC_FAULT_OVERVOLTAGE_MASK  = (1 << 4), /**< Overvoltage fault */
    MC_FAULT_HALL_MASK         = (1 << 5), /**< Hall effect sensor fault */
}
mc_fault_flags_t;

/**
 * @ingroup mclib
 * @brief Describes the motor status.
 */
typedef union
{
    struct
    {
        uint8_t state : 7;      /**< Motor state */
        uint8_t direction : 1;  /**< Motor direction */
        mc_fault_flags_t flags; /**< Motor fault flags */
    };

    uint16_t word; /**< Motor status as a 16-bit word. */
}
mc_status_t;


/**
 * @ingroup mclib
 * @brief Describes the motor states.
 */
typedef enum
{
    IDLE,    /**< Motor is idle */
    RUNNING, /**< Motor is running */
    FAULT,   /**< Motor is in a fault state */
}
mc_states_t;

/**
 * @ingroup mclib
 * @brief Pointer to a function that receives motor status information.
 */
typedef void (* mc_status_handler_t)(mc_status_t);

/**
 * @ingroup mclib
 * @brief Speed as angle units/sample, stored as an unsigned 16-bit integer.
 * @note Use along with the MC_RPM_TO_MCSPEED and MC_MCSPEED_TO_RPM macros defined in @ref motor_control.h.
 */
typedef uint16_t mc_speed_t;

/**
 * @ingroup mclib
 * @brief Describes the motor position.
 */
typedef uint16_t mc_position_t;

/**
 * @ingroup mclib
 * @brief Describes the Hall effect sensor error codes.
 */
typedef enum
{
    HALL_NO_ERROR            = 0x00, /**< No error reported */
    HALL_ERROR_TOO_EARLY     = 0x01, /**< Hall sensor signal detected too early */
    HALL_ERROR_TOO_LATE      = 0x02, /**< Hall sensor signal detected too late */
    HALL_ERROR_DISCONNECTED  = 0x04, /**< Hall sensors disconnected */
    HALL_ERROR_WRONG_PATTERN = 0x08, /**< Wrong Hall sensor pattern */
    HALL_ERROR_MOTOR_STOPPED = 0x10, /**< Motor stopped */
}
mc_hall_error_t;


#endif	/* MC_PUBLIC_TYPES_H */
