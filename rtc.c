#include <LPC21xx.H>

#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"

// Array to hold names of days of the week
char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};


/*
Initialize the Real-Time Clock (RTC)
This function disables the RTC, sets the prescaler values, 
and then enables the RTC.
*/
void RTC_Init(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;

#if (CPU == LPC2129)	
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
	CCR = RTC_ENABLE; 
#elif (CPU == LPC2148)
  // Enable the RTC
	CCR = RTC_ENABLE | RTC_CLKSRC;  
#endif
}

/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
void GetRTCTimeInfo(S32 *hour, S32 *minute, S32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

/*
Display the RTC time on LCD
hour value (0 23)
minute value (0 59)
second value (0 59) seperated by ':'
*/
void DisplayRTCTime(U32 hour, U32 minute, U32 second)
{
	cmdLCD(GOTO_LINE1_POS0);
	charLCD((hour/10)+48);
	charLCD((hour%10)+48);
	charLCD(':');
	charLCD((minute/10)+48);
	charLCD((minute%10)+48);
	charLCD(':');
	charLCD((second/10)+48);
	charLCD((second%10)+48);
}

/*
Get the current RTC date
day Pointer to store the current date (1 31)
month Pointer to store the current month (1 12)
year Pointer to store the current year (four digits)
*/
void GetRTCDateInfo(S32 *date, S32 *month, S32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

/*
Display the RTC date on LCD
Day of month (1 31)
Month (1 12)
Year (four digits) and seperated by '/'
*/
void DisplayRTCDate(U32 date, U32 month, U32 year)
{
	cmdLCD(GOTO_LINE2_POS0);
	charLCD((date/10)+48);
	charLCD((date%10)+48);
	charLCD('/');
	charLCD((month/10)+48);
	charLCD((month%10)+48);
	charLCD('/');
	U32LCD(year);
}

/*
Set the RTC time
Hour to set (0 23)
Minute to set (0 59)
Second to set (0 59)
*/
void SetRTCTimeInfo(U32 hour, U32 minute, U32 second)
{
	HOUR = hour;
	MIN = minute;
	SEC = second;
}
void SetRTCHour(U32 hour){
	HOUR=hour;
}

void SetRTCMin(U32 min){
	MIN=min;
}

void SetRTCSec(U32 sec){
	SEC=sec;
}

/*
Set the RTC date
day of month to set (1 31)
month to set (1 12)
year to set (four digits)
*/
void SetRTCDateInfo(U32 date, U32 month, U32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
}
void SetRTCDate(U32 date){
	DOM=date;
}

void SetRTCMonth(U32 month){
	MONTH=month;
}

void SetRTCYear(U32 year){
	YEAR=year;
}
/*
Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(S32 *day)
{
	*day = DOW;
}

/*
Display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/
void DisplayRTCDay(U32 day)
{
	cmdLCD(GOTO_LINE1_POS0+9);
	StrLCD(week[day]);
  
}

/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(U32 day)
{
	DOW = day;
}
