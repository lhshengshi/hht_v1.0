#ifndef __PUBLIC_H
#define __PUBLIC_H

#include "stm32f10x.h"

#define KEY_INTO_SUB   15
#define KEY_RETURN     13
#define KEY_NEXT_White 12
#define KEY_IO_MENU     8
extern uint8_t setTime,m,nline,into_menu,back_menu,setMeun,keyscan;
extern uint8_t ReadValue;

//键盘全局声明
extern unsigned int Keyboard_Val ;          //当前键值
extern unsigned char Keyboard_Change_Flag;  //键值改变标志，读入新键值后，标志位清零
extern u8  key_pressed_flag;                //有按键按下时置1

extern uint8_t IICSend[20],IICRecive[20];

#define jj  5					   //宏定义，字符显示的时间差

#endif
