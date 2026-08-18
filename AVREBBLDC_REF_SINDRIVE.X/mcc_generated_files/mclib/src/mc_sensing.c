/**
 *  @file mc_sensing.c
 *
 *  @ingroup mclib
 *
 *  @brief This Source File contains the implementation of the functions used
 *         for sensing the rotor position.
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


#include "../../system/pins.h"

#include <string.h>

#include "../mc_pins.h"
#include "../mc_config.h"
#include "../mc_sensing.h"
#include "../mc_comparator.h"
#include "../mc_sm.h"


static mc_sense_t sensing_state;
static uint8_t hall_table[8];

void MC_Sensing_Initialize(void)
{
    sensing_state.byte = 0x00;
    memset((void *) hall_table, 0, sizeof(hall_table));
}

mc_sense_t MC_Sensing_Get(void)
{
    return sensing_state;
}


#define HALL_READ(VALUE)    ((VALUE == 0) ? true : false)

mc_sense_t MC_Hall_IntGet(void)
{
    uint8_t event = 0;

    if (HALL_READ(PIN_HALL_A_GetValue())) event |= 1;
    if (HALL_READ(PIN_HALL_B_GetValue())) event |= 2;
    if (HALL_READ(PIN_HALL_C_GetValue())) event |= 4;

    mc_sense_t retval;
    retval.byte = 0;

    uint8_t index = hall_table[event & 7];

    if (index != 0)
    {
        index++;
        retval.id = index;
    }

    retval.state = event;
    sensing_state = retval;

    return retval;
}

uint8_t * MC_Sensing_HallTable_Get(void)
{
    return hall_table;
}
