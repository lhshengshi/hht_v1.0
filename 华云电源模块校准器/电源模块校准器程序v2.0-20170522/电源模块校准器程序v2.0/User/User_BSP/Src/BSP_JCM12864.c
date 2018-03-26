/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
 * �ļ���   ��BSP_JCM12864.C
 * ����     :
 * ����	 	  : MDK4.54-�̼���V3.5�汾
 * ʵ��ƽ̨ ��TOP9110-STM32F103RBT6-8MHz->72MHz
 * �汾     ��V1.0.0
 * ����     ��
 * �޸�ʱ�� ��2013-12-20
 * Ӳ������ : JCM12864�ӿ���STM32-GPIO
              JCM12864-1- VSS 		------ GND		    JCM12864-11-DB4	  ------
							JCM12864-2- VCC 		------ 5V			    JCM12864-12-DB5	  ------
							JCM12864-3- V0			------ 5V			    JCM12864-13-DB6	  ------
							JCM12864-4- RS(CS)	------ 5V			    JCM12864-14-DB7	  ------
							JCM12864-5- R/W(SID)------ PC0				JCM12864-15-PSB	  ------  GND
							JCM12864-6- E(SCLK)	------ PC1				JCM12864-16-NC	  ------
							JCM12864-7- DB0			------ 				    JCM12864-17-RESET	------  5V
							JCM12864-8- DB1			------ 				    JCM12864-18-VOUT	------
							JCM12864-9- DB2			------ 				    JCM12864-19-LED+	------  5V
							JCM12864-10-DB3			------ 				    JCM12864-20-LED-	------	PC2			
*******************************************************************************/
#include  "BSP_JCM12864_Demo.h"
#include  "BSP_JCM12864.h"
#include 	"Heard_Public.h"
#include  <stdlib.h>
#include "User_BSP.h"
/* Private defines--------------------------------------*/
#define  JCM12864_SID_H     GPIO_SetBits(JCM12864_GPIO,JCM12864_PIN_SID )	    //��
#define  JCM12864_SID_L     GPIO_ResetBits(JCM12864_GPIO,JCM12864_PIN_SID )   //��
#define  JCM12864_CLK_H     GPIO_SetBits(JCM12864_GPIO,JCM12864_PIN_CLK )	    //��
#define  JCM12864_CLK_L     GPIO_ResetBits(JCM12864_GPIO,JCM12864_PIN_CLK)    //��
#define  JCM12864_ON        GPIO_SetBits(GPIOA,JCM12864_PIN_BLC )	    //��
#define  JCM12864_OFF       GPIO_ResetBits(GPIOA,JCM12864_PIN_BLC )   //��

/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
//extern u8  Read_KeyValue();
void JCM12864_Delay(__IO uint32_t nCount);
 u8   JCM12864_GetByte(void);
void JCM12864_SendOneByte(unsigned char dat);
 void JCM12864_CheckBusy(void);//JCM12864_check_busy
 void JCM12864_SendCom(unsigned char cmd);
 void JCM12864_SendData(unsigned char dat);
 u8 Read_Data(void);
 void d_dian(u8 x,u8 y,u8 clor);
 void Check_Busy(void);
uint8_t Receive_Byte(void);
uint8_t const Lcd_Con_X_Y[4][2]={{0x80,0x80},{0x80,0x90},{0x88,0x80},{0x88,0x90}};        //LCD�з�����ʾ����
uint16_t LCD12864_Buffer[64][16] = {0};
uint8_t Local_Network_Tempbuff[] = {0};
uint8_t tempnumber = 0;//���Լ���ֵ
uint8_t Input_Mode_Flag = 0;

uint8_t Set_Port_Flag = 0;
uint8_t Set_IP_Flag = 0;
uint8_t IP[16] = {0};
uint8_t Port[16] = {0};
uint8_t Local_Port_Tempbuff[2] = {0x00,0x00};

//uint32_t Local_Port_Temp = 0;
//uint8_t Local_Port_Temp1 = 0;
//uint8_t Local_Port_Temp2 = 0;

//uint32_t Net_Server_Port_Temp = 0;
//uint8_t Net_Server_Port_Temp1 = 0;
//uint8_t Net_Server_Port_Temp2 = 0;

//uint32_t GPRS_Server_Port_Temp = 0;
//uint8_t GPRS_Server_Port_Temp1 = 0;
//uint8_t GPRS_Server_Port_Temp2 = 0;

uint8_t KeyVal = 0;					//��ֵ
uint8_t INPUT_ENABLE = 0;		//����ģʽʹ��
u8 Set_Ok_Flag = 0; //������ȷ��־
u8 Calibration_Flag = 0; //У׼�����ѷ��ͱ�־λ
u8 Switch_Flag = 0;//���������ѷ��ͱ�־λ

uint8_t Open_All_Flag = 0;//ȫ�������ѷ��ͱ�־λ
uint8_t Close_All_Flag = 0;//ȫ�������ѷ��ͱ�־λ
/********************************************************************/
uint8_t const  num_lcd[] = {"+1234567890. :-_/"};		//�����ַ���
//uint8_t num[Temp_Num] = {0} ;//������ʱ���飬���ڴ�������Ѽ���λȨ������λ����ͬʱ��Ķ�
uint8_t IP_num[Temp_Num] = {0x00};//�˿�������ʱ����
float DisVal = 0;		//����������ֵ
/* Private functions -----------------------------------*/
/**********************************************
*	�� �� ��: JCM12864_Init(void)
*	��    �Σ�
*	�� �� ֵ: 
*	����˵��: JCM12864���г�ʼ��				
**********************************************/ 
void JCM12864_Init(void) 
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(JCM12864_GPIO_CLK, ENABLE);

//	GPIO_InitStructure.GPIO_Pin = JCM12864_PIN_SID | JCM12864_PIN_CLK | JCM12864_PIN_BLT ;
	GPIO_InitStructure.GPIO_Pin = JCM12864_PIN_SID | JCM12864_PIN_CLK |JCM12864_PIN_CS ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(JCM12864_GPIO, &GPIO_InitStructure);
	GPIO_SetBits(JCM12864_GPIO,JCM12864_PIN_CS);
	//	  GPIO_SetBits(JCM12864_GPIO,JCM12864_PIN_BLT  );
	JCM12864_Delay(0xfff);
	JCM12864_SendCom(0x30);
	JCM12864_SendCom(0x0C);//0000,1100 ������ʾ���α�off���α�λ��off
	JCM12864_SendCom(0x01);//0000,0001 ��DDRAM
	JCM12864_SendCom(0x02);//0000,0010 DDRAM��ַ��λ
	JCM12864_SendCom(0x06);//0000,0010 DDRAM��ַ��λ
	JCM12864_SendCom(0x80);//1000,0000 �趨DDRAM 7λ��ַ000��0000����ַ������A
	JCM12864_clear();
	Delay_ms(10);
	Draw_Clear();					// ����
}

void Draw_Clear(void) 
{
	u8 x, y;

	for (y=0; y<64; y++)
	{
		for (x=0; x<16; x++)
		{
			LCD12864_Buffer[y][x] = 0;
		}
	}
}


