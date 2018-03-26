#include "TIM3_Dirver.h"
#include "Heard_Public.h"
#include "User_BSP.h"
//////////////////////////////////////////////////////////////////////////////////   	 

//bit0：温湿度
//bit1:浸水+拨码开关

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
//arr = 9,psc = 7999 设定时间 = 1ms
//arr = 9999,psc = 7999 设定时间 = 1s
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //使能指定的TIM3中断,允许更新中断
	
	//中断优先级NVIC设置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级4级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
	}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		if(Run_Tim3_Flag>3000)
		{
			Run_Tim3_Flag =0;
			}
		else
		{
			Run_Tim3_Flag ++;
		}
		
		if(LCD_Update_Flag>=4000)
		{
			LCD_Update_Flag = 4000;
		}
		else
		{
			LCD_Update_Flag ++;
		}
 
		if(LCD_Power_Update_Flag>=4000)
		{
			LCD_Power_Update_Flag = 4000;
		}
		else
		{
			LCD_Power_Update_Flag ++;
		}
		
		if(LCD_Twinkle_Flag1>=1000)
		{
			LCD_Twinkle_Flag1 = 1000;
		}
		else
		{
			LCD_Twinkle_Flag1 ++;
		}
		
		if(LCD_Twinkle_Flag2>=1000)
		{
			LCD_Twinkle_Flag2 = 1000;
		}
		else
		{
			LCD_Twinkle_Flag2 ++;
		}
//		if(System_Flag == 0)//开机状态
//		{
//			if(Run_Tim3_Flag >= 3000)//2S后开机运行
//			{
//				System_Flag = 1;
////				System_State_Flag |= 0x01;
//				}	
//			else 
//			{
////				System_State_Flag = 0;
//				}
//			}
//		if((Run_Tim3_Flag !=0)&&(Run_Tim3_Flag%100)==0)//浸水和拨码开关，100ms更新一次
//		{
//			if(((Data_Read_Flag>>1)&0x01)==0x01)	{;}
//			else
//			{
//				Data_Read_Flag |= (1<<1); 
//				}
//			}
		
		if(((zhiling == 0)||(zhiling == 6))&&(Task == LunXun))
		{
			ZL_Time ++;
			if(ZL_Time>500)
			{
				ZL_Time = 0;
				zhiling = 5;
			}
//			else if((zhiling == 6)&&(Task == LunXun))
//			{
//				ZL_Time ++;
//				if(ZL_Time>500)
//				{
//					ZL_Time = 0;
//					zhiling = 5;
//				}
//			}		
		}
		else if (Task == CaoZuo)
		{
			ZL_Time = 0;
			zhiling = 0;
		}
		if((Run_Tim3_Flag !=0)&&(Run_Tim3_Flag%500)==0)//温湿度数据每500ms读一次数据
		{
			tempnumber++;
		}
		if((Run_Tim3_Flag !=0)&&(Run_Tim3_Flag%500)==0)//温湿度数据每500ms读一次数据
		{
			if(((Data_Read_Flag>>0)&0x01)==0x01)
			{;}
			else
			{
				Data_Read_Flag |= (1<<0); 
			}
		}
		if(Usart3_Rece_Count !=0 )//通讯过程中超时判断，在接收中断中清除计时
		{
			Usart3_Rece_Time ++;
			if(Usart3_Rece_Time > 1000)
			{
				//LD3_OFF();
				Usart3_Rece_Time ++;
				Usart3_Rece_Count = 0;
				Comm3_Err_Flag = 1;
			}
		}
		else
		{
			if(Usart3_Rece_Flag == 1)
			{
				Usart3_Rece_Time = 0;
			}
		}
			
//		if(Tx_Flag==1)//串口三已经send标志位
//		{
//			Comm3_Overtime_Flag ++;
//			if(Comm3_Overtime_Flag >= Comm3_Err_Max)
//			{
//				Comm3_Overtime_Flag = Comm3_Err_Max;
//				Usart3_Rece_Count = 0;
//				Usart3_Rece_Flag = 0;
//				Comm3_Err_Flag = 1;
//				System_State_Flag |= (1<<3);
//				}
//			}
//		else
//		{
//			if(Usart3_Rece_Flag == 1)
//			{
//				Comm3_Err_Flag = 0;
//				Comm3_Overtime_Flag=0;
//				System_State_Flag &= ~(1<<3);
//				}
//			}
//		
//		if(Comm_USART1.Rece_Count !=0 )//通讯过程中超时判断，在接收中断中清除计时
//		{
//			Comm_USART1.Rece_Time ++;
//			if(Comm_USART1.Rece_Time >= 1000)
//			{
//				Comm_USART1.Rece_Time = 0;
//				Comm_USART1.Rece_Count = 0;
////				Comm1_Err_Flag = 1;
//			}
//		}
//		else
//		{;}
//		if(Comm_USART1.Rece_Time<1000)
//		{
//			Comm_USART1.Comm_Err_Flag = 0;
//		}
//		Comm_USART1.Comm_Time ++;
//		if(Comm_USART1.Comm_Time>=Comm_Err_Max)
//		{
//			Comm_USART1.Comm_Time = Comm_Err_Max;
//			Comm_USART1.Comm_Err_Flag = 1;
//		}
//		else
//		{
//			Comm_USART1.Comm_Err_Flag = 0;
//		}
//		if(Comm_USART2.Rece_Count !=0 )//通讯过程中超时判断，在接收中断中清除计时
//		{
//			Comm_USART2.Rece_Time ++;
//			if(Comm_USART2.Rece_Time >= 1000)
//			{
//				Comm_USART2.Rece_Time = 0;
//				Comm_USART2.Rece_Count = 0;
////				Comm1_Err_Flag = 1;
//			}
//		}
//		else
//		{;}
//		if(Comm_USART2.Rece_Time<1000)
//		{
//			Comm_USART2.Comm_Err_Flag = 0;
//		}
//		Comm_USART2.Comm_Time ++;
//		if(Comm_USART2.Comm_Time>=Comm_Err_Max)
//		{
//			Comm_USART2.Comm_Time = Comm_Err_Max;
//			Comm_USART2.Comm_Err_Flag = 1;
//		}
//		else
//		{
//			Comm_USART2.Comm_Err_Flag = 0;
//		}
	}
}












