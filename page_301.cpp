#include "page301.h"
#include "common.h"
#include "inform.h"

int p301()
{
	int hover_state;
	int new_hover;
	int judge;
	judge=page301_judge();
	if(judge==0) {page301_draw_N("您还没有申请年审");return 3;}
	else if(judge==1) {page301_draw_N("正在审核您的申请");return 3;}
	page301_draw(judge-2);
	while(1){
		newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(270,80+24+72*4+20,140+100+130,80+24+72*4+48+20)==1){
			review_ensure();
			return 3;
		}
		else if(mouse_press(600, 0+20, 639, 39+20)==1){
			return 3;
		}
		
		newmouse(&MouseX , &MouseY , &press);
		if(check_mouse_click(270,80+24+72*4+20,140+100+130,80+24+72*4+48+20)==1)
			{
				new_hover=1;
			}
		else new_hover=0;
		if(new_hover!=hover_state){		
		   setcolor(new_hover?RED:YELLOW);
		   setlinestyle(0,0,3);
		   clrmous(MouseX, MouseY);
		   rectangle(270,80+24+72*4+20,140+100+130,80+24+72*4+48+20);   	 
		}
		hover_state=new_hover;
		
		
		delay(20);
	}
}

void page301_draw(int judge)
{
	clrmous(MouseX , MouseY);
	setbkcolor(WHITE);
	cleardevice();
	char username[30];
	strcpy(username,Get_username());
	setfillstyle(SOLID_FILL,YELLOW);
	User_information information[3];
	user_information_get(information,username);
	char a[5][10];
	strcpy(a[0],"密码名");strcpy(a[1],"车辆名");strcpy(a[2],"城市名");strcpy(a[3],"车牌号");
	for(int i=0;i<4;i++){
		bar(98+144,80+24+i*72-72,98+144+300,80+24+48+i*72-72);
		puthz(98,80+24+i*72-72,a[i],48,48,BLUE);
	}
	bar(270,80+24+72*4+20,140+100+130,80+24+72*4+48+20);
	puthz(140+130+2,80+24+72*4+2+20,"确认",48,48,RED);
	setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0+20, 639, 39+20);
    setcolor(RED);
    line(600, 0+20, 639, 39+20);
    line(600, 39+20, 639, 0+20);
    setcolor(BLUE);
    settextstyle(0,0,3);
    outtextxy(98+144+15,80+24+0*72+15-72,information->password);
    outtextxy(98+144+15,80+24+1*72+15-72,information->car_name);
    outtextxy(98+144+15,80+24+3*72+15-72,information->car_plate);
    puthz(98+144+10,80+24+2*72+1-72,information->city,48,48,BLUE); 
    puthz(98+1-60,80+24+3*72+1,"审核状态",48,48,RED);
    if(judge==1) puthz(98+1+48*4+10-60,80+24+3*72+1,"同意您的年审申请",48,48,RED);
    else if(judge==0) puthz(98+1+48*4+10-60,80+24+3*72+1,"拒绝您的年审申请",48,48,RED);
}
void page301_draw_N(char *wenben)
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

int page301_judge()
{
	char username[20];
	strcpy(username,Get_username());
	char path[30];
	char buffer[40];
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sre.txt",username);
	FILE *fp;
	fp=fopen(path,"rt");
	if(!fp) return 0;
	fgets(buffer,sizeof(buffer),fp);
	fclose(fp);
	if(strstr(buffer,"PENDING")) return 1;
	else if(strstr(buffer,"APPROVE")) return 3;
	else if(strstr(buffer,"REJECTED")) return 2;
	else return 3;
}
void review_ensure()
{
	char path[50];
	char username[15];
	strcpy(username,Get_username());
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sre.txt",username);
	remove(path);
}
