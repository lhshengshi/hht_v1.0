/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                   ARM Cortex-M3 Port
* �ļ���    : BSP_OutPut.c
* ��  ��    :
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
*******************************************************************************/
/* Includes---------------------------------------------*/
#include "Led_Dirver.h"
void Led_Dirver_Init(void);
void Led_Dirver(void);

/**********************************************
*	�� �� ��: static void Led_Dirver_Init(void)
*	��    �Σ�
*	�� �� ֵ: 
*	����˵��: LED�˿ڳ�ʼ��				
**********************************************/ 
void Led_Dirver_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//Ҫ�ȿ�ʱ�ӣ�����ӳ�䣻�ر�jtag������swd��        

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB�˿�
	}
void Led_Dirver(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	Delay_ms(200);
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
//	Delay_ms(100);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
//	Delay_ms(100);
//	GPIO_SetBits(GPIOB,GPIO_Pin_4);

	}
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/


