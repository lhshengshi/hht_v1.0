#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

//蜂鸣器端口定义
#define BEEP PBout(7)	// BEEP,蜂鸣器接口		   
#define BEEP_GPIO                   GPIOB
#define BEEP_PIN                    (GPIO_Pin_7)
#define BEEP_0 GPIO_ResetBits(BEEP_GPIO, BEEP_PIN)
#define BEEP_1 GPIO_SetBits(BEEP_GPIO, BEEP_PIN)
void BEEP_Init(void);	//初始化
void BEEP_500MS(void);
		 				    
#endif

