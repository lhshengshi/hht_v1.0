/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
                   ARM Cortex-M3 Port
* 文件名    : BSP_Usart3.c
* 描  述    : 
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
* 备 注     : Bug1.Usart3映射到PB6.7上串口接收到数据，不知道什么原因。
*******************************************************************************/
/* Includes---------------------------------------------*/
 #include "Usart3_Dirver.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
 #include "Heard_Public.h"
 #include "User_BSP.h"
void Sys_Soft_Reset(void)
{  
	__set_FAULTMASK(1);      // 关闭所有中断
 //  SCB->AIRCR =0X05FA0000|(u32)0x04;  
	NVIC_SystemReset( );
}


uint8_t Usart3_Rece_Flag=0; 
uint8_t Usart3_SendBuff[Comm_Que];
uint8_t Usart3_ReceBuff[Comm_Rece_Que];
uint8_t Usart3_Rece_Count=0; 
uint8_t Usart3_Rece_Len=0; 
uint32_t Usart3_Rece_Time=0; 
uint16_t Comm3_Overtime_Count = 0;
uint16_t Comm3_Overtime_Flag = 0;
uint16_t Roll_Err_Count = 0;

uint8_t CH1_Statu = 0;
uint8_t CH2_Statu = 0;
uint8_t CH3_Statu = 0;
uint8_t CH4_Statu = 0;
uint8_t CH5_Statu = 0;
uint8_t CH6_Statu = 0;


uint8_t CAL_Power_CH1_Vol1 = 0;
uint8_t CAL_Power_CH1_Vol2 = 0;
uint8_t CAL_Power_CH1_Cur1 = 0;
uint8_t CAL_Power_CH1_Cur2 = 0;

uint8_t CAL_Power_CH2_Vol1 = 0;
uint8_t CAL_Power_CH2_Vol2 = 0;
uint8_t CAL_Power_CH2_Cur1 = 0;
uint8_t CAL_Power_CH2_Cur2 = 0;

uint8_t CAL_Power_CH3_Vol1 = 0;
uint8_t CAL_Power_CH3_Vol2 = 0;
uint8_t CAL_Power_CH3_Cur1 = 0;
uint8_t CAL_Power_CH3_Cur2 = 0;

uint8_t CAL_Power_CH4_Vol1 = 0;
uint8_t CAL_Power_CH4_Vol2 = 0;
uint8_t CAL_Power_CH4_Cur1 = 0;
uint8_t CAL_Power_CH4_Cur2 = 0;

uint8_t CAL_Power_CH5_Vol1 = 0;
uint8_t CAL_Power_CH5_Vol2 = 0;
uint8_t CAL_Power_CH5_Cur1 = 0;
uint8_t CAL_Power_CH5_Cur2 = 0;

uint8_t CAL_Power_CH6_Vol1 = 0;
uint8_t CAL_Power_CH6_Vol2 = 0;
uint8_t CAL_Power_CH6_Cur1 = 0;
uint8_t CAL_Power_CH6_Cur2 = 0;

uint16_t CAL_Power_CH1_Current = 0;
uint16_t CAL_Power_CH1_Voltage = 0;

uint16_t CAL_Power_CH2_Current = 0;
uint16_t CAL_Power_CH2_Voltage = 0;

uint16_t CAL_Power_CH3_Current = 0;
uint16_t CAL_Power_CH3_Voltage = 0;

uint16_t CAL_Power_CH4_Current = 0;
uint16_t CAL_Power_CH4_Voltage = 0;

uint16_t CAL_Power_CH5_Current = 0;
uint16_t CAL_Power_CH5_Voltage = 0;

uint16_t CAL_Power_CH6_Current = 0;
uint16_t CAL_Power_CH6_Voltage = 0;
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/


void USART3_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

	/* config Usart3 clock */
	//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	
	/* Configure USART3 Rx (PB.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART3 Tx (PB.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PB12端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10);//输出0	
	GPIO_SetBits(GPIOB,GPIO_Pin_11);//输出0	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//输出0
	/* Usart3 mode config */
	USART_InitStructure.USART_BaudRate = Usart3_BaudRate ;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure); 
		
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
		 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART3, ENABLE);                    //使能串口 		
	}

