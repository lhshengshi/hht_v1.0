/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
				ARM Cortex-M3 Port
* �ļ���    : User_Conf.h
* ��  ��    : ϵͳ��Դ������
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
*******************************************************************************/
#ifndef __User_Conf_H
#define __User_Conf_H
/* Includes---------------------------------------------*/
#include "Utility.h"
/* Private defines--------------------------------------*/
//�������汾���ƣ������ڳ�������ʱ�������Ƿ�Բ���������������
#define SysParam_Ver        ((u32)(0x00000000))	

// Uart1 �û���������
#define USART1_Remap            TRUE 
#define Usart1_BaudRate         115200
#define USART1_INT_ENABLE       TRUE      //FALSE��ʹ���жϽ��ܣ�TRUEʹ���жϽ���

#if USART1_INT_ENABLE// �����ж����ȼ���BSP.C����NVIC_Configurationʹ������
		#define USART1_PreemptionPriority  0
		#define USART1_ChannelSubPriority  0 
#endif 

// �û�LEDָʾ�Ʋ�������
//#define LED_Pin0         GPIO_Pin_3
//#define LED_Pin1         GPIO_Pin_4
//#define LED_GPIO_Port   GPIOB
#define LED_Port_RCC    RCC_APB2Periph_GPIOB
/* Private function prototypes--------------------------*/
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
#endif
