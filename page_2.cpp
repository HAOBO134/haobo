#include "common.h"

int p2()
{
	clrmous(MouseX,MouseY);
	
	int i;
	
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL,GREEN);
	bar(0,0,640,480);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(104,96,536,192);
	bar(104,288,536,384);
	puthz(152,120,"普通登录",48,90,BLACK);
	puthz(152,312,"管理登录",48,90,BLACK);
	setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0, 639, 39);
    setcolor(RED);
    line(600, 0, 639, 39);
    line(600, 39, 639, 0);

	while(1)
	{
		newmouse(&MouseX,&MouseY,&press);
		
		if(mouse_press(104,96,536,192)==1)
		{
			setcolor(RED);
			setlinestyle(0,0,3);
			rectangle(104+1,96+1,536-1,196-1);
			
			clrmous( MouseX , MouseY );
		    setfillstyle(1,YELLOW);
			bar(150,160,490,300 );
			setcolor(BLACK);
			setlinestyle(0, 0, 3);
			rectangle(150+1,160+1,490-1,300-1);
			puthz(263, 200, "登录成功",24,30,BLACK);
			for ( i=1;i<500;i++)
			{
				newmouse(&MouseX,&MouseY,&press);
				delay( 1);
			}
			return 3;
		}
		//普通登录 
		else if(mouse_press(104,288,536,384)==1)
		{   setcolor(RED);
			setlinestyle(0,0,3);
			rectangle(104+1,288+1,536-1,384-1);
			
			clrmous( MouseX , MouseY );
			setfillstyle(1,YELLOW);
			bar(150,160,490,300 );
			setcolor(BLACK);
			setlinestyle(0, 0, 3);
			rectangle(150+1,160+1,490-1,300-1);
			puthz(263, 200, "登录成功",24,30,BLACK);
			for ( i=1;i<500;i++)
			{
				newmouse(&MouseX,&MouseY,&press);
				delay( 1);
			}
			return 4;
		}
		//管理登录 
		else if(mouse_press(600, 0, 639, 39)==1)
		{
			delay(100);
			newmouse(&MouseX,&MouseY,&press);
			if(mouse_press(600, 0, 639, 39)==2){
			return 0;}
		}
	}
	
	
	
}
