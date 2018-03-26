#include "TIM3_Dirver.h"
#include "Heard_Public.h"
#include "User_BSP.h"
//////////////////////////////////////////////////////////////////////////////////   	 

//bit0����ʪ��
//bit1:��ˮ+���뿪��

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
//arr = 9,psc = 7999 �趨ʱ�� = 1ms
//arr = 9999,psc = 7999 �趨ʱ�� = 1s
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM3�ж�,��������ж�
	
	//�ж����ȼ�NVIC����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�4��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
	}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
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
//		if(System_Flag == 0)//����״̬
//		{
//			if(Run_Tim3_Flag >= 3000)//2S�󿪻�����
//			{
//				System_Flag = 1;
////				System_State_Flag |= 0x01;
//				}	
//			else 
//			{
////				System_State_Flag = 0;
//				}
//			}
//		if((Run_Tim3_Flag !=0)&&(Run_Tim3_Flag%100)==0)//��ˮ�Ͳ��뿪�أ�100ms����һ��
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
		if((Run_Tim3_Flag !=0)&&(Run_Tim3_Flag%500)==0)//��ʪ������ÿ500ms��һ������
		{
			tempnumber++;
		}
		if((Run_Tim3_Flag !=0)&&(Run_Tim3_Flag%500)==0)//��ʪ������ÿ500ms��һ������
		{
			if(((Data_Read_Flag>>0)&0x01)==0x01)
			{;}
			else
			{
				Data_Read_Flag |= (1<<0); 
			}
		}
		if(Usart3_Rece_Count !=0 )//ͨѶ�����г�ʱ�жϣ��ڽ����ж��������ʱ
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
			
//		if(Tx_Flag==1)//�������Ѿ�send��־λ
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
//		if(Comm_USART1.Rece_Count !=0 )//ͨѶ�����г�ʱ�жϣ��ڽ����ж��������ʱ
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
//		if(Comm_USART2.Rece_Count !=0 )//ͨѶ�����г�ʱ�жϣ��ڽ����ж��������ʱ
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












