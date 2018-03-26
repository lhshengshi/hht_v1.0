/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
                   ARM Cortex-M3 Port
* 文件名    : BSP_USART1.h
* 描  述    : 
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
*******************************************************************************/
#ifndef __Usart3_Dirver_H
#define __Usart3_Dirver_H
/* Includes---------------------------------------------*/
#include "User_Conf.h"

//模式控制
#define RS485_TX_EN		PBout(0)	//485模式控制.0,接收;1,发送.


/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
extern void USART3_GPIO_Config(void);
extern void Usart3_Send(uint8_t *buf,uint8_t len);
extern void Usart3_Init(void);
extern uint8_t XORValid(uint8_t *buffer,uint16_t Len);
extern  void Fill_Information(void);
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif
