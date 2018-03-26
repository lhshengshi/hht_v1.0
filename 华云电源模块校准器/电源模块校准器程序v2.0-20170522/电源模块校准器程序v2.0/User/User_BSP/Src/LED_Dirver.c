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
#include "Led_Dirver.h"
void Led_Dirver_Init(void);
void Led_Dirver(void);

/**********************************************
*	函 数 名: static void Led_Dirver_Init(void)
*	形    参：
*	返 回 值: 
*	功能说明: LED端口初始化				
**********************************************/ 
void Led_Dirver_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//要先开时钟，再重映射；关闭jtag，保留swd。        

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB端口
	}
void Led_Dirver(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	Delay_ms(200);
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
//	Delay_ms(100);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
//	Delay_ms(100);
//	GPIO_SetBits(GPIOB,GPIO_Pin_4);

	}
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/


