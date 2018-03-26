/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                   ARM Cortex-M3 Port
* �ļ���    : User_BSP.h
* ��  ��    :
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
*******************************************************************************/
#ifndef __Heard_Public_H
#define __Heard_Public_H
/* Includes---------------------------------------------*/
#include "stdint.h"
#include "Heard_Public.h"
#include "User_BSP.h"

/* Private defines--------------------------------------*/

#define RS485_Rece()  {GPIO_ResetBits(GPIOB,GPIO_Pin_0);}
#define RS485_Send() 	{GPIO_SetBits(GPIOB,GPIO_Pin_0);}
#define Open 1
#define Close 0
#define In_High 1
#define In_Low 0
#define Error 2
#define Connect_Error 2
#define Comm_Que 20
#define Comm_Rece_Que 200
#define Usart1_BaudRate         115200
#define Usart2_BaudRate         115200
#define Usart3_BaudRate         9600

#define Comm_Err_Max     10000
#define Temp_Num 15
#define Comm3_Err_Max     3000
#define LunXun 0
#define CaoZuo 1



extern uint8_t zhiling;
extern uint8_t Buzzer_Flag ;
extern uint8_t Calibration_CH1_Buff[11] ;
extern uint8_t Calibration_CH2_Buff[11] ;
extern uint8_t Calibration_CH3_Buff[11] ;
extern uint8_t Calibration_CH4_Buff[11] ;
extern uint8_t Calibration_CH5_Buff[11] ;
extern uint8_t Calibration_CH6_Buff[11] ;
extern uint8_t Request_Power_Module[9] ;

extern uint8_t Open_All_CH_Buff[];
extern uint8_t Close_All_CH_Buff[];

extern uint8_t Open_CH1_Buff[];
extern uint8_t Open_CH2_Buff[];
extern uint8_t Open_CH3_Buff[];
extern uint8_t Open_CH4_Buff[];
extern uint8_t Open_CH5_Buff[];
extern uint8_t Open_CH6_Buff[];

extern uint8_t Close_CH1_Buff[];
extern uint8_t Close_CH2_Buff[];
extern uint8_t Close_CH3_Buff[];
extern uint8_t Close_CH4_Buff[];
extern uint8_t Close_CH5_Buff[];
extern uint8_t Close_CH6_Buff[];

extern uint8_t Status_Buff[Comm_Rece_Que];
extern  uint8_t Power_Module_Status_Buff[Comm_Rece_Que];


extern uint32_t ZL_Time;
extern uint32_t Lock_Code;

typedef struct
{
  uint8_t Comm_Err_Flag;    
	uint8_t Rece_Flag;	
	uint8_t Rece_Len;
	uint8_t Rece_Count;
	uint32_t Rece_Time;
	uint32_t Comm_Time;
	uint8_t ReceBuff[Comm_Rece_Que];
	uint8_t SendBuff[Comm_Que];
	}Communtion_TypeDef;
extern Communtion_TypeDef Comm_USART1;
extern Communtion_TypeDef Comm_USART2;
//extern Communtion_TypeDef Comm_USART3;
	/*
extern uint8_t Comm1_Err_Flag;
extern uint8_t Usart1_Rece_Flag;
extern uint8_t Usart1_Rece_Count;
extern uint32_t Usart1_Rece_Time;
extern uint32_t Usart1_Comm_Time;
extern uint8_t Usart1_ReceBuff[Comm_Que];
extern uint8_t Usart1_SendBuff[Comm_Que];

extern uint8_t Comm2_Err_Flag;
extern uint8_t Usart2_Rece_Flag;
extern uint8_t Usart2_Rece_Count;
extern uint32_t Usart2_Rece_Time;
extern uint32_t Usart2_Comm_Time;
extern uint8_t Usart2_SendBuff[Comm_Que];
	*/
extern uint8_t Usart3_Rece_Flag; 
extern uint8_t Usart3_SendBuff[Comm_Que];
extern uint8_t Usart3_ReceBuff[Comm_Rece_Que];
extern uint8_t Usart3_Rece_Count; 
extern uint8_t Usart3_Rece_Len; 
extern uint32_t Usart3_Rece_Time; 
extern uint8_t Comm3_Err_Flag;
extern uint16_t Comm3_Overtime_Count;
extern uint16_t Comm3_Overtime_Flag;
extern uint32_t ZL_Time;
extern uint16_t Roll_Err_Count;
extern uint8_t Usart3_Cabinet_Connect_Err_Flag;
extern uint8_t Usart3_Power_Connect_Err_Flag;

