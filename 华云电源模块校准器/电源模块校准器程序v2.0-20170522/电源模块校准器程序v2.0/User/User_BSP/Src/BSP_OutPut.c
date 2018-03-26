/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
                   ARM Cortex-M3 Port
* 文件名    : BSP_OutPut.c
* 描  述    :
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
*******************************************************************************/
/* Includes---------------------------------------------*/
#include "BSP_OutPut.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
//static void LED_Init(void);
/* Private functions -----------------------------------*/
/**********************************************
*	函 数 名: BSP_Output_Init(void)
*	形    参：
*	返 回 值: 
*	功能说明: 系统基本输出配置				
**********************************************/ 
//void BSP_OutPut_Init(void)
//{
//     LED_Init();
//}
///**********************************************
//*	函 数 名: static void LED_Init(void)
//*	形    参：
//*	返 回 值: 
//*	功能说明: LED端口初始化				
//**********************************************/ 
//static void LED_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//要先开时钟，再重映射；关闭jtag，保留swd。   
//	
//	RCC_APB2PeriphClockCmd(LED_Port_RCC , ENABLE);
//	
//	GPIO_InitStructure.GPIO_Pin = LED_Pin0|LED_Pin1 ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_Init(LED_GPIO_Port, &GPIO_InitStructure);

//GPIO_SetBits(LED_GPIO_Port,LED_Pin0|LED_Pin1);
//}
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/


