/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                 ARM Cortex-M3 Port
* �ļ���    : main.c
* ��  ��    :
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������


*******************************************************************************/
/* Includes---------------------------------------------*/
#include "Heard_Public.h"
#include  <stdlib.h>
#include "User_BSP.h"
#include "beep.h"
#include "key.h"
#include  "BSP_JCM12864_Demo.h"
#include  "BSP_JCM12864.h"
uint8_t System_Flag = 0;
uint16_t System_State_Flag;//ϵͳ����״̬
uint8_t Usart3_Cabinet_Connect_Err_Flag = 0;
uint8_t Usart3_Power_Connect_Err_Flag = 0;
uint32_t Run_Tim3_Flag=0;
uint16_t LCD_Update_Flag = 0;//lcd������ʾ��־
uint16_t LCD_Power_Update_Flag = 0;//lcd������ʾ��־
uint16_t LCD_Twinkle_Flag1 = 0;//lcd������ʾ��־
uint16_t LCD_Twinkle_Flag2 = 0;//lcd������ʾ��־

uint16_t Reset_Time = 0;
uint8_t  Data_Read_Flag = 0;//���ݶ�ȡ��־����ʱ��ȡ

uint32_t LCD_Show_Flag = 0;//Һ����ʾҳ���־λ
uint8_t key=100;
uint8_t volatile KeyValue=100;
uint8_t bai = 222;
uint8_t qian = 0x01;
uint8_t ge = 1;
uint8_t zhiling = 0;
uint8_t Buzzer_Flag = 0;
uint8_t key_cnt = 0;

uint8_t Calibration_CH1_Buff[11] = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X04,0X01,0XFF,0X52};
uint8_t Calibration_CH2_Buff[11] = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X04,0X02,0XFF,0X51};
uint8_t Calibration_CH3_Buff[11] = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X04,0X03,0XFF,0X50};
uint8_t Calibration_CH4_Buff[11] = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X04,0X04,0XFF,0X57};
uint8_t Calibration_CH5_Buff[11] = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X04,0X05,0XFF,0X56};
uint8_t Calibration_CH6_Buff[11] = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X04,0X06,0XFF,0X55};
uint8_t Request_Power_Module[9 ] = {0xfa,0xf5,0x00,0x04,0x01,0x01,0xa0,0x01,0xaa};

uint8_t Open_All_CH_Buff[]   = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0XF1,0XFF,0XA4};//0XFA 0XF5 0X00 0X05 0X01 0X01 0XA1 0X02 0XF1 0XFF 0XA4
uint8_t Close_All_CH_Buff[]  = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0XF0,0XFF,0XA5};//0XFA 0XF5 0X00 0X05 0X01 0X01 0XA1 0X02 0XF0 0XFF 0XA5

uint8_t Open_CH1_Buff[]   = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X11,0XFF,0X44};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X11 0XFF 0X44
uint8_t Open_CH2_Buff[]   = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X21,0XFF,0X74};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X21 0XFF 0X74
uint8_t Open_CH3_Buff[]   = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X31,0XFF,0X64};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X31 0XFF 0X64
uint8_t Open_CH4_Buff[]   = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X41,0XFF,0X14};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X41 0XFF 0X14
uint8_t Open_CH5_Buff[]   = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X51,0XFF,0X04};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X51 0XFF 0X04
uint8_t Open_CH6_Buff[]   = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X61,0XFF,0X34};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X61 0XFF 0X34

uint8_t Close_CH1_Buff[]  = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X10,0XFF,0X45};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X10 0XFF 0X45
uint8_t Close_CH2_Buff[]  = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X20,0XFF,0X75};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X20 0XFF 0X75
uint8_t Close_CH3_Buff[]  = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X30,0XFF,0X65};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X30 0XFF 0X65
uint8_t Close_CH4_Buff[]  = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X40,0XFF,0X15};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X40 0XFF 0X15
uint8_t Close_CH5_Buff[]  = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X50,0XFF,0X05};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X50 0XFF 0X05
uint8_t Close_CH6_Buff[]  = {0XFA,0XF5,0X00,0X06,0X01,0X01,0XA1,0X02,0X60,0XFF,0X35};//0XFA 0XF5 0X00 0X06 0X01 0X01 0XA1 0X02 0X60 0XFF 0X35

//0xfa	0xf5	0x00	0x04	0x01	0x01	0xa0	0x01	0xaa	
uint16_t Fixed_Addr = 0x0101;
uint16_t Addr_Value = 0x0101;

uint8_t Status_Buff[Comm_Rece_Que] = {0xff};
uint8_t Power_Module_Status_Buff[Comm_Rece_Que] = {0xff};

uint32_t ZL_Time=0;
uint8_t Tx_Flag=0;
uint8_t Comm3_Err_Flag = 0;
uint8_t Task = 0;

uint8_t KCnt,KSet,KOK;
//#include "systick.h"
//#include "12864.h"
//#include "menu1.h"
//#include "sys.h"
/* Private defines--------------------------------------*/
/* Private function prototypes--------------------------*/
/* Private functions -----------------------------------*/
uint8_t test_ipbuff[1] = {0xff};
u16 adcx;
u16 ADC_Voltage;
void JCM12864_Display_ADC_Voltage(u8 row,u8 col,u8 ADC_Voltage)
{
	uint8_t  temp = 0;
	switch(row)
	{
		case 0:temp=0x80;break;
		case 1:temp=0x90;break;
		case 2:temp=0x88;break;
		case 3:temp=0x98;break;
		default:break;
	}
	temp+=col;
	JCM12864_SendCom(temp);
	if(ADC_Voltage > 2500)
	{
		JCM12864_Display_String(row,col,"�쳣");
	}
	else
	{
		ADC_Voltage = ADC_Voltage/10;
		if((ADC_Voltage/100)>0)		//����ʾ0
		JCM12864_SendData(((ADC_Voltage/100)+0x30));  //��λ��ʾ
		if((ADC_Voltage/10)>0)		
		JCM12864_SendData((((ADC_Voltage/10)%10)+0x30));//��ʾʮλ
		JCM12864_SendData(((ADC_Voltage%10)+0x30));	//��ʾ��λ
		JCM12864_SendData((0x56));//��ʾ��λV		
	}
}

void JCM12864_Display_Port(uint8_t row,uint8_t col,uint8_t Port)
{
	uint8_t  temp;
	uint32_t port_temp;
	switch(row)
		{
			case 0:temp=0x80;break;
			case 1:temp=0x90;break;
			case 2:temp=0x88;break;
			case 3:temp=0x98;break;
			default:break;
		}
	temp+=col;
	JCM12864_SendCom(temp);
	port_temp = Port;
	if((port_temp/10000)>0)		//����ʾ0
		JCM12864_SendData(((port_temp/10000)+0x30)); //��λ��ʾ
	else
	{
		JCM12864_SendData(0x20);
	}
  if((port_temp/1000)>0)		//����ʾ0
		JCM12864_SendData((((port_temp/1000)%10)+0x30)); //��λ��ʾ
  else
	{
		JCM12864_SendData(0x20);
	}
	if((port_temp/100)>0)		
		JCM12864_SendData(((((port_temp/100)%10)%10)+0x30));//��ʾʮλ
	else
	{
		JCM12864_SendData(0x20);
	}
	if((port_temp/10)>0)		
		JCM12864_SendData((((((port_temp/10)%10)%10)%10)+0x30));//��ʾʮλ
	else
	{
		JCM12864_SendData(0x20);
	}
	JCM12864_SendData(((port_temp%10)+0x30));	//��ʾ��λ
}

