#ifndef __CN3153_H
#define __CN3153_H	 
#include "sys.h"

	   

//��س��ʱΪ0
#define BATC_GPIO                   GPIOB
#define BATC_PIN                    (GPIO_Pin_13)
#define BATC GPIO_ReadInputDataBit(BATC_GPIO, BATC_PIN)

//��س���ʱΪ0
#define BATM_GPIO                   GPIOB
#define BATM_PIN                    (GPIO_Pin_12)
#define BATM GPIO_ReadInputDataBit(BATM_GPIO, BATM_PIN)

//MCU_ADC ΢������adת������
#define MCUADC_GPIO                     GPIOB
#define MCUADC_PIN                    ( GPIO_PIN_1)
#define MCUAD GPIO_ReadInputDataBit(MCUADC_GPIO, MCUADC_PIN)

//ά�ֿ���״̬  
#define PWR_GPIO                   GPIOB
#define PWR_PIN                    (GPIO_Pin_14)
#define PWR_0  GPIO_ResetBits(PWR_GPIO, PWR_PIN)
#define PWR_1  GPIO_SetBits(PWR_GPIO, PWR_PIN)

void CN3153_Init(void); //IO��ʼ��
void Stop(void);
void start(void);

#endif

