#include "common.h"
#include "page303.h"
#include "inform.h"

int p303(){
	Scrap_information information[3];
	char username[20];
	char time[40];
	char location[15];
	char park[20];
	char status[20];
	int month;int day;
	int enter_state;
	int judge;
	strcpy(username,Get_username());
	enter_state=admission_information_get(username,time,location,park,status,&month,&day);
	if(!enter_state) {page303_draw_N("您的入校申请不完善"); return 3;} 
	if(strstr(status,"PENDING")) {page303_draw_N("您的申请正在审核中"); return 3;}
	else if(strstr(status,"APPROVE")) {judge=1;page303_draw(judge);}
	else if(strstr(status,"REJECTED")){judge=0;page303_draw(judge);}
	while(1){
		int hover_state;
		int new_hover;
		
		newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(270,90+96*4-24-24-12,270+100,90+96*4-12)==1){
			ensure();
			return 3;
		}
		else if(mouse_press(600, 0, 639, 39)==1){
			return 3;
		}
		newmouse(&MouseX , &MouseY , &press);
		if(check_mouse_click(270,90+96*4-24-24-12,270+100,90+96*4-12)==1)
			{
				new_hover=1;
			}
		else new_hover=0;
		if(new_hover!=hover_state){		
		   setcolor(new_hover?RED:YELLOW);
		   setlinestyle(0,0,3);
		   clrmous(MouseX, MouseY);
		   rectangle(270,90+96*4-24-24-12,270+100,90+96*4-12);   	 
		}
		hover_state=new_hover;
		
		
		delay(20);
	}
	
	
}

void page303_draw(int judge)
{
	char username[20];
	strcpy(username,Get_username());
	User_information information1[3];
	user_information_get(information1,username);
	char time[40];
	char time_month[5];
	char time_day[5];
	char clock[20];
	char buffer[30];
	char location[20];
	char park[20];
	char status[20];
	int month;int day;
	admission_information_get(username,time,location,park,status,&month,&day);
	char a[6][30];
	strcpy(a[0],"车辆名");strcpy(a[1],"车牌号");strcpy(a[2],"入校地点");strcpy(a[3],"停车位置");
	char result[30];
	if(judge==1) strcpy(result,"您的入校申请通过");
	else  strcpy(result,"拒绝您的入校申请"); 
	clrmous(MouseX , MouseY);
	setbkcolor(WHITE);
	cleardevice();
	puthz(80,24,"欢迎查看报废申请结果",48,48,RED);
	setfillstyle(SOLID_FILL,YELLOW);
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			bar(26+96+10+j*(136+96+10+50+25),90+i*96,26+96+10+120+j*(136+96+10+50+25)+50,90+24+i*96);
			puthz(26+96+10+j*(136+96+10+50+25)+1-96-10,90+i*96+1,a[2*i+j],24,24,BLUE);
		}
	}
	puthz(26,90+96*3-24,"审核状态",48,48,BLUE);
	puthz(26+48*4+10,90+96*3-24,result,48,48,RED);
	bar(270,90+96*4-24-24-12,270+100,90+96*4-12);
	puthz(270+1,90+96*4+1-24-24-12,"确认",48,48,BLUE);
	setcolor(BLUE);
	settextstyle(0,0,2);
	outtextxy(26+96+10+5,90+5,information1->car_name);
	outtextxy(26+96+10+136+96+10+50+25+5,90+5,information1->car_plate);
	puthz(26+96+10+1,90+96+1,location,24,24,BLUE);
	puthz(26+96+10+136+96+10+50+25+1,90+96+1,park,24,24,BLUE);
	if(strstr(time,"七点至九点")) strcpy(clock,"七点至九点");
	else if(strstr(time,"九点至十点")) strcpy(clock,"九点至十点");
	else if(strstr(time,"两点至四点")) strcpy(clock,"两点至四点");
	else if(strstr(time,"四点至六点")) strcpy(clock,"四点至六点");
    settextstyle(0,0,3);
	sprintf(time_month,"%d",month);
	sprintf(time_day,"%d",day);
	sprintf(buffer,"日%s",clock);
	puthz(26,90+96*2+3,"您的入校时间",24,24,BLUE);
	bar(175,90+96*2,614,90+96*2+24);
	puthz(26+288+5+5-144,90+96*2+3,"二零二六年",24,24,BLUE);
	outtextxy(26+288+5+5+120+10-144,90+96*2+3,time_month);//
	puthz(26+288+5+5+120+10+48+1-144,90+96*2+3,"月",24,24,BLUE);
	outtextxy(26+288+5+5+120+10+48+24+10-144,90+96*2+3,time_day);//
	puthz(26+288+5+5+120+10+48+24+10+48+1-144,90+96*2+3,buffer,24,24,BLUE);
	setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0, 639, 39);
    setcolor(RED);
    line(600, 0, 639, 39);
    line(600, 39, 639, 0);
}

void page303_draw_N(char * wenben){
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

void ensure()
{
	char path[4][50];
	char username[15];
	strcpy(username,Get_username());
	sprintf(path[0],"C:\\CODE\\SOURCE\\USER\\%stime.txt",username);
	sprintf(path[1],"C:\\CODE\\SOURCE\\USER\\%slocat.txt",username);
	sprintf(path[2],"C:\\CODE\\SOURCE\\USER\\%spark.txt",username);
	remove(path[0]);remove(path[1]);remove(path[2]);
}
 
