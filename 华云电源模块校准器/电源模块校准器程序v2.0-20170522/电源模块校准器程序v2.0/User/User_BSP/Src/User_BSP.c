/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
                   ARM Cortex-M3 Port
* 文件名    : User_BSP.c
* 描  述    :
* 环  境	: MDK4.73-固件库V3.5版本
* 实验平台  : STM32F103RBT6-8MHz->72MHz
* 版  本    : V1.0.0
* 作  者    :
* 修改时间  : 2013-12-20
* 硬件连接  : STM32F10x-STM32开发板
*******************************************************************************/
/* Includes---------------------------------------------*/
#include "User_BSP.h"
#include "Heard_Public.h"
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
static void NVIC_Configuration(void);
static void BSP_RCC_Init(void);
/* Private functions -----------------------------------*/
// 系统资源初始化
void User_BSP_Init(void)
{
	Systick_Init(72);	/*初始化Systick工作时钟*/
	BSP_RCC_Init();
	NVIC_Configuration();
	
//	IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s
//	WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//计数器值为7f,窗口寄存器为5f,分频数为8	
//	USART1_GPIO_Config(); 	/*初始化串口通信:115200@8-n-1*/
	Led_Dirver_Init();
	Led_Dirver();
	USART3_GPIO_Config();
	TIM3_Int_Init(9,7199);//1ms
	BEEP_Init();
	KEY_Init();
	KeyBoard_Init();
	JCM12864_Init(); 
	JCM12864_clear();
	CN3153_Init();//IO初始化
//	TIM2_Int_Init(9999,7199);//1s
//	Eeprom_GPIO_Init(); 
	

/*	*/
	}
void Soft_Init(void)
{
//	Usart1_Init();
//	Usart2_Init();
	Usart3_Init();
//	SHT2x_SoftReset();
//	Eeprom_Init();
}
static void BSP_RCC_Init(void)
{
	 /* Enable PWR and BKP clocks 	 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); */
  /* Enable DMA clock 									 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	 */
  /* Enable AFIO clock 									  */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	  
  /*GPIOA Periph clock enable							  */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	  
  /* GPIOB Periph clock enable 							  */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 
  /* GPIOC Periph clock enable 							  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	*/ 
  /* GPI0D Periph clock enable 							  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);	*/  
  /* GPI0E Periph clock enable 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	 */
  /* Enable TIM1 clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	 */
  /* EnableTIM2  TIM3  TIM4 clocks*/ 						 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);	 
  /*Enable USART1 										 */ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);		   
  /* Enable USART2 										  */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	   
  /*Enable USART3 */	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//要先开时钟，再重映射；关闭jtag，保留swd。   
  /*Enable  I2C1 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);	 */
  /*Enable  ADC1 										 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);	 */  
  /*Enable ADC2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);	 */
  /* DAC Periph clock enable 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);	 */
/* Enable SPI1 reset state 
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);*/
/* Enable WWDG	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); */  //   WWDG时钟使能
	}
/**************************************
* Function Name :void InterruptOrder(void)
* Description   :中断向量，优先级
* Input         :
* Output        :
* Other         :
* Date          :2011.10.27  11:50:05
***************************************/
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//响应优先级
	//USART1: NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//CAN1  : NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	//
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );//优先级设置  抢占优先级为0,0-15响应优先级
	/*串口2*/
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	/*串口1*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	/*串口3*/
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	/*定时器2*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级4级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	/*定时器3*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级4级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
}
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/


