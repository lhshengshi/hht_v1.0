/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                   ARM Cortex-M3 Port
* �ļ���    : BSP_USART1.c
* ��  ��    : 
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
* �� ע     : Bug1.Usart1ӳ�䵽PB6.7�ϴ��ڽ��յ����ݣ���֪��ʲôԭ��
*******************************************************************************/
/* Includes---------------------------------------------*/
 #include "BSP_Usart1.h"
 #include "Heard_Public.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
#if USART1_Remap == TRUE   // ��������CAN1��GPIO�˿�
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
uint32_t Usart1_Rece_Time=0; //ͨѶ�����м�ʱ��
uint32_t Usart1_Comm_Time=0; //û��ͨѶ��ʱ������ͨѶ�ж�
*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/

/* Private functions -----------------------------------*/
/**
  * @brief  USART1 GPIO ����,����ģʽ���á�9600 8-N-1
  * @param  ��
  * @retval ��
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
		GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE); //��������1��ӳ��ʱ��
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
		
//#if USART1_INT_ENABLE	//���ʹ���˽�������Usart1 NVIC   
//		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		 
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
//#endif
		USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 		
}

#if USART1_INT_ENABLE
/**********************************************
*	�� �� ��: USART1_IRQHandler(void)
*	��    �Σ�
*	�� �� ֵ: 
*	����˵��: USART1�жϺ���		
**********************************************/ 
void USART1_IRQHandler(void)
{
   uint8_t Res = 0;
	uint32_t Tmp_Comm=0;
	Tmp_Comm=Tmp_Comm;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		if(Comm_USART1.Rece_Flag == 0)
		{
			Comm_USART1.Rece_Time = 0;//������ϼ�ʱ
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
//���У��
uint8_t XORValid(uint8_t *buffer,uint16_t Len)
{
    uint8_t checksum = 0;
//    uint8_t ch1,c1; //У��λ�ĸ���λ�͵���λ
		uint8_t i;
//		uint16_t Len;
//		Len = (buffer[2]<<8)+buffer[3]+5;
    for (i = 0;  i<Len;  i++)
    {
        checksum = checksum ^ buffer[i]; //���������ȡֵ
			}
		return(checksum);

/*    ch1 = (checksum  >> 4) & 0x0F;  //ȡ��λ����  c1 = checksum & 0x0F;  //ȡ��λ����

    if (ch1 < 10) //����10����
        ch1 = ch1  +  '0';
    else
        ch1 = (ch1 - 10 ) +  'A'; //������10��16���������磺A��B��C��D��E��F

    if (c1 < 10)
        c1 = c1  +  '0';
    else
        c1 = (c1 - 10 )+  'A';

    XOR_High=ch1;
    XOR_Low =c1;*/
}

#endif

