#include <lpc214x.h>
#include "lcd_defines.h"
#include "lcd.h"
#include "kpm.h"
#include "rtc.h"
#include "delay.h"
#include "types.h"
#include "edit_rtc.h"
#include "pin_connect_block.h"
#include "adc.h"

// External Interrupt Configuration
#define EINT0_FUN FUN2
#define FUN2 1
#define EINT0 14

// ADC and LDR Configuration
#define LDR_CHANNEL 0       // Using ADC0.0 (P0.27) for LDR
#define LDR_THRESHOLD 2.0   // Threshold value for LDR

// LED Configuration
#define LEDS (0xFF000000)   // LEDs connected to P1.24–P1.31

// Function Prototype for External Interrupt ISR
void eint0_isr(void)__irq;

// Global Variables for RTC and ADC
S32 hour, min, sec, date, month, year, day;
float ldr_Val = 0.0;

int main()
{
    U32 adcValue = 0;

    // Initialize peripherals
    InitLCD();
    Init_KPM();
    RTC_Init();
    Init_ADC();

    // Configure LEDs as output (P1.24–P1.31)
    IODIR1 |= LEDS;   
    IOCLR1  = LEDS;   // Turn OFF all LEDs initially

    // Configure External Interrupt 0 (EINT0)
    CfgPortPinFunc(0,16,EINT0_FUN);
    VICIntEnable = 1 << EINT0;               // Enable EINT0 interrupt
    VICVectCntl0 = (1 << 5) | EINT0;         // Enable slot for ISR
    VICVectAddr0 = (U32)eint0_isr;           // Set ISR address
    EXTMODE = 1 << 0;                        // Edge triggered
    // EXTPOLAR &= ~(1<<0);                  // Falling edge (default)

    // Welcome message on LCD
    StrLCD("Hey.!! Welcome");
    delay_ms(500);
    cmdLCD(0x01); // Clear LCD

    // Set initial RTC values
   /* SetRTCTimeInfo(17,59,55);
    SetRTCDateInfo(25,8,2025);
    SetRTCDay(0);*/

    // Infinite loop
    while(1)
    {
        // Fetch RTC time, date, day and display on LCD
        GetRTCTimeInfo(&hour,&min,&sec);
        DisplayRTCTime(hour,min,sec);

        GetRTCDateInfo(&date,&month,&year);
        DisplayRTCDate(date,month,year);

        GetRTCDay(&day);
        DisplayRTCDay(day);

        // Read LDR value from ADC
        Read_ADC(LDR_CHANNEL, &adcValue, &ldr_Val);

        // Display LDR value on LCD (line 1, position 13)
        cmdLCD(GOTO_LINE1_POS0+13);
        F32LCD(ldr_Val,2);

        // Control logic for streetlight
        if((hour >= 18) || (hour < 6))   // Night time (6PM to 6AM)
        {
            if(ldr_Val < LDR_THRESHOLD) // LDR detects darkness
            {
                cmdLCD(GOTO_LINE2_POS0+11);
                StrLCD("ON ");
                IOSET1 = LEDS;          // Turn ON streetlights
            }
            else
            {
                cmdLCD(GOTO_LINE2_POS0+11);
                StrLCD("OFF");
                IOCLR1 = LEDS;          // Turn OFF streetlights
            }
        }
        else
        {
            // Daytime - always OFF
            IOCLR1 = LEDS;
            cmdLCD(GOTO_LINE2_POS0+11);
            StrLCD("OFF");
        }

        cmdLCD(0x10); // Shift cursor
        delay_ms(500);
    }
}
// ISR for External Interrupt 0 (EINT0)
void eint0_isr(void)__irq
{
    Edit_RTCInfo();     // Enter RTC edit mode
    cmdLCD(0x01);       // Clear LCD
    EXTINT = 1 << 0;    // Clear EINT0 interrupt flag
    VICVectAddr = 0;    // Acknowledge interrupt
}
