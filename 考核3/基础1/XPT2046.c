#include <REGX52.H>
#include "delay.h"
#include "intrins.h"

sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DIN=P3^4;
sbit XPT2046_DOUT=P3^7;

void Delay150us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 66;
	while (--i);
}



unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int ADValue=0;
	
	XPT2046_DCLK=0;
	XPT2046_CS=0;
	
	for(i=0;i<8;i++)
	{
		XPT2046_DIN=Command&(0x80>>i);
		XPT2046_DCLK=1;
		XPT2046_DCLK=0;
	}
	
	for(i=0;i<16;i++)
	{
		XPT2046_DCLK=1;
		Delay150us();
		//Delay(1);
		XPT2046_DCLK=0;
		if(XPT2046_DOUT)
		{
			ADValue|=(0x8000>>i);
		}
	}
	
	XPT2046_CS=1;
	if(Command&0x08)
	{
		ADValue=ADValue>>8;
	}else
	{
		ADValue=ADValue>>4;
	}
	
	return ADValue;
}