/**************(C) COPYRIGHT  DIYǶ��ʽ����������*****************************
 * �ļ���   ��BSP_JCM12864_Demo.C
 * ����     :
 * ����	 	  : MDK5.10-�̼���V3.5�汾
 * ʵ��ƽ̨ ��TOP9110-STM32F103RBT6-8MHz->72MHz
 * �汾     ��V1.0.0
 * ����     ��
 * �޸�ʱ�� ��2013-12-20
 * Ӳ������ : STM32F10x-STM32������
*******************************************************************************/
/* Includes---------------------------------------------*/
#include  "BSP_JCM12864_Demo.h"
#include  "BSP_JCM12864.h"
#include "User_Inc.h"
#include "User_BSP.h"
#include "Heard_Public.h"
#include  <stdlib.h>
//#include  "BSP.h"
//#include  "BSP_DHT11.h"

/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
/* Private functions -----------------------------------*/
//void BSP_JCM12864_Demo(void)
//{
//		static uint32_t old_flag =0x00;
//		uint32_t Lcd_Flag =0xFF;
//////    u8 LCD_Counter = FALSE;
////    Lcd_Flag = 0x00;
////			JCM12864_Display_String(0,0,"��ӭʹ��������!");
////			JCM12864_Display_String(1,0,"ʱ�䣺2016    ");
////		  JCM12864_Display_String(2,0,"�ص㣺��ɽ��");
////			JCM12864_Display_String(3,0,"�豸������");
////			Delay_ms(1000);
//	 if(old_flag != Lcd_Flag)
//			{
//				old_flag = Lcd_Flag;
////        JCM12864_clear() ;
//				switch (old_flag)
//        {
//        case 0xFF:  //��ʾ��ʼ������
//						BSP_JCM12864_DemoFF(); 
//						Delay_ms(1500);
//						JCM12864_Init(); 
//						Lcd_Flag =0;
//						break;
//        case 0:     //��ʾҳ��0
//            BSP_JCM12864_Demo0();
// 						break;
//        case 1:     //��ʾҳ��1
//						BSP_JCM12864_Demo1();
//						break;
//				case 2:     //��ʾҳ��2
//						BSP_JCM12864_Demo2();
//						break;
////        case 2:     //��ʾҳ��0
////             OLED_ShowCHV(0,0);
////            break;
////        case 3:     //��ʾҳ��0
////            OLED_ShowNetConfig(0,0);
////            break;
////        case 4:     //��ʾҳ��0
////						OLED_RTC(80,0);
////            OLED_GPRS_CCSQ(0,0,2,5);
////            OLED_ShowNetServerConfig(0,2);
////            break;
////        case 5:     //��ʾҳ��0
////						OLED_RTC(80,0);
////            OLED_GPRS_CCSQ(0,0,2,5);
////            OLED_ShowGPRSConfig(0,2);
////            break;
////        case 6:     //��ʾҳ��0
////            OLED_ShowReclosing(0,0);
////            break;
////        default:
////            Lcd_Flag =0;
////            break;
////        }
////        if((oled_Counter++)>=100)
////        {
////            Lcd_Flag =0;
////            oled_Counter=FALSE;
//        }
////        vTaskDelay(200);
//			}
//			else{;}
//	 
//}
void LCD_Show_Demo(void)
{	
	static uint32_t LCD_Old_Flag = 0;//Һ����ʾҳ���־λ
	if(1)
	{
		if(LCD_Old_Flag != LCD_Show_Flag)
		{
			LCD_Update_Flag = 0;
			LCD_Old_Flag = LCD_Show_Flag;
//			LCD_Clear_BMP();
//			JCM12864_clear();
//			BSP_JCM12864_Demo1(); 
			switch (LCD_Old_Flag)
			{
				case 100:
				{
					BSP_JCM12864_Demo100();
					break;
				}
				case 101:
				{
					BSP_JCM12864_Demo101();
					break;
				}
				case 102:
				{
					BSP_JCM12864_Demo102();
					break;
				}
				case 103:
				{
					BSP_JCM12864_Demo103();
					break;
				}
				case 111:
				{
					BSP_JCM12864_Demo111();
					break;
				}
				case 112:
				{
					BSP_JCM12864_Demo112();
					break;
				}
				case 113:
				{
					BSP_JCM12864_Demo113();
					break;
				}
				case 114:
				{
					BSP_JCM12864_Demo114();
					break;
				}
				case 115:
				{
					BSP_JCM12864_Demo115();
					break;
				}
				case 116:
				{
					BSP_JCM12864_Demo116();
					break;
				}
				case 62:
				{
					BSP_JCM12864_Demo62();
					break;
				}
				case 63:
				{
					BSP_JCM12864_Demo63();
					break;
				}
				case 64:
				{
					BSP_JCM12864_Demo64();
					break;
				}
				case 65:
				{
					BSP_JCM12864_Demo65();
					break;
				}
				case 66:
				{
					BSP_JCM12864_Demo66();
					break;
				}
				case 67:
				{
					BSP_JCM12864_Demo67();
					break;
				}	
				case 82:
				{
					BSP_JCM12864_Demo82();
					break;
				}
				case 83:
				{
					BSP_JCM12864_Demo83();
					break;
				}
				case 84:
				{
					BSP_JCM12864_Demo84();
					break;
				}
				case 85:
				{
					BSP_JCM12864_Demo85();
					break;
				}
				case 86:
				{
					BSP_JCM12864_Demo86();
					break;
				}
				case 87:
				{
					BSP_JCM12864_Demo87();
					break;
				}
				case 130://ȫ��
				{
					BSP_JCM12864_Demo130();
					break;
				}
				case 131://ȫ��
				{
					BSP_JCM12864_Demo131();
					break;
				}
				case 141://��1
				{
					BSP_JCM12864_Demo141();
					break;
				}
				case 142://��2
				{
					BSP_JCM12864_Demo142();
					break;
				}
				case 143://��3
				{
					BSP_JCM12864_Demo143();
					break;
				}
				case 144://��4
				{
					BSP_JCM12864_Demo144();
					break;
				}
				case 145://��5
				{
					BSP_JCM12864_Demo145();
					break;
				}
				case 146://��6
				{
					BSP_JCM12864_Demo146();
					break;
				}
//				case 151://��1
//				{
//					BSP_JCM12864_Demo151();
//					break;
//				}
//				case 152://��2
//				{
//					BSP_JCM12864_Demo152();
//					break;
//				}
//				case 153://��3
//				{
//					BSP_JCM12864_Demo153();
//					break;
//				}
//				case 154://��4
//				{
//					BSP_JCM12864_Demo154();
//					break;
//				}
//				case 155://��5
//				{
//					BSP_JCM12864_Demo155();
//					break;
//				}
//				case 156://��6
//				{
//					BSP_JCM12864_Demo156();
//					break;
//				}
				default: break;
			}
		}
		else
		{
			if(LCD_Update_Flag>=1000)
			{
				LCD_Update_Flag = 0;
				switch (LCD_Old_Flag)
				{
					case 62:
					{
						BSP_JCM12864_Demo72();
						break;
					}
					case 63:
					{
						BSP_JCM12864_Demo73();
						break;
					}
					case 64:
					{
						BSP_JCM12864_Demo74();
						break;
					}
					case 65:
					{
						BSP_JCM12864_Demo75();
						break;
					}
					case 66:
					{
						BSP_JCM12864_Demo76();
						break;
					}
					case 67:
					{
						BSP_JCM12864_Demo77();
						break;
					}	

					case 111:
					{
						BSP_JCM12864_Demo121();
						break;
					}
					case 112:
					{
						BSP_JCM12864_Demo122();
						break;
					}
					case 113:
					{
						BSP_JCM12864_Demo123();
						break;
					}
					case 114:
					{
						BSP_JCM12864_Demo124();
						break;
					}
					case 115:
					{
						BSP_JCM12864_Demo125();
						break;
					}
					case 116:
					{
						BSP_JCM12864_Demo126();
						break;
					}
					default: break;
				}
			}
			else
			{;}
		}
	}
	else
	{;}

}


///********** (C) COPYRIGHT DIYǶ��ʽ���������� *****END OF FILE****************/
