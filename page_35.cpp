#include "common.h"
#include "page35.h"
#include "inform.h"

int p35()
{
   int hover_state[5];
   int new_hover[5];
   int time_state=0;
   
   page35_draw();
   while(1){
   	newmouse(&MouseX , &MouseY , &press);
   	if(mouse_press(600, 0, 639, 39)==1)
   	{
   		delay(100);
   		newmouse(&MouseX , &MouseY , &press);
   		if(mouse_press(600, 0, 639, 39)==2) return 3;
	   }
	else if(mouse_press(16,178+96+96,16+192,178+96+96+48)==1) 
	{
		time_state=time_judge();
		switch(time_state){
			case 1:
				return 351;
			case 2:
				message("管理员正在审核您的申请",&time_state);
				break;
			case 3:
				message("请确认您的车辆预约申请",&time_state);
				break;
		}
		
	}
	else if(mouse_press(16+208,178+96+96,16+208+192,178+96+96+48)==1)
	{
		time_state=time_judge();
		if(time_state==3)
		{			
		message("请确认您的车辆预约申请",&time_state);
		break;
		}
		if(!location_judge())
		{
			return 352;
		}
		else
		{
		    message("管理员正在审核您的申请",&time_state);
		}
	}
	else if(mouse_press(16+208+208,178+96+96,16+208+208+192,178+96+96+48)==1)
	{
		time_state=time_judge();
		if(time_state==3)
		{			
		message("请确认您的车辆预约申请",&time_state);
		break;
		}
		if(!park_judge())
		{
			return 353;
		}
		else
		{
		    message("管理员正在审核您的申请",&time_state);
		}
		
	}	
	for(int i=0;i<3;i++)
	{
		if(check_mouse_click(16+208*i,178+96+96,16+192+208*i,178+96+96+48)==1)
			{
				new_hover[i]=1;
			}
		else new_hover[i]=0;
		if(new_hover[i]!=hover_state[i]){		
		   setcolor(new_hover[i]?RED:YELLOW);
		   setlinestyle(0,0,3);
		   clrmous(MouseX, MouseY);
		   rectangle(16+208*i,178+96+96,16+192+208*i,178+96+96+48);   	 
		}
		hover_state[i]=new_hover[i];
	}
   	
   	delay(20);
   }	
}

void page35_draw()
{   
    User_information Uinformation[4];
	char username[20];
	strcpy(username,Get_username());
    user_information_get(Uinformation,username);
	clrmous(MouseX , MouseY);
	setbkcolor(WHITE);
	cleardevice();
	puthz(80,30,"欢迎来到预约入校界面",48,48,RED);
	setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0, 639, 39);
    setcolor(RED);
    line(600, 0, 639, 39);
    line(600, 39, 639, 0);
    puthz(74,178,"预约用户",48,48,BLUE);
	puthz(74,178+96,"预约车辆",48,48,BLUE);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(270,178,270+300,178+48);
	bar(270,178+96,270+300,178+48+96);
	bar(16,178+96+96,16+192,178+96+96+48);
	bar(16+208,178+96+96,16+208+192,178+96+96+48);
	bar(16+208+208,178+96+96,16+208+208+192,178+96+96+48);
	puthz(16,178+96+96,"入校时间",48,48,BLUE);
	puthz(16+208,178+96+96,"入校地点",48,48,BLUE);
	puthz(16+208+208,178+96+96,"停车位置",48,48,BLUE);
	setcolor(RED);
	settextstyle(0,0,3);
	outtextxy(270+15,178+15,username);
	outtextxy(270+15,178+96+15,Uinformation->car_name);
}
int time_judge()
{
	char username[60];
    char path[100];
    char text[256];
    int has_pending;
    strcpy(username,Get_username());
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%stime.txt",username);
	FILE *fp=fopen(path,"rt");
	if(!fp) return 1;//还没有选择时间
	while(fgets(text,sizeof(text)-1,fp))
	{
		if(strstr(text,"PENDING"))
		{
			has_pending=2;//管理员正在审核 
			break;
		}
		
		if(strstr(text,"REJECTED")||strstr(text,"APPROVE"))
		{
			has_pending=3;//等待用户确认 
			break;
		}
	}
	fclose(fp);
	return has_pending;
}
void message(char *text,int *time_state)
{
	clrmous(MouseX, MouseY);
    setfillstyle(1, YELLOW);
    bar(150, 160, 550, 300);
    setcolor(RED);
    setlinestyle(0, 0, 3);
    rectangle(151, 161, 549, 299);
    puthz(173, 200, text, 24, 30, BLUE);

    // 延时等待任意键/鼠标关闭提示
    for (int i = 0; i < 500; i++)
    {
        delay(1);
        if (kbhit()) bioskey(0);
        newmouse(&MouseX, &MouseY, &press);
    }
    page35_draw();
    *time_state=0;
}

int location_judge()
{
	char username[60];
    char path[100];
    strcpy(username,Get_username());
    sprintf(path,"C:\\CODE\\SOURCE\\USER\\%slocat.txt",username);
	FILE *fp=fopen(path,"rt");
	if(!fp) {
	   fclose(fp);
	   return 0;}
	else{
		fclose(fp);
		return 1;
	}
}

int park_judge()
{
	char username[60];
    char path[100];
    strcpy(username,Get_username());
    sprintf(path,"C:\\CODE\\SOURCE\\USER\\%spark.txt",username);
	FILE *fp=fopen(path,"rt");
	if(!fp) {
	   fclose(fp);
	   return 0;}
	else{
		fclose(fp);
		return 1;
	}
}
