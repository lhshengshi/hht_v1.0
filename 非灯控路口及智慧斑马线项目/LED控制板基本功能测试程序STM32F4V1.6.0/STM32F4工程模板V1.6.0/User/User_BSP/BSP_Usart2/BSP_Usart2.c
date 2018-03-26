/******************** (C) COPYRIGHT DIY嵌入式开发工作室*******************************
 *
 *                              ARM Cortex-M4 Port
 *
 * 文件名称     : BSP.h (  )
 * 作    者     : MJQ
 * 环    境	 	: MDK5.10a-->固件库V1.5.0版本
 * 开发平台     : STM32F407ZGT6-25MHz->168MHz
 * 修改时间     : 2014-10-20
 * 版    本     : V1.0.0
 * 硬件连接     : STM32F40xx-STM32开发板
 * 说    明     :
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
    USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//禁止接收中断
    USART_Cmd(USART2, ENABLE);//使能串口2
    USART_ClearFlag(USART2, USART_FLAG_TC);
}

//需要在target选项中选择使用USE microLIB

//串口2中断服务程序
void USART2_IRQHandler(void)                	
{
    u8 Res = Res;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		if(Usart2_RxFlag > 100)//数据溢出，默认接受失败
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
        USART2->SR;//先读SR，DR目的为了清除USART_IT_IDLE中断
        USART2->DR;
		Usart2_RxFlag = FALSE;
        Usart2_Rx_Finish = TRUE;
    }
}
//RS485 发送函数
 u8 Usart2SendStr(u8 *str,u16 strlen)
{
	for(u8 i=0;i<strlen;i++)
	{
		USART_SendData(USART2,*(str+i));
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	}
    Delay_us(1000);//延时小了最后一个字节发送不出去，最少延时一个字节的时间
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
/********** (C) COPYRIGHT DIY嵌入式开发工作室 （END OF FILE ）************************/


