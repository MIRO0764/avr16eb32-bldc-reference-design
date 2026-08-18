/**
 *  @file mc_example.c
 *
 *  @ingroup mclib_example
 *
 *  @brief This Source File contains the implementation of the functions that
 *         are used to initialize and run the example application, along with
 *         their internal logic.
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


#include "../../../system/system.h"
#include <util/delay.h>

#include "../mc_example.h"
#include "../mc_button_led.h"

#include "../../../system/system.h"
#include "../../motor_control.h"
#include "../../mc_config.h"


#if MC_PRINTOUT_ENABLED == true
#include <stdio.h>
#define PRINT_OUT(...)    printf("\n\r"__VA_ARGS__)
#else
#define PRINT_OUT(...)
#endif /* MC_PRINTOUT_ENABLED == true */


uint16_t    volatile  my_speed;
uint16_t    volatile  my_pot;

static led_ctrl_t     led_ctrl;
static button_state_t button_state;

static mc_status_t    prev_motor_state;
static mc_direction_t direction;


static void PrintConfig(void)
{
    PRINT_OUT("Drive, sensing:        %s, %s", (MC_DRIVE_MODE==MC_STEPPED_MODE)? "trapezoidal" : "sinusoidal", (MC_CONTROL_MODE==MC_SENSORLESS_MODE)? "sensorless" : "sensored");
    PRINT_OUT("Motor pole-pairs no:   %u", MC_MOTOR_PAIR_POLES);
    PRINT_OUT("Motor phase-phase res: %u mOhm", (int)(1000.0 * MC_MOTOR_PHASE_PHASE_RESISTANCE));
    PRINT_OUT("Motor phase advance:   %u deg", (int)MOTOR_PHASE_ADVANCE);
    PRINT_OUT("Motor KV:              %u mV/rpm", (int)(1000.0 * MC_MOTOR_KV));
    PRINT_OUT("Start-up speed:        %u rpm", MC_STARTUP_SPEED);
    PRINT_OUT("Start-up current:      %u mA", (int)(1000.0 * MC_STARTUP_CURRENT));
    PRINT_OUT("Ramp-up time:          %u ms", MC_RAMP_UP_DURATION);
    PRINT_OUT("Ramp-down time:        %u ms", MC_RAMP_DOWN_DURATION);
    PRINT_OUT("PWM Frequency:         %u Hz", PWM_FREQUENCY);
    PRINT_OUT("Speed closed loop:     %s", (MC_SPEED_REGULATOR_EN==true)? "enabled" : "disabled");
    PRINT_OUT("Forced mode:           %s", (MC_SYNCHRONIZED==false)? "enabled" : "disabled");
    PRINT_OUT("Fault detection:       %s", (MC_FAULT_ENABLED==true)? "enabled" : "disabled");
    PRINT_OUT("Long-press the button to reboot");
    PRINT_OUT("Short-press the button to start or stop the motor");
}

static void Main_ShowFaults(mc_status_t status)
{
#if MC_PRINTOUT_ENABLED == true
    if(status.flags)
    {
        const char *str_uv = "";
        const char *str_ov = "";
        const char *str_stall = "";
        const char *str_hall = "";
        const char *str_hot = "";
        const char *str_oc = "";
        if(status.flags & MC_FAULT_UNDERVOLTAGE_MASK) str_uv = "Undervoltage ";
        if(status.flags & MC_FAULT_OVERVOLTAGE_MASK)  str_ov = "Overvoltage ";
        if(status.flags & MC_FAULT_STALL_MASK)        str_stall = "Stall ";
        if(status.flags & MC_FAULT_HALL_MASK)         str_hall = "Hall ";
        if(status.flags & MC_FAULT_OVERHEAT_MASK)     str_hot = "Hot ";
        if(status.flags & MC_FAULT_OVERCURRENT_MASK)  str_oc = "Overcurrent ";

        PRINT_OUT("Faults: %s%s%s%s%s%s", str_uv, str_ov, str_stall, str_hall, str_hot, str_oc);
    }
#else /* MC_PRINTOUT_ENABLED */
    (void)status;
#endif /* MC_PRINTOUT_ENABLED */
}

static void Main_PeriodicPrint(void)
{
    PRINT_OUT("Speed: %uRPM, Current: %dmA, VBUS: %umV, Temperature: %u°C, Pot: %u%%     ",
                my_speed,
                MC_CurrentRead(),
                MC_VoltageBusRead(),
                MC_TemperatureRead(),
                my_pot
             );
}

static void PeriodicHandler(mc_status_t status)
{
    MC_ReferenceSet(MC_FastPotentiometerRead());
    my_pot = MC_PotentiometerRead();
    my_speed = (uint16_t)MC_MCSPEED_TO_RPM(MC_SpeedGet());

    button_state = ButtonGet();
    switch(status.state)
    {
        case IDLE:      led_ctrl = LED_OFF;    break;
        case RUNNING:   led_ctrl = LED_ON;     break;
        case FAULT:     led_ctrl = LED_BLINK;  break;
        default:                               break;
    }
    LedControl(led_ctrl);

    if(status.state == RUNNING)
    {
        static uint16_t periodic_event_counter = 0;
        periodic_event_counter ++;
        if(periodic_event_counter == MC_PRINTOUT_REFRESH_INTERVAL)
        {
            Main_PeriodicPrint();
            periodic_event_counter = 0;
        }
    }
}

static void ResetDevice(void)
{
    _PROTECTED_WRITE(RSTCTRL.SWRR, RSTCTRL_SWRE_bm);
    while(true) { }
}

void MC_Example_Initialize(void)
{
    _delay_ms(1000);
    PRINT_OUT("============= START ================= ");
    MC_Initialize();
    MC_PeriodicHandlerRegister(PeriodicHandler);
    MC_DELAY_MS(500);
    PrintConfig();

    prev_motor_state.state = -1;
    direction = MC_DIR_CW;
}

void MC_Example_Run(void)
{
    MC_DELAY_MS(BUTTON_LED_TIME_STEP);
    mc_status_t motor_state = MC_StatusGet();

    if((button_state != BUTTON_IDLE) || (motor_state.word != prev_motor_state.word))
    {
        if (button_state == BUTTON_LONG_PRESS)
        {
            if(motor_state.state == RUNNING)
            {
                PRINT_OUT("Ramping-down");
                MC_StartStop(0);
            }
            PRINT_OUT("============= REBOOT ================ ");
            MC_DELAY_MS(10);
            ResetDevice();
        }
        switch(motor_state.state)
        {
            case IDLE:      if(button_state == BUTTON_SHORT_PRESS)
                            {
                                PRINT_OUT("Ramping-up ... %s", (direction==MC_DIR_CW)? "CW":"CCW");
                                MC_StartStop(direction);
                                if(direction == MC_DIR_CW) direction = MC_DIR_CCW;
                                else                       direction = MC_DIR_CW;
                            }
                            else
                            {
                                PRINT_OUT("Motor idle");
                            }
                            break;
            case RUNNING:   if(button_state == BUTTON_SHORT_PRESS)
                            {
                                PRINT_OUT("Ramping-down");
                                MC_StartStop(0);
                            }
                            else
                            {
                                PRINT_OUT("Motor running");
                            }
                            break;
            case FAULT:     Main_ShowFaults(motor_state);
                            break;
            default: break;
        }
        prev_motor_state = motor_state;
    }
}
