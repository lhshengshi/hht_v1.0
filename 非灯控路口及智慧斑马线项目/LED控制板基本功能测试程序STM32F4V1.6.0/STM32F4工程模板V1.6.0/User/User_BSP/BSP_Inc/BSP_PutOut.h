/******************** (C) COPYRIGHT DIYǶ��ʽ����������*******************************
 *                                
 *                              ARM Cortex-M4 Port
 *
 * �ļ�����     : BSP_PutOut.h ( FreeTROS For STM32F4 )
 * ��    ��     : MJQ	 
 * ��    ��	 	: MDK5.10a-->�̼���V1.3.0�汾-->FreeRTOS V8.1.2 �汾
 * ����ƽ̨     : STM32F407ZGT6-25MHz->168MHz 
 * �޸�ʱ��     : 2014-10-20 
 * ��    ��     : V1.0.0
 * Ӳ������     : STM32F40xx-STM32������
 * ˵    ��     : 
 * 			  
 *				   
**************************************************************************************/
#ifndef __BSP_PutOut_H
#define __BSP_PutOut_H
/* Includes---------------------------------------------*/
#include "User_conf.h"
/* Private defines--------------------------------------*/
#define LED0 PDout(12)	// DS0
#define LED1 PDout(13)	// DS1	
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
void BSP_PutOut_Init(void);
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
#endif

