#include "User_BSP.h"
#include "Heard_Public.h"
#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
						    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_15;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
//u8 KEY_Scan(u8 mode)
//{	
//	static u8 key_up=1;//�������ɿ���־

//	if(mode)key_up=1;  //֧������		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
//	{
//		Delay_ms(10);//ȥ����
//		key_up=0;
//		if(KEY0==0)return 17;
//		else if(KEY1==0)return 18;
//		else if(KEY2==0)return 19;
//		else if(KEY3==0)return 20;
//	}
//	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
// 	return 0;// �ް�������
//}

//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//�������ɿ���־
//	if(mode)key_up=1;  //֧������		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
//	{
//		Delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(KEY0==0)return 20;
//		else if(KEY1==0)return 19;
//		else if(KEY2==0)return 18;
//		else if(KEY3==0)return 17;
//	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
// 	return 0;// �ް�������
//}
/*--------------------------------------------------------------------------------------* �����������
* �� ��: keyboard.c
* ��д�ˣ� 
* ������ ɨ��4x4 ����������룬�����ؼ�ֵ
* ���÷�Χ�� ��������ST3.5 ���д��������STM32F10x ϵ�е�Ƭ��
* �������ţ� PA0-PA7
* ��дʱ�䣺 2014 ��5 ��20 ��
--------------------------------------------------------------------------------------*/

/*--------------------------------������̳�ʼ��----------------------------------------* ���ܣ� ��ʼ��stm32 ��Ƭ��GPIO //PA0-PA7
* �������ݣ�
* ���룺 ��
* ����ֵ����
--------------------------------------------------------------------------------------*/
void KeyBoard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

