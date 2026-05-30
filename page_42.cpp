#include "page42.h"
#include "common.h"
#include "inform.h"

int p42(char *username){
	
	int new_hover[3];
	int hover_state[3];
	int review_state;
	int handle_state;
	review_state=review_judge(username);
	if(review_state==0){ page42_draw_N("该用户暂无年审申请"); return 41;}
	else if(review_state==2) { page42_draw_N("年审申请已审核"); return 41;}
	page42_draw(username);
	while(1){
		
		
		newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(140+260*0,80+24+72*4+20,140+100+260*0,80+24+72*4+48+20)==1){
			handle_state=1;
			review_handle(username,handle_state);
			return 41;
		}
		else if(mouse_press(140+260*1,80+24+72*4+20,140+100+260*1,80+24+72*4+48+20)==1){
			handle_state=0;
			review_handle(username,handle_state);
			return 41;
		}
		else if(mouse_press(600, 0+20, 639, 39+20)==1){
			delay(100);
			return 41;
		}
	    
		newmouse(&MouseX , &MouseY , &press);
		for(int i=0;i<2;i++){
		if(check_mouse_click(140+260*i,80+24+72*4+20,140+100+260*i,80+24+72*4+48+20)==1)
			{
				new_hover[i]=1;
			}
		else new_hover[i]=0;
		if(new_hover[i]!=hover_state[i]){		
		   setcolor(new_hover[i]?RED:YELLOW);
		   setlinestyle(0,0,3);
		   clrmous(MouseX, MouseY);
		   rectangle(140+260*i,80+24+72*4+20,140+100+260*i,80+24+72*4+48+20);   	 
		}
		hover_state[i]=new_hover[i];
	   
      } 
		
		delay(20);
	}
	
}

void page42_draw(char *username)
{
	clrmous(MouseX , MouseY);
	setbkcolor(WHITE);
	cleardevice();
	setfillstyle(SOLID_FILL,YELLOW);
	User_information information[3];
	user_information_get(information,username);
	char a[5][10];
	strcpy(a[0],"密码名");strcpy(a[1],"车辆名");strcpy(a[2],"城市名");strcpy(a[3],"车牌号");
	puthz(80,30,"欢迎来到年审管理界面",48,48,RED);
	for(int i=0;i<4;i++){
		bar(98+144,80+24+i*72,98+144+300,80+24+48+i*72);
		puthz(98,80+24+i*72,a[i],48,48,BLUE);
	}
	bar(140,80+24+72*4+20,140+100,80+24+72*4+48+20);
	bar(140+260,80+24+72*4+20,140+100+260,80+24+72*4+48+20);
	puthz(140+2,80+24+72*4+2+20,"同意",48,48,RED);
	puthz(140+260+2,80+24+72*4+2+20,"拒绝",48,48,RED);
	setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0+20, 639, 39+20);
    setcolor(RED);
    line(600, 0+20, 639, 39+20);
    line(600, 39+20, 639, 0+20);
    setcolor(BLUE);
    settextstyle(0,0,3);
    outtextxy(98+144+15,80+24+0*72+15,information->password);
    outtextxy(98+144+15,80+24+1*72+15,information->car_name);
    outtextxy(98+144+15,80+24+3*72+15,information->car_plate);
    puthz(98+144+10,80+24+2*72+1,information->city,48,48,BLUE);
}

void page42_draw_N(char * wenben)
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

int review_judge(char *username){
	char path[30];
	char buffer[40];
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sre.txt",username);
	FILE *fp;
	fp=fopen(path,"rt");
	if(!fp) { return 0;}
	fgets(buffer,sizeof(buffer),fp);
	fclose(fp);
	if(strstr(buffer,"PENDING")) return 1;
	else if(strstr(buffer,"APPROVE")||strstr(buffer,"REJECTED")) return 2;
	return 3; 
	
	
}

void review_handle(char *username,int handle_state)
{
	char path[30];
	char buffer[40];
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sre.txt",username);
	FILE *fp;
	fp=fopen(path,"rt");
	if(!fp) { exit(0);}
	fgets(buffer,sizeof(buffer),fp);
	fclose(fp);
	if(handle_state==1) strcpy(buffer,"Status :APPROVE");
	else if(handle_state==0) strcpy(buffer,"Status :REJECTED");
	fp=fopen(path,"wt");
	if(!fp) { exit(0);}
	fprintf(fp,"%s",buffer);
	fclose(fp);
}
