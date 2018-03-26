/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
				ARM Cortex-M3 Port
* �ļ���    : UTILITY.h
* ��  ��    : ������������
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
*******************************************************************************/
#ifndef _UTILITY_H
#define _UTILITY_H
/* Includes---------------------------------------------*/
#include "sys.h"
/* Private defines--------------------------------------*/
/* Private function prototypes--------------------------*/
void Systick_Init (uint8_t SYSCLK);
void Delay_s( uint32_t time_s );
void Delay_us(uint32_t time_us);
void Delay_ms(uint32_t time_ms);
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
#endif