int main(void)
{ 	
	float temp; 
	User_BSP_Init();//IO��ʼ��
	Soft_Init();//������ʼ��
	JCM12864_Init();
	Adc_Init();		
	JCM12864_clear();
	Delay_ms(10);
	BSP_JCM12864_DemoFF();
//	BSP_JCM12864_Demo100();
	zhiling = 5;
	BEEP = 0;
	
// CAL_Power_CH1_Vol1 = 0x00;
// CAL_Power_CH1_Vol2 = 0xff;
// CAL_Power_CH1_Cur1 = 0x00;
// CAL_Power_CH1_Cur2 =0x1f;
// LCD_Show_Flag = 100;
//	start();

//	PWR_1;
//	Delay_s(2);
//	PWR_1;
//	CH3_Statu = 0x31;
//	BSP_JCM12864_Demo111();
//	while(1)
//	{	
////		JCM12864_clear();
////		Delay_ms(100);
////		JCM12864_Display_Power_Channel_Voltage(1,3,0x00,0xff);
////		JCM12864_Display_Power_Channel_Current(1,6,0x00,0x5f);		Delay_s(2);
////		JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
////		JCM12864_Display_String(1,0,"ͨ��һУ׼�ɹ�  ");
////		JCM12864_Display_String(2,0,"  2:  220V  9.9A");
////		JCM12864_Display_String(3,0,"  3:  220V  9.9A");
////		Delay_s(2);
////		
//		if(System_Flag == 0)//����״̬��
//		{	
////			if(Run_Tim3_Flag>0)
////			{
////				PWR_1;
////			}
//			if(Run_Tim3_Flag >= 2500)//2.5S�󿪻�����
//			{
//				LCD_Update_Flag = 0;
////				BSP_JCM12864_Demo100();
//				LCD_Show_Flag = 100;
//				System_Flag = 1;
////				BSP_JCM12864_Demo112();
//			}
//		}
//		else
//		{
//			Fill_Information();
//			KEY_Handle_Demo();
//			LCD_Show_Demo();
////			if(KOK==2)//���������ػ�
////			{
////				Stop();
////			}
////			while(Usart3_Power_Connect_Err_Flag == 1)
////			{
////				JCM12864_Display_String(0,0,"У׼�����Դģ��");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
////				JCM12864_Display_String(1,0,"ͨѶʧ�ܣ�����");
////				JCM12864_Display_String(2,0,"�����߼���Դģ��");
////				JCM12864_Display_String(3,0,"����������������");
////				Delay_s(2);
////			}
//		}
//	}
	while(1)
	{
		PWR_1;
		adcx=Get_Adc_Average(ADC_Channel_9,10);
		temp=(float)adcx*(3.3/4096);
//		temp=((float)((int)((temp+0.005)*100)))/100;
		adcx=temp;
//		temp-=adcx;
//		temp=temp-adcx;
//		temp*=1000;
		adcx = (adcx*10000)/10;
		temp = temp*10000;
		JCM12864_Display_Port(0,0,temp);
		LED0=!LED0;
		Delay_ms(250);
	}
}


//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"  ��ѯ����״̬");
//	JCM12864_Display_String(1,0,"  ��������ģ��");
//	JCM12864_Display_String(2,0,"  ���ù���ģ��");
//	JCM12864_Display_String(3,0,">>У׼��Դģ��");	
//}
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��һ      ");
//	JCM12864_Display_String(1,0,"��ѹ      220V");
//	JCM12864_Display_String(2,0,"����      9.9A");
//	JCM12864_Display_String(3,0,"У׼        ����");
//}

//Delay_s(1);
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"ͨ��һУ׼�ɹ�  ");
//	JCM12864_Display_String(2,0,"  2:  220V  9.9A");
//	JCM12864_Display_String(3,0,"  3:  220V  9.9A");
//}

//Delay_s(1);
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"����У׼ͨ��һ  ");
//	JCM12864_Display_String(2,0,"  2:  220V  9.9A");
//	JCM12864_Display_String(3,0,"  3:  220V  9.9A");
//}
//Delay_s(1);
