/******************** (C) COPYRIGHT DIY嵌入式开发工作室*******************************
 *
 *                              ARM Cortex-M4 Port
 *
 * 文件名称     : W5500_SPI.h (  )
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
#include "./BSP_Internet/w5500/W5500.h"
#include "./BSP_Internet/w5500/W5500_SPI.h"
#include "./BSP_Internet/w5500/W5500_Conf.h"
#include "./BSP_Internet/w5500/W5500_Socket.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
/* Private functions -----------------------------------*/
void  Internet_Init(void)
{
    W5500_SPI_Configuration();	         /*初始化MCU相关引脚*/
	Delay_ms(2000);
    /*硬复位W5500*/
    GPIO_ResetBits(WIZ_RESET_PORT, WIZ_RESET);
    Delay_ms(50);
    GPIO_SetBits(WIZ_RESET_PORT, WIZ_RESET);
    Delay_ms(2000);
    W5500_Set_MAC();			         /*配置MAC地址*/
    W5500_Set_IP();                      /*配置IP地址*/
    socket_buf_init(txsize, rxsize);     /*初始化8个Socket的发送接收缓存大小*/	
}
/**
  * @brief  根据外部SPI设备配置SPI相关参数
  * @retval None
  */
void W5500_SPI_Configuration(void)
{
    SPI_InitTypeDef SPI_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | WIZ_RESET_RCC | WIZ_SCS_RCC | WIZ_Pwr_RCC, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13,  GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14,  GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15,  GPIO_AF_SPI2);
    //PA4->CS,PA5->SCK,PA6->MISO,PA7->MOSI
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	
    //初始化片电源控制引脚
    GPIO_InitStruct.GPIO_Pin = WIZ_Pwr;
    GPIO_Init(WIZ_Pwr_PORT, &GPIO_InitStruct);
    GPIO_SetBits(WIZ_Pwr_PORT,WIZ_Pwr);
	//初始化片选输出引脚
    GPIO_InitStruct.GPIO_Pin = WIZ_SCS;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(WIZ_SCS_PORT, &GPIO_InitStruct);
    GPIO_SetBits(WIZ_SCS_PORT,WIZ_SCS);
    //初始化复位输出引脚
    GPIO_InitStruct.GPIO_Pin = WIZ_RESET;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(WIZ_RESET_PORT, &GPIO_InitStruct);
    GPIO_SetBits(WIZ_RESET_PORT,WIZ_RESET);

    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2,&SPI_InitStruct);

    SPI_Cmd(SPI2, ENABLE);
}

/**
*@brief		W5500基本SPI读写函数
*@param		无
*@return	无
*/
uint8_t W5500_SPI_SendByte(uint8_t byte)
{

	/* Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    /* Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI2, byte);

    /* Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    /* Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI2);
}
/********** (C) COPYRIGHT DIY嵌入式开发工作室 （END OF FILE ）************************/
