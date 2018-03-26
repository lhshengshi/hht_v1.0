#include "User_BSP.h"
#include "Heard_Public.h"
#include "stm32f10x.h"
#include "sys.h" 
#include "CN3153.h"


							    
//按键初始化函数
void CN3153_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能GPIOB端口时钟

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 //根据参数初始化GPIOB.8
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 //根据参数初始化GPIOB.8
}

//按键处理  KOK=1 短按     KOK=2 长按
//void start()
//{
//	uint8_t i=0;
//	 if(ON_OFF_KEY==0)//按键引起的开机
//	 {
//	 while(1)
//		 {
//			Delay_ms(200);
//			if(ON_OFF_KEY==0)//按键引起的开机
//			i++;
//			else i = 0;
//			if(i>6)//3秒钟之后
//			{
//				BEEP_500MS();
//				PWR_1;//保持开机状态
//				//显示开机LOGO
//				while(ON_OFF_KEY==0);
//				KOK=0;
//				break;
//			}
////					 else
////					 {
////					    if(ON_OFF_KEY!=0) i=0;//按键时间小于3秒
////					 }
//		 }
//	 }
//	 else//充电引起的开机
//	 {
//		 i=0;
//		  while(1)
//		 {
//			Delay_ms(200);
//	//				   刷新充电界面
//	//				   cd();
//	//				   LED_0;
//			if(ON_OFF_KEY==0)//按键按下
//			 {
//			   if(++i>6)//3秒钟之后
//				 {
//					PWR_1;//保持开机状态  
//	//                          显示开机LOGO
//	//						    LED_1;
//					BEEP_500MS();
//					while(ON_OFF_KEY==0)
//					{

//					}
//					KOK=0;
//					KCnt=0;
//					break;
//				 }
//			 }
//			 else //按键抬起就要重新计时
//			 {
//				i=0;				 
//			 }
//		 }
//	 }
//}

//	//关机操作
//	void Stop()
//	{
//	uint8_t i=0;
//	BEEP_500MS();
//	 Delay_ms(50);
//	 BEEP_500MS();
//	 if((BATC==0)|(BATM==0))//充电状态
//	 {
////	     clear_screen();
//		   PWR_0;
//		   while(1)//充电状态关机后进入充电界面
//			 {
//					 Delay_ms(200);
//				   //刷新充电界
////				   cd();
////				   LED_0;
//				   if(ON_OFF_KEY==0)//按键按下
//					 {
//						if(++i>6)//3秒钟之后
//						{
//							PWR_1;//保持开机状态 
////							显示开机LOGO
////							 LED_1;
//							 BEEP_500MS();
//							 while(ON_OFF_KEY==0); 
//							 KOK=0;
//							 KCnt=0;
//							 break;
//						}		
//					 }
//					 else //按键抬起就要重新计时
//					 {
//						i=0;				 
//					 }
//			 }
//	 }
//	 else //非充电状态直接关机
//	 {
//			 //关机LOGO
//		   PWR_0;
//		   while(1);
//	 }
//}
