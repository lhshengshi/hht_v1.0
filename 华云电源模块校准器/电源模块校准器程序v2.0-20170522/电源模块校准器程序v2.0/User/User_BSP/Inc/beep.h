#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

//�������˿ڶ���
#define BEEP PBout(7)	// BEEP,�������ӿ�		   
#define BEEP_GPIO                   GPIOB
#define BEEP_PIN                    (GPIO_Pin_7)
#define BEEP_0 GPIO_ResetBits(BEEP_GPIO, BEEP_PIN)
#define BEEP_1 GPIO_SetBits(BEEP_GPIO, BEEP_PIN)
void BEEP_Init(void);	//��ʼ��
void BEEP_500MS(void);
		 				    
#endif

