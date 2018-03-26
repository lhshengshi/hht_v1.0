/******************** (C) COPYRIGHT DIY嵌入式开发工作室*******************************
 *                                
 *                              ARM Cortex-M4 Port
 *
 * 文件名称     : main.c (  )
 * 作    者     : MJQ	 
 * 环    境	 	: MDK5.10a-->固件库V1.5.0版本
 * 开发平台     : STM32F407ZGT6-25MHz->168MHz 
 * 修改时间     : 2015-05-01 
 * 版    本     : V1.0.0
 * 硬件连接     : STM32F40xx-STM32开发板
 * 说    明     : 
 * 			  
 *				   
**************************************************************************************/
/* Includes---------------------------------------------*/
#include "main.h"
#include "BSP_USART2.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
uint8_t Internet_Rxbuff[1024];	/*定义一个1KB的缓存*/
//uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x4E,0x00,0x00,0x01,0xEF};	/*查询可读文件个数*/
//uint8_t Play_Music[8] = {0x7E,0xFF,

uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x18,0x00,0x00,0x01,0xEF};	/*随机播放音乐001*/
//uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x9,0x00,0x00,0x04,0xEF};	/*随机播放FLASH1*/
//uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x08,0x00,0x00,0x01,0xEF};	/*循环播放音乐001*/
//uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x06,0x00,0x00,0x12,0xEF};	/*循环音量设置*/
uint8_t Internet_Txbuff[8] = {0xaa,0xFF,0xaa,0xFF,0xaa,0xFF,0xaa,0xFF};	/*随机播放音乐001*/
uint8_t ALL_AA_FF[8] = {0xaa,0xFF,0xaa,0xFF,0xaa,0xFF,0xaa,0xFF};	/*随机播放音乐001*/
uint8_t ALL_AA[8] = {0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa};	/*随机播放音乐001*/
uint8_t ALL_FF[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};	/*随机播放音乐001*/
//7E FF 06 08 00 00 01 xx xx EF
//7E FF 06 06 00 00 0F FF D5 EF
//7E FF 06 0F 00 01 01 xx xx EF
//7E FF 06 3F 00 00 00 EF        0x7E,0xFF,0x06,0x03,0x00,0x00,0x01,0xEF    
//7E FF 06 4E 00 00 01 EF
//7E FF 06 18 00 00 00 EF
//7E FF 06 09 00 00 04 xx xx EF 指定播放flash
/* Private function prototypes -------------------------*/
/* Private functions -----------------------------------*/
/*************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
**************************************************/
static  unsigned char TCP_Client_Demo(u16 SendLen)
{
    uint16_t len=0;
    uint8_t  rt = FALSE;
    uint16_t local_port2 =5010;
	for(u8 i=5;i>0;i--)
	{
		switch(getSn_SR(SOCK_TCPC))								       /*获取socket的状态*/
		{
			case SOCK_CLOSED:											/*socket处于关闭状态*/
				socket(SOCK_TCPC,Sn_MR_TCP,local_port2+i,Sn_MR_ND);
				break;

			case SOCK_INIT:												/*socket处于初始化状态*/
				rt = 0x10;
				connect(SOCK_TCPC,ConfigMsg.serip,ConfigMsg.serport);   /*socket连接服务器*/
				break;

			case SOCK_ESTABLISHED: 										 /*socket处于连接建立状态*/
				if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
				{
					setSn_IR(SOCK_TCPC, Sn_IR_CON); 					/*清除接收中断标志位*/
				}
				len=getSn_RX_RSR(SOCK_TCPC); 							/*定义len为已接收数据的长度*/
				if(len>0)
				{
					recv(SOCK_TCPC,Internet_Txbuff,len); 				/*接收来自Server的数据*/
					Internet_Txbuff[len]=0x00;  						/*添加字符串结束符*/
					send(SOCK_TCPC,ALL_FF,8);				/*向Server发送数据*/
				} else send(SOCK_TCPC,ALL_AA,SendLen);          /*向Server发送数据*/
				rt |= 0x01 ;
				break;
			case SOCK_CLOSE_WAIT: 										/*socket处于等待关闭状态*/
				close(SOCK_TCPC);
				break;
		}
		if((rt == 0x11)||(rt == 0x01)) break;									
	}  
    return rt ;
}

int main(void)
{
	u8 clitest;
	u16  len;
	BSP_Init();
	/* 进入主程序循环体 */
	
//	Usart2SendStr(Play_Music,8);
	PDout(12) = 0    ;
	Delay_ms(50);
//	for(;;)
//	{
//	   Delay_ms(5000);
//	}

	Get_NetMsg();
	Internet_Init();
	PDout(8) = 1;
	while(W5500_Check_Link())  //没有插入网线
	{
		Internet_Init();
	}
	
	while (1)
	{
		LED0   =~LED0;
		LED1   =~LED1;
		Delay_ms(50);
		LED0   =~LED0;
		LED1   =~LED1;
		Delay_ms(50);
//		tcp server demo
		switch(getSn_SR(SOCK_TCPS))									   /*获取socket的状态*/
        {
		case SOCK_CLOSED:											    /*socket处于关闭状态*/
			socket(SOCK_TCPS ,Sn_MR_TCP,ConfigMsg.port,Sn_MR_ND);	     /*打开socket*/
			break;

		case SOCK_INIT:													/*socket已初始化状态*/
			listen(SOCK_TCPS);											/*socket建立监听*/
			break;

		case SOCK_ESTABLISHED:											/*socket处于连接建立状态*/
			if(getSn_IR(SOCK_TCPS) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPS, Sn_IR_CON);							/*清除接收中断标志位*/
			}
			len=getSn_RX_RSR(SOCK_TCPS);							    /*定义len为已接收数据的长度*/
			if(len>0)
			{
				recv(SOCK_TCPS,Internet_Rxbuff,len);					/*接收来自Client的数据*/
				send(SOCK_TCPS,ALL_FF,8);	/*向Client发送数据*/

//				send(SOCK_TCPS,Internet_Rxbuff,len);	/*向Client发送数据*/
//			    close(SOCK_TCPS);	//短连接，每接受完成一次数据，断开连接
			}	
			break;
		 case SOCK_CLOSE_WAIT:	/*socket处于等待关闭状态*/
			close(SOCK_TCPS);
			break;
       }
//		clitest = TCP_Client_Demo(8);
	}
}


/************************************
*	函 数 名: assert_failed
*	形    参：file : 源代码文件名称。关键字__FILE__表示源代码文件名。
*			  line ：代码行号。关键字 __LINE__ 表示源代码行号
*	返 回 值: 无
************************************/
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* 
		用户可以添加自己的代码报告源代码文件名和代码行号，比如将错误文件和行号打印到串口
		printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	*/	
	/* 这是一个死循环，断言失败时程序会在此处死机，以便于用户查错 */
	while (1)
	{
		
	}
}
#endif
/********** (C) COPYRIGHT DIY嵌入式开发工作室 （END OF FILE ）************************/





