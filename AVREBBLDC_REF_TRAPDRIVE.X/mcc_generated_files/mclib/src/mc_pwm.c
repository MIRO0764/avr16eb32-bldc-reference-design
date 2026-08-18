/**
 *  @file mc_pwm.c
 *
 *  @ingroup mclib
 *
 *  @brief This Source File contains the implementation of the functions that
 *         are used to control the PWM signals.
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


#include <avr/interrupt.h>
#include <util/atomic.h>

#include "../../system/clock.h"
#include "../mc_pwm.h"
#include "../mc_config.h"
#include "../../timer/tce0.h"
#include "../../timer/wex0.h"


static const uint8_t wex_settings[8] =
{
    0,
    WEX_PGMOVR0_bm | WEX_PGMOVR1_bm,
    WEX_PGMOVR2_bm | WEX_PGMOVR3_bm,
    WEX_PGMOVR0_bm | WEX_PGMOVR1_bm | WEX_PGMOVR2_bm | WEX_PGMOVR3_bm,
    WEX_PGMOVR4_bm | WEX_PGMOVR5_bm,
    WEX_PGMOVR0_bm | WEX_PGMOVR1_bm | WEX_PGMOVR4_bm | WEX_PGMOVR5_bm,
    WEX_PGMOVR2_bm | WEX_PGMOVR3_bm | WEX_PGMOVR4_bm | WEX_PGMOVR5_bm,
    WEX_PGMOVR0_bm | WEX_PGMOVR1_bm | WEX_PGMOVR2_bm | WEX_PGMOVR3_bm | WEX_PGMOVR4_bm | WEX_PGMOVR5_bm,
};

#define _MC_PWM_PERIOD()              TCE0_PER_US_TO_TICKS(PWM_PERIOD, F_CPU, 1)
#define _MC_PWM_PERIOD_SET()          do { TCE0_PeriodSet(_MC_PWM_PERIOD()); TCE0_Compare3Set((uint16_t)((1.0 - MC_BEMF_SAMPLING_POINT) * TCE0_PER_US_TO_TICKS(PWM_PERIOD, F_CPU, 1))); } while (0)
#define _MC_PWM_DCY_SET(X, Y, Z)      do { TCE0_PWM_BufferedDutyCycle0Set(( X )); TCE0_PWM_BufferedDutyCycle1Set(( Y )); TCE0_PWM_BufferedDutyCycle2Set(( Z )); } while (0)
#define _MC_PWM_TRAP_DCY(X)           do { stepped_data = ( X ); Map(MC_FP_TO_FIPu16(1.0), MC_FP_TO_FIPu16(0.0)); _MC_PWM_DCY_SET(scaled_dcy0, scaled_dcy1, scaled_dcy2); WEX0_PatternGenerationOverrideBufferSet(wex_settings[( X ) & (MC_PHASE_FLOAT_A | MC_PHASE_FLOAT_B | MC_PHASE_FLOAT_C)]); } while (0)
#define _MC_PWM_SINE_DCY(X, Y, Z)     _MC_PWM_DCY_SET(( X ), ( Y ), ( Z ))
#define _MC_PWM_SENSE_REGISTER(X)     TCE0_Compare3CallbackRegister(( X ))
#define _MC_PWM_START()               TCE0_Start()
#define _MC_PWM_STOP()                TCE0_Stop()
#define _MC_PWM_AMPLITUDE_SET(X)      do { ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { frac_amplitude = ( X ); } TCE0_AmplitudeSet(X); } while (0)
#define _MC_PWM_OUTPUT_DISABLE()      do { TCE0_OutputsEnable(0x00); WEX0_OutputOverrideEnable(0x00); } while (0)
#define _MC_PWM_OUTPUT_ENABLE()       do { TCE0_OutputsEnable(TCE_CMP0_bm | TCE_CMP1_bm | TCE_CMP2_bm); WEX0_OutputOverrideEnable(WEX_PGMOVR0_bm | WEX_PGMOVR1_bm | WEX_PGMOVR2_bm | WEX_PGMOVR3_bm | WEX_PGMOVR4_bm | WEX_PGMOVR5_bm); } while (0)
#define _MC_PWM_FAULT_CLEAR()         do { WEX0_SoftwareCommand(WEX_CMD_FAULTCLR_gc); WEX0_SoftwareCommand(WEX_CMD_UPDATE_gc); } while (0)


static mc_amplitude_t frac_amplitude;
static mc_int_dcy_t   scaled_dcy0, scaled_dcy1, scaled_dcy2;
static mc_stepped_t   stepped_data;


typedef union
{
    struct __attribute__((packed))
    {
         __attribute__((packed)) uint16_t  dummy0:14;
         __attribute__((packed)) uint16_t  RSH14:16;
    };

    struct __attribute__((packed))
    {
         __attribute__((packed)) uint16_t  dummy1:16;
         __attribute__((packed)) uint16_t  RSH16:16;
    };

    uint32_t  W32;
}
shifter_t;


#if (MC_SCALE_MODE == MC_SCALE_CENTER) && (MC_DRIVE_MODE == MC_STEPPED_MODE)
static inline void Map(mc_int_dcy_t top, mc_int_dcy_t bot)
{
    if(stepped_data & MC_PHASE_HIGH_A)     scaled_dcy0 = top;
    else if(stepped_data & MC_PHASE_LOW_A) scaled_dcy0 = bot;
    else                                   scaled_dcy0 = 0;
    if(stepped_data & MC_PHASE_HIGH_B)     scaled_dcy1 = top;
    else if(stepped_data & MC_PHASE_LOW_B) scaled_dcy1 = bot;
    else                                   scaled_dcy1 = 0;
    if(stepped_data & MC_PHASE_HIGH_C)     scaled_dcy2 = top;
    else if(stepped_data & MC_PHASE_LOW_C) scaled_dcy2 = bot;
    else                                   scaled_dcy2 = 0;
}

static inline void Scale(void)
{
    mc_int_dcy_t amp, bias, top, bot;
    shifter_t temp;
    bias = (mc_int_dcy_t)MC_SCALE_FIPu16(0.5, _MC_PWM_PERIOD());

    temp.W32 = (uint32_t)frac_amplitude * (uint32_t)_MC_PWM_PERIOD();
    amp = (mc_int_dcy_t)temp.RSH16;

    top = bias + amp;
    bot = bias - amp;
    Map(top, bot);
}
#endif  /* (MC_SCALE_MODE == MC_SCALE_CENTER) && (MC_DRIVE_MODE == MC_STEPPED_MODE) */


