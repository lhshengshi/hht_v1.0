/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
                   ARM Cortex-M3 Port
* 文件名    : BSP_USART1.c
* 描  述    : 
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
* 备 注     : Bug1.Usart1映射到PB6.7上串口接收到数据，不知道什么原因。
*******************************************************************************/
/* Includes---------------------------------------------*/
 #include "Usart2_Dirver.h"
 #include "Heard_Public.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/

Communtion_TypeDef Comm_USART2;
//uint8_t Usart2_Rece_Flag=0; 
//uint8_t Usart2_SendBuff[Comm_Que];
//uint8_t Usart2_ReceBuff[Comm_Que];
//uint8_t Usart2_Rece_Count=0; 
//uint16_t Usart2_Rece_Len=0; 
//uint32_t Usart2_Rece_Time=0; //通讯过程中计时，
//uint32_t Usart2_Comm_Time=0; //没有通讯计时，用于通讯判断
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/

void USART2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//485控制
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* config USART2 clock */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	
	/* Configure USART2 Rx (PA.03) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure USART2 Tx (PA.02) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
			
		/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = Usart2_BaudRate ;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure); 
		
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
		 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART2, ENABLE);                    //使能串口 		
	}

#if 1
/**********************************************
*	函 数 名: USART_IRQHandler(void)
*	形    参：
*	返 回 值: 
*	功能说明: USART中断函数		
**********************************************/ 

void USART2_IRQHandler(void)
{
  uint8_t Res = 0;
	uint32_t Tmp_Comm=0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		Res = Res;
		Tmp_Comm=Tmp_Comm;
//		if(Comm_USART2.Rece_Flag == 0)
//		{
//			Comm_USART2.Rece_Time = 0;//清除故障计时
//			if(Comm_USART2.Rece_Count == 0)
//			{
//				if(Res == 0xfa)
//				{
//					Comm_USART2.ReceBuff[Comm_USART2.Rece_Count] = Res;
//					Comm_USART2.Rece_Count ++;
//					}
//				else
//				{
//					Comm_USART2.Rece_Count = 0;
//					}
//				}
//			else
//			if(Comm_USART2.Rece_Count == 1)
//			{
//				if(Res == 0xf5)
//				{
//					Comm_USART2.ReceBuff[Comm_USART2.Rece_Count] = Res;
//					Comm_USART2.Rece_Count ++;
//					}
//				else
//				{
//					Comm_USART2.Rece_Count = 0;
//					}
//				}
//			else
//			if(Comm_USART2.Rece_Count == 2)
//			{
//				Comm_USART2.ReceBuff[Comm_USART2.Rece_Count] = Res;
//				Comm_USART2.Rece_Count ++;
//				}
//			else
//			if(Comm_USART2.Rece_Count == 3)
//			{
//				Comm_USART2.ReceBuff[Comm_USART2.Rece_Count] = Res;
//				Tmp_Comm = (Comm_USART2.ReceBuff[Comm_USART2.Rece_Count-1]<<8)+Comm_USART2.ReceBuff[Comm_USART2.Rece_Count];
//				if(Tmp_Comm>Comm_Rece_Que)
//				{
//					Comm_USART2.Rece_Count = 0;
//					}
//				else
//				{
//					Comm_USART2.Rece_Len = (Comm_USART2.ReceBuff[2]<<8)+Comm_USART2.ReceBuff[3];
//					Comm_USART2.Rece_Count ++;
//					}
//				}
//			else
//			if(Comm_USART2.Rece_Count == 4)
//			{
//				Comm_USART2.ReceBuff[Comm_USART2.Rece_Count] = Res;
//				Comm_USART2.Rece_Count ++;
//				}
//			else
//			if(Comm_USART2.Rece_Count == 5)
//			{
//				Comm_USART2.ReceBuff[Comm_USART2.Rece_Count] = Res;
//				Tmp_Comm = (Comm_USART2.ReceBuff[Comm_USART2.Rece_Count-1]<<8)+Comm_USART2.ReceBuff[Comm_USART2.Rece_Count];
//				if((Tmp_Comm == Fixed_Addr)||(Tmp_Comm == 0)||(Tmp_Comm == Addr_Value))
//				{
//					Comm_USART2.Rece_Count ++;
//					}
//				else
//				{
//					Comm_USART2.Rece_Count = 0;
//					Comm_USART2.Rece_Len = 0;
//					}
//				}
//			else
//			{
//				Comm_USART2.ReceBuff[Comm_USART2.Rece_Count] = Res;
//				Comm_USART2.Rece_Count ++;
//				if(Comm_USART2.Rece_Count>=(Comm_USART2.Rece_Len+5))
//				{
//					Comm_USART2.Rece_Flag = 1;
//					Comm_USART2.Rece_Count = 0;
//					}
//				}
//			}
		}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE );
	}
