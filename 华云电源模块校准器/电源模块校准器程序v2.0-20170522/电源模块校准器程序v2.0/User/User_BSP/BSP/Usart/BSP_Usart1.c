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
 #include "BSP_Usart1.h"
 #include "Heard_Public.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
#if USART1_Remap == TRUE   // 定义驱动CAN1的GPIO端口
		#define USART1_PIN_Rx        GPIO_Pin_7
		#define USART1_PIN_Tx        GPIO_Pin_6
		#define USART1_GPIO          GPIOB
		#define USART1_GPIO_CLK      RCC_APB2Periph_GPIOB
#else
		#define USART1_PIN_Rx        GPIO_Pin_10
		#define USART1_PIN_Tx        GPIO_Pin_9
		#define USART1_GPIO          GPIOA
		#define USART1_GPIO_CLK      RCC_APB2Periph_GPIOA
#endif
Communtion_TypeDef Comm_USART1;
/*
uint8_t Usart1_Rece_Flag=0; 
uint8_t Usart1_SendBuff[Comm_Que];
uint8_t Usart1_ReceBuff[Comm_Que];
uint8_t Usart1_Rece_Count=0; 
uint16_t Usart1_Rece_Len=0; 
uint32_t Usart1_Rece_Time=0; //通讯过程中计时，
uint32_t Usart1_Comm_Time=0; //没有通讯计时，用于通讯判断
*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/

/* Private functions -----------------------------------*/
/**
  * @brief  USART1 GPIO 配置,工作模式配置。9600 8-N-1
  * @param  无
  * @retval 无
  */
void USART1_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
	
#if USART1_INT_ENABLE
//		NVIC_InitTypeDef NVIC_InitStructure;
#endif		
		/* config USART1 clock */
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | USART1_GPIO_CLK, ENABLE);
//	
#if USART1_Remap
		GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE); //开启串口1重映射时钟
#endif
		/* USART1 GPIO config */
		/* Configure USART1 Tx (PA.09) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = USART1_PIN_Tx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(USART1_GPIO, &GPIO_InitStructure);    
		/* Configure USART1 Rx (PA.10) as input floating */
		GPIO_InitStructure.GPIO_Pin = USART1_PIN_Rx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
			
		/* USART1 mode config */
		USART_InitStructure.USART_BaudRate = Usart1_BaudRate ;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure); 
		
//#if USART1_INT_ENABLE	//如果使能了接收配置Usart1 NVIC   
//		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
		 
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
//#endif
		USART_Cmd(USART1, ENABLE);                    //使能串口 		
}

#if USART1_INT_ENABLE
/**********************************************
*	函 数 名: USART1_IRQHandler(void)
*	形    参：
*	返 回 值: 
*	功能说明: USART1中断函数		
**********************************************/ 
void USART1_IRQHandler(void)
{
   uint8_t Res = 0;
	uint32_t Tmp_Comm=0;
	Tmp_Comm=Tmp_Comm;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		if(Comm_USART1.Rece_Flag == 0)
		{
			Comm_USART1.Rece_Time = 0;//清除故障计时
			if(Comm_USART1.Rece_Count == 0)
			{
				Res = Res;
//				if(Res == 0xfa)
//				{
//					Comm_USART1.ReceBuff[Comm_USART1.Rece_Count] = Res;
//					Comm_USART1.Rece_Count ++;
//					}
//				else
//				{
//					Comm_USART1.Rece_Count = 0;
//					}
//				}
//			else
//			if(Comm_USART1.Rece_Count == 1)
//			{
//				if(Res == 0xf5)
//				{
//					Comm_USART1.ReceBuff[Comm_USART1.Rece_Count] = Res;
//					Comm_USART1.Rece_Count ++;
//					}
//				else
//				{
//					Comm_USART1.Rece_Count = 0;
//					}
//				}
//			else
//			if(Comm_USART1.Rece_Count == 2)
//			{
//				Comm_USART1.ReceBuff[Comm_USART1.Rece_Count] = Res;
//				Comm_USART1.Rece_Count ++;
//				}
//			else
//			if(Comm_USART1.Rece_Count == 3)
//			{
//				Comm_USART1.ReceBuff[Comm_USART1.Rece_Count] = Res;
//				Tmp_Comm = (Comm_USART1.ReceBuff[Comm_USART1.Rece_Count-1]<<8)+Comm_USART1.ReceBuff[Comm_USART1.Rece_Count];
//				if(Tmp_Comm>Comm_Rece_Que)
//				{
//					Comm_USART1.Rece_Count = 0;
//					}
//				else
//				{
//					Comm_USART1.Rece_Len = (Comm_USART1.ReceBuff[2]<<8)+Comm_USART1.ReceBuff[3];
//					Comm_USART1.Rece_Count ++;
//					}
//				}
//			else
//			if(Comm_USART1.Rece_Count == 4)
//			{
//				Comm_USART1.ReceBuff[Comm_USART1.Rece_Count] = Res;
//				Comm_USART1.Rece_Count ++;
//				}
//			else
//			if(Comm_USART1.Rece_Count == 5)
//			{
//				Comm_USART1.ReceBuff[Comm_USART1.Rece_Count] = Res;
//				Tmp_Comm = (Comm_USART1.ReceBuff[Comm_USART1.Rece_Count-1]<<8)+Comm_USART1.ReceBuff[Comm_USART1.Rece_Count];
//				if((Tmp_Comm == Fixed_Addr)||(Tmp_Comm == 0)||(Tmp_Comm == Addr_Value))
//				{
//					Comm_USART1.Rece_Count ++;
//					}
//				else
//				{
//					Comm_USART1.Rece_Count = 0;
//					Comm_USART1.Rece_Len = 0;
//					}
//				}
//			else
//			{
//				Comm_USART1.ReceBuff[Comm_USART1.Rece_Count] = Res;
//				Comm_USART1.Rece_Count ++;
//				if(Comm_USART1.Rece_Count>=(Comm_USART1.Rece_Len+5))
//				{
//					Comm_USART1.Rece_Flag = 1;
//					Comm_USART1.Rece_Count = 0;
//					}
				}
			}
		}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE );
	}
void Usart1_Init(void)
{
	uint8_t i;
	for(i=0;i<Comm_Que;i++)
	{
		Comm_USART1.SendBuff[i] = 0xff;
		}
	}
void Usart1_Send(uint8_t Len)
{
	uint8_t i;
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	for(i=0;i<Len;i++)
	{
		USART_SendData(USART1, Comm_USART1.SendBuff[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		}
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

/*    ch1 = (checksum  >> 4) & 0x0F;  //取高位数；  c1 = checksum & 0x0F;  //取低位数；

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

#endif