/**********************************************
*	�� �� ��: JCM12864_clear(void) 
*	��    �Σ�
*	�� �� ֵ: 
*	����˵��: �����ʾ		
**********************************************/ 
void JCM12864_clear(void)        //�����ʾ
{
    JCM12864_SendCom(0x01);
}

//***********************************
//�趨xyλ��

//*********************************
void LCD_Set_XY(u8 X, u8 Y)	//�趨��ʾ����
{ 
	u8 address;
	switch(X)
	{
		case 0:
		 address = 0x80 + Y;//��һ���׵�ַ0x80
		 break;   
		case 1:
		 address = 0x90 + Y;//�ڶ����׵�ַ0x90
		 break;
		case 2:
		 address = 0x88 + Y;//�������׵�ַ0x88
		 break;
		case 3:
		 address = 0x98 + Y;//�������׵�ַ0x98
		 break;
		default:
		 address = 0x80 + Y;
		 break;
	}
	JCM12864_SendCom(address);
}


/**********************************************
*	�� �� ��: JCM12864_Display_String(uint8_t row,uint8_t col, unsigned char *str)
*	��    �Σ�row���У�0-3��,col���У�0-7��, *str
*	�� �� ֵ: 
*	����˵��: ��ָ����λ����ʾ�ַ���*str				
**********************************************/ 
void JCM12864_Display_String(uint8_t row,uint8_t col, unsigned char *str)    
{
    unsigned char i,temp;
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
    for(i=0;str[i]!='\0';i++)
    {
        JCM12864_SendData(str[i]);  
    }

}
/**********************************************
*	�� �� ��: JCM12864_Display_Number(uint8_t row,uint8_t col, unsigned char Number)
*	��    �Σ�row���У�0-3��,col���У�0-7��, Number��0-999��
*	�� �� ֵ: 
*	����˵��: ��ָ����λ����ʾ����Number	
**********************************************/ 
void JCM12864_Display_Number(uint8_t  row,uint8_t  col,u16 Number)
{  
	uint8_t  temp;
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
  if((Number/100)>0)		//����ʾ0
		JCM12864_SendData(((Number/100)+0x30));  //��λ��ʾ
	if((Number/10)>0)		
		JCM12864_SendData((((Number/10)%10)+0x30));//��ʾʮλ
	JCM12864_SendData(((Number%10)+0x30));	//��ʾ��λ
//	JCM12864_SendData((0x2e));	//��ʾС����
}

/**********************************************
*	�� �� ��: void JCM12864_Display_Point(uint8_t  row,uint8_t  col);//���κ�λ��дС����
*	��    �Σ�row���У�0-3��,col���У�0-7��, Number��0-999��
*	�� �� ֵ: 
*	����˵��: ��ָ����λ����ʾ����Number	
**********************************************/ 
void JCM12864_Display_Point(uint8_t  row,uint8_t  col)//���κ�λ��дС����
{  
	uint8_t  temp;
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
	JCM12864_SendData(0x20);	//��ʾС����
	JCM12864_SendData(0x2e);	//��ʾС����
}


void JCM12864_Display_Power_Channel_Voltage(u8 row,u8 col,u8 channelx_vol1,u8 channelx_vol2)
{
	uint8_t  temp = 0;
	uint16_t  channelx_vol_temp = 0;
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
	channelx_vol_temp = ((channelx_vol1<<8) + channelx_vol2);
	if(channelx_vol_temp > 5000)
	{
		JCM12864_Display_String(row,col,"�쳣");
	}
	else
	{
		channelx_vol_temp = channelx_vol_temp/10;
		if((channelx_vol_temp/100)>0)		//����ʾ0
		JCM12864_SendData(((channelx_vol_temp/100)+0x30));  //��λ��ʾ
		if((channelx_vol_temp/10)>0)		
		JCM12864_SendData((((channelx_vol_temp/10)%10)+0x30));//��ʾʮλ
		JCM12864_SendData(((channelx_vol_temp%10)+0x30));	//��ʾ��λ
		JCM12864_SendData((0x56));//��ʾ��λV		
	}
}

void JCM12864_Display_Power_Channel_Current(u8 row,u8 col,u8 channelx_cur1,u8 channelx_cur2)
{
	uint8_t  temp = 0;
	uint16_t  channelx_cur_temp = 0;
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
	
	channelx_cur_temp = ((channelx_cur1<<8) + channelx_cur2);
	if(channelx_cur_temp > 99)
	{
		JCM12864_Display_String(row,col,"�쳣");
	}
	else
	{
//		channelx_cur_temp = channelx_cur_temp/10;
		if((channelx_cur_temp/100)>0)		//����ʾ0
		JCM12864_SendData(((channelx_cur_temp/100)+0x30));  //��λ��ʾ
		if((channelx_cur_temp/10)>0)		
		JCM12864_SendData((((channelx_cur_temp/10)%10)+0x30));//��ʾʮλ
		else 
		JCM12864_SendData((0x30));//��ʾ0
		JCM12864_SendData((0x2e));//��ʾС����
		JCM12864_SendData((channelx_cur_temp%10)+0x30);//��ʾС��
		JCM12864_SendData((0x41));//��ʾ��λA	
	}
	
}

/****Static Private functions***********************/
 void JCM12864_Delay(__IO uint32_t nCount)
{
   for(; nCount != 0; nCount--);
}
 void JCM12864_SendOneByte(unsigned char dat)//
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
			if(((dat<<i)&0x80)==0x80) {JCM12864_SID_H;}	
			else {JCM12864_SID_L;}
      JCM12864_CLK_H;
			JCM12864_Delay(20);
      JCM12864_CLK_L;
			JCM12864_Delay(20);				
    }
}
 u8 JCM12864_GetByte(void)
{
     unsigned char i,temp1=0,temp2=0;     
     for(i=0;i<8;i++)   
     {   
           temp1=temp1<<1;   
           JCM12864_CLK_L;  
					 JCM12864_Delay(20);
           JCM12864_CLK_H;  
					 JCM12864_Delay(20);             
           JCM12864_CLK_L;   
           if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_13)) temp1++;   
     }   
     for(i=0;i<8;i++)   
     {   
           temp2=temp2<<1;   
           JCM12864_CLK_L;  
					JCM12864_Delay(20);  
           JCM12864_CLK_H; 
					JCM12864_Delay(20);   
           JCM12864_CLK_L;   
           if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_13))  temp2++;   
     }   
     return ((0xf0&temp1)+(0x0f&temp2));   
}
void JCM12864_CheckBusy(void)
{
    do
    {
        JCM12864_SendOneByte(0xfc);
    }
    while((JCM12864_GetByte()&0x8000)==0x8000);
}
 void JCM12864_SendCom(unsigned char cmd)
{
	JCM12864_CheckBusy();
	JCM12864_SendOneByte(0xf8);    //
	JCM12864_SendOneByte(cmd&0xf0); //
	JCM12864_SendOneByte((cmd&0x0f)<<4); //
}
 void JCM12864_SendData(unsigned char dat)
{
	JCM12864_CheckBusy();
	JCM12864_SendOneByte(0xfa);//rw=0;rs=1
	JCM12864_SendOneByte(dat&0xf0);
	JCM12864_SendOneByte((dat&0x0f)<<4);
}




