/**
 *  @file mc_button_led.c
 *
 *  @ingroup mclib_example
 *
 *  @brief This Source File contains the implementation of the functions that
 *         are used to control the LED and read the button.
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


#include "../mc_button_led.h"

#include "../../../system/pins.h"

#include <stdbool.h>


#define LED_BLINK_NUMBER(X)    ( (X) * LED_BLINK_DURATION * 2 )


button_state_t ButtonGet(void)
{
    static uint16_t counter = 0;
    static bool prev_state = 0;

    button_state_t retVal = BUTTON_IDLE;
    bool actual_state = !PIN_BUTTON_GetValue();

    if ( (actual_state == false) && (prev_state == true) )
    {
        if (counter < BUTTON_TIME_LONG)
        {
            retVal = BUTTON_SHORT_PRESS;
        }

        counter = 0;
    }

    if (actual_state)
    {
        ++counter;

        if (counter == BUTTON_TIME_LONG)
        {
            retVal = BUTTON_LONG_PRESS;
        }
    }

    prev_state = actual_state;

    return retVal;
}

void LedControl(led_ctrl_t state)
{
    static uint8_t toggle_counter = 0;
    static uint16_t blinks_counter = LED_BLINK_NUMBER(LED_FAULT_BLINKS);
    static bool fault_flag = false;

    if (state == LED_BLINK) fault_flag = true;

    if (fault_flag == true)
    {
        if (blinks_counter > 0)
        {
            if (toggle_counter == LED_BLINK_DURATION - 1)
            {
                PIN_LED_Toggle();
                toggle_counter = 0;
            }
            else
            {
                toggle_counter++;
            }

            blinks_counter--;
        }
        else
        {
            fault_flag = false;
            blinks_counter = LED_BLINK_NUMBER(LED_FAULT_BLINKS);
            toggle_counter = 0;
            PIN_LED_Toggle();
        }
    }
    else
    {
        if (state == LED_ON)     PIN_LED_SetLow();
        if (state == LED_OFF)    PIN_LED_SetHigh();
    }
}
