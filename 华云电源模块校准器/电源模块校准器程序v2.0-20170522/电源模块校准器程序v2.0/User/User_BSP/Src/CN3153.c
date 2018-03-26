#include "User_BSP.h"
#include "Heard_Public.h"
#include "stm32f10x.h"
#include "sys.h" 
#include "CN3153.h"


							    
//������ʼ������
void CN3153_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��GPIOB�˿�ʱ��

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8
}

//��������  KOK=1 �̰�     KOK=2 ����
//void start()
//{
//	uint8_t i=0;
//	 if(ON_OFF_KEY==0)//��������Ŀ���
//	 {
//	 while(1)
//		 {
//			Delay_ms(200);
//			if(ON_OFF_KEY==0)//��������Ŀ���
//			i++;
//			else i = 0;
//			if(i>6)//3����֮��
//			{
//				BEEP_500MS();
//				PWR_1;//���ֿ���״̬
//				//��ʾ����LOGO
//				while(ON_OFF_KEY==0);
//				KOK=0;
//				break;
//			}
////					 else
////					 {
////					    if(ON_OFF_KEY!=0) i=0;//����ʱ��С��3��
////					 }
//		 }
//	 }
//	 else//�������Ŀ���
//	 {
//		 i=0;
//		  while(1)
//		 {
//			Delay_ms(200);
//	//				   ˢ�³�����
//	//				   cd();
//	//				   LED_0;
//			if(ON_OFF_KEY==0)//��������
//			 {
//			   if(++i>6)//3����֮��
//				 {
//					PWR_1;//���ֿ���״̬  
//	//                          ��ʾ����LOGO
//	//						    LED_1;
//					BEEP_500MS();
//					while(ON_OFF_KEY==0)
//					{

//					}
//					KOK=0;
//					KCnt=0;
//					break;
//				 }
//			 }
//			 else //����̧���Ҫ���¼�ʱ
//			 {
//				i=0;				 
//			 }
//		 }
//	 }
//}

//	//�ػ�����
//	void Stop()
//	{
//	uint8_t i=0;
//	BEEP_500MS();
//	 Delay_ms(50);
//	 BEEP_500MS();
//	 if((BATC==0)|(BATM==0))//���״̬
//	 {
////	     clear_screen();
//		   PWR_0;
//		   while(1)//���״̬�ػ�����������
//			 {
//					 Delay_ms(200);
//				   //ˢ�³���
////				   cd();
////				   LED_0;
//				   if(ON_OFF_KEY==0)//��������
//					 {
//						if(++i>6)//3����֮��
//						{
//							PWR_1;//���ֿ���״̬ 
////							��ʾ����LOGO
////							 LED_1;
//							 BEEP_500MS();
//							 while(ON_OFF_KEY==0); 
//							 KOK=0;
//							 KCnt=0;
//							 break;
//						}		
//					 }
//					 else //����̧���Ҫ���¼�ʱ
//					 {
//						i=0;				 
//					 }
//			 }
//	 }
//	 else //�ǳ��״ֱ̬�ӹػ�
//	 {
//			 //�ػ�LOGO
//		   PWR_0;
//		   while(1);
//	 }
//}
