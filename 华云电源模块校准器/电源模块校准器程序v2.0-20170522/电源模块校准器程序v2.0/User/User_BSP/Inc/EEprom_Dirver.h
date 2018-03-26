/**************
*******************************************************************************/
#ifndef __EEprom_Dirver_H
#define __EEprom_Dirver_H
/* Includes---------------------------------------------*/
#include "User_Conf.h" 
//#include <inttypes.h>
/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define GPIO_PORT_I2C	GPIOA			/* GPIO�˿� */
#define I2C_SCL_PIN		GPIO_Pin_8			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define I2C_SDA_PIN		GPIO_Pin_9			/* ���ӵ�SDA�����ߵ�GPIO */

#define I2C_WR	0		/* д����bit */
#define I2C_RD	1		/* ������bit */

//#define EE_DEV_ADDR			0xA0		/* 24xx02���豸��ַ */
//#define EE_PAGE_SIZE		8			/* 24xx02��ҳ���С */
//#define EE_SIZE				256			/* 24xx02������ */

/* �����дSCL��SDA�ĺ꣬�����Ӵ���Ŀ���ֲ�ԺͿ��Ķ��� */

#define I2C_SCL_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 1 */
#define I2C_SCL_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 0 */
	
#define I2C_SDA_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 1 */
#define I2C_SDA_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 0 */

#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)	/* ��SDA����״̬ */


//#define I2C_SCL_1()  GPIO_SetBits(GPIOB, GPIO_Pin_6)		/* SCL = 1 */
//#define I2C_SCL_0()  GPIO_ResetBits(GPIOB, GPIO_Pin_6)		/* SCL = 0 */
//	
//#define I2C_SDA_1()  GPIO_SetBits(GPIOB, GPIO_Pin_7)		/* SDA = 1 */
//#define I2C_SDA_0()  GPIO_ResetBits(GPIOB, GPIO_Pin_7)		/* SDA = 0 */
//	
//#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)	/* ��SDA����״̬ */

//extern uint16_t eeprom_num;                     // ��ǰ�洢������š�

void Eeprom_GPIO_Init(void);
void Eeprom_Init(void);
//extern uint8_t eepromdatawrite[];
//extern uint8_t eepromdataread[];
uint8_t RW24XX(uint8_t *DataBuff,uint8_t ByteQuantity,uint16_t Address,uint8_t ControlByte);
	   /*
extern void Delay1(uint8_t DelayCount);
extern void IICStart(void);
extern void IICStop(void);
//bit  IICRecAck(void);
extern uint8_t IICRecAck(void);
extern void IICNoAck(void);
extern void IICAck(void);
extern uint8_t IICReceiveByte(void);
extern void IICSendByte(uint8_t sendbyte);
extern void i2c_Delay(void); */
#endif
