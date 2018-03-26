/* Includes ------------------------------------------------------------------*/
#include "EEprom_Dirver.h"
#include "Heard_Public.h"
#include "User_BSP.h"

#define  ERRORCOUNT 10

uint16_t Addr_EEprom=0;
uint16_t eeprom_num = 0;                     // 当前存储到的序号。
uint8_t eepromdatawrite[8]={8,9,5,4,3,2,1,0};
uint8_t eepromdataread[8]={0,0,0,0,0,0,0,0};

//DataBuff为读写数据输入／输出缓冲区的首址
//ByteQuantity 为要读写数据的字节数量
//Address 为EEPROM的片内地址
//ControlByte 为EEPROM的控制字节，具体形式为(1)(0)(1)(0)(A2)(A1)(A0)(R/W),其中R/W=1,
//表示读操作,R/W=0为写操作,A2,A1,A0为EEPROM的页选或片选地址;
//EepromType为枚举变量,需为M2401至M24256中的一种,分别对应24C01至24C256;
//函数返回值为一个位变量，若返回1表示此次操作失效，0表示操作成功;
//ERRORCOUNT为允许最大次数，若出现ERRORCOUNT次操作失效后，则函数中止操作，并返回1
//SDA和SCL由用户自定义，这里暂定义为P0^0和P0^1;
//其余的用户不用管，只要把只子程序放在你的程序中并调用它就可以了;

/*
*********************************************************************************************************
*	函 数 名: i2c_Delay
*	功能说明: I2C总线位延迟，最快400KHz
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Delay(void)
{
	uint8_t i;

	/*　
	 	下面的时间是通过安富莱AX-Pro逻辑分析仪测试得到的。
		CPU主频72MHz时，在内部Flash运行, MDK工程不优化
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
        
        IAR工程编译效率高，不能设置为7
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
		I2C_SDA_0();	/* CPU驱动SDA = 0 */
		i2c_Delay();
		I2C_SCL_1();	/* CPU产生1个时钟 */
		i2c_Delay();
		I2C_SCL_0();
		i2c_Delay();
		I2C_SDA_1();	/* CPU释放SDA总线 */
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


/*****************以下是对IIC总线的操作子程序***/
/*****************启动总线**********************/
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

/*****************停止IIC总线****************/
void IICStop(void)
{
		/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_0();
	}

/**************检查应答位*******************/
/*bit IICRecAck(void)
{
SCL1=0;
SDA1=1;
SCL1=1;
_nop_();
_nop_();
_nop_();
_nop_();
CY=SDA1;                 //因为返回值总是放在CY中的
SCL1=0;
return(CY);
}
*/
uint8_t IICRecAck(void)
{
	uint8_t re;

	I2C_SDA_1();	/* CPU释放SDA总线 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
	if (I2C_SDA_READ())	/* CPU读取SDA口线状态 */
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
/***************对IIC总线产生应答*******************/
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
  
/*****************不对IIC总线产生应答***************/
void IICNoAck(void)
{
		I2C_SDA_1();	/* CPU驱动SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	}


/*******************向IIC总线写数据*********************/
void IICSendByte(uint8_t sendbyte)
{
	uint8_t i;

	/* 先发送字节的高位bit7 */
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
			 I2C_SDA_1(); // 释放总线
			}
		sendbyte <<= 1;	/* 左移一个bit */
		i2c_Delay();
	}


}
/**********************从IIC总线上读数据子程序**********/
uint8_t IICReceiveByte(void)
{
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;////开漏输出，外部需要加上拉电阻 GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	}
void Eeprom_Init(void)
{
	}
