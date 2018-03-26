#include "menu1.h"
#include "stm32f10x.h"
#include "12864.h"
#include "systick.h"
#include <stdio.h>
#include <stdlib.h>
#include "key.h"
#include "public.h"

/*菜单结构体*/
typedef struct menu
{
 u8 range_from,range_to; //当前选择的项开始及结束符号
 u8 itemCount;//项目总数
 u8 selected;//当前选择项
 u8 *menuItems[17];//菜单项目
 struct menu **subMenus;//子菜单
 struct menu *parent;//上级菜单，若是主菜单则为null
 void (**func)();//选择相应按键后执行的函数

}Menu; 


Menu MainMenu1 = { 
 0,3,4,0,						//默认显示0-3项，总共4项，当前选择0项，
  {
  "dis1234           \x10",//"\x10"表示一个小箭头
  "dis2           \x10",
  "dis3           \x10",
  "dis4           \x10",
  }
}; 

Menu dis1Menu = { 
 0,3,4,0,						//默认显示0-3项，总共4项，当前选择0项，
  {
  "secondline1_1    \x10",//"\x10"表示一个小箭头
  "secondline1_2    \x10",
  "secondline1_3    \x10",
  "secondline1_4    \x10",
  }
}; 
Menu dis2Menu = { 
 0,3,4,0,						//默认显示0-3项，总共4项，当前选择0项，
  {
  "secondline2_1    \x10",//"\x10"表示一个小箭头
  "secondline2_2    \x10",
  "secondline2_3    \x10  ",
  "secondline2_4    \x10",
  }
}; 
Menu dis3Menu = { 
 0,3,4,0,						//默认显示0-3项，总共4项，当前选择0项，
  {
  "secondline2_1    \x10",//"\x10"表示一个小箭头
  "secondline2_2    \x10",
  "secondline2_3    \x10  ",
  "secondline2_4    \x10",
  }
}; 

Menu *currentMenu;//当前菜单
/*用于显示菜单*/
void displaymenu(u8 line)
{
	int i;
	line = 3-(currentMenu->range_to-line);
	/*4次循环打印菜单*/
	for(i = 0;i<4;i++)
		Display_LCD_String(i,currentMenu->menuItems[i+currentMenu->range_from],5);
	con_disp(line,1);
	
}
void func(void)
{
	
}

void initmenu(void)
{
	currentMenu = &MainMenu1;
	
	MainMenu1.subMenus = malloc(sizeof(&MainMenu1)*4);
	MainMenu1.subMenus[0] = &dis1Menu;
	MainMenu1.subMenus[1] = &dis2Menu;
	MainMenu1.subMenus[2] = NULL;
	MainMenu1.subMenus[3] = NULL;
	
	MainMenu1.func = malloc(sizeof(&func)*4);
	MainMenu1.func[0] = NULL;
	MainMenu1.func[1] = NULL;
	MainMenu1.func[2] = NULL;
	MainMenu1.func[3] = NULL;
	
	MainMenu1.parent = NULL;//mainmenu is top menu
	
	dis1Menu.subMenus = malloc(sizeof(&dis1Menu)*4);
	dis1Menu.subMenus[0] = NULL;
	dis1Menu.subMenus[1] = NULL;
	dis1Menu.subMenus[2] = NULL;
	dis1Menu.subMenus[3] = NULL;
	
	dis1Menu.func = malloc(sizeof(&func)*4);
	dis1Menu.func[0] = NULL;
	dis1Menu.func[1] = NULL;
	dis1Menu.func[2] = NULL;
	dis1Menu.func[3] = NULL;
	
	dis1Menu.parent = &MainMenu1;//dis1menu parent menu is mainmenu1
	
	
	dis2Menu.subMenus =  malloc(sizeof(&dis1Menu)*4);
	dis2Menu.subMenus[0] = NULL;
	dis2Menu.subMenus[1] = NULL;
	dis2Menu.subMenus[2] = NULL;
	dis2Menu.subMenus[3] = NULL;
	
	dis2Menu.func = malloc(sizeof(&func)*4);
	dis2Menu.func[0] = NULL;
	dis2Menu.func[1] = NULL;
	dis2Menu.func[2] = NULL;
	dis2Menu.func[3] = NULL;
	
	dis2Menu.parent = &MainMenu1;//dis2menu parent menu is mainmenu1
	
}

void menutest(void)
{
	initmenu();
	displaymenu(currentMenu->selected);
	
	while(1)
	{	ReadValue=KEY_Scan(0);
//		if(key_pressed_flag)
		if(ReadValue!=0)
		{
			
			
			

					switch(ReadValue)
					{
						case KEY0_PRES://按键A（确认按键）
						{
						if(currentMenu->subMenus[currentMenu->selected] !=NULL)
							{
								currentMenu = currentMenu->subMenus[currentMenu->selected];
								displaymenu(0);
							}
							break;
						}
						case KEY3_PRES://按键B（上一行菜单）
						{
							if(currentMenu->selected == 0)
								break;
							else
							{
								currentMenu->selected--;
								if(currentMenu->selected < currentMenu->range_from)
								{
									currentMenu->range_from = currentMenu->selected;
									currentMenu->range_to = currentMenu->range_from+3;
								}
								displaymenu(currentMenu->selected);
								
							}	
							break;
						}
						case KEY1_PRES://按键C（下一行菜单 ）
						{
							if(currentMenu->selected == currentMenu->itemCount-1)
								break;
							else
							{
								currentMenu->selected++;
								if(currentMenu->selected>currentMenu->range_to)
								{
									currentMenu->range_to = currentMenu->selected;
									currentMenu->range_from = currentMenu->range_to-3;
								}
								displaymenu(currentMenu->selected);
								
							}
							break;
						}	
						case KEY2_PRES://按键D（返回）
						{
							if(currentMenu->parent!=NULL)
							{
								currentMenu = currentMenu->parent;
								displaymenu(currentMenu->selected);
							}
							break;
						}
						default:
							break;
					}
				
				
		}
	}
}
