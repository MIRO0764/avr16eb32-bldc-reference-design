 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
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
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/mclib/example/mc_example.h"

void ATA_RegisterWrite(uint8_t reg, uint8_t data);
void ATA_Setup(void);
void ATA_WDGTRIG(void);
uint8_t ATA_Reading(uint8_t reg);
uint16_t ATA_Status(void);

#define REG_WDTMR_TRIG 0x20
#define REG_WDCFG1 0x20
#define REG_GDU1 0x05
#define REG_GDU2 0x06
#define REG_GDU3 0x07
#define REG_GDU4 0x08
#define REG_CURR_SENSE 0x0C
#define REG_CURR_LIMIT 0x09
#define REG_CURR_TRESH 0x0A
#define REG_DEV_OP 0x01
#define REG_GDU_OP 0x03

int main(void)
{
    SYSTEM_Initialize();
    MC_Example_Initialize();
    
    
    ATA_CS_SetDigitalOutput();
    ATA_CS_SetHigh();
    
    ATA_Setup();
    
    ATA_Status();
    
    while(NIRQ_GetValue()==1);
    ATA_RegisterWrite(REG_GDU_OP,0x07);

    while(1)
    {
        MC_Example_Run();
    }    
}

void ATA_RegisterWrite(uint8_t reg, uint8_t data)
{
    ATA_CS_SetLow();
    SPI0_Open(SPI0_DEFAULT);
    SPI0_ByteExchange(reg<<1);
    
    SPI0_ByteExchange(data);
   
    SPI0_Close();
    ATA_CS_SetHigh();
    
}


void ATA_Setup(void)
{
    ATA_WDGTRIG(); //Watchdog Reset + Confirmation of OFF
    
    
    
    ATA_RegisterWrite(REG_GDU1,0x0F); //Gate Driver Unit Register 1
    ATA_RegisterWrite(REG_GDU2,0xD1); //Gate Driver Unit Register 2
    ATA_RegisterWrite(REG_GDU3,0x55); //Gate Driver Unit Register 3
    ATA_RegisterWrite(REG_GDU4,0x0F); //Gate Driver Unit Register 4
   
    ATA_RegisterWrite(REG_CURR_SENSE,0xDC); //Current Sense Control Register
    ATA_RegisterWrite(REG_CURR_LIMIT,0xC0); //Current Limitation Control Register
    ATA_RegisterWrite(REG_CURR_TRESH,0x71); //Current Limitation Threshold Register
    
    ATA_RegisterWrite(REG_DEV_OP,0xC7); //Device Op Mode
    
    ATA_RegisterWrite(REG_GDU_OP,0x04); //Gate Driver Op Mode 
}

void ATA_WDGTRIG(void)
{   
    
    ATA_RegisterWrite(0x20,0x55); //WD Timer Trig
    ATA_RegisterWrite(0x20,0x55); //WD Timer Trig
    ATA_RegisterWrite(0x20,0x55); //WD Timer Trig
    ATA_RegisterWrite(0x21,0x20); //WD Configuration Register 1
    
}

uint8_t ATA_Reading(uint8_t reg)
{   ATA_CS_SetLow();
    SPI0_Open(SPI0_DEFAULT);
    SPI0_ByteWrite((reg<<1)|1);
    uint8_t read = SPI0_ByteExchange(0xFF);
    SPI0_Close();
    ATA_CS_SetHigh();
    return read;
}

uint16_t ATA_Status(void)
{
    uint16_t full_read;
    full_read  = ((uint16_t)ATA_Reading(0x10) << 8); // Read high byte and shift left
    full_read |= ATA_Reading(0x11);                  // Read low byte and OR it in
    return full_read;
}  