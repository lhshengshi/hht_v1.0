/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                   ARM Cortex-M3 Port
* �ļ���    : User_BSP.h
* ��  ��    :
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
*******************************************************************************/
#ifndef __User_BSP_H
#define __User_BSP_H
/* Includes---------------------------------------------*/
#include "User_Conf.h" 
#include "BSP_Usart1.h"
#include "Led_Dirver.h"
#include "Usart2_Dirver.h"
#include "Usart3_Dirver.h"
//#include "Sht2x_Dirver2.h"
//#include "Switch_Dirver.h"
#include "IWDG_Dirver.h"
#include "TIM3_Dirver.h"
#include "EEprom_Dirver.h"
#include "TIM2_Dirver.h"

#include "beep.h"
#include "key.h"
#include "BSP_JCM12864_Demo.h"
#include "BSP_JCM12864.h"
#include "CN3153.h"
#include "adc.h"
/* Private defines--------------------------------------*/

//extern uint8_t System_Flag;//ϵͳ���н׶α�־
	//0������
	//1������
//extern uint16_t System_State_Flag;//ϵͳ����״̬
//bit0:����/����״̬
//bit1:��λ����λ��ɼ�ȡ����״̬
//bit2:ͨѶ״̬��ָ�ⲿ485ͨѶ
//bit3:�¶ȼ����ϱ�־λ
//bit4:ʪ�ȼ����ϱ�־λ
//bit5:��ˮ�����ϱ�־λ
//bit6:
//bit7:�ܹ��ϱ�־
//bit8:�����±���
//bit9:�����±���
//bit10:��ʪ����
//bit11:���ɱ���
//bit12:��ˮ����
//bit13:
//bit14:
//bit15:�ܱ���λ
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
extern void User_BSP_Init(void);
void Soft_Init(void);
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
#endif

