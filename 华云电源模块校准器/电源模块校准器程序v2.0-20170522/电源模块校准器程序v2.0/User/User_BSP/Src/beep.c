#include "beep.h"
#include "User_BSP.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��
void BEEP_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��GPIOB�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //BEEP-->PB.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8

	GPIO_ResetBits(GPIOB,GPIO_Pin_7);//���0���رշ��������
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);//���1������ص�Դ
	BEEP = 0;
}
void BEEP_500MS()
{
    uint8_t i=0;
	  BEEP_Init();
	  for(i=0;i<100;i++)
	  { 
		BEEP_1;
		Delay_ms(500);
		BEEP_0;
//		Delay_s(1);
	  }
}