///**********************************************
//*	函 数 名: Usart3_IRQHandler(void)
//*	形    参：
//*	返 回 值: 
//*	功能说明: Usart3中断函数		
//**********************************************/ 
void USART3_IRQHandler(void)
{
    u8 Res = 0;
	uint32_t Tmp_Comm=0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res = USART_ReceiveData(USART3);//(Usart3->DR);	//读取接收到的数据
		if(Usart3_Rece_Flag == 0)
		{
			Usart3_Rece_Time = 0;//清除故障计时
//			Comm3_Overtime_Count = 0;
//			System_State_Flag &= ~(1<<3);
			if(Usart3_Rece_Count == 0)
			{
				if(Res == 0xfa)
				{
					Usart3_ReceBuff[Usart3_Rece_Count] = Res;
					Usart3_Rece_Count ++;
				}
				else
				{
					Usart3_Rece_Count = 0;
				}
			}
			else
			if(Usart3_Rece_Count == 1)
			{
				if(Res == 0xf5)
				{
					Usart3_ReceBuff[Usart3_Rece_Count] = Res;
					Usart3_Rece_Count ++;
				}
				else
				{
					Usart3_Rece_Count = 0;
				}
			}
   			else
			if(Usart3_Rece_Count == 2)
			{
				Usart3_ReceBuff[Usart3_Rece_Count] = Res;//长度高位
				Usart3_Rece_Count ++;
				}
			else
			if(Usart3_Rece_Count == 3)
			{
				Usart3_ReceBuff[Usart3_Rece_Count] = Res;//长度低位
				Tmp_Comm = (Usart3_ReceBuff[Usart3_Rece_Count - 1]<<8) + Usart3_ReceBuff[Usart3_Rece_Count];
				if(Tmp_Comm>Comm_Rece_Que)
				{
					Usart3_Rece_Count = 0;
					}
				else
				{
					Usart3_Rece_Len = (Usart3_ReceBuff[2]<<8)+Usart3_ReceBuff[3];
					Usart3_Rece_Count ++;
				}
			}
			else if (Usart3_Rece_Count == 4)
			{
				Usart3_ReceBuff[Usart3_Rece_Count] = Res;//地址高位
				Usart3_Rece_Count ++;
			}
			else if(Usart3_Rece_Count == 5)
			{
				Usart3_ReceBuff[Usart3_Rece_Count] = Res;//地址低位
				Tmp_Comm = (Usart3_ReceBuff[Usart3_Rece_Count - 1]<<8) + Usart3_ReceBuff[Usart3_Rece_Count];
				if((Tmp_Comm == Fixed_Addr)||(Tmp_Comm == 0)||(Tmp_Comm == Addr_Value))
				{
					Usart3_Rece_Count ++;
				}
				else
				{
					Usart3_Rece_Count = 0;
					Usart3_Rece_Len = 0;
				}
			}
			else
			{
				Usart3_ReceBuff[Usart3_Rece_Count] = Res;//数据
				Usart3_Rece_Count ++;
				if(Usart3_Rece_Count>=(Usart3_Rece_Len + 5))
				{
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 1;

				}
			}
		}
	}
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}

//void USART3_IRQHandler(void)                	//串口3中断服务程序
//{
//    u8 Res = Res;
//    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//    {
//        Res =USART_ReceiveData(USART3);//(USART1->DR);	//读取接收到的数据
//		if(Usart3_Rece_Count > Comm_Rece_Que)//数据溢出，默认接受失败
//		{
//		    Usart3_Rece_Count = FALSE ;
//			Usart3_Rece_Flag = FALSE;
//		}
//		if((Usart3_Rece_Count > FALSE)&&(Usart3_Rece_Flag != TRUE))
//		{
//			Usart3_ReceBuff[Usart3_Rece_Count++] =Res;	
//		}
//		else if((Usart3_Rece_Count == FALSE)&&(Res==(0x0a))&&(Usart3_Rece_Flag != TRUE))
//		{
//			Usart3_ReceBuff[Usart3_Rece_Count++] =Res;
//		}	
//    }
//    else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
//    {
//        USART3->SR;//先读SR，DR目的为了清除USART_IT_IDLE中断
//        USART3->DR;
////		RS485_RD(High);
//		Usart3_Rece_Count = FALSE;
//        Usart3_Rece_Flag = TRUE;
//    }
//}

