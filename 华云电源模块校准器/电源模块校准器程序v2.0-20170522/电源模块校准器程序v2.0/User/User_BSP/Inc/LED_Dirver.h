/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
                   ARM Cortex-M3 Port
* 文件名    : BSP_OutPut.h
* 描  述    :
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
*******************************************************************************/
#ifndef __Led_Dirver_H
#define __Led_Dirver_H
/* Includes---------------------------------------------*/
#include "User_Conf.h" 
/* Private defines--------------------------------------*/

#define LED0   PAout(11)//
//#define LED1   PBout(4)//
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
void Led_Dirver_Init(void);
void Led_Dirver(void);
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif

