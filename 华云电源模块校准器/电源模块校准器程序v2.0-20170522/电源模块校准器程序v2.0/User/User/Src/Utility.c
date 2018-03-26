
/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
             ARM Cortex-M3 Port
* 文件名    : utility.c
* 描  述    : 公共实用函数 延时函数
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
*******************************************************************************/
/* Includes---------------------------------------------*/
#include "utility.h"
/* Private defines--------------------------------------*/
static u8  fac_us=0;																										/*us延时倍乘数*/
static u16 fac_ms=0;
/* Private function prototypes--------------------------*/
/* Private functions -----------------------------------*/
/**
*@brief		初始化延迟函数
*@param		SYSCLK:系统时钟
*@return	无
*/
void Systick_Init (u8 sysclk)
{
    SysTick->CTRL&=0xfffffffb;																						/*bit2清空,选择外部时钟  HCLK/8*/
    fac_us=sysclk/8;
    fac_ms=(u16)fac_us*1000;
}

/**
*@brief	  秒延时函数
*@param		time_s:要延时秒间数
*@return	无
*/
void Delay_s( uint32_t time_s )
{
    for(; time_s>0; time_s--)
        Delay_ms(1000);
}

/**
*@brief	  毫秒延时函数
*@param		time_ms:要延时毫秒时间数
*@return	无
*/
void Delay_ms( uint32_t time_ms )
{
    u32 temp;
    SysTick->LOAD=(u32)time_ms*fac_ms;																		/*时间加载(SysTick->LOAD为24bit)*/
    SysTick->VAL =0x00;           																				/*清空计数器*/
    SysTick->CTRL=0x01 ;         																					/*开始倒数*/
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));																		/*等待时间到达*/
    SysTick->CTRL=0x00;       																						/*关闭计数器*/
    SysTick->VAL =0X00;      																							/*清空计数器*/
}

/**
*@brief	  微秒延时函数
*@param		time_ms:要延时微秒时间数
*@return	无
*/
void Delay_us( uint32_t time_us )
{
    u32 temp;
    SysTick->LOAD=time_us*fac_us; 																				/*时间加载*/
    SysTick->VAL=0x00;        																						/*清空计数器*/
    SysTick->CTRL=0x01 ;      																						/*开始倒数 */
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));																		/*等待时间到达*/
    SysTick->CTRL=0x00;       																						/*关闭计数器*/
    SysTick->VAL =0X00;       																						/*清空计数器*/
}

/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/


/*ms延时倍乘数*/


