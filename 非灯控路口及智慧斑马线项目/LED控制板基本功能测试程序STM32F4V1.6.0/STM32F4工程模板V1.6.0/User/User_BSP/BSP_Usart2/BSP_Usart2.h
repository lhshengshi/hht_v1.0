/******************** (C) COPYRIGHT DIYǶ��ʽ����������*******************************
 *                                
 *                              ARM Cortex-M4 Port
 *
 * �ļ�����     : BSP_USART3.h ( FreeTROS For STM32F4 )
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
#ifndef __BSP_USART2_H
#define __BSP_USART2_H
/* Includes---------------------------------------------*/
#include "User_config.h"
/* Private defines--------------------------------------*/
#define USART2_BaudRate     9600
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
void USART2_Configuration(void);
void USART2_IRQHandler(void)  ;  
u8 Usart2SendStr(u8 *str,u16 strlen) ;
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
#endif

