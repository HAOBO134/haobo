#include "common.h"
#include "inform.h"
#include "page302.h"

int p302(){
	Scrap_information information[3];
	char username[20];
	int scrap_state;
	int judge;
	int new_hover;
	int hover_state;
	strcpy(username,Get_username());
	scrap_state=scrap_information_get(information,username);
	if(!scrap_state) {page302_draw_N("您还没有报废申请"); return 3;}
	if(strstr(information->status,"PENDING")) {page302_draw_N("您的申请正在审核中"); return 3;}
	else if(strstr(information->status,"APPROVE")) {judge=1;page302_draw(judge);}
	else if(strstr(information->status,"REJECTED")){judge=0;page302_draw(judge);}
	while(1){
		
		newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(270,24+96*4,270+100,24+96*4+48)==1){
			scrap_ensure(judge);
			return 3;
		}
		else if(mouse_press(600, 0, 639, 39)==1){
			delay(100);
			newmouse(&MouseX , &MouseY , &press);
			if(mouse_press(600, 0, 639, 39)==2) return 3;
		}
		
		newmouse(&MouseX , &MouseY , &press);
		if(check_mouse_click(270,24+96*4,270+100,24+96*4+48)==1)
			{
				new_hover=1;
			}
		else new_hover=0;
		if(new_hover!=hover_state){		
		   setcolor(new_hover?RED:YELLOW);
		   setlinestyle(0,0,3);
		   clrmous(MouseX, MouseY);
		   rectangle(270,24+96*4,270+100,24+96*4+48);   	 
		}
		hover_state=new_hover;
		
		delay(20);
	}
} 


void page302_draw(int judge)
{
	clrmous(MouseX , MouseY);
	setbkcolor(WHITE);
	cleardevice();
	char a[5][15];
	char j[10];
	Scrap_information information[3];
	scrap_information_get(information,Get_username());
	strcpy(j,information->reason_code); 
	int reason=atoi(j);
	strcpy(a[0],"用户名");strcpy(a[1],"车辆名");strcpy(a[2],"报废原因");strcpy(a[3],"审核状态");
	setfillstyle(SOLID_FILL,YELLOW);
	for(int i=0;i<4;i++){
		puthz(74+1,24+i*96+1,a[i],48,48,BLUE);
		bar(74+192,24+i*96,74+192+300,24+48+i*96);
	}
	bar(270,24+96*4,270+100,24+96*4+48);
	puthz(270+2,24+96*4+2,"确认",48,48,BLUE);
	switch (reason)
	{
		case 1 :
			puthz(74+192+2,24+2*96+1,"电动车老旧",48,48,BLUE);
			break;
		case 2:
			puthz(74+192+2,24+2*96+1,"电动车损毁",48,48,BLUE);
			break;
		case 3:
			puthz(74+192+2,24+2*96+1,"电动车车祸",48,48,BLUE);
		    break;
		case 4:
		    puthz(74+192+2,24+2*96+1,"电动车泡水",48,48,BLUE);
		    break;
	}
	settextstyle(0,0,3);
	setcolor(BLUE);
	outtextxy(74+192+15,24+15,information->username);
	outtextxy(74+192+15,24+96+15,information->car_name);
	if(judge==1) puthz(74+192+2,24+3*96+2,"同意报废申请",48,48,RED);
	else         puthz(74+192+2,24+3*96+2,"拒绝报废申请",48,48,RED);
		setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0, 639, 39);
    setcolor(RED);
    line(600, 0, 639, 39);
    line(600, 39, 639, 0);
}

void page302_draw_N(char *wenben){
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

void scrap_ensure(int judge)
{
	if(judge==1){
	char path[40];
	char username[15];
	char password[15];
	strcpy(username,Get_username());
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sscrap.txt",username);
	remove(path);
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%s.txt",username);
	FILE *fp;
	fp=fopen(path,"rt");
	fgets(password,sizeof(password),fp);
	trim_newline1(password);
	fclose(fp);
	fp=fopen(path,"wt");
	fprintf(fp,"%s",password);
	fclose(fp);}
	else{
	char path[40];
	char username[15];
	strcpy(username,Get_username());
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sscrap.txt",username);
	remove(path);
	}
	
}
