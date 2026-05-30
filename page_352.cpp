#include "common.h"
#include "page352.h"

int p352()
{
	int hover_state[12]={0};
	int new_hover[12]={0};
	int button_state[10]={0};
	char location[10][15];
    strcpy(location[0],"南大门");strcpy(location[1],"南二门");strcpy(location[2],"南三门");strcpy(location[3],"东大门");
    strcpy(location[4],"东小门");strcpy(location[5],"东九门");strcpy(location[6],"紫菘门");strcpy(location[7],"湖溪门");
	int location_num;
	page352_draw();
	while(1)
	{
		newmouse(&MouseX , &MouseY , &press);
		for(int i=0;i<2;i++){
			for(int j=0;j<4;j++){
				if(mouse_press(14+j*156,130+96*i,14+144+j*156,130+48+96*i)==1)
				{
					for(int k=0;k<10;k++) button_state[k]=0;
					button_state[4*i+j]=1;
				}
				if(button_state[4*i+j]==1)
				{
					setcolor(RED);
					rectangle(14+j*156,130+96*i,14+144+j*156,130+48+96*i);
				}
			}
		}
		
		newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(270,130+96*2,270+100,130+96*2+48)==1)
		{
			int k=0;
			while(!button_state[k]&&k<8) k++;
			location_num=k;
			if(!button_state[k]){
					clrmous(MouseX, MouseY);
                    setfillstyle(1, YELLOW);
                    bar(150, 160, 550, 300);
                    setcolor(RED);
                    setlinestyle(0, 0, 3);
                    rectangle(151, 161, 549, 299);
                    puthz(173, 180, "请选择您的入校地点", 24, 24, BLUE);
                    // 延时等待任意键/鼠标关闭提示
                    for (int i = 0; i < 500; i++)
                    {
                       delay(1);
                       if (kbhit()) bioskey(0);
                       newmouse(&MouseX, &MouseY, &press);
                   }
                    page352_draw();
                    continue; 
			}
			
			else{
				enter_location(location[k]);
				return 35; 
			}
		}
		
		for(i=0;i<2;i++){
			for(int j=0;j<4;j++){
				    newmouse(&MouseX , &MouseY , &press);
					if(button_state[4*i+j]==0){
					 if(check_mouse_click(14+j*156,130+96*i,14+144+j*156,130+48+96*i)==1)
				       	{
				       	    new_hover[4*i+j]=1;
						}
					 else new_hover[4*i+j]=0;
					 if(new_hover[4*i+j]!=hover_state[4*i+j]){		
					    setcolor(new_hover[4*i+j]?RED:YELLOW);
				        setlinestyle(0,0,3);
				        clrmous(MouseX, MouseY);
					    rectangle(14+j*156,130+96*i,14+144+j*156,130+48+96*i);   	 
				       }
				     hover_state[4*i+j]=new_hover[4*i+j];
				   }
			}
		}	
		
		for(i=0;i<1;i++){
				     newmouse(&MouseX , &MouseY , &press);
					 if(check_mouse_click(270,130+96*2,270+100,130+96*2+48)==1)
				       	{
				       	    new_hover[9]=1;
						}
					 else new_hover[9]=0;
					 if(new_hover[9]!=hover_state[9]){		
					    setcolor(new_hover[9]?RED:YELLOW);
				        setlinestyle(0,0,3);
				        clrmous(MouseX, MouseY);
					    rectangle(270,130+96*2,270+100,130+96*2+48);   	 
				       }
				     hover_state[9]=new_hover[9];
				   
		}
		/**newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(270,130+96*2,270+100,130+96*2+48)==1)
		{
			int k=0;
			while(!button_state[k]&&k<8) k++;
			location_num=k;
			if(!button_state[k]){
					clrmous(MouseX, MouseY);
                    setfillstyle(1, YELLOW);
                    bar(150, 160, 550, 300);
                    setcolor(RED);
                    setlinestyle(0, 0, 3);
                    rectangle(151, 161, 549, 299);
                    puthz(173, 180, "请选择您的入校地点", 24, 24, BLUE);
                    // 延时等待任意键/鼠标关闭提示
                    for (int i = 0; i < 500; i++)
                    {
                       delay(1);
                       if (kbhit()) bioskey(0);
                       newmouse(&MouseX, &MouseY, &press);
                   }
                    page352_draw();
                    continue; 
			}
			
			else{
				enter_location(location[k]);
				getch();
				exit(0);
			}
		}**/
		
		delay(20);
	}
}

void page352_draw()
{
   char location[10][15];
   strcpy(location[0],"南大门");strcpy(location[1],"南二门");strcpy(location[2],"南三门");strcpy(location[3],"东大门");
   strcpy(location[4],"东小门");strcpy(location[5],"东九门");strcpy(location[6],"紫菘门");strcpy(location[7],"湖溪门");
   clrmous(MouseX , MouseY);
   setbkcolor(WHITE);
   cleardevice();
   puthz(104,30,"请选择您的入校地点",48,48,RED);
   setfillstyle(SOLID_FILL,YELLOW);
   for(int i=0;i<2;i++)
   {
   	for(int j=0;j<4;j++)
   	{
   		bar(14+j*156,130+96*i,14+144+j*156,130+48+96*i);
   		puthz(14+j*156+1,130+96*i+1,location[4*i+j],48,48,BLUE);
	   }
   }
   bar(270,130+96*2,270+100,130+96*2+48);
   puthz(270+3,130+96*2+1,"确认",48,48,RED);
}

void enter_location(char *location)
{
	char path[50];
	char username[20];
	strcpy(username,Get_username());
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%slocate.txt",username);
	FILE *fp=fopen(path,"wt");
	if(!fp){printf("fail to open the file");exit(0);}
	fprintf(fp,"location :%s",location);
	fclose(fp);
	clrmous(MouseX, MouseY);
    setfillstyle(1, YELLOW);
	bar(150, 160, 550, 300);
	setcolor(RED);
	setlinestyle(0, 0, 3);
	rectangle(151, 161, 549, 299);
	puthz(173, 180, "您已完成预约申请", 48, 48, BLUE);
	// 延时等待任意键/鼠标关闭提示
	for (int i = 0; i < 500; i++)
	{
	  delay(1);
	  if (kbhit()) bioskey(0);
	  newmouse(&MouseX, &MouseY, &press);
    }
	
}