void Usart3_Init(void)
{
	uint8_t i = 0;
	for(i=0;i<Comm_Que;i++)
	{
		Usart3_SendBuff[i] = 0xff;
		}
//	for(j=0;j<33;j++)
//	{
//		Localnet_Set_Outbuff[j] = 0xff;
//		}
//	for(k=0;k<21;k++)
//	{
//		Netserver_Set_Outbuff[k] = 0xff;
//		}
//	for(l=0;l<21;l++)
//	{
//		GPRSserver_Set_Outbuff[l] = 0xff;
//		}
}

void Usart3_Send(uint8_t *buf,uint8_t len)
{
	uint8_t t;	
	RS485_TX_EN=1;			//设置为发送模式
	Delay_ms(2);
	for(t=0;t<len;t++)		//循环发送数据
	{		   
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART3,buf[t]);
	}	 
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);		
	RS485_TX_EN=0;				//设置为接收模式	
	Delay_ms(2);
}

//-----------------------------------------------------------------------------
//异或校验
uint8_t XORValid(uint8_t *buffer,uint16_t Len)
{
    uint8_t checksum = 0;
//    uint8_t ch1,c1; //校验位的高四位和第四位
		uint8_t i;
//		uint16_t Len;
//		Len = (buffer[2]<<8)+buffer[3]+5;
    for (i = 0;  i<Len;  i++)
    {
        checksum = checksum ^ buffer[i]; //进行异或交验取值
			}
		return(checksum);

/*    ch1 = (checksum  >> 4) & 0x0F;  //取高位数；
    c1 = checksum & 0x0F;  //取低位数；

    if (ch1 < 10) //低于10的数
        ch1 = ch1  +  '0';
    else
        ch1 = (ch1 - 10 ) +  'A'; //不低于10的16进制数，如：A、B、C、D、E、F

    if (c1 < 10)
        c1 = c1  +  '0';
    else
        c1 = (c1 - 10 )+  'A';

    XOR_High=ch1;
    XOR_Low =c1;*/
}