/*********************************************************
* Function Name  : LCD_Clear_BMP
* Description    : ͼƬ�����
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
void LCD_Clear_BMP( void )
{
	u8 i,j;
	JCM12864_SendCom(0x34);      //8Bit����ָ�,��ʹ��36HҲҪд����
	JCM12864_SendCom(0x36);      //��ͼON,����ָ�����36H���ܿ���ͼ
	for(i=0;i<32;i++)            //12864ʵ��Ϊ256x32
	{
		JCM12864_SendCom(0x80|i);      //��λ��
		JCM12864_SendCom(0x80);      //��λ��
		for(j=0;j<32;j++)            //256/8=32 byte
			JCM12864_SendData(0);
	}
	JCM12864_SendCom(0x30);
}

 u8 Read_Data(void)
{
	JCM12864_CheckBusy();
	JCM12864_SendData(0xfe);    //11111��RW(1),RS(1),0 LCD->MCU
	return  JCM12864_GetByte();
}

/*********************************************************
* Function Name  : Receive_Byte
* Description    : ��LCD����
* Input          : None
* Output         : None
* Return         : temp1+temp2
*********************************************************/
u8 Receive_Byte(void)
{
	u8 i,temp1,temp2,value;
	temp1=0;
	temp2=0;
	for(i=0;i<8;i++)
	{
		temp1=temp1<<1;
		JCM12864_CLK_L;
		JCM12864_CLK_H;
		JCM12864_CLK_L;
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13))
		{
			temp1++;
		}
	}
	for(i=0;i<8;i++)
	{
		temp2=temp2<<1;
		JCM12864_CLK_L;
		JCM12864_CLK_H;
		JCM12864_CLK_L;
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13))
		{
			temp2++;
		}
	}
	temp1=0xf0&temp1;
	temp2=0x0f&temp2;
	value=temp1+temp2;
	return   value ;
}




void lcd_address(uint16_t page,uint16_t column)
{
	column=column-0x01;
	JCM12864_SendCom(0xb0+page-1);   /*����ҳ��ַ*/ //1-8
	JCM12864_SendCom(0x10+(column>>4&0x0f));	/*�����е�ַ�ĸ�4λ*///0-128
	JCM12864_SendCom(column&0x0f);	/*�����е�ַ�ĵ�4λ*/	
}

/*��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��*/
void display_graphic_16x16(uint16_t page,uint16_t column,uint8_t *dp)
{
	uint16_t i,j;
 	LCD_CS_RESET;	
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<16;i++)
		{	
			JCM12864_SendData(*dp);	 /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
			dp++;
		}
	}
	LCD_CS_SET;
	//delay_us(5);
}


/*��ʾ8x16����ͼ��ASCII, ��8x16����������ַ�������ͼ��*/
void display_graphic_8x16(uint16_t page,uint8_t column,uint8_t *dp)
{
	uint16_t i,j;
	LCD_CS_SET;	
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<8;i++)
		{	
			JCM12864_SendData(*dp);	 	/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
			dp++;
		}
	}
	LCD_CS_RESET;
}

/*********************************************************
��ֲ4*5������ʾ���̳���
������: LCD_Clear_BMP
����ֵ����
��  ��:	ͼƬ�����
*********************************************************/
//**********************************
/*********************************************************
������: Display_LCD_Pos
����ֵ����
��  ��:������ʾλ��
*********************************************************/
void Display_LCD_Pos(u8 x,u8 y) 
{
 u8 pos;
 switch(x)
		 {
			case 0: x=0x80;break;
		case 1: x=0x90;break;
			case 2: x=0x88;break;
		case 3: x=0x98;break;
	 }
 pos=x+y;
 JCM12864_SendCom(pos);
 }
/*********************************************************
������:Display_LCD_String()
����ֵ����
��  ��:��ʾ�ַ���
*********************************************************/

void Display_LCD_String(u8 x,u8 *p,u8 time)
	{
	 u8 i,addr,num;
	 num=sizeof p;
	 switch(x)
	     {
		   	 case 0: addr=0x80;break;
		   	 case 1: addr=0x90;break;
		   	 case 2: addr=0x88;break;
		   	 case 3: addr=0x98;break;
		 }
	  JCM12864_SendCom(addr);
	  for(i=0;i<(num*4);i++)
	     {
		   JCM12864_SendData(*(p++));
		   Delay_ms(time);
		 
		 }

	}




/**********************************************
*	�� �� ��: void Choose_Bit(u8 X, u8 Y,u8 PART,u8 val)
*	��    �Σ�row���У�0-3��,col���У�0-7��, port��0 OR 1��
*	�� �� ֵ: none
*	����˵��: //�����ֵλ��˸ part 0����λ part 1;��λ val �����ֵ
**********************************************/ 

void Choose_Bit(u8 X, u8 Y,u8 PART,u8 val)//"_"��˸Ч��������λ��ѡ��,partΪǰ�˸���˸�(0,1)
{
	if(PART==0)
	{
		if(LCD_Twinkle_Flag1 == 500)
		{
//			Delay_ms(370);
			Display_LCD_Pos( X, Y );
			JCM12864_SendData(0x20);	//��ʾ�ո�
			JCM12864_SendData(0x20);	//��ʾ�ո�
		}
		
		else if(LCD_Twinkle_Flag1 == 1000)
		{
//			Delay_ms(370);
			Display_LCD_Pos( X, Y );
			JCM12864_SendData(0x5f);	//��ʾ"_"
			JCM12864_SendData(0x20);	//��ʾ�ո�
			LCD_Twinkle_Flag1 = 0;
		}
	}
	else if(PART==1)
	{
		if(LCD_Twinkle_Flag2 == 500)
		{
			Display_LCD_Pos( X, Y );
			if(val == 11)
			{
				JCM12864_SendData(0x2e);	//��ʾ  .
			}
			else
			{
				JCM12864_SendData(val+0x30);	//��ʾǰһλ��
			}
			JCM12864_SendData(0x20);	//��ʾ�ո�
		}
		else if(LCD_Twinkle_Flag2 == 1000)
		{
			Display_LCD_Pos( X, Y );
			if(val == 11)
			{
				JCM12864_SendData(0x2e);//��ʾ .
			}
			else
			{
				JCM12864_SendData(val+0x30);//��ʾǰһλ��
			}
			
			JCM12864_SendData(0x5f);	//��ʾ"_"
			LCD_Twinkle_Flag2 = 0;
		}
		
	}
}


/**********************************************
*	�� �� ��: void LCD_Write_Number(u8 s)	//��ʾ����
*	��    �Σ�u8 s
*	�� �� ֵ: none
*	����˵��: //��ʾ����
**********************************************/ 
void LCD_Write_Number(u8 s)	//��ʾ����
{ 
	JCM12864_SendData(num_lcd[s]);
	Delay_ms(1);	
}