#if (MC_SCALE_MODE == MC_SCALE_BOTTOM) && (MC_DRIVE_MODE == MC_STEPPED_MODE)
static inline void Scale(void)
{
    mc_int_dcy_t top;
    shifter_t temp;
    temp.W32 = (uint32_t)frac_amplitude * (uint32_t)(2 * _MC_PWM_PERIOD());
    top = (mc_int_dcy_t)temp.RSH16;
    if(stepped_data & MC_PHASE_HIGH_A)     scaled_dcy0 = top;
    else                                   scaled_dcy0 = 0;
    if(stepped_data & MC_PHASE_HIGH_B)     scaled_dcy1 = top;
    else                                   scaled_dcy1 = 0;
    if(stepped_data & MC_PHASE_HIGH_C)     scaled_dcy2 = top;
    else                                   scaled_dcy2 = 0;
}

static inline void Map(mc_int_dcy_t top, mc_int_dcy_t bot)
{
    if(stepped_data & MC_PHASE_HIGH_A)     scaled_dcy0 = top;
    else if(stepped_data & MC_PHASE_LOW_A) scaled_dcy0 = bot;
    else                                   scaled_dcy0 = 0;
    if(stepped_data & MC_PHASE_HIGH_B)     scaled_dcy1 = top;
    else if(stepped_data & MC_PHASE_LOW_B) scaled_dcy1 = bot;
    else                                   scaled_dcy1 = 0;
    if(stepped_data & MC_PHASE_HIGH_C)     scaled_dcy2 = top;
    else if(stepped_data & MC_PHASE_LOW_C) scaled_dcy2 = bot;
    else                                   scaled_dcy2 = 0;
}
#endif  /* (MC_SCALE_MODE == MC_SCALE_BOTTOM) && (MC_DRIVE_MODE == MC_STEPPED_MODE)  */


