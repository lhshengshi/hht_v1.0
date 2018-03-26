/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                   ARM Cortex-M3 Port
* �ļ���    : BSP_USART1.h
* ��  ��    : 
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
*******************************************************************************/
#ifndef __Usart3_Dirver_H
#define __Usart3_Dirver_H
/* Includes---------------------------------------------*/
#include "User_Conf.h"

//ģʽ����
#define RS485_TX_EN		PBout(0)	//485ģʽ����.0,����;1,����.


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
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
#endif
