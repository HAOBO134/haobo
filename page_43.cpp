#include "common.h"
#include "page43.h"
#include "inform.h"

int p43(char * username)
{
	int hover_state[3]={0};
    int new_hover[3]={0};
    int enter_handle_state;
    int state;
    state=enter_judge(username);
    if(state==1){
	  page43_draw(username);
	  while(1){
		newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(600, 0, 639, 39)==1) return 41;
		else if(mouse_press(145,398,245,398+48)==1)
		{
		   enter_handle_state=1;
		   enter_handle(enter_handle_state,username);
		   return 41;
		   	
		}
		
		else if(mouse_press(145+250,398,145+100+250,398+48)==1)
		{
		   enter_handle_state=0;
		   enter_handle(enter_handle_state,username);
		   return 41;
		}
		for( int i=0;i<2;i++){
		if(check_mouse_click(145+i*250,398,145+100+i*250,398+48)==1)
			{
			   new_hover[i]=1;
			}
		else new_hover[i]=0;
		if(new_hover[i]!=hover_state[i]){		
		    setcolor(new_hover[i]?RED:YELLOW);
		    setlinestyle(0,0,3);
			clrmous(MouseX, MouseY);
			rectangle(145+i*250,398,145+100+i*250,398+48);   	 
		}
	    hover_state[i]=new_hover[i];
    } 
		delay(20);
	}
  }
  else if(state==0)
  {
  	page43_draw_N("该用户没有入校申请");
  	return  41; 
  }
  else if(state==2)
  {
  	page43_draw_N("该用户申请已审核完毕");
  	return  41; 
  }
	else return 41;
}

void page43_draw(char *username)
{
	clrmous(MouseX , MouseY);
	setbkcolor(WHITE);
	cleardevice();
	User_information information[2];
	char time[100];//读的time 
	char time_month[20];
	char time_day[20]; 
	char location[30];
	char buffer[30];
	char park[30];
	char status[20];
	char clock[30];
	int month;int day;
	char a[7][12];
	char b[3][10];
	strcpy(b[0],"同意");strcpy(b[1],"拒绝");
	strcpy(a[0],"用户名");strcpy(a[1],"车辆名");strcpy(a[2],"车牌号");strcpy(a[3],"入校地点");strcpy(a[4],"停车位置");
	user_information_get(information,username);
	admission_information_get(username,time,location,park,status,&month,&day);
	if(strstr(time,"七点至九点")) strcpy(clock,"七点至九点");
	else if(strstr(time,"九点至十点")) strcpy(clock,"九点至十点");
	else if(strstr(time,"两点至四点")) strcpy(clock,"两点至四点");
	else if(strstr(time,"四点至六点")) strcpy(clock,"四点至六点");
	sprintf(time_month,"%d",month);
	sprintf(time_day,"%d",day);
	sprintf(buffer,"日%s",clock);
	puthz(80,30-12,"欢迎来到入校管理界面",48,48,RED);
	setfillstyle(SOLID_FILL,YELLOW);
	for(int i=0;i<5;i++){
		puthz(79+1-5,80+i*48+1+24,a[i],24,24,BLUE);
		bar(79+96,80+i*48+24,79+96+300,80+i*48+24+24);
	}
	puthz(26,80+48*5+3+24,"您的入校时间",24,24,BLUE);
	bar(175,80+48*5+24,614,80+48*5+30+24);
	for(i=0;i<2;i++){
		bar(145+i*250,398,145+100+i*250,398+48);
		puthz(145+i*250+3,398+1,b[i],48,48,RED);
	}
	settextstyle(0,0,3);
    setcolor(BLUE);
	puthz(26+288+5+5-144,80+48*5+3+24,"二零二六年",24,24,BLUE);
	outtextxy(26+288+5+5+120+10-144,80+48*5+3+24,time_month);
	puthz(26+288+5+5+120+10+48+1-144,80+48*5+3+24,"月",24,24,BLUE);
	outtextxy(26+288+5+5+120+10+48+24+10-144,80+48*5+3+24,time_day);
	puthz(26+288+5+5+120+10+48+24+10+48+1-144,80+48*5+3+24,buffer,24,24,BLUE);
    settextstyle(0,0,2);
    outtextxy(79+96+50,80+24+4,username);
    outtextxy(76+96+50,80+48+24+6,information->car_name);
    outtextxy(76+96+50,80+2*48+24+6,information->car_plate);
	puthz(79+96+50,80+3*48+24,location,24,24,BLUE);
	puthz(79+96+50,80+4*48+24,park,24,24,BLUE);
	setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0, 639, 39);
    setcolor(RED);
    line(600, 0, 639, 39);
    line(600, 39, 639, 0);
}

void enter_handle(int enter_handle_state,char *username)
{
	char path[50];
	char buffer[200];
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%stime.txt",username);
	FILE *fp=fopen(path,"rt");
	fread(buffer,1,sizeof(buffer)-1,fp);
	fclose(fp);
	char *pos=strstr(buffer,"PENDING");
	if(pos!=NULL&&enter_handle_state==1) strcpy(pos,"APPROVE\n");
	else if(pos!=NULL&&enter_handle_state==0) strcpy(pos,"REJECTED\n");
	fp=fopen(path,"wt");
	fputs(buffer,fp);
	fclose(fp);
}
void page43_draw_N(char * wenben)
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
int enter_judge(char *username)
{
	FILE *fp0,*fp1,*fp2;
	char path1[50];
	char buffer[200];
	char path[4][50];
	sprintf(path[0],"C:\\CODE\\SOURCE\\USER\\%stime.txt",username);
	sprintf(path[1],"C:\\CODE\\SOURCE\\USER\\%slocat.txt",username);
	sprintf(path[2],"C:\\CODE\\SOURCE\\USER\\%spark.txt",username);
	fp0=fopen(path[0],"rt");fp1=fopen(path[1],"rt");fp2=fopen(path[2],"rt");
	if(!fp0||!fp1||!fp2) return 0;//入校信息不完善 
	fclose(fp0);fclose(fp1);fclose(fp2);
	sprintf(path1,"C:\\CODE\\SOURCE\\USER\\%stime.txt",username);
	FILE *fp=fopen(path1,"rt");
	if(!fp) return 0;
	fread(buffer,1,sizeof(buffer)-1,fp);
	fclose(fp);
	if(strstr(buffer,"PENDING")) return 1;//等待审核
	else if(strstr(buffer,"APPROVE")) return 2;
	else if(strstr(buffer,"REJECTED")) return 2;
	else return 3;
}
