#include <REGX52.H>

/**
  * @brief  串口初始化，9600bps@11.0592MHz
  * @param	无
  * @retval	无
  */

void UART_Init(void)	//9600bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
//	AUXR &= 0xBF;		//定时器时钟12T模式
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	EA=1;
	ES=1;
}

/**
  * @brief  串口发送一个字节数据
  * @param	Byte要发送的一个字节数据
  * @retval	无
  */

char putchar(char ch)
{
    SBUF = ch;   // 把字符写入串口发送寄存器（硬件核心）
    while(TI == 0); // 等待发送完成
    TI = 0;       // 清发送标志
    return ch;
}

void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

/*串口中断函数模版
void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		
		RI=0;
	}
}
*/