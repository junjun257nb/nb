#include <REGX52.H>

void Timer0_Init(void)
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
    // 11.0592MHz 1ms 定时初值
	TL0 = 0x66;
	TH0 = 0xFC;
	TF0 = 0;
	TR0 = 1;
	ET0=1;
	EA=1;
	PT0=0;
}

/*定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/
