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
#ifndef __IWDG_Dirver_H
#define __IWDG_Dirver_H
/* Includes---------------------------------------------*/
#include "User_Conf.h" 
/* Private defines--------------------------------------*/

/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);
void WWDG_Init(u8 tr,u8 wr,u32 fprer);//初始化WWDG
void WWDG_Set_Counter(u8 cnt);       //设置WWDG的计数器
void WWDG_NVIC_Init(void);
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif

