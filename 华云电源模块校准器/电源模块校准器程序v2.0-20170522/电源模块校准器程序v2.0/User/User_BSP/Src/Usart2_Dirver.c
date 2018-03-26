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
//uint32_t Usart2_Rece_Time=0; //ͨѶ�����м�ʱ��
//uint32_t Usart2_Comm_Time=0; //û��ͨѶ��ʱ������ͨѶ�ж�
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/

void USART2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//485����
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
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 		
	}

#if 1
/**********************************************
*	�� �� ��: USART_IRQHandler(void)
*	��    �Σ�
*	�� �� ֵ: 
*	����˵��: USART�жϺ���		
**********************************************/ 

void USART2_IRQHandler(void)
{
  uint8_t Res = 0;
	uint32_t Tmp_Comm=0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		Res = Res;
		Tmp_Comm=Tmp_Comm;
//		if(Comm_USART2.Rece_Flag == 0)
//		{
//			Comm_USART2.Rece_Time = 0;//������ϼ�ʱ
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
	if(XORValid(Buff_IN,Length_IN) == Buff_IN[Length_IN])//�ж�У��ֵ
	{
		Tmp_Inform = (Buff_IN[4]<<8)+Buff_IN[5];
		if((Tmp_Inform == Addr_Value)||(Tmp_Inform == Fixed_Addr))//�жϵ�ַ
		{
			if(Buff_IN[6]==0xa0)//������
			{
				switch(Buff_IN[7])
				{
					case 0://��������
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
					case 1://��ѯ����
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 26;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						if(((System_State_Flag>>3)&0x01) == 0x01)//�¶ȹ���
						{
							Buff_OUT[8] = 5;
							Buff_OUT[9] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>8)&0x01) == 0x01)//�����±���
							{
								Buff_OUT[8] = 1;
								}
							else
							if(((System_State_Flag>>9)&0x01) == 0x01)//�����±���
							{
								Buff_OUT[8] = 3;
								}
							else
							{
								Buff_OUT[8] = 0;
								}
							Buff_OUT[9] = Temperture_Now.Sign;//����ʱȫ��Ϊ0xff
							Buff_OUT[10] = Temperture_Now.Value/10;
							Buff_OUT[11] = Temperture_Now.Value%10;		
							}
						if(((System_State_Flag>>4)&0x01) == 0x01)//ʪ�ȹ���
						{
							Buff_OUT[12] = 5;
							Buff_OUT[13] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[14] = 0xff;
							Buff_OUT[15] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>10)&0x01) == 0x01)//��ʪ����
							{
								Buff_OUT[12] = 1;
								}
							else
							if(((System_State_Flag>>11)&0x01) == 0x01)//���ɱ���
							{
								Buff_OUT[12] = 3;
								}
							else
							{
								Buff_OUT[12] = 0;
								}
							Buff_OUT[13] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[14] = 0xff;
							Buff_OUT[15] = Humidity_Now/10;		
							}
						if(((System_State_Flag>>5)&0x01) == 0x01)//��ˮ����
						{
							Buff_OUT[16] = 5;
							Buff_OUT[17] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[18] = 0xff;
							Buff_OUT[19] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>12)&0x01) == 0x01)//��ˮ����
							{
								Buff_OUT[16] = 1;
								}
							else
							{
								Buff_OUT[16] = 0;
								}

							Buff_OUT[17] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[18] = 0xff;
							Buff_OUT[19] = 0xff;		
							}
						if(((Out_state>>8)&0x01) == 0x01)//���±�������
						{
							Buff_OUT[20] = 1;
							Buff_OUT[21] = 0xff;
							}
						else
						{
							Buff_OUT[20] = 0;
							Buff_OUT[21] = 0xff;
							}
						if(((Out_state>>9)&0x01) == 0x01)//���±�������
						{
							Buff_OUT[22] = 1;
							Buff_OUT[23] = 0xff;
							}
						else
						{
							Buff_OUT[22] = 0;
							Buff_OUT[23] = 0xff;
							}
						if(((Out_state>>10)&0x01) == 0x01)//��ʪ��������
						{
							Buff_OUT[24] = 1;
							Buff_OUT[25] = 0xff;
							}
						else
						{
							Buff_OUT[24] = 0;
							Buff_OUT[25] = 0xff;
							}
						if(((Out_state>>11)&0x01) == 0x01)//���ɱ�������
						{
							Buff_OUT[26] = 1;
							Buff_OUT[27] = 0xff;
							}
						else
						{
							Buff_OUT[26] = 0;
							Buff_OUT[27] = 0xff;
							}
						if(((Out_state>>12)&0x01) == 0x01)//��ˮ��������
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
					case 2://��ѯ��ǰ�趨ֵ
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 24;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						Buff_OUT[8] = 0xff;													//�����±�����Ϣ
						Buff_OUT[9] = Temperture_Set_High.Sign;
						Buff_OUT[10] = Temperture_Set_High.Value/10;
						Buff_OUT[11] = Temperture_Set_High.Value%10;
						Buff_OUT[12] = 0xff;												//�����±�����Ϣ
						Buff_OUT[13] = Temperture_Set_Low.Sign;
						Buff_OUT[14] = Temperture_Set_Low.Value/10;
						Buff_OUT[15] = Temperture_Set_Low.Value%10;
						Buff_OUT[16] = 0xff;												//��ʪ������Ϣ
						Buff_OUT[17] = 0xff;
						Buff_OUT[18] = 0xff;
						Buff_OUT[19] = Humidity_Set_High/10;
						Buff_OUT[20] = 0xff;												//���ɱ�����Ϣ
						Buff_OUT[21] = 0xff;
						Buff_OUT[22] = 0xff;
						Buff_OUT[23] = Humidity_Set_Low/10;
						Buff_OUT[24] = 0xff;												//��ˮ������Ϣ
						Buff_OUT[25] = 0xff;
						Buff_OUT[26] = 0xff;
						Buff_OUT[27] = 0xff;						
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 3://��ѯ�¶���Ϣ
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 20;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						if(((System_State_Flag>>3)&0x01) == 0x01)//�¶ȹ���
						{
							Buff_OUT[8] = 5;
							Buff_OUT[9] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>8)&0x01) == 0x01)//�����±���
							{
								Buff_OUT[8] = 1;
								}
							else
							if(((System_State_Flag>>9)&0x01) == 0x01)//�����±���
							{
								Buff_OUT[8] = 3;
								}
							else
							{
								Buff_OUT[8] = 0;
								}
							Buff_OUT[9] = Temperture_Now.Sign;//����ʱȫ��Ϊ0xff
							Buff_OUT[10] = Temperture_Now.Value/10;
							Buff_OUT[11] = Temperture_Now.Value%10;		
							}					
						if(((Out_state>>8)&0x01) == 0x01)//���±�������
						{
							Buff_OUT[12] = 1;
							Buff_OUT[13] = 0xff;
							}
						else
						{
							Buff_OUT[12] = 0;
							Buff_OUT[13] = 0xff;
							}
						if(((Out_state>>9)&0x01) == 0x01)//���±�������
						{
							Buff_OUT[14] = 1;
							Buff_OUT[15] = 0xff;
							}
						else
						{
							Buff_OUT[14] = 0;
							Buff_OUT[15] = 0xff;
							}
						Buff_OUT[16] = 0xff;													//�����±�����Ϣ
						Buff_OUT[17] = Temperture_Set_High.Sign;
						Buff_OUT[18] = Temperture_Set_High.Value/10;
						Buff_OUT[19] = Temperture_Set_High.Value%10;
						Buff_OUT[20] = 0xff;												//�����±�����Ϣ
						Buff_OUT[21] = Temperture_Set_Low.Sign;
						Buff_OUT[22] = Temperture_Set_Low.Value/10;
						Buff_OUT[23] = Temperture_Set_Low.Value%10;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 4://��ѯʪ����Ϣ
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 20;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						if(((System_State_Flag>>4)&0x01) == 0x01)//ʪ�ȹ���
						{
							Buff_OUT[8] = 5;
							Buff_OUT[9] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>10)&0x01) == 0x01)//��ʪ����
							{
								Buff_OUT[8] = 1;
								}
							else
							if(((System_State_Flag>>11)&0x01) == 0x01)//���ɱ���
							{
								Buff_OUT[8] = 3;
								}
							else
							{
								Buff_OUT[8] = 0;
								}
							Buff_OUT[9] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = Humidity_Now/10;		
							}
						if(((Out_state>>10)&0x01) == 0x01)//��ʪ��������
						{
							Buff_OUT[12] = 1;
							Buff_OUT[13] = 0xff;
							}
						else
						{
							Buff_OUT[12] = 0;
							Buff_OUT[13] = 0xff;
							}
						if(((Out_state>>11)&0x01) == 0x01)//���ɱ�������
						{
							Buff_OUT[14] = 1;
							Buff_OUT[15] = 0xff;
							}
						else
						{
							Buff_OUT[14] = 0;
							Buff_OUT[15] = 0xff;
							}
						Buff_OUT[16] = 0xff;												//��ʪ������Ϣ
						Buff_OUT[17] = 0xff;
						Buff_OUT[18] = 0xff;
						Buff_OUT[19] = Humidity_Set_High/10;
						Buff_OUT[20] = 0xff;												//���ɱ�����Ϣ
						Buff_OUT[21] = 0xff;
						Buff_OUT[22] = 0xff;
						Buff_OUT[23] = Humidity_Set_Low/10;
						Length_OUT = (Buff_OUT[2]<<8)+Buff_OUT[3]+4;
						Buff_OUT[Length_OUT] = XORValid(Buff_OUT,Length_OUT);
						Length_OUT = Length_OUT + 1;
						break;
						}
					case 5://��ѯ��ˮ��Ϣ
					{
						Buff_OUT[0] = 0xfa;
						Buff_OUT[1] = 0xf5;
						Buff_OUT[2] = 0;
						Buff_OUT[3] = 16;
						Buff_OUT[4] = Addr_Value/256;
						Buff_OUT[5] = Addr_Value%256;
						Buff_OUT[6] = Buff_IN[6];
						Buff_OUT[7] = Buff_IN[7];
						if(((System_State_Flag>>5)&0x01) == 0x01)//��ˮ����
						{
							Buff_OUT[8] = 5;
							Buff_OUT[9] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;
							}
						else
						{
							if(((System_State_Flag>>12)&0x01) == 0x01)//��ˮ����
							{
								Buff_OUT[8] = 1;
								}
							else
							{
								Buff_OUT[8] = 0;
								}

							Buff_OUT[9] = 0xff;//����ʱȫ��Ϊ0xff
							Buff_OUT[10] = 0xff;
							Buff_OUT[11] = 0xff;		
							}	
						if(((Out_state>>12)&0x01) == 0x01)//��ˮ��������
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
					case 6://��ѯ�����̶�����
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
					case 7://��ѯģ�鿪������
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
			if(Buff_IN[6]==0xa1)//д����
			{
				switch(Buff_IN[7])
				{
					case 0:																										//��λ����
					{
						Err_Dat = 0xaa;
						if(((System_State_Flag>>1)&0x01) == 0x01)//����ִ�У������ظ�ִ��
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
					case 1:																									//�趨����ֵ
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
							Charge_flag |= (1<<1);						//��������
							}
						if(Err_Dat == 0x55){;}
						else
						{
							Tmp_Inform = 0;
							if(Buff_IN[12]>1)  //����λ������0��1
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
									Charge_flag |= (1<<2);						//��������
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
								Charge_flag |= (1<<3);						//��������
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
								Charge_flag |= (1<<4);						//��������
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
					case 2:																									//���Ʊ������أ����ڹ��Ϻ��ޱ���ʱ�����ã���������򷵻ش���
					{
						Err_Dat = 0xaa;
						if(Buff_IN[8]>1)
						{
							Err_Dat = 0x55;
							}
						else
						{
							if(Buff_IN[8]==1)//���Ƹ��¿��رպϣ���Ҫ�ж��Ƿ񱨾�
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
								if(Buff_IN[10]==1)//���Ƶ��¿��رպϣ���Ҫ�ж��Ƿ񱨾�
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
								if(Buff_IN[12]==1)//���Ƴ�ʪ���رպϣ���Ҫ�ж��Ƿ񱨾�
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
								if(Buff_IN[14]==1)//���Ƴ�ʪ���رպϣ���Ҫ�ж��Ƿ񱨾�
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
								if(Buff_IN[16]==1)//���Ƴ�ʪ���رպϣ���Ҫ�ж��Ƿ񱨾�
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
			else//�����������
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


/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/

