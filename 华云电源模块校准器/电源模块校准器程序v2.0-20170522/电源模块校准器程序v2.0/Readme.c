/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                   ARM Cortex-M3 Port
* �ļ���    : Readme.h
* ��  ��    :
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    : MJQ
* �޸�ʱ��  : 
* Ӳ������  :  
* ���������: 
            main.c(User_BSP.h)
			  |
			  |->User_BSP.c(User_Inc.h)
			        |
					|->BSP_Usart1.c ���ڲ���
					|->BSP_XXX.c
					|->BSP_OutPut.c(BSP_OutPut.h) ���������
					                   |->User_Conf.h �û���������
									         |->Utility.h ��������
									               |->sys.h λ����
											           |->stm32f10x_conf.h
												       |->stm32f10x.h
													   |->stdio.h
						 
*******************************************************************************/
////20170109
//��ѯ״̬�Ͳ�ѯ����ֿ���
//�������ָ��
//20170123 for50���ж�ͨ��״̬  �����޸����ú����ָ��һ�������BUG 
//20170419 ���ӵ�س������һ�����ػ�

























/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
                   ARM Cortex-M3 Port
* �ļ���    : BSP_OutPut.h
* ��  ��    :
* ��  ��	: MDK4.73-�̼���V3.5�汾
* ʵ��ƽ̨  : STM32F103RBT6-8MHz->72MHz
* ��  ��    : V1.0.0
* ��  ��    :
* �޸�ʱ��  : 2013-12-20
* Ӳ������  : STM32F10x-STM32������
*******************************************************************************/
//#ifndef __BSP_OutPut_H
//#define __BSP_OutPut_H
///* Includes---------------------------------------------*/
//#include "User_Conf.h" 
///* Private defines--------------------------------------*/
//#define LED   PCout(13)// 

////#define Lamp_R_ON   GPIO_SetBits(GPIOA,GPIO_Pin_6  )
////#define Lamp_R_OFF  GPIO_ResetBits(GPIOA,GPIO_Pin_6)

///* Private typedef -------------------------------------*/
///* Private macro ---------------------------------------*/
///* Private variables -----------------------------------*/
///* Private function prototypes -------------------------*/
//void BSP_OutPut_Init(void);
///* Private functions -----------------------------------*/
///********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
//#endif














