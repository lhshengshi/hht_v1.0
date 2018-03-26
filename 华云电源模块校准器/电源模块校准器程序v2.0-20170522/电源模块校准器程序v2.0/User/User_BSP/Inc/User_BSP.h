/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
                   ARM Cortex-M3 Port
* 文件名    : User_BSP.h
* 描  述    :
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
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

//extern uint8_t System_Flag;//系统运行阶段标志
	//0：开机
	//1：运行
//extern uint16_t System_State_Flag;//系统运行状态
//bit0:开机/运行状态
//bit1:复位，复位完成即取消此状态
//bit2:通讯状态，指外部485通讯
//bit3:温度检测故障标志位
//bit4:湿度检测故障标志位
//bit5:浸水检测故障标志位
//bit6:
//bit7:总故障标志
//bit8:超高温报警
//bit9:超低温报警
//bit10:超湿报警
//bit11:超干报警
//bit12:浸水报警
//bit13:
//bit14:
//bit15:总报警位
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
extern void User_BSP_Init(void);
void Soft_Init(void);
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif

