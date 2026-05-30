#include "common.h"//报废审核功能 
#include "inform.h"
#include "page44.h"
#include "page34.h"

Scrap_information information3[4];
int scrap_state;
int p44(char *username)
{
   int hover_state[4];
   int new_hover[4];
   char wenben[30];
   int scrap_handle_state;
   scrap_state=scrap_information_get(information3,username);
   if((strstr(information3->status,"APPROVE"))||(strstr(information3->status,"REJECTED"))) scrap_state=3;
  
   if(scrap_state==1) page44_draw();
   else if(scrap_state==0)
   {
   	   strcpy(wenben,"该用户没有报废申请");
   	   page44_draw_N(wenben); 
   	   return 41;
   }
   else if(scrap_state==3)
   {
   	   strcpy(wenben,"该用户申请已审核完毕");
   	   page44_draw_N(wenben); 
   	   return 41;
   }
   
   while(1)
   {
   	newmouse(&MouseX , &MouseY , &press);	
   	if(mouse_press(600, 0, 639, 39)==1)
   	{
   		delay(100);
   		newmouse(&MouseX , &MouseY , &press);
   		if(mouse_press(600, 0, 639, 39)==2) return 41;
	}
	
	else if(mouse_press(100,178+96+96,100+100,178+96+96+48)==1)
	{
		scrap_handle_state=1;
		scrap_handle(scrap_handle_state);
		return 41;
	}
	else if(mouse_press(100+340,178+96+96,100+340+100,178+96+96+48)==1)
	{
		scrap_handle_state=0;
		scrap_handle(scrap_handle_state);
		return 41;	
	}
	for(int i=0;i<2;i++){
		if(check_mouse_click(100+i*340,178+96+96,100+100+i*340,178+96+96+48)==1)
			{
				new_hover[i]=1;
			}
		else new_hover[i]=0;
		if(new_hover[i]!=hover_state[i]){		
		   setcolor(new_hover[i]?RED:YELLOW);
		   setlinestyle(0,0,3);
		   clrmous(MouseX, MouseY);
		   rectangle(100+i*340,178+96+96,100+100+i*340,178+96+96+48);   	 
		}
		hover_state[i]=new_hover[i];
	   
      } 
   	delay(20);
   }
   
   
}

void page44_draw()
{
	clrmous(MouseX , MouseY);
	cleardevice();
	setbkcolor(WHITE);
	puthz(80,30,"欢迎来到报废管理界面",48,48,RED);
	puthz(74,178,"报废车辆",48,48,BLUE);
	puthz(74,178+96,"报废原因",48,48,BLUE);
	setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0, 639, 39);
    setcolor(RED);
    line(600, 0, 639, 39);
    line(600, 39, 639, 0);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(270,178,270+300,178+48);
	bar(270,178+96,270+300,178+48+96);
	bar(100,178+96+96,100+100,178+96+96+48);
	bar(100+340,178+96+96,100+340+100,178+96+96+48);
	puthz(100+2,178+96+96+1,"同意",48,48,RED);
	puthz(100+340+2,178+96+96+1,"拒绝",48,48,RED);
	setcolor(BLUE);
	settextstyle(0,0,3);
	outtextxy(270+15,178+15,information3->car_name);
	char i[10];
	strcpy(i,information3->reason_code); 
	int reason=atoi(i);
	switch (reason)
	{
		case 1 :
			puthz(270+15-5,178+96+2,"电动车老旧",48,48,BLUE);
			break;
		case 2:
			puthz(270+15-5,178+96+2,"电动车损毁",48,48,BLUE);
			break;
		case 3:
			puthz(270+15-5,178+96+2,"电动车车祸",48,48,BLUE);
		    break;
		case 4:
		    puthz(270+15-5,178+96+2,"电动车泡水",48,48,BLUE);
		    break;
	}
	
}

void page44_draw_N(char * wenben)
{
	clrmous(MouseX, MouseY);
    setfillstyle(1, YELLOW);
    bar(150, 160, 550, 300);
    setcolor(RED);
    setlinestyle(0, 0, 3);
	rectangle(151, 161, 549, 299);
	puthz(173, 200, wenben, 24, 30, BLUE);
    // 延时等待任意键/鼠标关闭提示
	for (int i = 0; i < 500; i++)
	{
       delay(1);
	   if (kbhit()) bioskey(0);
	   newmouse(&MouseX, &MouseY, &press);
    }
}

void scrap_handle(int scrap_handle_state)
{
	char path[50];
	char buffer[200];
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sscrap.txt",information3->username);
	FILE *fp=fopen(path,"rt");
	fread(buffer,1,sizeof(buffer)-1,fp);
	fclose(fp);
	char *pos=strstr(buffer,"PENDING");
	if(pos!=NULL&&scrap_handle_state==1) strcpy(pos,"APPROVE\n");
	else if(pos!=NULL&&scrap_handle_state==0) strcpy(pos,"REJECTED\n");
	fp=fopen(path,"wt");
	fputs(buffer,fp);
	fclose(fp);
}


