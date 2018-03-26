/******************** (C) COPYRIGHT DIY嵌入式开发工作室*******************************
 *                                
 *                              ARM Cortex-M4 Port
 *
 * 文件名称     : BSP.h (  )
 * 作    者     : MJQ	 
 * 环    境	 	: MDK5.10a-->固件库V1.3.0版本
 * 开发平台     : STM32F407ZGT6-25MHz->168MHz 
 * 修改时间     : 2014-10-20 
 * 版    本     : V1.0.0
 * 硬件连接     : STM32F40xx-STM32开发板
 * 说    明     : 
 * 			  
 *				   
**************************************************************************************/
#ifndef _BSP_H_
#define _BSP_H_
/* Includes---------------------------------------------*/
#include "SYS.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
/* 提供给其他C文件调用的函数 */
void BSP_Init(void);
void Delay_init(u8 SYSCLK);
void Delay_us(u32 nus);
void Delay_ms(u16 nms);
/* Private functions -----------------------------------*/
#endif
/********** (C) COPYRIGHT DIY嵌入式开发工作室 （END OF FILE ）************************/


