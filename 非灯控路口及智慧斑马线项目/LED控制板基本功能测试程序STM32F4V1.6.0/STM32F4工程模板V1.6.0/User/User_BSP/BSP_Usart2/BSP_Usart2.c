/******************** (C) COPYRIGHT DIYǶ��ʽ����������*******************************
 *
 *                              ARM Cortex-M4 Port
 *
 * �ļ�����     : BSP.h (  )
 * ��    ��     : MJQ
 * ��    ��	 	: MDK5.10a-->�̼���V1.5.0�汾
 * ����ƽ̨     : STM32F407ZGT6-25MHz->168MHz
 * �޸�ʱ��     : 2014-10-20
 * ��    ��     : V1.0.0
 * Ӳ������     : STM32F40xx-STM32������
 * ˵    ��     :
 *
 *
**************************************************************************************/
/* Includes---------------------------------------------*/
#include "BSP_USART2.h"
u8 Usart2_RxFlag,Usart2_Rx_Finish = 0;
u8 Usart2_RxBuf[8] = {0};
/* Private defines--------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
/* Private functions -----------------------------------*/
void USART2_Configuration(void)
{
    USART_InitTypeDef USART_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = USART2_BaudRate;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStruct);
    USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//��ֹ�����ж�
    USART_Cmd(USART2, ENABLE);//ʹ�ܴ���2
    USART_ClearFlag(USART2, USART_FLAG_TC);
}

//��Ҫ��targetѡ����ѡ��ʹ��USE microLIB

//����2�жϷ������
void USART2_IRQHandler(void)                	
{
    u8 Res = Res;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res = USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		if(Usart2_RxFlag > 100)//���������Ĭ�Ͻ���ʧ��
		{
		    Usart2_RxFlag = FALSE ;
			Usart2_Rx_Finish = FALSE;
		}
		if((Usart2_RxFlag > FALSE)&&(Usart2_Rx_Finish != TRUE))
		{
			Usart2_RxBuf[Usart2_RxFlag++] =Res;	
		}
		else if((Usart2_RxFlag == FALSE)&&((Usart2_Rx_Finish != TRUE)))
		{
			Usart2_RxBuf[Usart2_RxFlag++] =Res;
		}	
    }
    else if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        USART2->SR;//�ȶ�SR��DRĿ��Ϊ�����USART_IT_IDLE�ж�
        USART2->DR;
		Usart2_RxFlag = FALSE;
        Usart2_Rx_Finish = TRUE;
    }
}
//RS485 ���ͺ���
 u8 Usart2SendStr(u8 *str,u16 strlen)
{
	for(u8 i=0;i<strlen;i++)
	{
		USART_SendData(USART2,*(str+i));
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	}
    Delay_us(1000);//��ʱС�����һ���ֽڷ��Ͳ���ȥ��������ʱһ���ֽڵ�ʱ��
	return TRUE;
}

PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART2,(uint8_t)ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

    return ch;
}
/********** (C) COPYRIGHT DIYǶ��ʽ���������� ��END OF FILE ��************************/


