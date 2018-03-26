/******************** (C) COPYRIGHT DIY嵌入式开发工作室*******************************
 *                                
 *                              ARM Cortex-M4 Port
 *
 * 文件名称     : BSP_USART3.h ( FreeTROS For STM32F4 )
 * 作    者     : MJQ	 
 * 环    境	 	: MDK5.10a-->固件库V1.3.0版本-->FreeRTOS V8.1.2 版本
 * 开发平台     : STM32F407ZGT6-25MHz->168MHz 
 * 修改时间     : 2014-10-20 
 * 版    本     : V1.0.0
 * 硬件连接     : STM32F40xx-STM32开发板
 * 说    明     : 
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
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif

