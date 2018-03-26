/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
                   ARM Cortex-M3 Port
* 文件名    : Readme.h
* 描  述    :
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    : MJQ
* 修改时间  : 
* 硬件连接  :  
* 库包含级别: 
            main.c(User_BSP.h)
			  |
			  |->User_BSP.c(User_Inc.h)
			        |
					|->BSP_Usart1.c 串口操作
					|->BSP_XXX.c
					|->BSP_OutPut.c(BSP_OutPut.h) 开关量输出
					                   |->User_Conf.h 用户参数配置
									         |->Utility.h 公共函数
									               |->sys.h 位操作
											           |->stm32f10x_conf.h
												       |->stm32f10x.h
													   |->stdio.h
						 
*******************************************************************************/
////20170109
//查询状态和查询网络分开做
//添加重启指令
//20170123 for50次判断通信状态  用来修复设置后接收指令一的命令的BUG 
//20170419 增加电池充电管理和一键开关机

























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
//#ifndef __BSP_OutPut_H
//#define __BSP_OutPut_H
///* Includes---------------------------------------------*/
//#include "User_Conf.h" 
///* Private defines--------------------------------------*/
//#define LED   PCout(13)// 

////#define Lamp_R_ON   GPIO_SetBits(GPIOA,GPIO_Pin_6  )
////#define Lamp_R_OFF  GPIO_ResetBits(GPIOA,GPIO_Pin_6)

///* Private typedef -------------------------------------*/
///* Private macro ---------------------------------------*/
///* Private variables -----------------------------------*/
///* Private function prototypes -------------------------*/
//void BSP_OutPut_Init(void);
///* Private functions -----------------------------------*/
///********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
//#endif














