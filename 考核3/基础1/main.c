#include <REGX52.H>
#include "delay.h"
#include "uart.h"
#include "timer0.h"
#include <stdio.h>
#include "XPT2046.H"
#include <string.h>

unsigned int ADValue1,ADValue2,ADValue3,ADValue4;

unsigned int a=100,b=40;

void main()
{
	UART_Init();
	Timer0_Init();
	
	while(1)
	{
//		ADValue1=XPT2046_ReadAD(XPT2046_XP_8);		//读取AIN0，可调电阻
//		
//		ADValue2=XPT2046_ReadAD(XPT2046_YP_8);		//读取AIN1，热敏电阻
//				
//		ADValue3=XPT2046_ReadAD(XPT2046_VBAT_8);		//读取AIN2，光敏电阻
//		
//		ADValue4=XPT2046_ReadAD(XPT2046_AUX_8);		//读取AIN3，方波
//			
//		printf("%u,%u,%u,%u,%u,%u\n",ADValue1,ADValue2,ADValue3,ADValue4,a,b);

	}
}

int to_num(char *s)
{
    int num = 0;
    while(*s >= '0' && *s <= '9')
    {
        num = num * 10 + (*s - '0');
        s++;
    }
    return num;
}


unsigned char d[30];	//储存接受内容
unsigned char idx=0;	//当前位置指针

// 串口中断服务函数
void Uart_Interrupt(void) interrupt 4
{
    unsigned char dat;		//储存每一个读取到的内容
	char *p=NULL;
	int num;
	int i;
    
    if(RI)   // 如果收到数据
    {
        RI=0;        // 清除标志
        dat=SBUF;    // 读到数据

        // 收到回车/换行 → 指令结束，开始解析
        if(dat=='\r' || dat=='\n')
        {
            d[idx]='\0';  // 字符串结束符
            
            // = 号位置
            for(i=0;i<idx;i++)
			{
				if(d[i]=='=')
				{
					p=d+i;
					break;
				}
			}
            
            if(p!=NULL)  // 找到了 =
            {
                // 提取等号后面的数字
                num=to_num(p + 1);

                // 判断前面是 a / b 
                if(d[0]=='a')
                {
                    a=num;
                }
                else if(d[0]=='b')
                {
                    b=num;
                }
            }

            // 清空，准备接收下一条指令
            idx=0;
            for(i=0;i<30;i++)
            {
                d[i]=0;
            }
        }
        // 正常字符，存入缓冲区
        else
        {
            if(idx<29)
            {
                d[idx++]=dat;
            }
        }
    }
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count=0;
	TL0 = 0x66;
	TH0 = 0xFC;
	T0Count++;
	if(T0Count>=a)
	{
		T0Count=0;
	}
	
	if(T0Count<b)
	{
		PUTOUT=1;
	}else
	{
		PUTOUT=0;
	}
	
	ADValue4=XPT2046_ReadAD(XPT2046_AUX_8);		//读取AIN3，方波
	printf("%u\n",ADValue4);
}