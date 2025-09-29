#include <LPC21xx.h>
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"
void WriteLCD(unsigned char  anyByte)
{
        IOCLR0=1<<LCD_RW;//Select Write Operation
        WRITEBYTE(IOPIN0,LCD_DATA,anyByte);//put any byte onto datapins D0-D7
        IOSET0=1<<LCD_EN;//provide high-low pulse
        delay_us(1);
        IOCLR0=1<<LCD_EN;
        delay_ms(2);
}
void cmdLCD(unsigned char cmd)
{
        IOCLR0=1<<LCD_RS;//Select cmd/inst reg
        WriteLCD(cmd);//Write cmd to reg
        delay_ms(2);
}
void charLCD(unsigned char asciiVal)
{
        IOSET0=1<<LCD_RS;//select data reg
        WriteLCD(asciiVal);//Write Ascii Via data reg to DDRAM Display
        delay_ms(2);
}
void StrLCD(char *p)
{
        while(*p)
        {
                charLCD(*p++);
        }
}
void InitLCD(void)
{
        //cfg P1.16-P0.31 as GPIO OutPins
        IODIR0=(0xFF<<LCD_DATA)|1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
        delay_ms(15);//power ON delay
        cmdLCD(0x30);
        delay_ms(4);
        delay_us(100);
        cmdLCD(0x30);
				delay_us(100);
        cmdLCD(0x30);
        cmdLCD(MODE_8BIT_2LINE);
        cmdLCD(DISP_ON_CUR_OFF);
        cmdLCD(CLEAR_LCD);
        cmdLCD(SHIFT_CUR_RIGHT);
}
void U32LCD(unsigned int num)
{
        unsigned char a[10];
        int i=0;
        if(num==0)
        {
                charLCD('0');
        }
        else
        {
                while(num>0)
                {
                        a[i]=(num%10)+48;
                        i++;
                        num/=10;
                }
                for(--i;i>=0;i--)
                {
                        charLCD(a[i]);
                }
        }
}
void S32LCD(int Snum)
{
        if(Snum<0)
        {
                charLCD('-');
                Snum=-Snum;
        }
        U32LCD(Snum);
}
void F32LCD(float fNum,unsigned char nDP)
{
        unsigned int num,i;
        if(fNum<0.0)
        {
                charLCD('-');
                fNum=-fNum;
        }
        num=fNum;
        U32LCD(num);
        charLCD('.');
        for(i=0;i<nDP;i++)
        {
                fNum=(fNum-num)*10;
                num=fNum;
                charLCD(num+48);
        }
}
void BuidCGRAM(unsigned char *p, unsigned char nBytes)
{
        unsigned int i;
        //Goto CGRAM Start
        cmdLCD(GOTO_CGRAM_START);
        IOSET0=1<<LCD_RS;//select data reg
        for(i=0;i<nBytes;i++)
        {
                        WriteLCD(p[i]);//write to CGRAM Memory
        }
        //return back to DDRAM
        cmdLCD(GOTO_LINE1_POS0);
}
