void delay_us(unsigned int delayUS)
{
	delayUS*=12;
	while(delayUS--);
}
void delay_ms(unsigned int delayMS)
{
	delayMS*=12000;
	while(delayMS--);
}
void delay_S(unsigned int delayS)
{
	delayS*=12000000;
	while(delayS--);
}
