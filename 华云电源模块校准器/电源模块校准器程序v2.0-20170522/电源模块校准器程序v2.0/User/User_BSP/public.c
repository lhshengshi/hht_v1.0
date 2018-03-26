#include "public.h"

uint8_t IICSend[20],IICRecive[20];

uint8_t ReadValue;   //按键扫描值


uint8_t nline=0,
				into_menu=1,
				back_menu=0,
				keyscan=0; 

uint8_t key_pressed_flag=0;

unsigned char Keyboard_Change_Flag =0;

unsigned int Keyboard_Val ;          //当前键值

