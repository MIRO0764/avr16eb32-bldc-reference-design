/**
 *  @defgroup mclib_example AVR® MCU Motor Control Library Example
 *
 *  @brief The AVR® MCU Motor Control Library Example demonstrates the usage of the
 *         library functions and features. The example application initializes the
 *         library and offers the user the ability to run the motor clockwise or
 *         counterclockwise.
 **/

/**
 *  @file mc_example.h
 *
 *  @ingroup mclib_example
 *
 *  @brief This header file contains the declarations of the functions that are
 *         used to initialize and run the example application.
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


#ifndef MC_EXAMPLE_H
#define MC_EXAMPLE_H


/**
 * @ingroup mclib_example
 * @brief Initializes the example application.
 * @note Call this function before the main loop.
 * @param None.
 * @return None.
 */
void MC_Example_Initialize(void);

/**
 * @ingroup mclib_example
 * @brief Runs the example application.
 * @note Call this function inside the main loop.
 * @param None.
 * @return None.
 */
void MC_Example_Run(void);


#endif /* MC_EXAMPLE_H */