void Usart2_Init(void)
{
	uint8_t i;
	for(i=0;i<Comm_Que;i++)
	{
		Comm_USART2.SendBuff[i] = 0xff;
		}
	RS485_Rece();
	}

void Usart2_Send(uint8_t Len)
{
	uint8_t i;
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	for(i=0;i<Len;i++)
	{
		USART_SendData(USART2, Comm_USART2.SendBuff[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		}
	}
/*
uint8_t Get_Information2(uint8_t *Buff_IN,uint8_t *Buff_OUT)
{
	uint16_t Length_IN=0;
	uint16_t Tmp_Inform=0;
	uint8_t Length_OUT = 0;
	uint8_t Err_Dat=0;
	Length_IN = (Buff_IN[2]<<8)+Buff_IN[3]+4;
	if(XORValid(Buff_IN,Length_IN) == Buff_IN[Length_IN])//判断校验值
	{
		Tmp_Inform = (Buff_IN[4]<<8)+Buff_IN[5];
		if((Tmp_Inform == Addr_Value)||(Tmp_Inform == Fixed_Addr))//判断地址
		{
			if(Buff_IN[6]==0xa0)//读命令
			{
				switch(Buff_IN[7])
				{
					case 0://握手命令
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 4;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 1://查询命令
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 26;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						if(((System_State_Flag>>3)&0x01) == 0x01)//温度故障
						{
							Buff_OUT[8] = 5;
							Buff_OUT[9] = 0xff;//故障时全部为0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>8)&0x01) == 0x01)//超高温报警
							{
								Buff_OUT[8] = 1;
								}
							else
							if(((System_State_Flag>>9)&0x01) == 0x01)//超低温报警
							{
								Buff_OUT[8] = 3;
								}
							else
							{
								Buff_OUT[8] = 0;
								}
							Buff_OUT[9] = Temperture_Now.Sign;//故障时全部为0xff
							Buff_OUT[10] = Temperture_Now.Value/10;
							Buff_OUT[11] = Temperture_Now.Value%10;		
							}
						if(((System_State_Flag>>4)&0x01) == 0x01)//湿度故障
						{
							Buff_OUT[12] = 5;
							Buff_OUT[13] = 0xff;//故障时全部为0xff
							Buff_OUT[14] = 0xff;
							Buff_OUT[15] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>10)&0x01) == 0x01)//超湿报警
							{
								Buff_OUT[12] = 1;
								}
							else
							if(((System_State_Flag>>11)&0x01) == 0x01)//超干报警
							{
								Buff_OUT[12] = 3;
								}
							else
							{
								Buff_OUT[12] = 0;
								}
							Buff_OUT[13] = 0xff;//故障时全部为0xff
							Buff_OUT[14] = 0xff;
							Buff_OUT[15] = Humidity_Now/10;		
							}
						if(((System_State_Flag>>5)&0x01) == 0x01)//浸水故障
						{
							Buff_OUT[16] = 5;
							Buff_OUT[17] = 0xff;//故障时全部为0xff
							Buff_OUT[18] = 0xff;
							Buff_OUT[19] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>12)&0x01) == 0x01)//浸水报警
							{
								Buff_OUT[16] = 1;
								}
							else
							{
								Buff_OUT[16] = 0;
								}

							Buff_OUT[17] = 0xff;//故障时全部为0xff
							Buff_OUT[18] = 0xff;
							Buff_OUT[19] = 0xff;		
							}
						if(((Out_state>>8)&0x01) == 0x01)//高温报警开关
						{
							Buff_OUT[20] = 1;
							Buff_OUT[21] = 0xff;
							}
						else
						{
							Buff_OUT[20] = 0;
							Buff_OUT[21] = 0xff;
							}
						if(((Out_state>>9)&0x01) == 0x01)//低温报警开关
						{
							Buff_OUT[22] = 1;
							Buff_OUT[23] = 0xff;
							}
						else
						{
							Buff_OUT[22] = 0;
							Buff_OUT[23] = 0xff;
							}
						if(((Out_state>>10)&0x01) == 0x01)//超湿报警开关
						{
							Buff_OUT[24] = 1;
							Buff_OUT[25] = 0xff;
							}
						else
						{
							Buff_OUT[24] = 0;
							Buff_OUT[25] = 0xff;
							}
						if(((Out_state>>11)&0x01) == 0x01)//超干报警开关
						{
							Buff_OUT[26] = 1;
							Buff_OUT[27] = 0xff;
							}
						else
						{
							Buff_OUT[26] = 0;
							Buff_OUT[27] = 0xff;
							}
						if(((Out_state>>12)&0x01) == 0x01)//浸水报警开关
						{
							Buff_OUT[28] = 1;
							Buff_OUT[29] = 0xff;
							}
						else
						{
							Buff_OUT[28] = 0;
							Buff_OUT[29] = 0xff;
							}
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 2://查询当前设定值
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 24;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						Buff_OUT[8] = 0xff;													//超高温报警信息
						Buff_OUT[9] = Temperture_Set_High.Sign;
						Buff_OUT[10] = Temperture_Set_High.Value/10;
						Buff_OUT[11] = Temperture_Set_High.Value%10;
						Buff_OUT[12] = 0xff;												//超低温报警信息
						Buff_OUT[13] = Temperture_Set_Low.Sign;
						Buff_OUT[14] = Temperture_Set_Low.Value/10;
						Buff_OUT[15] = Temperture_Set_Low.Value%10;
						Buff_OUT[16] = 0xff;												//超湿报警信息
						Buff_OUT[17] = 0xff;
						Buff_OUT[18] = 0xff;
						Buff_OUT[19] = Humidity_Set_High/10;
						Buff_OUT[20] = 0xff;												//超干报警信息
						Buff_OUT[21] = 0xff;
						Buff_OUT[22] = 0xff;
						Buff_OUT[23] = Humidity_Set_Low/10;
						Buff_OUT[24] = 0xff;												//浸水报警信息
						Buff_OUT[25] = 0xff;
						Buff_OUT[26] = 0xff;
						Buff_OUT[27] = 0xff;						
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 3://查询温度信息
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 20;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						if(((System_State_Flag>>3)&0x01) == 0x01)//温度故障
						{
							Buff_OUT[8] = 5;
							Buff_OUT[9] = 0xff;//故障时全部为0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>8)&0x01) == 0x01)//超高温报警
							{
								Buff_OUT[8] = 1;
								}
							else
							if(((System_State_Flag>>9)&0x01) == 0x01)//超低温报警
							{
								Buff_OUT[8] = 3;
								}
							else
							{
								Buff_OUT[8] = 0;
								}
							Buff_OUT[9] = Temperture_Now.Sign;//故障时全部为0xff
							Buff_OUT[10] = Temperture_Now.Value/10;
							Buff_OUT[11] = Temperture_Now.Value%10;		
							}					
						if(((Out_state>>8)&0x01) == 0x01)//高温报警开关
						{
							Buff_OUT[12] = 1;
							Buff_OUT[13] = 0xff;
							}
						else
						{
							Buff_OUT[12] = 0;
							Buff_OUT[13] = 0xff;
							}
						if(((Out_state>>9)&0x01) == 0x01)//低温报警开关
						{
							Buff_OUT[14] = 1;
							Buff_OUT[15] = 0xff;
							}
						else
						{
							Buff_OUT[14] = 0;
							Buff_OUT[15] = 0xff;
							}
						Buff_OUT[16] = 0xff;													//超高温报警信息
						Buff_OUT[17] = Temperture_Set_High.Sign;
						Buff_OUT[18] = Temperture_Set_High.Value/10;
						Buff_OUT[19] = Temperture_Set_High.Value%10;
						Buff_OUT[20] = 0xff;												//超低温报警信息
						Buff_OUT[21] = Temperture_Set_Low.Sign;
						Buff_OUT[22] = Temperture_Set_Low.Value/10;
						Buff_OUT[23] = Temperture_Set_Low.Value%10;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 4://查询湿度信息
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 20;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						if(((System_State_Flag>>4)&0x01) == 0x01)//湿度故障
						{
							Buff_OUT[8] = 5;
							Buff_OUT[9] = 0xff;//故障时全部为0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>10)&0x01) == 0x01)//超湿报警
							{
								Buff_OUT[8] = 1;
								}
							else
							if(((System_State_Flag>>11)&0x01) == 0x01)//超干报警
							{
								Buff_OUT[8] = 3;
								}
							else
							{
								Buff_OUT[8] = 0;
								}
							Buff_OUT[9] = 0xff;//故障时全部为0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = Humidity_Now/10;		
							}
						if(((Out_state>>10)&0x01) == 0x01)//超湿报警开关
						{
							Buff_OUT[12] = 1;
							Buff_OUT[13] = 0xff;
							}
						else
						{
							Buff_OUT[12] = 0;
							Buff_OUT[13] = 0xff;
							}
						if(((Out_state>>11)&0x01) == 0x01)//超干报警开关
						{
							Buff_OUT[14] = 1;
							Buff_OUT[15] = 0xff;
							}
						else
						{
							Buff_OUT[14] = 0;
							Buff_OUT[15] = 0xff;
							}
						Buff_OUT[16] = 0xff;												//超湿报警信息
						Buff_OUT[17] = 0xff;
						Buff_OUT[18] = 0xff;
						Buff_OUT[19] = Humidity_Set_High/10;
						Buff_OUT[20] = 0xff;												//超干报警信息
						Buff_OUT[21] = 0xff;
						Buff_OUT[22] = 0xff;
						Buff_OUT[23] = Humidity_Set_Low/10;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 5://查询浸水信息
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 16;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						if(((System_State_Flag>>5)&0x01) == 0x01)//浸水故障
						{
							Buff_OUT[8] = 5;
							Buff_OUT[9] = 0xff;//故障时全部为0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>12)&0x01) == 0x01)//浸水报警
							{
								Buff_OUT[8] = 1;
								}
							else
							{
								Buff_OUT[8] = 0;
								}

							Buff_OUT[9] = 0xff;//故障时全部为0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;		
							}	
						if(((Out_state>>12)&0x01) == 0x01)//浸水报警开关
						{
							Buff_OUT[12] = 1;
							Buff_OUT[13] = 0xff;
							}
						else
						{
							Buff_OUT[12] = 0;
							Buff_OUT[13] = 0xff;
							}
						Buff_OUT[14] = 0xff;
						Buff_OUT[15] = 0xff;
						Buff_OUT[16] = 0xff;
						Buff_OUT[17] = 0xff;
						Buff_OUT[18] = 0xff;
						Buff_OUT[19] = 0xff;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 6://查询本机固定编码
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 10;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						Buff_OUT[8] = Fixed_Addr/256;
						Buff_OUT[9] = Fixed_Addr%256;
						Buff_OUT[10] = (Lock_Code>>24)&0x0ff;
						Buff_OUT[11] = (Lock_Code>>16)&0x0ff;
						Buff_OUT[12] = (Lock_Code>>8)&0x0ff;
						Buff_OUT[13] = Lock_Code&0x0ff;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 7://查询模块开机次数
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 6;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						Buff_OUT[8] = Start_Count/256;
						Buff_OUT[9] = Start_Count%256;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					default : break; 
					}
				}
			else
			if(Buff_IN[6]==0xa1)//写命令
			{
				switch(Buff_IN[7])
				{
					case 0:																										//复位命令
					{
						Err_Dat = 0xaa;
						if(((System_State_Flag>>1)&0x01) == 0x01)//正在执行，不可重复执行
						{
							Err_Dat = 0x55;
							}
						System_State_Flag |= (1<<1);
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 6;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						Buff_OUT[8] = Err_Dat;
						Buff_OUT[9] = 0xff;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 1:																									//设定报警值
					{
						Err_Dat = 0xaa;
						Tmp_Inform = 0;
						Tmp_Inform = Buff_IN[8]*10;
//						Temperture_Set_High.Value = Tmp_Inform+Buff_IN[9];
						Tmp_Inform = Tmp_Inform+Buff_IN[9];
						if((Tmp_Inform>Temperture_High_Max)||(Tmp_Inform<=Temperture_High_Min))
						{
							Err_Dat = 0x55;
							}
						else
						{
							Temperture_Set_High.Sign = 0;
							Temperture_Set_High.Value = Tmp_Inform;
							Charge_flag |= (1<<1);						//更新数据
							}
						if(Err_Dat == 0x55){;}
						else
						{
							Tmp_Inform = 0;
							if(Buff_IN[12]>1)  //符号位仅允许0和1
							{
								Err_Dat = 0x55;
								}
							else
							{;}
							}
						if(Err_Dat == 0x55){;}
						else
						{
							Tmp_Inform = Buff_IN[13]*10;
							Tmp_Inform = Tmp_Inform+Buff_IN[14];
							if(Buff_IN[12] == 0)
							{
								if(Tmp_Inform >= Temperture_Set_High.Value)
								{
									Err_Dat = 0x55;
									}
								else
								{
									Temperture_Set_Low.Sign = Buff_IN[12];
									Temperture_Set_Low.Value = Tmp_Inform;
									}
								}
							else
							{
								if(Tmp_Inform>Temperture_Low_Max)
								{
									Err_Dat = 0x55;
									}
								else
								{
									Temperture_Set_Low.Sign = Buff_IN[12];
									Temperture_Set_Low.Value = Tmp_Inform;
									Charge_flag |= (1<<2);						//更新数据
									}
								}
							}
						if(Err_Dat == 0x55){;}
						else
						{
							Tmp_Inform = Buff_IN[18]*10;
							if((Tmp_Inform>1000)||(Tmp_Inform<=200))
							{
								Err_Dat = 0x55;
								}
							else
							{
								Humidity_Set_High = Tmp_Inform;
								Charge_flag |= (1<<3);						//更新数据
								}
							}
						if(Err_Dat == 0x55){;}
						else
						{
							Tmp_Inform = Buff_IN[20]*10;
							if((Tmp_Inform>=600)||(Tmp_Inform>=Humidity_Set_High)||(Tmp_Inform == 0))
							{
								if(Err_Dat == 0x55){;}
								else							 {Err_Dat = 0x55;}
								}
							else
							{
								Humidity_Set_Low = Tmp_Inform;
								Charge_flag |= (1<<4);						//更新数据
								}
							}
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 6;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						Buff_OUT[8] = Err_Dat;
						Buff_OUT[9] = 0xff;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 2:																									//控制报警开关，仅在故障和无报警时起作用，如果报警则返回错误
					{
						Err_Dat = 0xaa;
						if(Buff_IN[8]>1)
						{
							Err_Dat = 0x55;
							}
						else
						{
							if(Buff_IN[8]==1)//控制高温开关闭合，需要判断是否报警
							{
								if(((System_State_Flag>>8)&0x01) == 0x01)
								{
									Err_Dat = 0x55;
									}
								else
								{
									Switch_Contorl |= (1<<0);
									}
								}
							else
							{
								Switch_Contorl &= ~(1<<0);
								}
							}

						if(Err_Dat == 0x55){;}
						else
						{
							if(Buff_IN[10]>1)
							{
								Err_Dat = 0x55;
								}
							else
							{
								if(Buff_IN[10]==1)//控制低温开关闭合，需要判断是否报警
								{
									if(((System_State_Flag>>9)&0x01) == 0x01)
									{
										Err_Dat = 0x55;
										}
									else
									{
										Switch_Contorl |= (1<<2);
										}
									}
								else
								{
									Switch_Contorl &= ~(1<<2);
									}
								}
							}
						if(Err_Dat == 0x55){;}
						else
						{
							if(Buff_IN[12]>1)
							{
								Err_Dat = 0x55;
								}
							else
							{								
								if(Buff_IN[12]==1)//控制超湿开关闭合，需要判断是否报警
								{
									if(((System_State_Flag>>10)&0x01) == 0x01)
									{
										Err_Dat = 0x55;
										}
									else
									{
										Switch_Contorl |= (1<<4);
										}
									}
								else
								{
									Switch_Contorl &= ~(1<<4);
									}
								}
							}
						if(Err_Dat == 0x55){;}
						else
						{
							if(Buff_IN[14]>1)
							{
								Err_Dat = 0x55;
								}
							else
							{
								if(Buff_IN[14]==1)//控制超湿开关闭合，需要判断是否报警
								{
									if(((System_State_Flag>>11)&0x01) == 0x01)
									{
										Err_Dat = 0x55;
										}
									else
									{
										Switch_Contorl |= (1<<6);
										}
									}
								else
								{
									Switch_Contorl &= ~(1<<6);
									}
								}
							}
						if(Err_Dat == 0x55){;}
						else
						{
							if(Buff_IN[16]>1)
							{
								Err_Dat = 0x55;
								}
							else
							{
								if(Buff_IN[16]==1)//控制超湿开关闭合，需要判断是否报警
								{
									if(((System_State_Flag>>12)&0x01) == 0x01)
									{
										Err_Dat = 0x55;
										}
									else
									{
										Switch_Contorl |= (1<<8);
										}
									}
								else
								if(Buff_IN[16]==0)
								{
									Switch_Contorl &= ~(1<<8);
									}
								else
								{
									Err_Dat = 0x55;
									}
								}
							}
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 6;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						Buff_OUT[8] = Err_Dat;
						Buff_OUT[9] = 0xff;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					default : break;
					}
				
				}
			else//其他命令不返回
			{
				Length_OUT = 0;
				}
			}
		else
		{
			Length_OUT = 0;
			}
		}
	else
	{
		Length_OUT = 0;
		}
	return(Length_OUT);
	}*/
#endif 


/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/

