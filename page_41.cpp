#include "common.h"
#include "page41.h"
#include "inform.h"
char User_name[30];
User_information information2[4];
int hover_state[8]={0};
int new_hover[8]={0};
int p41(char *username)
{
   strcpy(User_name,username);
   page41_draw(User_name);
   while(1){
   	newmouse(&MouseX , &MouseY , &press);
   	if (mouse_press(16+208*0,128+96+96+96,16+192+208*0,128+96+96+96+48)==1) return 42;
   	else if(mouse_press(16+208*1,128+96+96+96,16+192+208*1,128+96+96+96+48)==1) return 43;
   	else if(mouse_press(16+208*2,128+96+96+96,16+192+208*2,128+96+96+96+48)==1) return 44;
   	else if(mouse_press(600, 0+30, 639, 39+30)==1) {
    			return 4;
		}
    

   newmouse(&MouseX , &MouseY , &press);
   for(int i=0;i<3;i++){
		if(check_mouse_click(16+208*i,128+96+96+96,16+192+208*i,128+96+96+96+48)==1)
			{
			   new_hover[i]=1;
			}
		else new_hover[i]=0;
		if(new_hover[i]!=hover_state[i]){		
		    setcolor(new_hover[i]?RED:YELLOW);
		    setlinestyle(0,0,3);
			clrmous(MouseX, MouseY);
			rectangle(16+208*i,128+96+96+96,16+192+208*i,128+96+96+96+48);   	 
		}
	    hover_state[i]=new_hover[i];
    } 
}	
}

void page41_draw(char *username)
{
    clrmous(MouseX , MouseY);
	cleardevice();
	setbkcolor(WHITE);
	puthz(80,30,"欢迎来到车辆管理界面",48,48,RED);
	setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0+30, 639, 39+30);
    setcolor(RED);
    line(600, 0+30, 639, 39+30);
    line(600, 39+30, 639, 0+30);
    puthz(74,128,"管理用户",48,48,BLUE);
    puthz(74,128+96,"管理车辆",48,48,BLUE);
    puthz(74,128+96+96,"车辆车牌",48,48,BLUE);
    setfillstyle(SOLID_FILL,YELLOW);
    bar(271,128,571,128+48);
    bar(271,128+96,571,128+48+96);
    bar(271,128+96+96,571,128+48+96+96);
    bar(16,128+96+96+96,16+192,128+96+96+96+48);
    bar(208+16,128+96+96+96,208+192+16,128+96+96+96+48);
    bar(208+192+16+16,128+96+96+96,208+192+192+16+16,128+96+96+96+48);
    puthz(16+1,128+96+96+96+1,"年审管理",48,48,RED);
    puthz(208+16+1,128+96+96+96+1,"入校管理",48,48,RED);
    puthz(208+192+16+16+1,128+96+96+96+1,"报废管理",48,48,RED);
    setcolor(BLUE);
    user_information_get(information2,username);
    settextstyle(0,0,3);
    outtextxy(271+15,128+15,username);
    outtextxy(271+15,128+96+15,information2->car_name);
    puthz(271+1,128+96+96,information2->city,48,48,BLUE);
	outtextxy(271+15+50,128+96+96+15,information2->car_plate);
    
}