extern uint8_t Usart3_Rece_Flag;
extern uint8_t Usart3_SendBuff[Comm_Que];

extern uint8_t Comm3_Err_Flag;
extern uint32_t ZL_Time;
extern uint8_t Tx_Flag;

extern uint8_t Charge_flag;
extern uint16_t Start_Count;
extern uint32_t Run_Tim3_Flag;
extern uint16_t LCD_Update_Flag;//lcd������ʾ��־
extern uint16_t LCD_Power_Update_Flag;//lcd������ʾ��־
extern uint16_t LCD_Twinkle_Flag1;//lcd������ʾ��־
extern uint16_t LCD_Twinkle_Flag2;//lcd������ʾ��־
extern uint8_t tempnumber;

extern uint8_t Data_Read_Flag;

extern uint8_t System_Flag;//ϵͳ���н׶α�־
	//0������
	//1������
extern uint16_t System_State_Flag;//ϵͳ����״̬

extern uint32_t LCD_Show_Flag ;
extern uint8_t key;
extern uint8_t bai;
extern uint8_t qian;
extern uint8_t ge;


extern uint8_t CH1_Statu;
extern uint8_t CH2_Statu;
extern uint8_t CH3_Statu;
extern uint8_t CH4_Statu;
extern uint8_t CH5_Statu;
extern uint8_t CH6_Statu;

extern uint8_t CAL_Power_CH1_Vol1;
extern uint8_t CAL_Power_CH1_Vol2;
extern uint8_t CAL_Power_CH1_Cur1;
extern uint8_t CAL_Power_CH1_Cur2;

extern uint8_t CAL_Power_CH2_Vol1;
extern uint8_t CAL_Power_CH2_Vol2;
extern uint8_t CAL_Power_CH2_Cur1;
extern uint8_t CAL_Power_CH2_Cur2;

extern uint8_t CAL_Power_CH3_Vol1;
extern uint8_t CAL_Power_CH3_Vol2;
extern uint8_t CAL_Power_CH3_Cur1;
extern uint8_t CAL_Power_CH3_Cur2;

extern uint8_t CAL_Power_CH4_Vol1;
extern uint8_t CAL_Power_CH4_Vol2;
extern uint8_t CAL_Power_CH4_Cur1;
extern uint8_t CAL_Power_CH4_Cur2;

extern uint8_t CAL_Power_CH5_Vol1;
extern uint8_t CAL_Power_CH5_Vol2;
extern uint8_t CAL_Power_CH5_Cur1;
extern uint8_t CAL_Power_CH5_Cur2;

extern uint8_t CAL_Power_CH6_Vol1;
extern uint8_t CAL_Power_CH6_Vol2;
extern uint8_t CAL_Power_CH6_Cur1;
extern uint8_t CAL_Power_CH6_Cur2;

extern uint16_t CAL_Power_CH1_Current;
extern uint16_t CAL_Power_CH1_Voltage;

extern uint16_t CAL_Power_CH2_Current;
extern uint16_t CAL_Power_CH2_Voltage;

extern uint16_t CAL_Power_CH3_Current;
extern uint16_t CAL_Power_CH3_Voltage;

extern uint16_t CAL_Power_CH4_Current;
extern uint16_t CAL_Power_CH4_Voltage;

extern uint16_t CAL_Power_CH5_Current;
extern uint16_t CAL_Power_CH5_Voltage;

extern uint16_t CAL_Power_CH6_Current;
extern uint16_t CAL_Power_CH6_Voltage;

extern uint16_t Fixed_Addr ;
extern uint16_t Addr_Value ;


extern uint8_t KeyVal;					//��ֵ
extern uint8_t volatile KeyValue;
extern uint8_t INPUT_ENABLE;		//����ģʽʹ��
extern uint8_t Set_Ok_Flag ; //������ȷ��־
extern uint8_t Calibration_Flag; //У׼�����ѷ��ͱ�־λ
extern uint8_t Switch_Flag;//���������ѷ��ͱ�־λ

extern uint8_t Open_All_Flag;//ȫ�������ѷ��ͱ�־λ
extern uint8_t Close_All_Flag;//ȫ�������ѷ��ͱ�־λ
/********************************************************************/
extern uint8_t const  num_lcd[] ;		//�����ַ���
extern uint8_t num[Temp_Num];			//���ڴ�������Ѽ���λȨ������λ����ͬʱ��Ķ�
extern float DisVal;		//����������ֵ

extern uint8_t Task;

extern uint8_t KCnt,KSet,KOK,key_cnt;
extern uint16_t adcx;
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
//extern uint8_t XORValid(uint8_t *buffer,uint16_t Len);

/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
#endif

