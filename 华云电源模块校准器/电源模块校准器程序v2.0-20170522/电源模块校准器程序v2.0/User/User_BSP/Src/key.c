#include "User_BSP.h"
#include "Heard_Public.h"
#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
						    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_15;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0设置成输入，默认上拉	  
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
//u8 KEY_Scan(u8 mode)
//{	
//	static u8 key_up=1;//按键按松开标志

//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
//	{
//		Delay_ms(10);//去抖动
//		key_up=0;
//		if(KEY0==0)return 17;
//		else if(KEY1==0)return 18;
//		else if(KEY2==0)return 19;
//		else if(KEY3==0)return 20;
//	}
//	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
// 	return 0;// 无按键按下
//}

//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//按键按松开标志
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
//	{
//		Delay_ms(10);//去抖动 
//		key_up=0;
//		if(KEY0==0)return 20;
//		else if(KEY1==0)return 19;
//		else if(KEY2==0)return 18;
//		else if(KEY3==0)return 17;
//	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
// 	return 0;// 无按键按下
//}
/*--------------------------------------------------------------------------------------* 矩阵键盘驱动
* 文 件: keyboard.c
* 编写人： 
* 描述： 扫描4x4 矩阵键盘输入，并返回键值
* 适用范围： 驱动采用ST3.5 库编写，适用于STM32F10x 系列单片机
* 所用引脚： PA0-PA7
* 编写时间： 2014 年5 月20 日
--------------------------------------------------------------------------------------*/

/*--------------------------------矩阵键盘初始化----------------------------------------* 功能： 初始化stm32 单片机GPIO //PA0-PA7
* 参数传递：
* 输入： 无
* 返回值：无
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
	u8 mode = 0                                        ; //mode = 0 ；不支持连按模式
	static u8 key_up=1;//key_up = 1 ；按键松开标志
	
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
//	key_up=0;  //支持连按
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
//	{
//		Delay_ms(10);//去抖动 
//		key_up=0;
//		if(KEY0==0)return 17;
//		else if(KEY1==0)return 18;
//		else if(KEY2==0)return 19;
//		else if(KEY3==0)return 20;
//	}
//	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 
//	return 0;
	/****************************************************************/
	
//		static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		Delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 20;
		else if(KEY1==0)return 19;
		else if(KEY2==0)return 18;
		else if(KEY3==0)return 17;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
 	return 0;// 无按键按下
//	if(mode)
//		key_up=1;  //支持连按
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
//	{
//		Delay_ms(10);//去抖动 
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
			case 102://全关
				
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
			case 103://全开
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
			case 111://通道一状态
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
			
			case 112://通道二状态
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
			
			
			case 113://通道3状态
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
			
			
			case 114://通道4状态
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
			
			
			case 115://通道5状态
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
			
			
			case 116://通道6状态
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
			
			case 62://通道1
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
			case 63://通道2
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
			case 64://通道3
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
			case 65://通道4
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
			case 66://通道5
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
			case 67://通道6
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
			case 82://校准通道1	
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
			case 83://校准通道2	
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
			case 84://校准通道3	
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
			case 85://校准通道4	
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
			case 86://校准通道5	
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
			case 87://校准通道6	
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
			case 130://全关
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
			case 131://全开	
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
			case 141://开关1	
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
			case 142://开关2
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
			case 143://开关3	
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
			case 144://开关4
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
			case 145://开关5	
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
			case 146://开关6
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
