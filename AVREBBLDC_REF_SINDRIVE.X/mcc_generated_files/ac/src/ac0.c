/**
 * AC0 Generated Driver File
 * 
 * @file ac0.c
 * 
 * @ingroup  ac0
 * 
 * @brief This file contains the API implementation for the AC0 driver.
 *
 * @version AC0 Driver Version 1.1.0
*/
/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <util/atomic.h>
#include "../ac0.h"

static ac_cb_t AC0_cb = NULL;

int8_t AC0_Initialize(void)
{
    //WINSEL Window function disabled; 
    AC0.CTRLB = (uint8_t)0x0U;

    //DACREF 0; 
    AC0.DACREF = (uint8_t)0x0U;
    
    //CMP disabled; INTMODE Positive and negative inputs crosses; 
    AC0.INTCTRL = (uint8_t)0x0U;
    
    //INITVAL LOW; INVERT disabled; MUXNEG Negative Pin 0; MUXPOS Positive Pin 0;   
    AC0.MUXCTRL = (uint8_t)0x0U;

    
    //ENABLE enabled; HYSMODE No hysteresis; OUTEN disabled; POWER Power profile 0, Fastest response time, highest consumption; RUNSTDBY disabled; 
    AC0.CTRLA = (uint8_t)0x1U;

    return 0;
}

ISR(AC0_AC_vect)
{
    /* The interrupt flag has to be cleared manually */
    AC0.STATUS = (uint8_t)AC_CMPIF_bm;
    if (AC0_cb != NULL)
    {
        AC0_cb();
    }
}

void AC0_MuxSet(uint8_t mode)
{
    uint8_t temp;
    temp = AC0.MUXCTRL;
    temp &= (uint8_t)(~((uint8_t)AC_MUXPOS_gm | (uint8_t)AC_MUXNEG_gm));
    temp |= mode;
    AC0.MUXCTRL = temp;
}

void AC0_Invert(bool config)
{     
    if (true == config)
    {
        AC0.MUXCTRL |=  (uint8_t)AC_INVERT_bm;
    }
    else
    {
        AC0.MUXCTRL &= (uint8_t)(~AC_INVERT_bm);
    }
}

bool AC0_Read(void)
{
    uint8_t nullValue = 0U;
    return ((AC0.STATUS & (uint8_t)AC_CMPSTATE_bm) != nullValue);
}

void AC0_CallbackRegister(ac_cb_t comparator_cb)
{
    AC0_cb = comparator_cb;
}

void AC0_DACRefValueSet (uint8_t value)
{ 
    AC0.DACREF = value;
}
