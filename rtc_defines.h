#ifndef RTC_DEFINES_H
#define RTC_DEINES_H
//System Clock AND Peripheral Clock MARCROS
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
//RTC MACROS
#define PREINT_VAL (int)((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-(PREINT_VAL+1)*32768)
#define RTC_ENABLE (1<<0)
#define RTC_RESET (1<<1)
#define RTC_CLKSRC (1<<4)
#define CPU LPC2148
#endif