void BSP_JCM12864_DemoFF(void)
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);			
	JCM12864_Display_String(0,0,"��ӭʹ��У׼����");
	JCM12864_Display_String(1,0,"���ڻ�ȡͨ������");
	JCM12864_Display_String(2,0,"���Ժ�......");
}

//void BSP_JCM12864_Demo61(void)
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"  ��ѯ����״̬");
//	JCM12864_Display_String(1,0,"  ��������ģ��");
//	JCM12864_Display_String(2,0,"  ���ù���ģ��");
//	JCM12864_Display_String(3,0,">>У׼��Դģ��");	
//}

void BSP_JCM12864_Demo100(void)
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,">>У׼��Դģ��  ");
	JCM12864_Display_String(1,0,"  ���Ե�Դģ��  ");
	JCM12864_Display_String(2,0,"  �ر�ȫ��ͨ��  ");
	JCM12864_Display_String(3,0,"  ����ȫ��ͨ��  ");	
}

void BSP_JCM12864_Demo101(void)
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"  У׼��Դģ��  ");
	JCM12864_Display_String(1,0,">>���Ե�Դģ��  ");
	JCM12864_Display_String(2,0,"  �ر�ȫ��ͨ��  ");
	JCM12864_Display_String(3,0,"  ����ȫ��ͨ��  ");
}

void BSP_JCM12864_Demo102(void)
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"  У׼��Դģ��  ");
	JCM12864_Display_String(1,0,"  ���Ե�Դģ��  ");
	JCM12864_Display_String(2,0,">>�ر�ȫ��ͨ��  ");
	JCM12864_Display_String(3,0,"  ����ȫ��ͨ��  ");	
}

void BSP_JCM12864_Demo103(void)
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"  У׼��Դģ��  ");
	JCM12864_Display_String(1,0,"  ���Ե�Դģ��  ");
	JCM12864_Display_String(2,0,"  �ر�ȫ��ͨ��  ");
	JCM12864_Display_String(3,0,">>����ȫ��ͨ��  ");
}

void BSP_JCM12864_Demo111(void)//ͨ��1 ״̬
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��        ״̬");
	JCM12864_Display_String(1,0,">>1:            ");
	JCM12864_Display_String(2,0,"  2:            ");
	JCM12864_Display_String(3,0,"  3:            ");
	
	if(CH1_Statu == 0x11)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH2_Statu == 0x21)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH3_Statu == 0x31)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo112(void)//ͨ��2 ״̬
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��        ״̬");
	JCM12864_Display_String(1,0,"  1:            ");
	JCM12864_Display_String(2,0,">>2:            ");
	JCM12864_Display_String(3,0,"  3:            ");
	
	if(CH1_Statu == 0x11)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH2_Statu == 0x21)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH3_Statu == 0x31)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo113(void)//ͨ��3 ״̬
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��        ״̬");
	JCM12864_Display_String(1,0,"  1:            ");
	JCM12864_Display_String(2,0,"  2:            ");
	JCM12864_Display_String(3,0,">>3:            ");
	
	if(CH1_Statu == 0x11)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH2_Statu == 0x21)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH3_Statu == 0x31)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo114(void)//ͨ��4 ״̬
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��        ״̬");
	JCM12864_Display_String(1,0,">>4:            ");
	JCM12864_Display_String(2,0,"  5:            ");
	JCM12864_Display_String(3,0,"  6:            ");
	
	if(CH4_Statu == 0x41)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH5_Statu == 0x51)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH6_Statu == 0x61)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo115(void)//ͨ��5 ״̬
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��        ״̬");
	JCM12864_Display_String(1,0,"  4:            ");
	JCM12864_Display_String(2,0,">>5:            ");
	JCM12864_Display_String(3,0,"  6:            ");
	
	if(CH4_Statu == 0x41)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH5_Statu == 0x51)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH6_Statu == 0x61)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo116(void)//ͨ��6 ״̬
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��        ״̬");
	JCM12864_Display_String(1,0,"  4:            ");
	JCM12864_Display_String(2,0,"  5:            ");
	JCM12864_Display_String(3,0,">>6:            ");
	
	if(CH4_Statu == 0x41)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH5_Statu == 0x51)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH6_Statu == 0x61)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}

void BSP_JCM12864_Demo121(void)//����ͨ��1״̬
{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��        ״̬");
//	JCM12864_Display_String(1,0,">>1:            ");
//	JCM12864_Display_String(2,0,"  2:            ");
//	JCM12864_Display_String(3,0,"  3:            ");
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");
	if(CH1_Statu == 0x11)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH2_Statu == 0x21)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH3_Statu == 0x31)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo122(void)//����ͨ��2״̬
{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��        ״̬");
//	JCM12864_Display_String(1,0,"  1:            ");
//	JCM12864_Display_String(2,0,">>2:            ");
//	JCM12864_Display_String(3,0,"  3:            ");
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");
	if(CH1_Statu == 0x11)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH2_Statu == 0x21)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH3_Statu == 0x31)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo123(void)//����ͨ��3״̬
{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

////	JCM12864_Display_String(0,0,"ͨ��        ״̬");
//	JCM12864_Display_String(1,0,"  1:            ");
//	JCM12864_Display_String(2,0,"  2:            ");
//	JCM12864_Display_String(3,0,">>3:            ");
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");
	if(CH1_Statu == 0x11)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH2_Statu == 0x21)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH3_Statu == 0x31)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo124(void)//����ͨ��4״̬
{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

////	JCM12864_Display_String(0,0,"ͨ��        ״̬");
//	JCM12864_Display_String(1,0,">>4:            ");
//	JCM12864_Display_String(2,0,"  5:            ");
//	JCM12864_Display_String(3,0,"  6:            ");
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");
	if(CH4_Statu == 0x41)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH5_Statu == 0x51)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH6_Statu == 0x61)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo125(void)//����ͨ��5״̬
{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

////	JCM12864_Display_String(0,0,"ͨ��        ״̬");
//	JCM12864_Display_String(1,0,"  4:            ");
//	JCM12864_Display_String(2,0,">>5:            ");
//	JCM12864_Display_String(3,0,"  6:            ");
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");
	if(CH4_Statu == 0x41)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH5_Statu == 0x51)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH6_Statu == 0x61)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo126(void)//����ͨ��6״̬
{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

////	JCM12864_Display_String(0,0,"ͨ��        ״̬");
//	JCM12864_Display_String(1,0,"  4:            ");
//	JCM12864_Display_String(2,0,"  5:            ");
//	JCM12864_Display_String(3,0,">>6:            ");
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");
	if(CH4_Statu == 0x41)
	{
		JCM12864_Display_String(1,6,"����");
	}
	else 
	{
		JCM12864_Display_String(1,6,"�ر�");
	}
	if(CH5_Statu == 0x51)
	{
		JCM12864_Display_String(2,6,"����");
	}
	else 
	{
		JCM12864_Display_String(2,6,"�ر�");
	}
	if(CH6_Statu == 0x61)
	{
		JCM12864_Display_String(3,6,"����");
	}
	else 
	{
		JCM12864_Display_String(3,6,"�ر�");
	}
}
void BSP_JCM12864_Demo62(void)
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,">>1:            ");
	JCM12864_Display_String(2,0,"  2:            ");
	JCM12864_Display_String(3,0,"  3:            ");
	
	if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}
	
	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
