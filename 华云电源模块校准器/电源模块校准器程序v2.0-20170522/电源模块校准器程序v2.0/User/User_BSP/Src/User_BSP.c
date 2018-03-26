/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                   ARM Cortex-M3 Port
* �ļ���    : User_BSP.c
* ��  ��    :
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
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
// ϵͳ��Դ��ʼ��
void User_BSP_Init(void)
{
	Systick_Init(72);	/*��ʼ��Systick����ʱ��*/
	BSP_RCC_Init();
	NVIC_Configuration();
	
//	IWDG_Init(4,625);    //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s
//	WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	
//	USART1_GPIO_Config(); 	/*��ʼ������ͨ��:115200@8-n-1*/
	Led_Dirver_Init();
	Led_Dirver();
	USART3_GPIO_Config();
	TIM3_Int_Init(9,7199);//1ms
	BEEP_Init();
	KEY_Init();
	KeyBoard_Init();
	JCM12864_Init(); 
	JCM12864_clear();
	CN3153_Init();//IO��ʼ��
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
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//Ҫ�ȿ�ʱ�ӣ�����ӳ�䣻�ر�jtag������swd��   
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); */  //   WWDGʱ��ʹ��
	}
/**************************************
* Function Name :void InterruptOrder(void)
* Description   :�ж����������ȼ�
* Input         :
* Output        :
* Other         :
* Date          :2011.10.27  11:50:05
***************************************/
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//��Ӧ���ȼ�
	//USART1: NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//CAN1  : NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	//
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );//���ȼ�����  ��ռ���ȼ�Ϊ0,0-15��Ӧ���ȼ�
	/*����2*/
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	/*����1*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	/*����3*/
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	/*��ʱ��2*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�4��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	/*��ʱ��3*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�4��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
}
/********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/


