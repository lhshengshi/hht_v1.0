/******************** (C) COPYRIGHT DIY嵌入式开发工作室*******************************
 *                                
 *                              ARM Cortex-M4 Port
 *
 * 文件名称     : BSP_PutOut.h ( FreeTROS For STM32F4 )
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
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif

