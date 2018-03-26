/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
 * 文件名   ：JCM12864.h
 * 描述     :
 * 环境	 	  : MDK4.73-固件库V3.5版本
 * 实验平台 ：TOP9110-STM32F103RBT6-8MHz->72MHz
 * 版本     ：V1.0.0
 * 作者     ：
 * 修改时间 ：2013-12-20
 * 硬件连接 : STM32F10x-STM32开发板
*******************************************************************************/
#ifndef __BSP_JCM12864_H
#define __BSP_JCM12864_H
/* Includes---------------------------------------------*/
#include "sys.h"
#include "User_Conf.h" 




///* Private defines--------------------------------------*/
//#define JCM12864_PIN_SID        GPIO_Pin_0
//#define JCM12864_PIN_CLK        GPIO_Pin_1
////#define JCM12864_PIN_BLT        GPIO_Pin_12
//#define JCM12864_PIN_CS         GPIO_Pin_5
////#define JCM12864_PIN_RST       GPIO_Pin_9
//#define JCM12864_GPIO           GPIOB
//#define JCM12864_GPIO_CLK       RCC_APB2Periph_GPIOB
//#define LCD_CS_SET 			    GPIO_SetBits(GPIOB, GPIO_Pin_5)//CS<->PC4
//#define LCD_CS_RESET 			GPIO_ResetBits(GPIOB, GPIO_Pin_5)
//#define Local_Network_Flag 1
//#define Network_Server_Flag 2
//#define GPRS_Server_Flag 3

/* Private defines--------------------------------------*/
#define JCM12864_PIN_SID        GPIO_Pin_4
#define JCM12864_PIN_CLK        GPIO_Pin_5
//#define JCM12864_PIN_BLC        GPIO_Pin_15
#define JCM12864_PIN_CS         GPIO_Pin_3
//#define JCM12864_PIN_RSC       GPIO_Pin_15
#define JCM12864_GPIO           GPIOB
#define JCM12864_GPIO_CLK       RCC_APB2Periph_GPIOB
#define LCD_CS_SET 			    GPIO_SetBits(GPIOB, GPIO_Pin_3)//CS<->PC4
#define LCD_CS_RESET 			GPIO_ResetBits(GPIOB, GPIO_Pin_3)
#define Local_Network_Flag 1
#define Network_Server_Flag 2
#define GPRS_Server_Flag 3
#define CH1 0X01
#define CH2 0X02
#define CH3 0X03
#define CH4 0X04
#define CH5 0X05
#define CH6 0X06

/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
void JCM12864_Init(void);
void JCM12864_clear(void);        //清除显示
void LCD_Set_XY(uint8_t X, uint8_t Y);	//设定显示坐标
void JCM12864_Display_String(unsigned char y_add , unsigned char x_add , unsigned char *str) ;
void Input_Value(uint8_t X, uint8_t Y, uint8_t bits);//"_"闪烁效果，用于位的选择,part为前八格或后八格(0,1)
void JCM12864_Display_Number(uint8_t  row,uint8_t  col,u16 Number);//在任何位置写数字
void JCM12864_Display_OneBbyte(uint8_t  row,uint8_t  col,uint8_t Number);//在任何位置写一字节数
void JCM12864_Display_Point(uint8_t  row,uint8_t  col);//在任何位置写小数点

void JCM12864_Display_Power_Channel_Voltage(u8 row,u8 col,u8 channelx_vol1,u8 channelx_vol2);
void JCM12864_Display_Power_Channel_Current(u8 row,u8 col,u8 channelx_cur1,u8 channelx_cur2);

void JCM12864_Display_Humidity(u8 row,u8 col,u8 humidity_Value1,u8 humidity_Value2);
void JCM12864_Display_Temperature(u8  row,u8  col,u8 temperature_sign,u8 temperature_Value_1,u8 temperature_Value_2);
void JCM12864_Display_Voltage(u8  row,u8  col,u8 Vol_Value1,u8 Vol_Value2);
void JCM12864_Display_Current(u8  row,u8  col,u8 Cur_Value_1,u8 Cur_Value_2);
void JCM12864_Display_Leakage(u8  row,u8  col,u8 Leakage_Value1,u8 Leakage_Value2);
void JCM12864_Display_Port(uint8_t  row,uint8_t  col,u8 Port);//写5位端口号0-65535
//void JCM12864_Display_IP(uint8_t  row,uint8_t  col,u16 Port);//写IP 192.168.100.100
void JCM12864_Display_IP(u8  row,u8  col,u8 IP1,u8 IP2,u8 IP3,u8 IP4);
void JCM12864_Display_MAC(u8  row,u8  col,u8 MAC1,u8 MAC2,u8 MAC3,u8 MAC4,u8 MAC5,u8 MAC6);
void JCM12864_inverse(void);
//void con_disp (unsigned int line,unsigned int enable);
void con_disp (u8 _line,u8 enable);//用于反白
void con_disp8(unsigned int x,unsigned int y,unsigned int direction);
void LCD_Clear_BMP( void );
void DrawDots(u8 x,u8 y,u8 clor);
void Lcd_12864_White(u8 x,u8 y,u8 length);
void GUI_Point(u8 x,u8 y,u8 flag);
void Draw_Clear(void);
void display_graphic_16x16(uint16_t page,uint16_t column,uint8_t *dp);
void display_graphic_8x16(uint16_t page,uint8_t column,uint8_t *dp);
void lcd_address(uint16_t page,uint16_t column);
void LCD_Show_Demo(void);

void Display_LCD_Pos(u8 x,u8 y);
void Disp_HZ(u8 X,const u8 * pt,u8 num);
void Display_LCD_String(u8 x,u8 *p,u8 time);
void PutBMP(u8 *puts);
void Draw_Dots(u8 x, u8 y, u8 color);
void Draw_Update(void);
void Draw_Char4x5(u8 x, u8 y, u8 value);
void Draw_Char4x5Line(u8 x, u8 y, u8 *value, u8 len);
void LCD12864_writeData(u8 row,u8 cols,u8* pBuf,u8 dataSize);//写数据
void LCD12864_setPos(u8 row, u8 cols);			//设置光标位置
void jpcon_disp (uint8_t data1,uint8_t data2,uint8_t x0,uint8_t y0,uint8_t xl,uint8_t yl);
void Dis_Set_Port(uint8_t *Port);
void Dis_Set_IP(uint8_t *IP);
void Choose_Bit(u8 X, u8 Y,u8 PART,u8 val);//选择位闪烁


void Input_Port1(u8 X, u8 Y, u8 *Port);
void JCM12864_SendData(unsigned char dat);
void JCM12864_SendCom(unsigned char cmd);
void LCD_Write_Number(u8 key );	//显示数字

uint8_t Calibration_CH1(void);
uint8_t Calibration_CH2(void);
uint8_t Calibration_CH3(void);
uint8_t Calibration_CH4(void);
uint8_t Calibration_CH5(void);
uint8_t Calibration_CH6(void);

uint8_t On_Off_CH1(void);
uint8_t On_Off_CH2(void);
uint8_t On_Off_CH3(void);
uint8_t On_Off_CH4(void);
uint8_t On_Off_CH5(void);
uint8_t On_Off_CH6(void);

uint8_t Close_All_CH(void);
uint8_t Open_All_CH(void);

uint8_t Open_CH1(void);
uint8_t Open_CH2(void);
uint8_t Open_CH3(void);
uint8_t Open_CH4(void);
uint8_t Open_CH5(void);
uint8_t Open_CH6(void);

uint8_t Close_CH1(void);
uint8_t Close_CH2(void);
uint8_t Close_CH3(void);
uint8_t Close_CH4(void);
uint8_t Close_CH5(void);
uint8_t Close_CH6(void);

uint8_t Switch_CHX(uint8_t CHX);
uint8_t Open_CHX(uint8_t CHX);
uint8_t Close_CHX(uint8_t CHX);
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif 