#if (MC_SCALE_MODE == MC_SCALE_CENTER) && (MC_DRIVE_MODE == MC_CONTINUOUS_MODE)
static inline void Scale(void)
{
    mc_int_dcy_t bias, amp1, amp2;
    shifter_t temp;

    temp.W32 = (uint32_t)frac_amplitude * (uint32_t)_MC_PWM_PERIOD();
    amp1 = (mc_int_dcy_t)temp.RSH14;
    amp2 = (mc_int_dcy_t)temp.RSH16;
    bias = (mc_int_dcy_t)MC_SCALE_FIPu16(0.5, _MC_PWM_PERIOD()) - amp2;

    temp.W32 = (uint32_t)amp1 * (uint32_t)frac_dcy0;
    scaled_dcy0 = (mc_int_dcy_t)temp.RSH16 + bias;
    temp.W32 = (uint32_t)amp1 * (uint32_t)frac_dcy1;
    scaled_dcy1 = (mc_int_dcy_t)temp.RSH16 + bias;
    temp.W32 = (uint32_t)amp1 * (uint32_t)frac_dcy2;
    scaled_dcy2 = (mc_int_dcy_t)temp.RSH16 + bias;
}

static inline void Map(mc_int_dcy_t a, mc_int_dcy_t b) {(void)a; (void)b;}
#endif /* (MC_SCALE_MODE == MC_SCALE_CENTER) && (MC_DRIVE_MODE == MC_CONTINUOUS_MODE) */

#if (MC_SCALE_MODE == MC_SCALE_BOTTOM) && (MC_DRIVE_MODE == MC_CONTINUOUS_MODE)
static inline void Map(mc_int_dcy_t a, mc_int_dcy_t b) {(void)a; (void)b;}
#endif /* (MC_SCALE_MODE == MC_SCALE_BOTTOM) && (MC_DRIVE_MODE == MC_CONTINUOUS_MODE) */


/* Fault Action - Recovery*/
void MC_PWM_ForceStop(void)
{
    _MC_PWM_OUTPUT_DISABLE();
    _MC_PWM_SINE_DCY(0, 0, 0);
}

void MC_PWM_FaultRecovery(void)
{
    _MC_PWM_FAULT_CLEAR();
}

void MC_PWM_ForceStart(void)
{
    _MC_PWM_SINE_DCY(0, 0, 0);
    _MC_PWM_OUTPUT_ENABLE();
}

void MC_PWM_Initialize(void)
{
    _MC_PWM_START();
    sei();
}

void MC_PWM_Start(void)
{
    _MC_PWM_START();
}

void MC_PWM_Stop(void)
{
    _MC_PWM_STOP();
}

void MC_PWM_HandlerRegister(mc_handler_t cb)
{
    _MC_PWM_SENSE_REGISTER(cb);
}

void MC_PWM_ContinuousScale(mc_fip_dcy_t fch0, mc_fip_dcy_t fch1, mc_fip_dcy_t fch2)
{
    _MC_PWM_SINE_DCY(fch0, fch1, fch2);
}

void MC_PWM_SteppedScale(mc_stepped_t data)
{
    _MC_PWM_TRAP_DCY(data);
}

void MC_PWM_AmplitudeSet(mc_amplitude_t amplitude)
{
    _MC_PWM_AMPLITUDE_SET(amplitude);
}

mc_amplitude_t MC_PWM_AmplitudeGet(void)
{
    mc_amplitude_t retval;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        retval = frac_amplitude;
    }
    return retval;
}