//	JCM12864_Display_Power_Channel_Voltage(2,4,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
//	JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
//	JCM12864_Display_Power_Channel_Voltage(3,4,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
//	JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
}
void BSP_JCM12864_Demo63(void)
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,"  1:            ");
	JCM12864_Display_String(2,0,">>2:            ");
	JCM12864_Display_String(3,0,"  3:            ");
		if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}
	
	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
	
//	JCM12864_Display_Power_Channel_Voltage(1,4,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
//	JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
//	JCM12864_Display_Power_Channel_Voltage(2,4,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
//	JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
//	JCM12864_Display_Power_Channel_Voltage(3,4,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
//	JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
}
void BSP_JCM12864_Demo64(void)
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,"  1:            ");
	JCM12864_Display_String(2,0,"  2:            ");
	JCM12864_Display_String(3,0,">>3:            ");
	
		if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}
	
	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
	
//	JCM12864_Display_Power_Channel_Voltage(1,4,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
//	JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
//	JCM12864_Display_Power_Channel_Voltage(2,4,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
//	JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
//	JCM12864_Display_Power_Channel_Voltage(3,4,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
//	JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
}
void BSP_JCM12864_Demo65(void)//ͨ��4
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,">>4:            ");
	JCM12864_Display_String(2,0,"  5:            ");
	JCM12864_Display_String(3,0,"  6:            ");
	if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
}

void BSP_JCM12864_Demo66(void)//ͨ��5
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,"  4:            ");
	JCM12864_Display_String(2,0,">>5:            ");
	JCM12864_Display_String(3,0,"  6:            ");
		if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
}
void BSP_JCM12864_Demo67(void)//ͨ��6
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,"  4:            ");
	JCM12864_Display_String(2,0,"  5:            ");
	JCM12864_Display_String(3,0,">>6:            ");
		if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
}

void BSP_JCM12864_Demo72(void)//������ʾ1
{
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,">>1:            ");
//	JCM12864_Display_String(2,0,"  2:            ");
//	JCM12864_Display_String(3,0,"  3:            ");
	if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}

	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
}
void BSP_JCM12864_Demo73(void)//������ʾ2
{
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");


//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  1:            ");
//	JCM12864_Display_String(2,0,">>2:            ");
//	JCM12864_Display_String(3,0,"  3:            ");
	if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}
	
	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
}
void BSP_JCM12864_Demo74(void)//������ʾ3
{
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  1:            ");
//	JCM12864_Display_String(2,0,"  2:            ");
//	JCM12864_Display_String(3,0,">>3:            ");
	if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}
	
	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
}
void BSP_JCM12864_Demo75(void)//������ʾ4
{
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,">>4:            ");
//	JCM12864_Display_String(2,0,"  5:            ");
//	JCM12864_Display_String(3,0,"  6:            ");
	if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
}
void BSP_JCM12864_Demo76(void)//������ʾ5
{
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  4:            ");
//	JCM12864_Display_String(2,0,">>5:            ");
//	JCM12864_Display_String(3,0,"  6:            ");
	if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
}
void BSP_JCM12864_Demo77(void)//������ʾ6
{
	JCM12864_Display_String(1,2,"            ");
	JCM12864_Display_String(2,2,"            ");
	JCM12864_Display_String(3,2,"            ");

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  4:            ");
//	JCM12864_Display_String(2,0,"  5:            ");
//	JCM12864_Display_String(3,0,">>6:            ");
		if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
}

void BSP_JCM12864_Demo82(void)//У׼ͨ��1
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,">>1:            ");
	JCM12864_Display_String(2,0,"  2:            ");
	JCM12864_Display_String(3,0,"  3:            ");
	if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}
	
	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
	Task = CaoZuo;
	while(!Calibration_Flag)
	{
		Calibration_CH1();
	}
	Calibration_Flag = 0;
	Task = LunXun;
	zhiling = 0;
}

uint8_t Calibration_CH1(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;	
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Calibration_CH1_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Calibration_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count=0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(1,0,"ͨ��һУ׼�ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(1,0,"ͨ��һУ׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(1,0,"ͨ��һУ׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(1,0,"ͨ��һУ׼ʧ�ܣ�");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(1,0,"���Դͨ��ʧ�ܣ�");
		Calibration_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return Connect_Error;
	}
}

//void BSP_JCM12864_Demo83(void)//У׼ͨ��2
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  1: 220V 9.9A");
//	JCM12864_Display_String(2,0,">>2: 220V 9.9A");
//	JCM12864_Display_String(3,0,"  3: 220V 9.9A");
//}
//void BSP_JCM12864_Demo84(void)//У׼ͨ��3
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  1: 220V 9.9A");
//	JCM12864_Display_String(2,0,"  2: 220V 9.9A");
//	JCM12864_Display_String(3,0,">>3: 220V 9.9A");
//}
//void BSP_JCM12864_Demo85(void)//У׼ͨ��4
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,">>4: 220V 9.9A");
//	JCM12864_Display_String(2,0,"  5: 220V 9.9A");
//	JCM12864_Display_String(3,0,"  6: 220V 9.9A");
//}
//void BSP_JCM12864_Demo86(void)//У׼ͨ��5
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  4: 220V 9.9A");
//	JCM12864_Display_String(2,0,">>5: 220V 9.9A");
//	JCM12864_Display_String(3,0,"  6: 220V 9.9A");
//}
//void BSP_JCM12864_Demo87(void)//У׼ͨ��6
//{
//	JCM12864_Init(); 
//	JCM12864_clear();
//	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  4: 220V 9.9A");
//	JCM12864_Display_String(2,0,"  5: 220V 9.9A");
//	JCM12864_Display_String(3,0,">>6: 220V 9.9A");
//}


void BSP_JCM12864_Demo83(void)//У׼ͨ��2
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,"  1:            ");
	JCM12864_Display_String(2,0,">>2:            ");
	JCM12864_Display_String(3,0,"  3:            ");
	if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}
	
	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
	Task = CaoZuo;
	while(!Calibration_Flag)
	{
		Calibration_CH2();
	}
	Calibration_Flag = 0;
	Task = LunXun;
	zhiling = 0;
}

uint8_t Calibration_CH2(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;	
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Calibration_CH2_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Calibration_Flag = 1;
			ZL_Time = 0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(2,0,"ͨ����У׼�ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(2,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(2,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(2,0,"ͨ����У׼ʧ�ܣ�");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(2,0,"���Դͨ��ʧ�ܣ�");
		Calibration_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return Connect_Error;
	}
}

