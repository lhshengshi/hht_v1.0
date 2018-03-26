#include "systick.h"

/*******************************************************************************
* Function Name  : delay_us
* Description    : 延时函数，延时us
* Input          : i
* Output         : None
* Return         : None
*******************************************************************************/
void delay_us(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 //设置重装数值, 72MHZ时
	SysTick->CTRL=0X01;		 //使能，减到零是无动作，采用外部时钟源
	SysTick->VAL=0;		   	 //清零计数器
	do
	{
		temp=SysTick->CTRL;		   //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //等待时间到达
	SysTick->CTRL=0;	//关闭计数器
	SysTick->VAL=0;		//清空计数器
}

/*******************************************************************************
* Function Name  : delay_ms
* Description    : 延时函数，延时ms
								 * 只能精确延时1000ms，就是1s，超过1秒就会乱
* Input          : i
* Output         : None
* Return         : None
*******************************************************************************/
void delay_ms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;	  //设置重装数值, 72MHZ时               系统默认SysTick时钟是8分频（HCLK/8），当前系统时钟是72MHz时，SysTick时钟是9MHz。
	SysTick->CTRL=0X01;		//使能，减到零是无动作，采用外部时钟源
	SysTick->VAL=0;			//清零计数器
	do
	{
		temp=SysTick->CTRL;	   //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//等待时间到达
	SysTick->CTRL=0;	//关闭计数器
	SysTick->VAL=0;		//清空计数器
}
/*******************************************************************************
* Function Name  : delay_s
* Description    : 延时函数，延时s
* Input          : i
* Output         : None
* Return         : None
*******************************************************************************/

void delay_s (u32 i)
{
	u32 m;
	for (m=i;m>0;m--)
		delay_ms(1000);
}
