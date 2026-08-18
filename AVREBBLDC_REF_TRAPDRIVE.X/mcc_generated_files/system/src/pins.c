/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
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

#include "../pins.h"

static void (*PIN_BEMF_NEUTRAL_InterruptHandler)(void);
static void (*IO_PD5_InterruptHandler)(void);
static void (*IO_PD4_InterruptHandler)(void);
static void (*IO_PD6_InterruptHandler)(void);
static void (*IO_PC2_InterruptHandler)(void);
static void (*IO_PC1_InterruptHandler)(void);
static void (*PIN_BEMF_A_InterruptHandler)(void);
static void (*PIN_VBUS_InterruptHandler)(void);
static void (*PIN_TEMPERATURE_InterruptHandler)(void);
static void (*PIN_POTENTIOMETER_InterruptHandler)(void);
static void (*PIN_BUTTON_InterruptHandler)(void);
static void (*PIN_LED_InterruptHandler)(void);
static void (*WEX0_WO0_InterruptHandler)(void);
static void (*WEX0_WO1_InterruptHandler)(void);
static void (*WEX0_WO2_InterruptHandler)(void);
static void (*WEX0_WO3_InterruptHandler)(void);
static void (*WEX0_WO4_InterruptHandler)(void);
static void (*WEX0_WO5_InterruptHandler)(void);
static void (*NIRQ_InterruptHandler)(void);
static void (*IO_PF1_InterruptHandler)(void);
static void (*IO_PF2_InterruptHandler)(void);
static void (*IO_PF3_InterruptHandler)(void);
static void (*ATA_CS_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{

  /* OUT Registers Initialization */
    PORTA.OUT = 0x0;
    PORTC.OUT = 0x2;
    PORTD.OUT = 0x81;
    PORTF.OUT = 0x0;

  /* DIR Registers Initialization */
    PORTA.DIR = 0x3F;
    PORTC.DIR = 0x2;
    PORTD.DIR = 0xD1;
    PORTF.DIR = 0x0;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x80;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x80;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x80;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x4;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x4;
    PORTD.PIN2CTRL = 0x4;
    PORTD.PIN3CTRL = 0x4;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x8;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x4;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x0;
    PORTF.PIN7CTRL = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x4;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TCEROUTEA = 0x0;
    PORTMUX.TCFROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x4;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    PIN_BEMF_NEUTRAL_SetInterruptHandler(PIN_BEMF_NEUTRAL_DefaultInterruptHandler);
    IO_PD5_SetInterruptHandler(IO_PD5_DefaultInterruptHandler);
    IO_PD4_SetInterruptHandler(IO_PD4_DefaultInterruptHandler);
    IO_PD6_SetInterruptHandler(IO_PD6_DefaultInterruptHandler);
    IO_PC2_SetInterruptHandler(IO_PC2_DefaultInterruptHandler);
    IO_PC1_SetInterruptHandler(IO_PC1_DefaultInterruptHandler);
    PIN_BEMF_A_SetInterruptHandler(PIN_BEMF_A_DefaultInterruptHandler);
    PIN_VBUS_SetInterruptHandler(PIN_VBUS_DefaultInterruptHandler);
    PIN_TEMPERATURE_SetInterruptHandler(PIN_TEMPERATURE_DefaultInterruptHandler);
    PIN_POTENTIOMETER_SetInterruptHandler(PIN_POTENTIOMETER_DefaultInterruptHandler);
    PIN_BUTTON_SetInterruptHandler(PIN_BUTTON_DefaultInterruptHandler);
    PIN_LED_SetInterruptHandler(PIN_LED_DefaultInterruptHandler);
    WEX0_WO0_SetInterruptHandler(WEX0_WO0_DefaultInterruptHandler);
    WEX0_WO1_SetInterruptHandler(WEX0_WO1_DefaultInterruptHandler);
    WEX0_WO2_SetInterruptHandler(WEX0_WO2_DefaultInterruptHandler);
    WEX0_WO3_SetInterruptHandler(WEX0_WO3_DefaultInterruptHandler);
    WEX0_WO4_SetInterruptHandler(WEX0_WO4_DefaultInterruptHandler);
    WEX0_WO5_SetInterruptHandler(WEX0_WO5_DefaultInterruptHandler);
    NIRQ_SetInterruptHandler(NIRQ_DefaultInterruptHandler);
    IO_PF1_SetInterruptHandler(IO_PF1_DefaultInterruptHandler);
    IO_PF2_SetInterruptHandler(IO_PF2_DefaultInterruptHandler);
    IO_PF3_SetInterruptHandler(IO_PF3_DefaultInterruptHandler);
    ATA_CS_SetInterruptHandler(ATA_CS_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for PIN_BEMF_NEUTRAL at application runtime
*/
void PIN_BEMF_NEUTRAL_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PIN_BEMF_NEUTRAL_InterruptHandler = interruptHandler;
}

void PIN_BEMF_NEUTRAL_DefaultInterruptHandler(void)
{
    // add your PIN_BEMF_NEUTRAL interrupt custom code
    // or set custom function using PIN_BEMF_NEUTRAL_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD5 at application runtime
*/
void IO_PD5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD5_InterruptHandler = interruptHandler;
}

void IO_PD5_DefaultInterruptHandler(void)
{
    // add your IO_PD5 interrupt custom code
    // or set custom function using IO_PD5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD4 at application runtime
*/
void IO_PD4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD4_InterruptHandler = interruptHandler;
}

void IO_PD4_DefaultInterruptHandler(void)
{
    // add your IO_PD4 interrupt custom code
    // or set custom function using IO_PD4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD6 at application runtime
*/
void IO_PD6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD6_InterruptHandler = interruptHandler;
}

void IO_PD6_DefaultInterruptHandler(void)
{
    // add your IO_PD6 interrupt custom code
    // or set custom function using IO_PD6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC2 at application runtime
*/
void IO_PC2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC2_InterruptHandler = interruptHandler;
}

void IO_PC2_DefaultInterruptHandler(void)
{
    // add your IO_PC2 interrupt custom code
    // or set custom function using IO_PC2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC1 at application runtime
*/
void IO_PC1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC1_InterruptHandler = interruptHandler;
}

void IO_PC1_DefaultInterruptHandler(void)
{
    // add your IO_PC1 interrupt custom code
    // or set custom function using IO_PC1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PIN_BEMF_A at application runtime
*/
void PIN_BEMF_A_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PIN_BEMF_A_InterruptHandler = interruptHandler;
}

void PIN_BEMF_A_DefaultInterruptHandler(void)
{
    // add your PIN_BEMF_A interrupt custom code
    // or set custom function using PIN_BEMF_A_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PIN_VBUS at application runtime
*/
void PIN_VBUS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PIN_VBUS_InterruptHandler = interruptHandler;
}

void PIN_VBUS_DefaultInterruptHandler(void)
{
    // add your PIN_VBUS interrupt custom code
    // or set custom function using PIN_VBUS_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PIN_TEMPERATURE at application runtime
*/
void PIN_TEMPERATURE_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PIN_TEMPERATURE_InterruptHandler = interruptHandler;
}

void PIN_TEMPERATURE_DefaultInterruptHandler(void)
{
    // add your PIN_TEMPERATURE interrupt custom code
    // or set custom function using PIN_TEMPERATURE_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PIN_POTENTIOMETER at application runtime
*/
void PIN_POTENTIOMETER_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PIN_POTENTIOMETER_InterruptHandler = interruptHandler;
}

void PIN_POTENTIOMETER_DefaultInterruptHandler(void)
{
    // add your PIN_POTENTIOMETER interrupt custom code
    // or set custom function using PIN_POTENTIOMETER_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PIN_BUTTON at application runtime
*/
void PIN_BUTTON_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PIN_BUTTON_InterruptHandler = interruptHandler;
}

void PIN_BUTTON_DefaultInterruptHandler(void)
{
    // add your PIN_BUTTON interrupt custom code
    // or set custom function using PIN_BUTTON_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PIN_LED at application runtime
*/
void PIN_LED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PIN_LED_InterruptHandler = interruptHandler;
}

void PIN_LED_DefaultInterruptHandler(void)
{
    // add your PIN_LED interrupt custom code
    // or set custom function using PIN_LED_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO0 at application runtime
*/
void WEX0_WO0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO0_InterruptHandler = interruptHandler;
}

void WEX0_WO0_DefaultInterruptHandler(void)
{
    // add your WEX0_WO0 interrupt custom code
    // or set custom function using WEX0_WO0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO1 at application runtime
*/
void WEX0_WO1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO1_InterruptHandler = interruptHandler;
}

void WEX0_WO1_DefaultInterruptHandler(void)
{
    // add your WEX0_WO1 interrupt custom code
    // or set custom function using WEX0_WO1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO2 at application runtime
*/
void WEX0_WO2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO2_InterruptHandler = interruptHandler;
}

void WEX0_WO2_DefaultInterruptHandler(void)
{
    // add your WEX0_WO2 interrupt custom code
    // or set custom function using WEX0_WO2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO3 at application runtime
*/
void WEX0_WO3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO3_InterruptHandler = interruptHandler;
}

void WEX0_WO3_DefaultInterruptHandler(void)
{
    // add your WEX0_WO3 interrupt custom code
    // or set custom function using WEX0_WO3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO4 at application runtime
*/
void WEX0_WO4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO4_InterruptHandler = interruptHandler;
}

void WEX0_WO4_DefaultInterruptHandler(void)
{
    // add your WEX0_WO4 interrupt custom code
    // or set custom function using WEX0_WO4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for WEX0_WO5 at application runtime
*/
void WEX0_WO5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    WEX0_WO5_InterruptHandler = interruptHandler;
}

void WEX0_WO5_DefaultInterruptHandler(void)
{
    // add your WEX0_WO5 interrupt custom code
    // or set custom function using WEX0_WO5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for NIRQ at application runtime
*/
void NIRQ_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    NIRQ_InterruptHandler = interruptHandler;
}

void NIRQ_DefaultInterruptHandler(void)
{
    // add your NIRQ interrupt custom code
    // or set custom function using NIRQ_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PF1 at application runtime
*/
void IO_PF1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF1_InterruptHandler = interruptHandler;
}

void IO_PF1_DefaultInterruptHandler(void)
{
    // add your IO_PF1 interrupt custom code
    // or set custom function using IO_PF1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PF2 at application runtime
*/
void IO_PF2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF2_InterruptHandler = interruptHandler;
}

void IO_PF2_DefaultInterruptHandler(void)
{
    // add your IO_PF2 interrupt custom code
    // or set custom function using IO_PF2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PF3 at application runtime
*/
void IO_PF3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF3_InterruptHandler = interruptHandler;
}

void IO_PF3_DefaultInterruptHandler(void)
{
    // add your IO_PF3 interrupt custom code
    // or set custom function using IO_PF3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for ATA_CS at application runtime
*/
void ATA_CS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    ATA_CS_InterruptHandler = interruptHandler;
}

void ATA_CS_DefaultInterruptHandler(void)
{
    // add your ATA_CS interrupt custom code
    // or set custom function using ATA_CS_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       WEX0_WO0_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       WEX0_WO1_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT2_bm)
    {
       WEX0_WO2_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT3_bm)
    {
       WEX0_WO3_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT4_bm)
    {
       WEX0_WO4_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT5_bm)
    {
       WEX0_WO5_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT2_bm)
    {
       IO_PC2_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT1_bm)
    {
       IO_PC1_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT0_bm)
    {
       PIN_TEMPERATURE_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       NIRQ_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT3_bm)
    {
       PIN_BEMF_NEUTRAL_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       IO_PD5_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT4_bm)
    {
       IO_PD4_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       IO_PD6_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT2_bm)
    {
       PIN_BEMF_A_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT1_bm)
    {
       PIN_POTENTIOMETER_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT0_bm)
    {
       PIN_LED_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       ATA_CS_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT4_bm)
    {
       PIN_VBUS_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT0_bm)
    {
       PIN_BUTTON_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT1_bm)
    {
       IO_PF1_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT2_bm)
    {
       IO_PF2_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT3_bm)
    {
       IO_PF3_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/