uint8_t Read_KeyValue(void)
{
	u8 mode = 0                                        ; //mode = 0 ����֧������ģʽ
	static u8 key_up=1;//key_up = 1 �������ɿ���־
	
	if((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f)
	{
		Delay_ms(10);
		if((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
			switch(GPIO_ReadInputData(GPIOA)&0xff)
			{
//				case 0x11: KeyValue = 1; break;12
//				case 0x21: KeyValue = 5; break;2
//				case 0x41: KeyValue = 9; break;4
//				case 0x81: KeyValue = 13;break;
				case 0x11: KeyValue = 12; break;
				case 0x21: KeyValue = 2; break;
				case 0x41: KeyValue = 4; break;
				case 0x81: KeyValue = 13;break;
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3);
			switch(GPIO_ReadInputData(GPIOA)&0xff)
			{
//				case 0x12: KeyValue = 2; break;
//				case 0x22: KeyValue = 6; break;
//				case 0x42: KeyValue = 10;break;
//				case 0x82: KeyValue = 14;break;
				case 0x12: KeyValue = 11; break;
				case 0x22: KeyValue = 1; break;
				case 0x42: KeyValue = 9;break;
				case 0x82: KeyValue = 14;break;
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3);
			switch(GPIO_ReadInputData(GPIOA)&0xff)
			{
//				case 0x14: KeyValue = 3; break;
//				case 0x24: KeyValue = 7; break;
//				case 0x44: KeyValue = 10;break;
//				case 0x84: KeyValue = 15;break;
				case 0x14: KeyValue = 10; break;
				case 0x24: KeyValue = 6; break;
				case 0x44: KeyValue = 8;break;
				case 0x84: KeyValue = 15;break;
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			switch(GPIO_ReadInputData(GPIOA)&0xff)
			{
//				case 0x18: KeyValue = 4; break;
//				case 0x28: KeyValue = 8; break;
//				case 0x48: KeyValue = 12;break;
//				case 0x88: KeyValue = 16;break;
				case 0x18: KeyValue = 3; break;
				case 0x28: KeyValue = 5; break;
				case 0x48: KeyValue = 7;break;
				case 0x88: KeyValue = 16;break;
			}
			GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
			GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |
			GPIO_Pin_7);
			while((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f);
			return KeyValue;
		}
//		if((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f)
//		{
//			GPIO_SetBits(GPIOA, GPIO_Pin_0);
//			GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
//			switch(GPIO_ReadInputData(GPIOA)&0xff)
//			{
//				case 0x11: KeyValue = 1; break;
//				case 0x21: KeyValue = 5; break;
//				case 0x41: KeyValue = 9; break;
//				case 0x81: KeyValue = 13;break;
//			}
//			GPIO_SetBits(GPIOA, GPIO_Pin_1);
//			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3);
//			switch(GPIO_ReadInputData(GPIOA)&0xff)
//			{
//				case 0x12: KeyValue = 2; break;
//				case 0x22: KeyValue = 6; break;
//				case 0x42: KeyValue = 10;break;
//				case 0x82: KeyValue = 14;break;
//			}
//			GPIO_SetBits(GPIOA, GPIO_Pin_2);
//			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3);
//			switch(GPIO_ReadInputData(GPIOA)&0xff)
//			{
//				case 0x14: KeyValue = 3; break;
//				case 0x24: KeyValue = 7; break;
//				case 0x44: KeyValue = 11;break;
//				case 0x84: KeyValue = 15;break;
//			}
//			GPIO_SetBits(GPIOA, GPIO_Pin_3);
//			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
//			switch(GPIO_ReadInputData(GPIOA)&0xff)
//			{
//				case 0x18: KeyValue = 4; break;
//				case 0x28: KeyValue = 8; break;
//				case 0x48: KeyValue = 12;break;
//				case 0x88: KeyValue = 16;break;
//			}
//			GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
//			GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |
//			GPIO_Pin_7);
//			while((GPIO_ReadInputData(GPIOA)&0xff)!=0x0f);
//			return KeyValue;
//		}
	}
	
	/*************************************************************/
//	
//	if(mode)
//	key_up=0;  //֧������
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
//	{
//		Delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(KEY0==0)return 17;
//		else if(KEY1==0)return 18;
//		else if(KEY2==0)return 19;
//		else if(KEY3==0)return 20;
//	}
//	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 
//	return 0;
	/****************************************************************/
	
//		static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		Delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return 20;
		else if(KEY1==0)return 19;
		else if(KEY2==0)return 18;
		else if(KEY3==0)return 17;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
 	return 0;// �ް�������
//	if(mode)
//		key_up=1;  //֧������
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
//	{
//		Delay_ms(10);//ȥ���� 
//		key_up=0;
//			if(KEY0==0)
//			{
////				 key_cnt++;
//				 if(++key_cnt >= 200)
//				 {
//					KSet = 0;
//					key_cnt = 200;
//					KOK  = 2;
//					return 100;                                 
//				 }
//				else if(key_cnt>20)
//				{
//					KSet = 1;
//					return 17;
//				}
//			}
//		else if(KEY1==0)return 18;
//		else if(KEY2==0)return 19;
//		else if(KEY3==0)return 20;
//	}
//	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)
//	{
//		key_up=1;
//		key_cnt = 0;
//		if(KSet==1)
//		{
//			KSet = 0;
//			KOK = 1;
//		}
//	} 
//	return 0;
}

void KEY_Handle_Demo(void)
{
	key = Read_KeyValue();
	if(key)
	{
		if(key == 13)
		{
			if(Buzzer_Flag == 0)
				Buzzer_Flag = 1;
			else if(Buzzer_Flag == 1)
				Buzzer_Flag = 0;
		}

		if(Buzzer_Flag == 1)
		{
			BEEP = 1;
			Delay_ms(30);
			BEEP = 0;
		}

		if(key == 15)
		{
			LCD_Show_Flag = 100;
		}
		
		switch (LCD_Show_Flag)
		{
			case 100:
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 62;
						key =0;                                                                                                                                                                                
						break;
					}

					case DOWN:
					{
						LCD_Show_Flag = 101;
						key = 0;
						break;
					}

					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 101:
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 111;
						key =0;
						break;
					}

					case UP:
					{
						LCD_Show_Flag = 100;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 102;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 102://ȫ��
				
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 130;
						key =0;
						break;
					}

					case UP:
					{
						LCD_Show_Flag = 101;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 103;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 103://ȫ��
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 131;
						key =0;
						break;
					}
					
					case UP:
					{
						LCD_Show_Flag = 102;
						key = 0;
						break;
					}
					
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 111://ͨ��һ״̬
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 141;
						key =0;
						break;
					}

					case DOWN:
					{
						LCD_Show_Flag = 112;
						key = 0;
						break;
					}
					case RIGHT:
					{
						LCD_Show_Flag = 114;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 101;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			
			case 112://ͨ����״̬
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 142;
						key =0;
						break;
					}

					case DOWN:
					{
						LCD_Show_Flag = 113;
						key = 0;
						break;
					}
					case RIGHT:
					{
						LCD_Show_Flag = 114;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 111;
						key = 0;
						break;
					}

					case BACK:
					{
						LCD_Show_Flag = 101;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			
			
			case 113://ͨ��3״̬
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 143;
						key =0;
						break;
					}

					case DOWN:
					{
						LCD_Show_Flag = 114;
						key = 0;
						break;
					}
					
					case UP:
					{
						LCD_Show_Flag = 112;
						key = 0;
						break;
					}
					case RIGHT:
					{
						LCD_Show_Flag = 114;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 101;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			
			
			case 114://ͨ��4״̬
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 144;
						key =0;
						break;
					}

					case DOWN:
					{
						LCD_Show_Flag = 115;
						key = 0;
						break;
					}
					
					case UP:
					{
						LCD_Show_Flag = 113;
						key = 0;
						break;
					}
					case LEFT:
					{
						LCD_Show_Flag = 111;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 101;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			
			
			case 115://ͨ��5״̬
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 145;
						key =0;
						break;
					}

					case DOWN:
					{
						LCD_Show_Flag = 116;
						key = 0;
						break;
					}
					
					case UP:
					{
						LCD_Show_Flag = 114;
						key = 0;
						break;
					}
					case LEFT:
					{
						LCD_Show_Flag = 111;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 101;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			
			
			case 116://ͨ��6״̬
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 146;
						key =0;
						break;
					}

					case UP:
					{
						LCD_Show_Flag = 115;
						key = 0;
						break;
					}
					case LEFT:
					{
						LCD_Show_Flag = 111;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 101;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			
			case 62://ͨ��1
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 82;
						key = 0;
						break;
					}
					case RIGHT:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 63;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 100;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 63://ͨ��2
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 83;
						key = 0;
						break;
					}
					case RIGHT:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 62;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 64;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 100;
						key = 0;
						break;
					}					
					default: 
					{
						key = 0;	
						break;
					}
				}
			}	
			case 64://ͨ��3
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 84;
						key = 0;
						break;
					}
					case RIGHT:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 63;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 100;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}	
			case 65://ͨ��4
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 85;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 64;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 66;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 100;
						key = 0;
						break;
					}
					case LEFT:
					{
						LCD_Show_Flag = 62;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}	 
			case 66://ͨ��5
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 86;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 67;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 100;
						key = 0;
						break;
					}
					case LEFT:
					{
						LCD_Show_Flag = 62;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}	
			case 67://ͨ��6
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 87;
						key = 0;
						break;
					}
				
					case UP:
					{
						LCD_Show_Flag = 66;
						key = 0;
						break;
					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 65;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 100;
						key = 0;
						break;
					}
					case LEFT:
					{
						LCD_Show_Flag = 62;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 82://У׼ͨ��1	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 62;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
					case DOWN:
					{
						LCD_Show_Flag = 63;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 62;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 83://У׼ͨ��2	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 63;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 62;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 64;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 63;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}	
			case 84://У׼ͨ��3	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 64;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 63;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 64;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}	
			case 85://У׼ͨ��4	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 64;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 66;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}	
			case 86://У׼ͨ��5	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 66;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 65;
						key = 0;
						break;
					}
					case DOWN:
					{
						LCD_Show_Flag = 67;
						key = 0;
						break;
					}
					case BACK:
					{
						LCD_Show_Flag = 66;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}	
			case 87://У׼ͨ��6	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 67;
						key = 0;
						break;
					}
					case UP:
					{
						LCD_Show_Flag = 66;
						key = 0;
						break;
					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 67;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 130://ȫ��
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 102;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 102;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 131://ȫ��	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 103;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 103;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 141://����1	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 111;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 111;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 142://����2
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 112;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 112;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 143://����3	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 113;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 113;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 144://����4
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 114;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 114;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 145://����5	
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 115;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 115;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
			case 146://����6
			{
				switch (key)
				{
					case ENTER:
					{
						LCD_Show_Flag = 116;
						key = 0;
						break;
					}
//					case UP:
//					{
//						LCD_Show_Flag = 66;
//						key = 0;
//						break;
//					}
//					case DOWN:
//					{
//						LCD_Show_Flag = 64;
//						key = 0;
//						break;
//					}
					case BACK:
					{
						LCD_Show_Flag = 116;
						key = 0;
						break;
					}
					default: 
					{
						key = 0;	
						break;
					}
				}
			}
//			case 151://
//			{
//				switch (key)
//				{
//					case ENTER:
//					{
//						LCD_Show_Flag = 111;
//						key = 0;
//						break;
//					}
////					case UP:
////					{
////						LCD_Show_Flag = 66;
////						key = 0;
////						break;
////					}
////					case DOWN:
////					{
////						LCD_Show_Flag = 64;
////						key = 0;
////						break;
////					}
//					case BACK:
//					{
//						LCD_Show_Flag = 111;
//						key = 0;
//						break;
//					}
//					default: 
//					{
//						key = 0;	
//						break;
//					}
//				}
//			}
//			case 152://
//			{
//				switch (key)
//				{
//					case ENTER:
//					{
//						LCD_Show_Flag = 112;
//						key = 0;
//						break;
//					}
////					case UP:
////					{
////						LCD_Show_Flag = 66;
////						key = 0;
////						break;
////					}
////					case DOWN:
////					{
////						LCD_Show_Flag = 64;
////						key = 0;
////						break;
////					}
//					case BACK:
//					{
//						LCD_Show_Flag = 112;
//						key = 0;
//						break;
//					}
//					default: 
//					{
//						key = 0;	
//						break;
//					}
//				}
//			}
			
			default: 
			{
				key = 0;	
				break;
			}
		}
	}
}
/*--------------------------------THE END--------------------------------------------*/
