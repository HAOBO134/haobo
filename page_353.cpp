#include "common.h"
#include "page353.h"

int p353()
{
	char park[5][20];
	int hover_state[12]={0};
	int new_hover[12]={0};
	int button_state[10]={0};
	strcpy(park[0],"韵苑停车场");strcpy(park[1],"紫菘停车场");strcpy(park[2],"图书馆停车场");strcpy(park[3],"校史馆停车场");
	page353_draw();
	
	while(1){
		newmouse(&MouseX , &MouseY , &press);
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				if(mouse_press(16+j*320,130+96*i,16+288+j*320,130+48+96*i)==1)
				{
					for(int k=0;k<10;k++) button_state[k]=0;
					button_state[2*i+j]=1;
				}
				if(button_state[2*i+j]==1)
				{
					setcolor(RED);
					rectangle(16+j*320,130+96*i,16+288+j*320,130+48+96*i);
				}
			}
		}
		newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(270,130+96*2,270+100,130+96*2+48)==1)
		{
			int k=0;
			while(!button_state[k]&&k<4) k++;
			if(!button_state[k]){
					clrmous(MouseX, MouseY);
                    setfillstyle(1, YELLOW);
                    bar(150, 160, 550, 300);
                    setcolor(RED);
                    setlinestyle(0, 0, 3);
                    rectangle(151, 161, 549, 299);
                    puthz(173, 180, "请选择您的停车地点", 24, 24, BLUE);
                    // 延时等待任意键/鼠标关闭提示
                    for (int i = 0; i < 500; i++)
                    {
                       delay(1);
                       if (kbhit()) bioskey(0);
                       newmouse(&MouseX, &MouseY, &press);
                   }
                    page353_draw();
                    continue; 
			}
			
			else{
				park_location(park[k]);
				return 35; 
			}
		}
		
		for(i=0;i<2;i++){
			for(int j=0;j<2;j++){
				    newmouse(&MouseX , &MouseY , &press);
					if(button_state[2*i+j]==0){
					 if(check_mouse_click(16+j*320,130+96*i,16+288+j*320,130+48+96*i)==1)
				       	{
				       	    new_hover[2*i+j]=1;
						}
					 else new_hover[2*i+j]=0;
					 if(new_hover[2*i+j]!=hover_state[2*i+j]){		
					    setcolor(new_hover[2*i+j]?RED:YELLOW);
				        setlinestyle(0,0,3);
				        clrmous(MouseX, MouseY);
					    rectangle(16+j*320,130+96*i,16+288+j*320,130+48+96*i);   	 
				       }
				     hover_state[2*i+j]=new_hover[2*i+j];
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
		
		
		delay(20);
	}
}

void page353_draw()
{
   clrmous(MouseX , MouseY);
   setbkcolor(WHITE);
   cleardevice();
   char park[6][30];
   strcpy(park[0],"韵苑停车场");strcpy(park[1],"紫菘停车场");strcpy(park[2],"图书馆停车场");strcpy(park[3],"校史馆停车场");
   puthz(104,30,"请选择您的停车地点",48,48,RED);
   setfillstyle(SOLID_FILL,YELLOW);
   for(int i=0;i<2;i++){
   	for(int j=0;j<2;j++){
   		bar(16+j*320,130+96*i,16+288+j*320,130+48+96*i);
   		puthz(16+j*320+1,130+96*i+1,park[2*i+j],48,48,BLUE);
	   }
   } 
   bar(270,130+96*2,270+100,130+96*2+48);
   puthz(270+3,130+96*2+1,"确认",48,48,RED);
}

void park_location(char *location)
{
	char path[50];
	char username[20];
	strcpy(username,Get_username());
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%spark.txt",username);
	FILE *fp=fopen(path,"wt");
	if(!fp){printf("fail to open the file");exit(0);}
	fprintf(fp,"Park :%s",location);
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