void BSP_JCM12864_Demo84(void)//У׼ͨ��3
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,"  1:            ");
	JCM12864_Display_String(2,0,"  2:            ");
	JCM12864_Display_String(3,0,">>3:            ");
	if(CAL_Power_CH1_Voltage > 5000)//ͨ��1
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH1_Vol1,CAL_Power_CH1_Vol2);
	}
	
	if(CAL_Power_CH1_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH1_Cur1,CAL_Power_CH1_Cur2);
	}
	
	if(CAL_Power_CH2_Voltage > 5000)//ͨ��2
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH2_Vol1,CAL_Power_CH2_Vol2);
	}
	
	if(CAL_Power_CH2_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH2_Cur1,CAL_Power_CH2_Cur2);
	}
	
	if(CAL_Power_CH3_Voltage > 5000)//ͨ��3
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH3_Vol1,CAL_Power_CH3_Vol2);
	}
	
	if(CAL_Power_CH3_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH3_Cur1,CAL_Power_CH3_Cur2);
	}
	Task = CaoZuo;
	while(!Calibration_Flag)
	{
		Calibration_CH3();
	}
	Calibration_Flag = 0;
	Task = LunXun;
	zhiling = 0;
}

uint8_t Calibration_CH3(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;	
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Calibration_CH3_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Calibration_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count=0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(3,0,"ͨ����У׼�ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(3,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(3,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(3,0,"ͨ����У׼ʧ�ܣ�");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(3,0,"���Դͨ��ʧ�ܣ�");
		Calibration_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return Connect_Error;
	}
}

void BSP_JCM12864_Demo85(void)//У׼ͨ��4
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,">>4:            ");
	JCM12864_Display_String(2,0,"  5:            ");
	JCM12864_Display_String(3,0,"  6:            ");
	if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
	Task = CaoZuo;
	while(!Calibration_Flag)
	{
		Calibration_CH4();
	}
	Calibration_Flag = 0;
	Task = LunXun;
	zhiling = 0;
}

uint8_t Calibration_CH4(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;	
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Calibration_CH4_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Calibration_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count=0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(1,0,"ͨ����У׼�ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(1,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(1,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(1,0,"ͨ����У׼ʧ�ܣ�");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(1,0,"���Դͨ��ʧ�ܣ�");
		Calibration_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return Connect_Error;
	}
}

void BSP_JCM12864_Demo86(void)//У׼ͨ��5
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,"  4:            ");
	JCM12864_Display_String(2,0,">>5:            ");
	JCM12864_Display_String(3,0,"  6:            ");
	if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
	Task = CaoZuo;
	while(!Calibration_Flag)
	{
		Calibration_CH5();
	}
	Calibration_Flag = 0;
	Task = LunXun;
	zhiling = 0;
}

uint8_t Calibration_CH5(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;	
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Calibration_CH5_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Calibration_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count=0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(2,0,"ͨ����У׼�ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(2,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(2,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(2,0,"ͨ����У׼ʧ�ܣ�");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(2,0,"���Դͨ��ʧ�ܣ�");
		Calibration_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return Connect_Error;
	}
}

void BSP_JCM12864_Demo87(void)//У׼ͨ��6
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);

