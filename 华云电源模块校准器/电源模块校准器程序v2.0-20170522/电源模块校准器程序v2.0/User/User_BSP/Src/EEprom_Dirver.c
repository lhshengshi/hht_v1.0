/* Includes ------------------------------------------------------------------*/
#include "EEprom_Dirver.h"
#include "Heard_Public.h"
#include "User_BSP.h"

#define  ERRORCOUNT 10

uint16_t Addr_EEprom=0;
uint16_t eeprom_num = 0;                     // ��ǰ�洢������š�
uint8_t eepromdatawrite[8]={8,9,5,4,3,2,1,0};
uint8_t eepromdataread[8]={0,0,0,0,0,0,0,0};

//DataBuffΪ��д�������룯�������������ַ
//ByteQuantity ΪҪ��д���ݵ��ֽ�����
//Address ΪEEPROM��Ƭ�ڵ�ַ
//ControlByte ΪEEPROM�Ŀ����ֽڣ�������ʽΪ(1)(0)(1)(0)(A2)(A1)(A0)(R/W),����R/W=1,
//��ʾ������,R/W=0Ϊд����,A2,A1,A0ΪEEPROM��ҳѡ��Ƭѡ��ַ;
//EepromTypeΪö�ٱ���,��ΪM2401��M24256�е�һ��,�ֱ��Ӧ24C01��24C256;
//��������ֵΪһ��λ������������1��ʾ�˴β���ʧЧ��0��ʾ�����ɹ�;
//ERRORCOUNTΪ������������������ERRORCOUNT�β���ʧЧ��������ֹ������������1
//SDA��SCL���û��Զ��壬�����ݶ���ΪP0^0��P0^1;
//������û����ùܣ�ֻҪ��ֻ�ӳ��������ĳ����в��������Ϳ�����;

/*
*********************************************************************************************************
*	�� �� ��: i2c_Delay
*	����˵��: I2C����λ�ӳ٣����400KHz
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Delay(void)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ��������AX-Pro�߼������ǲ��Եõ��ġ�
		CPU��Ƶ72MHzʱ�����ڲ�Flash����, MDK���̲��Ż�
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
        
        IAR���̱���Ч�ʸߣ���������Ϊ7
	*/
	for (i = 0; i < 10; i++);
	}

/***********************************************************************************/
uint8_t RW24XX(uint8_t *DataBuff,uint8_t ByteQuantity,uint16_t Address,uint8_t ControlByte)//,enum eepromtype EepromType)
{
void i2c_Delay(void);
void Delay1(uint8_t DelayCount);
void IICStart(void);
void IICStop(void);
uint8_t IICRecAck(void);
void IICNoAck(void);
void IICAck(void);
uint8_t IICReceiveByte(void);
void IICSendByte(uint8_t sendbyte);
uint8_t j,i=ERRORCOUNT;
uint8_t errorflag=1;
while(i--)
{
   IICStart();

   IICSendByte(ControlByte&0xfe);
   if(IICRecAck())
       continue;
   
   IICSendByte((uint8_t)(Address>>8));
   if(IICRecAck())
       continue;

   IICSendByte((uint8_t)Address);
   if(IICRecAck())
       continue;
   if(!(ControlByte&0x01))
   {
      j=ByteQuantity;
      errorflag=0;                      //********clr errorflag
      while(j--)
      {
        IICSendByte(*DataBuff++);
        if(!IICRecAck())
           continue;
        errorflag=1;
        break;
        }
      if(errorflag==1)
        continue;
      break;
      }
   else
   {
     IICStart();
     IICSendByte(ControlByte);
     if(IICRecAck())
       continue;
     while(--ByteQuantity)
     {
       *DataBuff++=IICReceiveByte();
//       IICAck();
		I2C_SDA_0();	/* CPU����SDA = 0 */
		i2c_Delay();
		I2C_SCL_1();	/* CPU����1��ʱ�� */
		i2c_Delay();
		I2C_SCL_0();
		i2c_Delay();
		I2C_SDA_1();	/* CPU�ͷ�SDA���� */
		}
     *DataBuff=IICReceiveByte();        //read last byte data
     IICNoAck();
     errorflag=0;
     break;
     }
  }
IICStop();
	if(!(ControlByte&0x01))
	{

		Delay_us(200);
		Delay_us(200);
		Delay_us(200);
		Delay_us(200);
		}
return(errorflag);
}


/*****************�����Ƕ�IIC���ߵĲ����ӳ���***/
/*****************��������**********************/
void IICStart(void)
{
	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	}

/*****************ֹͣIIC����****************/
void IICStop(void)
{
		/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_0();
	}

/**************���Ӧ��λ*******************/
/*bit IICRecAck(void)
{
SCL1=0;
SDA1=1;
SCL1=1;
_nop_();
_nop_();
_nop_();
_nop_();
CY=SDA1;                 //��Ϊ����ֵ���Ƿ���CY�е�
SCL1=0;
return(CY);
}
*/
uint8_t IICRecAck(void)
{
	uint8_t re;

	I2C_SDA_1();	/* CPU�ͷ�SDA���� */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
	if (I2C_SDA_READ())	/* CPU��ȡSDA����״̬ */
	{
		re = 1;
		}
	else
	{
		re = 0;
		}
	I2C_SCL_0();
	i2c_Delay();
	return re;

}
/***************��IIC���߲���Ӧ��*******************/
void IICACK(void)
{
//	SDA1=0;
	I2C_SDA_0();
	i2c_Delay();
//	SCL1=1;
	I2C_SCL_1();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
	i2c_Delay();
//	SCL1=0;
	I2C_SCL_0();
//	_nop_();
	i2c_Delay();
//	SDA1=1;
	I2C_SDA_1();
	}
  
/*****************����IIC���߲���Ӧ��***************/
void IICNoAck(void)
{
		I2C_SDA_1();	/* CPU����SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	}


/*******************��IIC����д����*********************/
void IICSendByte(uint8_t sendbyte)
{
	uint8_t i;

	/* �ȷ����ֽڵĸ�λbit7 */
	for (i = 0; i < 8; i++)
	{		
		if (sendbyte & 0x80)
		{
			I2C_SDA_1();
			}
		else
		{
			I2C_SDA_0();
			}
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();	
		I2C_SCL_0();
		if (i == 7)
		{
			 I2C_SDA_1(); // �ͷ�����
			}
		sendbyte <<= 1;	/* ����һ��bit */
		i2c_Delay();
	}


}
/**********************��IIC�����϶������ӳ���**********/
uint8_t IICReceiveByte(void)
{
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1();
		i2c_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		i2c_Delay();
	}
	return value;
	}

	
void Eeprom_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;////��©������ⲿ��Ҫ���������� GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	}
void Eeprom_Init(void)
{
	}
