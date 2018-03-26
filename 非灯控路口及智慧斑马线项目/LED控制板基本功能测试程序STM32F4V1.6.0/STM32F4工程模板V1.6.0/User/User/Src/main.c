/******************** (C) COPYRIGHT DIYǶ��ʽ����������*******************************
 *                                
 *                              ARM Cortex-M4 Port
 *
 * �ļ�����     : main.c (  )
 * ��    ��     : MJQ	 
 * ��    ��	 	: MDK5.10a-->�̼���V1.5.0�汾
 * ����ƽ̨     : STM32F407ZGT6-25MHz->168MHz 
 * �޸�ʱ��     : 2015-05-01 
 * ��    ��     : V1.0.0
 * Ӳ������     : STM32F40xx-STM32������
 * ˵    ��     : 
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
uint8_t Internet_Rxbuff[1024];	/*����һ��1KB�Ļ���*/
//uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x4E,0x00,0x00,0x01,0xEF};	/*��ѯ�ɶ��ļ�����*/
//uint8_t Play_Music[8] = {0x7E,0xFF,

uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x18,0x00,0x00,0x01,0xEF};	/*�����������001*/
//uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x9,0x00,0x00,0x04,0xEF};	/*�������FLASH1*/
//uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x08,0x00,0x00,0x01,0xEF};	/*ѭ����������001*/
//uint8_t Play_Music[8] = {0x7E,0xFF,0x06,0x06,0x00,0x00,0x12,0xEF};	/*ѭ����������*/
uint8_t Internet_Txbuff[8] = {0xaa,0xFF,0xaa,0xFF,0xaa,0xFF,0xaa,0xFF};	/*�����������001*/
uint8_t ALL_AA_FF[8] = {0xaa,0xFF,0xaa,0xFF,0xaa,0xFF,0xaa,0xFF};	/*�����������001*/
uint8_t ALL_AA[8] = {0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa};	/*�����������001*/
uint8_t ALL_FF[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};	/*�����������001*/
//7E FF 06 08 00 00 01 xx xx EF
//7E FF 06 06 00 00 0F FF D5 EF
//7E FF 06 0F 00 01 01 xx xx EF
//7E FF 06 3F 00 00 00 EF        0x7E,0xFF,0x06,0x03,0x00,0x00,0x01,0xEF    
//7E FF 06 4E 00 00 01 EF
//7E FF 06 18 00 00 00 EF
//7E FF 06 09 00 00 04 xx xx EF ָ������flash
/* Private function prototypes -------------------------*/
/* Private functions -----------------------------------*/
/*************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
**************************************************/
static  unsigned char TCP_Client_Demo(u16 SendLen)
{
    uint16_t len=0;
    uint8_t  rt = FALSE;
    uint16_t local_port2 =5010;
	for(u8 i=5;i>0;i--)
	{
		switch(getSn_SR(SOCK_TCPC))								       /*��ȡsocket��״̬*/
		{
			case SOCK_CLOSED:											/*socket���ڹر�״̬*/
				socket(SOCK_TCPC,Sn_MR_TCP,local_port2+i,Sn_MR_ND);
				break;

			case SOCK_INIT:												/*socket���ڳ�ʼ��״̬*/
				rt = 0x10;
				connect(SOCK_TCPC,ConfigMsg.serip,ConfigMsg.serport);   /*socket���ӷ�����*/
				break;

			case SOCK_ESTABLISHED: 										 /*socket�������ӽ���״̬*/
				if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
				{
					setSn_IR(SOCK_TCPC, Sn_IR_CON); 					/*��������жϱ�־λ*/
				}
				len=getSn_RX_RSR(SOCK_TCPC); 							/*����lenΪ�ѽ������ݵĳ���*/
				if(len>0)
				{
					recv(SOCK_TCPC,Internet_Txbuff,len); 				/*��������Server������*/
					Internet_Txbuff[len]=0x00;  						/*����ַ���������*/
					send(SOCK_TCPC,ALL_FF,8);				/*��Server��������*/
				} else send(SOCK_TCPC,ALL_AA,SendLen);          /*��Server��������*/
				rt |= 0x01 ;
				break;
			case SOCK_CLOSE_WAIT: 										/*socket���ڵȴ��ر�״̬*/
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
	/* ����������ѭ���� */
	
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
	while(W5500_Check_Link())  //û�в�������
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
		switch(getSn_SR(SOCK_TCPS))									   /*��ȡsocket��״̬*/
        {
		case SOCK_CLOSED:											    /*socket���ڹر�״̬*/
			socket(SOCK_TCPS ,Sn_MR_TCP,ConfigMsg.port,Sn_MR_ND);	     /*��socket*/
			break;

		case SOCK_INIT:													/*socket�ѳ�ʼ��״̬*/
			listen(SOCK_TCPS);											/*socket��������*/
			break;

		case SOCK_ESTABLISHED:											/*socket�������ӽ���״̬*/
			if(getSn_IR(SOCK_TCPS) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPS, Sn_IR_CON);							/*��������жϱ�־λ*/
			}
			len=getSn_RX_RSR(SOCK_TCPS);							    /*����lenΪ�ѽ������ݵĳ���*/
			if(len>0)
			{
				recv(SOCK_TCPS,Internet_Rxbuff,len);					/*��������Client������*/
				send(SOCK_TCPS,ALL_FF,8);	/*��Client��������*/

//				send(SOCK_TCPS,Internet_Rxbuff,len);	/*��Client��������*/
//			    close(SOCK_TCPS);	//�����ӣ�ÿ�������һ�����ݣ��Ͽ�����
			}	
			break;
		 case SOCK_CLOSE_WAIT:	/*socket���ڵȴ��ر�״̬*/
			close(SOCK_TCPS);
			break;
       }
//		clitest = TCP_Client_Demo(8);
	}
}


/************************************
*	�� �� ��: assert_failed
*	��    �Σ�file : Դ�����ļ����ơ��ؼ���__FILE__��ʾԴ�����ļ�����
*			  line �������кš��ؼ��� __LINE__ ��ʾԴ�����к�
*	�� �� ֵ: ��
************************************/
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* 
		�û���������Լ��Ĵ��뱨��Դ�����ļ����ʹ����кţ����罫�����ļ����кŴ�ӡ������
		printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	*/	
	/* ����һ����ѭ��������ʧ��ʱ������ڴ˴��������Ա����û���� */
	while (1)
	{
		
	}
}
#endif
/********** (C) COPYRIGHT DIYǶ��ʽ���������� ��END OF FILE ��************************/