//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	JCM12864_Display_String(1,0,"  4:            ");
	JCM12864_Display_String(2,0,"  5:            ");
	JCM12864_Display_String(3,0,">>6:            ");
	if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
	{
		JCM12864_Display_String(1,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
	}
	
	if(CAL_Power_CH4_Current > 99)
	{
		JCM12864_Display_String(1,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
	}
	
	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
	{
		JCM12864_Display_String(2,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
	}
	
	if(CAL_Power_CH5_Current > 99)
	{
		JCM12864_Display_String(2,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
	}
	
	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
	{
		JCM12864_Display_String(3,3,"�쳣");
	}
	else
	{
		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
	}
	
	if(CAL_Power_CH6_Current > 99)
	{
		JCM12864_Display_String(3,6,"�쳣");
	}
	else 
	{
		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
	}
	Task = CaoZuo;
	while(!Calibration_Flag)
	{
		Calibration_CH6();
	}
	Calibration_Flag = 0;
	Task = LunXun;
	zhiling = 0;
}

uint8_t Calibration_CH6(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;	
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��        ״̬");
	Usart3_Send(Calibration_CH6_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Calibration_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count=0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(3,0,"ͨ����У׼�ɹ���");
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(3,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(3,0,"ͨ����У׼ʧ�ܣ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(3,0,"ͨ����У׼ʧ�ܣ�");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(3,0,"���Դͨ��ʧ�ܣ�");
		Calibration_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return Connect_Error;
	}
}

void BSP_JCM12864_Demo130(void)//ȫ��
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);
//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  4:            ");
//	JCM12864_Display_String(2,0,"  5:            ");
//	JCM12864_Display_String(3,0,">>6:            ");
//	if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
//	{
//		JCM12864_Display_String(1,3,"�쳣");
//	}
//	else
//	{
//		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
//	}
//	
//	if(CAL_Power_CH4_Current > 99)
//	{
//		JCM12864_Display_String(1,6,"�쳣");
//	}
//	else 
//	{
//		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
//	}
//	
//	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
//	{
//		JCM12864_Display_String(2,3,"�쳣");
//	}
//	else
//	{
//		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
//	}
//	if(CAL_Power_CH5_Current > 99)
//	{
//		JCM12864_Display_String(2,6,"�쳣");
//	}
//	else 
//	{
//		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
//	}
//	
//	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
//	{
//		JCM12864_Display_String(3,3,"�쳣");
//	}
//	else
//	{
//		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
//	}
//	
//	if(CAL_Power_CH6_Current > 99)
//	{
//		JCM12864_Display_String(3,6,"�쳣");
//	}
//	else 
//	{
//		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
//	}
	Task = CaoZuo;
	while(!Switch_Flag)
	{
		Close_All_CH();
	}
	Switch_Flag = 0;
	Task = LunXun;
	zhiling = 0;
}

//uint8_t HHT_Restart_Cabinet(void)//��������
//{
//	u8 Length_IN = 0;
//	uint8_t j=0;
//	Usart3_Rece_Count=0;
//	Usart3_Rece_Flag = 0;
//	while(!key||((key != 20)&&(key != 18)&&(key != 15))/*||(i == 0 && ( key == 10 ))*/)//"0","."��ֹ�ڵ�һλ���룬���������ּ�����ļ�ֵ
//	{
//		key = Read_KeyValue();
//	}
//	if(key)
//	{
//		if(Buzzer_Flag == 1)
//		{
//			BEEP = 1;
//			Delay_ms(30);
//			BEEP = 0;
//		}
//		if(key == 15)
//		{
//			Set_Ok_Flag = 1;
//			LCD_Show_Flag = 0;
//			Home_Flag = 1;
//			key = 0;
//			return 0;
//		}
//		else if(key == 20)
//		{
//			for(j=0;j<15;j++)
//			{
//				Usart3_SendBuff[j]=Restart_Cabinet[j];//����״̬
//			}
//			Usart3_Send(Usart3_SendBuff,15);//����
//			Delay_ms(1000);
//			if(Usart3_Rece_Flag == 1)
//			{
//				Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 14;
//				if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
//				{
//					if ((Usart3_ReceBuff[14] == 0xaa)&&(Usart3_ReceBuff[12] == 0x00)&&(Usart3_ReceBuff[13] == 0x0C))
//					{
//						Set_Ok_Flag = 1;

//						JCM12864_Display_String(0,0,"�����ǻ��ն˳ɹ�");
//						JCM12864_Display_String(1,0,"���ڻ�ȡ�������");
//	//					JCM12864_Display_String(1,0,"                ");
//						JCM12864_Display_String(2,0,"                ");
//						JCM12864_Display_String(3,0,"                ");
//						Delay_s(8);
//						LCD_Show_Flag =  40;
//						zhiling = 2;
//						ZL_Time=0;
//						Usart3_Rece_Count=0;
//						Usart3_Rece_Flag = 0;
//						Sys_Soft_Reset();
//					}
//					else if ((Usart3_ReceBuff[14] == 0x55)&&(Usart3_ReceBuff[12] == 0x00)&&(Usart3_ReceBuff[13] == 0x0C))
//					{
//						Set_Ok_Flag = 1;
//						JCM12864_Display_String(3,0,"�����ǻ��ն�ʧ��");
//						Delay_s(2);
//						zhiling = 2;
//						ZL_Time=0;
//						Usart3_Rece_Count=0;
//						Usart3_Rece_Flag = 0;			
//					}
//					else 
//					{
//						Set_Ok_Flag = 1;
//						Delay_s(2);
//						JCM12864_Display_String(3,0,"ָ������    ");
//						zhiling = 2;
//						ZL_Time=0;
//						Usart3_Rece_Count=0;
//						Usart3_Rece_Flag = 0;
//					}	
//				}
//				else
//				{
//					Set_Ok_Flag = 1;
//					zhiling = 2;;
//					ZL_Time=0;
//					Usart3_Rece_Count=0;
//					Usart3_Rece_Flag = 0;
//					JCM12864_Display_String(3,0,"���ݴ������    ");
//					Delay_s(2);
//				}
//			}
//			else
//			{
//				Set_Ok_Flag = 1;
//				JCM12864_Display_String(3,0,"��������������");
//				Delay_s(2);
//				zhiling = 2;
//				ZL_Time=0;
//				Usart3_Rece_Count=0;
//				Usart3_Rece_Flag = 0;
//			}
//		}
//		else if(key == 18)
//		{
//			Set_Ok_Flag = 1;
//			Delay_ms(100);
//			zhiling = 2;
//			LCD_Show_Flag =  40;
//			key = 0;
//		}
//	}
//	zhiling = 2;
//	return 0;
//}

uint8_t Close_All_CH(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Close_All_CH_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(0,0,"��Դȫ���رճɹ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(0,0,"��Դȫ���ر�ʧ��");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(0,0,"��Դȫ���ر�ʧ��");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(0,0,"��Դȫ���ر�ʧ��");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(0,0,"���Դͨ��ʧ�ܣ�");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}

void BSP_JCM12864_Demo131(void)//ȫ��
{
	JCM12864_Init(); 
	JCM12864_clear();
	Delay_ms(10);
//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
//	JCM12864_Display_String(1,0,"  4:            ");
//	JCM12864_Display_String(2,0,"  5:            ");
//	JCM12864_Display_String(3,0,">>6:            ");
//	if(CAL_Power_CH4_Voltage > 5000)//ͨ��4
//	{
//		JCM12864_Display_String(1,3,"�쳣");
//	}
//	else
//	{
//		JCM12864_Display_Power_Channel_Voltage(1,3,CAL_Power_CH4_Vol1,CAL_Power_CH4_Vol2);
//	}
//	
//	if(CAL_Power_CH4_Current > 99)
//	{
//		JCM12864_Display_String(1,6,"�쳣");
//	}
//	else 
//	{
//		JCM12864_Display_Power_Channel_Current(1,6,CAL_Power_CH4_Cur1,CAL_Power_CH4_Cur2);
//	}
//	
//	if(CAL_Power_CH5_Voltage > 5000)//ͨ��5
//	{
//		JCM12864_Display_String(2,3,"�쳣");
//	}
//	else
//	{
//		JCM12864_Display_Power_Channel_Voltage(2,3,CAL_Power_CH5_Vol1,CAL_Power_CH5_Vol2);
//	}
//	if(CAL_Power_CH5_Current > 99)
//	{
//		JCM12864_Display_String(2,6,"�쳣");
//	}
//	else 
//	{
//		JCM12864_Display_Power_Channel_Current(2,6,CAL_Power_CH5_Cur1,CAL_Power_CH5_Cur2);
//	}
//	
//	if(CAL_Power_CH6_Voltage > 5000)//ͨ��6
//	{
//		JCM12864_Display_String(3,3,"�쳣");
//	}
//	else
//	{
//		JCM12864_Display_Power_Channel_Voltage(3,3,CAL_Power_CH6_Vol1,CAL_Power_CH6_Vol2);
//	}
//	
//	if(CAL_Power_CH6_Current > 99)
//	{
//		JCM12864_Display_String(3,6,"�쳣");
//	}
//	else 
//	{
//		JCM12864_Display_Power_Channel_Current(3,6,CAL_Power_CH6_Cur1,CAL_Power_CH6_Cur2);
//	}
	Task = CaoZuo;
	while(!Switch_Flag)
	{
		Open_All_CH();
	}
	Switch_Flag = 0;
	Task = LunXun;
	zhiling = 0;
}

uint8_t Open_All_CH(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
//	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Open_All_CH_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(0,0,"��Դȫ���򿪳ɹ�");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x04))
				{
					JCM12864_Display_String(0,0,"��Դȫ����ʧ��");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(0,0,"��Դȫ����ʧ��");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(0,0,"��Դȫ����ʧ��");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(0,0,"���Դͨ��ʧ�ܣ�");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}

void BSP_JCM12864_Demo141(void)//����ͨ��1
{
	Task = CaoZuo;
	while(!Switch_Flag)	
	{
		Switch_CHX(CH1);
	}
	Switch_Flag = 0 ;
	Task = LunXun;
	zhiling = 0;
}
uint8_t Close_CH1(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Close_CH1_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(1,0,"ͨ��һ�رճɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(1,0,"ͨ��һ�ر�ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(1,0,"ͨ��һ�ر�ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(1,0,"ͨ��һ�ر�ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(1,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
//void BSP_JCM12864_Demo151(void)//��ͨ��1
//{
//	Switch_CHX(CH1);
//}

uint8_t Open_CH1(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Open_CH1_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(1,0,"ͨ��һ�����ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(1,0,"ͨ��һ����ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(1,0,"ͨ��һ����ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(1,0,"ͨ��һ����ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(1,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}

void BSP_JCM12864_Demo142(void)//����ͨ��2
{
	Task = CaoZuo;
	while(!Switch_Flag)	
	{
		Switch_CHX(CH2);
	}
	Switch_Flag = 0 ;
	Task = LunXun;
	zhiling = 0;
}
uint8_t Close_CH2(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Close_CH2_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(2,0,"ͨ�����رճɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(2,0,"ͨ�����ر�ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(2,0,"ͨ�����ر�ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(2,0,"ͨ�����ر�ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(2,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
//void BSP_JCM12864_Demo151(void)//��ͨ��1
//{
//	Switch_CHX(CH1);
//}

uint8_t Open_CH2(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Open_CH2_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(2,0,"ͨ���������ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(2,0,"ͨ��������ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(2,0,"ͨ��������ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(2,0,"ͨ��������ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(2,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
void BSP_JCM12864_Demo143(void)//����ͨ��3
{
	Task = CaoZuo;
	while(!Switch_Flag)	
	{
		Switch_CHX(CH3);
	}
	Switch_Flag = 0 ;
	Task = LunXun;
	zhiling = 0;
}
uint8_t Close_CH3(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Close_CH3_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(3,0,"ͨ�����رճɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(3,0,"ͨ�����ر�ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(3,0,"ͨ�����ر�ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(3,0,"ͨ�����ر�ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(3,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
//void BSP_JCM12864_Demo151(void)//��ͨ��1
//{
//	Switch_CHX(CH1);
//}

uint8_t Open_CH3(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Open_CH3_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(3,0,"ͨ���������ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(3,0,"ͨ��������ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(3,0,"ͨ��������ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(3,0,"ͨ��������ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(3,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
void BSP_JCM12864_Demo144(void)//����ͨ��2
{
	Task = CaoZuo;
	while(!Switch_Flag)	
	{
		Switch_CHX(CH4);
	}
	Switch_Flag = 0 ;
	Task = LunXun;
	zhiling = 0;
}
uint8_t Close_CH4(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Close_CH4_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(1,0,"ͨ���Ĺرճɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(1,0,"ͨ���Ĺر�ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(1,0,"ͨ���Ĺر�ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(1,0,"ͨ���Ĺر�ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(1,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
//void BSP_JCM12864_Demo151(void)//��ͨ��1
//{
//	Switch_CHX(CH1);
//}

uint8_t Open_CH4(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Open_CH4_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(1,0,"ͨ���Ŀ����ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(1,0,"ͨ���Ŀ���ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(1,0,"ͨ���Ŀ���ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(1,0,"ͨ���Ŀ���ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(1,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
void BSP_JCM12864_Demo145(void)//����ͨ��5
{
	Task = CaoZuo;
	while(!Switch_Flag)	
	{
		Switch_CHX(CH5);
	}
	Switch_Flag = 0 ;
	Task = LunXun;
	zhiling = 0;
}
uint8_t Close_CH5(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Close_CH5_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(2,0,"ͨ����رճɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(2,0,"ͨ����ر�ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(2,0,"ͨ����ر�ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(2,0,"ͨ����ر�ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(2,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
//void BSP_JCM12864_Demo151(void)//��ͨ��1
//{
//	Switch_CHX(CH1);
//}

uint8_t Open_CH5(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Open_CH5_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(2,0,"ͨ���忪���ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(2,0,"ͨ���忪��ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(2,0,"ͨ���忪��ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(2,0,"ͨ���忪��ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(2,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
void BSP_JCM12864_Demo146(void)//����ͨ��2
{
	Task = CaoZuo;
	while(!Switch_Flag)	
	{
		Switch_CHX(CH6);
	}
	Switch_Flag = 0 ;
	Task = LunXun;
	zhiling = 0;
}
uint8_t Close_CH6(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Close_CH6_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(3,0,"ͨ�����رճɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(3,0,"ͨ�����ر�ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(3,0,"ͨ�����ر�ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(3,0,"ͨ�����ر�ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(3,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}
//void BSP_JCM12864_Demo151(void)//��ͨ��1
//{
//	Switch_CHX(CH1);
//}

uint8_t Open_CH6(void)
{
	uint8_t TimeConuter = 0;
	uint8_t Length_IN = 0;
	Delay_ms(10);
	JCM12864_Display_String(0,0,"ͨ��  ��ѹ  ����");
	Usart3_Send(Open_CH6_Buff,11);
//	Usart3_Rece_Flag = 0;
	for(TimeConuter = 10; TimeConuter > 0;TimeConuter--)
	{
		if(Usart3_Rece_Flag == 1)
		{
			Switch_Flag = 1;
			ZL_Time=0;
			Usart3_Rece_Count = 0;
			Usart3_Rece_Flag = 0;
			Length_IN = (Usart3_ReceBuff[2]<<8) + Usart3_ReceBuff[3] + 4;
			if(XORValid(Usart3_ReceBuff,Length_IN) == Usart3_ReceBuff[Length_IN])
			{
				if ((Usart3_ReceBuff[8] == 0xaa)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(3,0,"ͨ���������ɹ���");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count = 0;
					Usart3_Rece_Flag = 0;
					return TRUE;
				}
				else if ((Usart3_ReceBuff[8] == 0x55)&&(Usart3_ReceBuff[7] == 0x02))
				{
					JCM12864_Display_String(3,0,"ͨ��������ʧ��00");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;	
					return FALSE;
				}
				else 
				{
					JCM12864_Display_String(3,0,"ͨ��������ʧ��11");
//					Delay_s(1);
//					Delay_ms(500);
					ZL_Time=0;
					Usart3_Rece_Count=0;
					Usart3_Rece_Flag = 0;
					return FALSE;
				}
			}
			else
			{
				JCM12864_Display_String(3,0,"ͨ��������ʧ��22");
//				Delay_s(1);
//				Delay_ms(500);				
				ZL_Time=0;
				Usart3_Rece_Count=0;
				Usart3_Rece_Flag = 0;
				return FALSE;
			}
		}
		else 
		Delay_ms(100);
	}
	{
		JCM12864_Display_String(3,0,"���Դͨ��ʧ��33");
		Switch_Flag = 1;
//		Delay_s(1);
//		Delay_ms(500);
		ZL_Time=0;
		Usart3_Rece_Count=0;
		Usart3_Rece_Flag = 0;
		return FALSE;
	}
}




uint8_t Switch_CHX(uint8_t CHX)
{
	
	switch (CHX)
	{
		case CH1:
		{
			if(CH1_Statu == 0x10)
			{
				Open_CH1();
			}
			else if(CH1_Statu == 0x11)
			{
				Close_CH1();
			}
			break;
		}
		case CH2:
		{
			if(CH2_Statu == 0x20)
			{
				Open_CH2();
			}
			else if(CH2_Statu ==0x21)
			{
				Close_CH2();
			}
			break;
		}
		case CH3:
		{
			if(CH3_Statu == 0x30)
			{
				Open_CH3();
			}
			else if(CH3_Statu == 0x31)
			{
				Close_CH3();
			}
			break;
		}
		case CH4:
		{
			if(CH4_Statu == 0x40)
			{
				Open_CH4();
			}
			else if(CH4_Statu == 0x41)
			{
				Close_CH4();
			}
			break;
		}
		case CH5:
		{
			if(CH5_Statu == 0x50)
			{
				Open_CH5();
			}
			if(CH5_Statu == 0x51)
			{
				Close_CH5();
			}
			break;
		}
		case CH6:
		{
			if(CH6_Statu == 0x60)
			{
				Open_CH6();
			}
			if(CH6_Statu == 0x61)
			{
				Close_CH6();
			}
			break;
		}
		default: break;
	}
	return ERROR;
}

