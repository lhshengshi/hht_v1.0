#ifndef __PUBLIC_H
#define __PUBLIC_H

#include "stm32f10x.h"

#define KEY_INTO_SUB   15
#define KEY_RETURN     13
#define KEY_NEXT_White 12
#define KEY_IO_MENU     8
extern uint8_t setTime,m,nline,into_menu,back_menu,setMeun,keyscan;
extern uint8_t ReadValue;

//����ȫ������
extern unsigned int Keyboard_Val ;          //��ǰ��ֵ
extern unsigned char Keyboard_Change_Flag;  //��ֵ�ı��־�������¼�ֵ�󣬱�־λ����
extern u8  key_pressed_flag;                //�а�������ʱ��1

extern uint8_t IICSend[20],IICRecive[20];

#define jj  5					   //�궨�壬�ַ���ʾ��ʱ���

#endif
