#include "systick.h"

/*******************************************************************************
* Function Name  : delay_us
* Description    : ��ʱ��������ʱus
* Input          : i
* Output         : None
* Return         : None
*******************************************************************************/
void delay_us(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		 //ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;		   	 //���������
	do
	{
		temp=SysTick->CTRL;		   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}

/*******************************************************************************
* Function Name  : delay_ms
* Description    : ��ʱ��������ʱms
								 * ֻ�ܾ�ȷ��ʱ1000ms������1s������1��ͻ���
* Input          : i
* Output         : None
* Return         : None
*******************************************************************************/
void delay_ms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;	  //������װ��ֵ, 72MHZʱ               ϵͳĬ��SysTickʱ����8��Ƶ��HCLK/8������ǰϵͳʱ����72MHzʱ��SysTickʱ����9MHz��
	SysTick->CTRL=0X01;		//ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;			//���������
	do
	{
		temp=SysTick->CTRL;	   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}
/*******************************************************************************
* Function Name  : delay_s
* Description    : ��ʱ��������ʱs
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
