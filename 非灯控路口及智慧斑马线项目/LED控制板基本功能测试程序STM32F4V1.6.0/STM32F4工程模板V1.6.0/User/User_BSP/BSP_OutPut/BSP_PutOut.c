/******************** (C) COPYRIGHT DIY嵌入式开发工作室*******************************
 *                                
 *                              ARM Cortex-M4 Port
 *
 * 文件名称     : BSP_PutOut.c ( FreeTROS For STM32F4 )
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
/* Includes---------------------------------------------*/
#include "BSP_PutOut.h"
/* Private defines--------------------------------------*/

/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
static void LED_Init(void);
/* Private functions -----------------------------------*/
/*************************************
*	函 数 名: LED_Init
*	功能说明: 配置LED指示灯相关的GPIO,  该函数被 bsp_Init() 调用。
*	形    参: 无
*	返 回 值: 无
**************************************/
void BSP_PutOut_Init(void)
{
    LED_Init();
}
/*************************************
*	函 数 名: LED_Init
*	功能说明: 配置LED指示灯相关的GPIO,  该函数被 bsp_Init() 调用。
*	形    参: 无
*	返 回 值: 无
**************************************/
static void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 打开GPIO时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* 设为输出口 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* 设为推挽模式 */
	GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_NOPULL;	/* 上下拉电阻不使能 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO口最大速度 */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}


/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/





