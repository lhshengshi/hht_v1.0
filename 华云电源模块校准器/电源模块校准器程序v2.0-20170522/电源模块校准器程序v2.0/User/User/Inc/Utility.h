/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
				ARM Cortex-M3 Port
* 文件名    : UTILITY.h
* 描  述    : 公共函数定义
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
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
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif
