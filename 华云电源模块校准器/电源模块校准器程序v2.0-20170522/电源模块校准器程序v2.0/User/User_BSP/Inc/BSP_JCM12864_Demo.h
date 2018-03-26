/**************(C) COPYRIGHT  DIY嵌入式开发工作室*****************************
 * 文件名   ：BSP_JCM12864_Demo.h
 * 描述     :
 * 环境	 	  : MDK5.10-固件库V3.5版本
 * 实验平台 ：TOP9110-STM32F103RBT6-8MHz->72MHz
 * 版本     ：V1.0.0
 * 作者     ：
 * 修改时间 ：2013-12-20
 * 硬件连接 : STM32F10x-STM32开发板
*******************************************************************************/
#ifndef __BSP_JCM12864_Demo_H
#define __BSP_JCM12864_Demo_H
/* Includes---------------------------------------------*/
#include "sys.h"
#include "User_Conf.h" 
/* Private defines--------------------------------------*/
/* Private typedef -------------------------------------*/
/* Private macro ---------------------------------------*/
/* Private variables -----------------------------------*/
/* Private function prototypes -------------------------*/
void BSP_JCM12864_DemoTest(void);
void BSP_JCM12864_DemoTest1(void);
void BSP_JCM12864_Demo(void);
void BSP_JCM12864_DemoFF(void);
void BSP_JCM12864_Demo0(void);
void BSP_JCM12864_DemoR0(void); 
void BSP_JCM12864_Demo1(void);
void BSP_JCM12864_Demo2(void);
void BSP_JCM12864_Demo3(void);
void BSP_JCM12864_Demo4(void);
void BSP_JCM12864_Demo5(void);
void BSP_JCM12864_Demo6(void);
void BSP_JCM12864_Demo7(void);
void BSP_JCM12864_Demo8(void);
void BSP_JCM12864_Demo9(void);
void BSP_JCM12864_Demo10(void);
void BSP_JCM12864_Demo11(void);
void BSP_JCM12864_Demo12(void);
void BSP_JCM12864_Demo13(void);
void BSP_JCM12864_Demo14(void);
void BSP_JCM12864_Demo15(void);
void BSP_JCM12864_Demo16(void);
void BSP_JCM12864_Demo17(void);
void BSP_JCM12864_Demo18(void);
void BSP_JCM12864_Demo19(void);
void BSP_JCM12864_Demo20(void);
void BSP_JCM12864_Demo21(void);
void BSP_JCM12864_Demo22(void);
void BSP_JCM12864_Demo23(void);
void BSP_JCM12864_Demo24(void);
void BSP_JCM12864_Demo25(void);
void BSP_JCM12864_Demo26(void);
void BSP_JCM12864_Demo27(void);
void BSP_JCM12864_Demo28(void);
void BSP_JCM12864_Demo29(void);
void BSP_JCM12864_Demo40(void);
void BSP_JCM12864_Demo41(void);

void BSP_JCM12864_Demo50(void);
void BSP_JCM12864_Demo51(void);
void BSP_JCM12864_Demo52(void);
void BSP_JCM12864_Demo53(void);
void BSP_JCM12864_Demo54(void);
void BSP_JCM12864_Demo55(void);
void BSP_JCM12864_Demo56(void);
void BSP_JCM12864_Demo57(void);
void BSP_JCM12864_Demo58(void);
void BSP_JCM12864_Demo59(void);
void BSP_JCM12864_Demo60(void);
void BSP_JCM12864_Demo61(void);
void BSP_JCM12864_Demo62(void);
void BSP_JCM12864_Demo63(void);
void BSP_JCM12864_Demo64(void);
void BSP_JCM12864_Demo65(void);
void BSP_JCM12864_Demo66(void);
void BSP_JCM12864_Demo67(void);

void BSP_JCM12864_Demo72(void);
void BSP_JCM12864_Demo73(void);
void BSP_JCM12864_Demo74(void);
void BSP_JCM12864_Demo75(void);
void BSP_JCM12864_Demo76(void);
void BSP_JCM12864_Demo77(void);

void BSP_JCM12864_Demo82(void);//校准通道1
void BSP_JCM12864_Demo83(void);//校准通道1
void BSP_JCM12864_Demo84(void);//校准通道1
void BSP_JCM12864_Demo85(void);//校准通道1
void BSP_JCM12864_Demo86(void);//校准通道1
void BSP_JCM12864_Demo87(void);//校准通道1

void BSP_JCM12864_Demo100(void);//校准选项
void BSP_JCM12864_Demo101(void);//测试选项
void BSP_JCM12864_Demo102(void);//开启全部
void BSP_JCM12864_Demo103(void);//关闭全部

void BSP_JCM12864_Demo111(void);//通道1状态
void BSP_JCM12864_Demo112(void);//通道2状态
void BSP_JCM12864_Demo113(void);//通道3状态
void BSP_JCM12864_Demo114(void);//通道4状态
void BSP_JCM12864_Demo115(void);//通道5状态
void BSP_JCM12864_Demo116(void);//通道6状态

void BSP_JCM12864_Demo121(void);//更新通道1状态
void BSP_JCM12864_Demo122(void);//更新通道2状态
void BSP_JCM12864_Demo123(void);//更新通道3状态
void BSP_JCM12864_Demo124(void);//更新通道4状态
void BSP_JCM12864_Demo125(void);//更新通道5状态
void BSP_JCM12864_Demo126(void);//更新通道6状态

void BSP_JCM12864_Demo130(void);//通道全关	
void BSP_JCM12864_Demo131(void);//通道全开

void BSP_JCM12864_Demo141(void);//开关通道1		
void BSP_JCM12864_Demo142(void);//开关通道2
void BSP_JCM12864_Demo143(void);//开关通道3
void BSP_JCM12864_Demo144(void);//开关通道4
void BSP_JCM12864_Demo145(void);//开关通道5
void BSP_JCM12864_Demo146(void);//开关通道6

//void BSP_JCM12864_Demo141(void);//关通道1		
//void BSP_JCM12864_Demo142(void);//关通道2
//void BSP_JCM12864_Demo143(void);//关通道3
//void BSP_JCM12864_Demo144(void);//关通道4
//void BSP_JCM12864_Demo145(void);//关通道5
//void BSP_JCM12864_Demo146(void);//关通道6

void BSP_JCM12864_Demo151(void);//开通道1
void BSP_JCM12864_Demo152(void);//开通道2
void BSP_JCM12864_Demo153(void);//开通道3
void BSP_JCM12864_Demo154(void);//开通道4
void BSP_JCM12864_Demo155(void);//开通道5
void BSP_JCM12864_Demo156(void);//开通道6
/* Private functions -----------------------------------*/
/********** (C) COPYRIGHT DIY嵌入式开发工作室 *****END OF FILE****************/
#endif