void Fill_Information(void)
{
	uint8_t Length_IN = 0;
	uint16_t TimeConuter = 0;
	if((zhiling == 5)&&(Task == LunXun))
	{
		uint8_t j = 0;
		Usart3_Rece_Count = 0;
		Usart3_Rece_Flag = 0;
		for( j = 0 ; j < 9 ; j++ )
			{
				Usart3_SendBuff[j] = Request_Power_Module[j];//请求电源参数
			}
		Usart3_Send(Usart3_SendBuff,9);//发送
		for(TimeConuter = 100; TimeConuter > 0;TimeConuter --)
		{
			if(Usart3_Rece_Flag == 1)
			{
				Usart3_Power_Connect_Err_Flag = 0;
				Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
				if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
				{
					Comm3_Overtime_Count = 0;
					Comm3_Overtime_Flag = 0;
					if(Usart3_ReceBuff[7] == 0x01)
					{
						u8 len = 0;
//						for(len=0;len<Usart3_Rece_Len;len++)
						for(len=0;len<75;len++)
						{
							Power_Module_Status_Buff[len] = Usart3_ReceBuff[len];
						}

					   {
						CH1_Statu = Power_Module_Status_Buff[8];
						CAL_Power_CH1_Vol1 = Power_Module_Status_Buff[12];
						CAL_Power_CH1_Vol2 = Power_Module_Status_Buff[13];
						CAL_Power_CH1_Cur1 = Power_Module_Status_Buff[16];
						CAL_Power_CH1_Cur2 = Power_Module_Status_Buff[17];
						   
						CH2_Statu = Power_Module_Status_Buff[18];
						CAL_Power_CH2_Vol1 = Power_Module_Status_Buff[22];
						CAL_Power_CH2_Vol2 = Power_Module_Status_Buff[23];
						CAL_Power_CH2_Cur1 = Power_Module_Status_Buff[26];
						CAL_Power_CH2_Cur2 = Power_Module_Status_Buff[27];
						   
						CH3_Statu = Power_Module_Status_Buff[28];
						CAL_Power_CH3_Vol1 = Power_Module_Status_Buff[32];
						CAL_Power_CH3_Vol2 = Power_Module_Status_Buff[33];
						CAL_Power_CH3_Cur1 = Power_Module_Status_Buff[36];
						CAL_Power_CH3_Cur2 = Power_Module_Status_Buff[37];
						   
						CH4_Statu = Power_Module_Status_Buff[38];
						CAL_Power_CH4_Vol1 = Power_Module_Status_Buff[42];
						CAL_Power_CH4_Vol2 = Power_Module_Status_Buff[43];
						CAL_Power_CH4_Cur1 = Power_Module_Status_Buff[46];
						CAL_Power_CH4_Cur2 = Power_Module_Status_Buff[47];
						
						CH5_Statu = Power_Module_Status_Buff[48];   
						CAL_Power_CH5_Vol1 = Power_Module_Status_Buff[52];
						CAL_Power_CH5_Vol2 = Power_Module_Status_Buff[53];
						CAL_Power_CH5_Cur1 = Power_Module_Status_Buff[56];
						CAL_Power_CH5_Cur2 = Power_Module_Status_Buff[57];
						
						CH6_Statu = Power_Module_Status_Buff[58];
						CAL_Power_CH6_Vol1 = Power_Module_Status_Buff[62];
						CAL_Power_CH6_Vol2 = Power_Module_Status_Buff[63];
						CAL_Power_CH6_Cur1 = Power_Module_Status_Buff[66];
						CAL_Power_CH6_Cur2 = Power_Module_Status_Buff[67];}
					   
						CAL_Power_CH1_Current = ((CAL_Power_CH1_Cur1 <<8) + CAL_Power_CH1_Cur2);
						CAL_Power_CH1_Voltage = ((CAL_Power_CH1_Vol1 <<8) + CAL_Power_CH1_Vol2);

						CAL_Power_CH2_Current = ((CAL_Power_CH2_Cur1 <<8) + CAL_Power_CH2_Cur2);
						CAL_Power_CH2_Voltage = ((CAL_Power_CH2_Vol1 <<8) + CAL_Power_CH2_Vol2);

						CAL_Power_CH3_Current = ((CAL_Power_CH3_Cur1 <<8) + CAL_Power_CH3_Cur2);
						CAL_Power_CH3_Voltage = ((CAL_Power_CH3_Vol1 <<8) + CAL_Power_CH3_Vol2);

						CAL_Power_CH4_Current = ((CAL_Power_CH4_Cur1 <<8) + CAL_Power_CH4_Cur2);
						CAL_Power_CH4_Voltage = ((CAL_Power_CH4_Vol1 <<8) + CAL_Power_CH4_Vol2);

						CAL_Power_CH5_Current = ((CAL_Power_CH5_Cur1 <<8) + CAL_Power_CH5_Cur2);
						CAL_Power_CH5_Voltage = ((CAL_Power_CH5_Vol1 <<8) + CAL_Power_CH5_Vol2);

						CAL_Power_CH6_Current = ((CAL_Power_CH6_Cur1 <<8) + CAL_Power_CH6_Cur2);
						CAL_Power_CH6_Voltage = ((CAL_Power_CH6_Vol1 <<8) + CAL_Power_CH6_Vol2);
						
						Usart3_Rece_Count = 0;
						Usart3_Rece_Flag = 0;
						zhiling = 6;
						ZL_Time = 0;
						return ;
					}
					else 
					{
						Usart3_Rece_Count=0;
						Usart3_Rece_Flag = 0;
						zhiling=6;
						ZL_Time=0;
						return ;
					}
				}
				else 
				{
						Usart3_Rece_Count=0;
						Usart3_Rece_Flag = 0;
						zhiling=6;
						ZL_Time=0;
						return ;	
				}
			}
			else
			{
				Delay_ms(10);
			}
		}
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		zhiling=6;
		ZL_Time=0;
		Usart3_Power_Connect_Err_Flag = 1;
		if(Usart3_Power_Connect_Err_Flag == 1)
		{
			u8 len = 0;
			for(len=0;len<75;len++)
			{
				Power_Module_Status_Buff[len] = 0;
			}
		}
	}
	else
	{;}
}


