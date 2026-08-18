/**
 *  @file mc_comparator.c
 *
 *  @ingroup mclib
 *
 *  @brief This Source File contains the implementation of the functions for the
 *         comparator related operations.
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


#include "../../system/system.h"

#include <util/delay.h>
#include <avr/io.h>

#include "../mc_comparator.h"
#include "../mc_pins.h"
#include "../../ac/ac0.h"
#include "../../ac/ac1.h"
#include "../../timer/wex0.h"


#define _MC_COMP_MUX_S0                 ( PHASE_A_AC_PIN | PHASE_N_AC_PIN )
#define _MC_COMP_MUX_S1                 ( PHASE_B_AC_PIN | PHASE_N_AC_PIN )
#define _MC_COMP_MUX_S2                 ( PHASE_C_AC_PIN | PHASE_N_AC_PIN )


#define _MC_COMP_FAULT_INIT()           do { VREF_AC_ReferenceSelect(VREF_REFSEL_VDD_gc); AC1_DACRefValueSet(0xFF); _delay_us(10); EVSYS_Initialize(); } while(0)
#define _MC_COMP_MUX_SET                AC0_MuxSet
#define _MC_COMP_INPUT_GET              AC0_Read
#define _MC_COMP_FAULT_GET              AC1_Read
#define _MC_COMP_HANDLER_REGISTER(X)
#define _MC_COMP_REFERENCE_SET(X)       AC1_DACRefValueSet(X)
#define _MC_COMP_INT_ENABLE             WEX0_FaultEnable
#define _MC_COMP_INT_DISABLE            WEX0_FaultDisable


void MC_Comparator_FaultInitialize(void)
{
    _MC_COMP_FAULT_INIT();
}

void MC_Comparator_MuxSet(uint8_t step)
{
    switch(step)
    {
        case MC_PHASE_FLOAT_A: _MC_COMP_MUX_SET(_MC_COMP_MUX_S0); break;
        case MC_PHASE_FLOAT_B: _MC_COMP_MUX_SET(_MC_COMP_MUX_S1); break;
        case MC_PHASE_FLOAT_C: _MC_COMP_MUX_SET(_MC_COMP_MUX_S2); break;
        default: break;
    }
}

bool MC_Comparator_Get(void)
{
    return _MC_COMP_INPUT_GET();
}

void MC_Comparator_HandlerRegister(mc_comparator_handler_t cb)
{
    _MC_COMP_HANDLER_REGISTER(cb);
}

void MC_Comparator_Reference(uint8_t dacRef)
{
    _MC_COMP_REFERENCE_SET(dacRef);
}

bool MC_Comparator_Fault_Get(void)
{
    return _MC_COMP_FAULT_GET();
}

void MC_Comparator_Int_Enable(void)
{
    _MC_COMP_INT_ENABLE();
}

void MC_Comparator_Int_Disable(void)
{
    _MC_COMP_INT_DISABLE();
}


// Temporary APIs - These will be removed in the future

void EVSYS_Initialize(void)
{
    EVSYS.CHANNEL1 = EVSYS_CHANNEL_TCE0_OVF_gc;
    EVSYS.USERADC0START = EVSYS_USER_CHANNEL1_gc;

    EVSYS.USEREVSYSEVOUTA = EVSYS_USER_CHANNEL1_gc;
    PORTMUX.EVSYSROUTEA = PORTMUX_EVOUTA_ALT1_gc;

    EVSYS.CHANNEL0 = EVSYS_CHANNEL_AC1_OUT_gc;
    EVSYS.USERWEXA = EVSYS_USER_CHANNEL0_gc;
}

void VREF_AC_ReferenceSelect(VREF_REFSEL_t const reference)
{
    uint8_t value = VREF.ACREF;
    value &= ~VREF_REFSEL_gm;
    value |= reference;
    VREF.ACREF = value;
}
