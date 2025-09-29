#include <LPC214x.h>
#include "pin_connect_block.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#include "kpm.h"
#include "rtc.h"
#include "edit_rtc.h"

// Function Prototype
void ValidateAndSet(char *msg, U32 minVal, U32 maxVal, void (*setFunc)(U32));

// Global variables
unsigned int val, opt1;
char key, op;

// Main function to show RTC edit menu
void Edit_RTCInfo()
{
    cmdLCD(0x01);                // Clear LCD
    cmdLCD(GOTO_LINE1_POS0);
    StrLCD("1.Edit RTC Info");   // Menu option 1
    cmdLCD(GOTO_LINE2_POS0); 
    StrLCD("2.Exit");            // Menu option 2

    ReadNum(&opt1,&key);         // Read user input
    op = key;

    if(op == '1')
    {
        Edit_RTC();              // Go to edit RTC menu
    }
    else if(op == '2')
    {
        cmdLCD(0x01);
        StrLCD("Exit");          // Exit menu
    }
    else
    {
        cmdLCD(0x01);
        StrLCD("Invalid Input"); // Wrong option
        delay_S(1);
    }
}

// Function to edit individual RTC fields
void Edit_RTC()
{
    while (1)
    {
        // Display sub-menu for RTC editing
        cmdLCD(0x01);
        cmdLCD(GOTO_LINE1_POS0);
        StrLCD("1.H 2.MM 3.S 4.D");   // Hour, Minute, Second, Date
        cmdLCD(GOTO_LINE2_POS0);
        StrLCD("5.M 6.Y 7.DA 8.E");   // Month, Year, Day, Exit
        delay_ms(500);

        // Read option from keypad
        ReadNum(&val,&key);
        op = key;

        // Based on option, validate and set respective RTC field
        if(op == '1')
            ValidateAndSet("Set Hours:", 0, 23, SetRTCHour);
        else if(op == '2')
            ValidateAndSet("Set Minutes:", 0, 59, SetRTCMin);
        else if(op == '3')
            ValidateAndSet("Set Seconds:", 0, 59, SetRTCSec);
        else if(op == '4')
            ValidateAndSet("Set Date:", 1, 31, SetRTCDate);
        else if(op == '5')
            ValidateAndSet("Set Month:", 1, 12, SetRTCMonth);
        else if(op == '6')
            ValidateAndSet("Set Year:", 2000, 2099, SetRTCYear);
        else if(op == '7')
            ValidateAndSet("Set Day(0-6):", 0, 6, SetRTCDay);
        else if(op == '8')
        {
            // Exit option
            cmdLCD(0x01); 
            StrLCD("Exiting Edit...");
            delay_ms(500);
						//return;
            break;   // Exit loop
        }
        else
        {
            // Invalid input
            cmdLCD(0x01); 
            StrLCD("Invalid Option");
            delay_ms(500);
        }
    }
}

// Generic function to validate user input and set RTC field
// msg     -> message to display on LCD
// minVal  -> minimum acceptable value
// maxVal  -> maximum acceptable value
// setFunc -> pointer to RTC setter function
void ValidateAndSet(char *msg, U32 minVal, U32 maxVal, void (*setFunc)(U32))
{
    unsigned int val;
    char key;
    while(1)
    {
        cmdLCD(0x01);
        StrLCD(msg);             // Show prompt message
        ReadNum(&val, &key);     // Read input from keypad

        if(val >= minVal && val <= maxVal)
        {
            setFunc(val);        // Call respective RTC set function
            break;
        }
        else
        {
            // Show error for invalid range
            cmdLCD(0x01);
            StrLCD("Invalid Range!");
            delay_S(1);
        }
    }
}
