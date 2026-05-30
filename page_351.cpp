#include "common.h"
#include "page351.h"

int p351()
{
   int time_state=0;
   int hover_state[33];
   int new_hover[33];
   int time_month;
   int time_day;
   int time_hour;
   int l=0;//是否选择时间 
   page351_draw_1();
   while(1){
   
   if(time_state==0)// month
   {
	  newmouse(&MouseX , &MouseY , &press);	 
	  for(int i=0;i<3;i++){
	  	for(int j=0;j<4;j++){
	  		if(mouse_press(14+j*156,120+i*120,14+144+j*156,120+48+i*120)==1)
	  		{
	  		    time_state=1;
		        page351_draw_2();
				time_month=4*i+j+1;
				continue;	
			}
		  }
	   }
	  
	  for( i=0;i<3;i++){
	  	for(int j=0;j<4;j++)
	  	{
	  		newmouse(&MouseX , &MouseY , &press);
	  		if(check_mouse_click(14+j*156,120+i*120,14+144+j*156,120+48+i*120)==1)
			{
				new_hover[4*i+j]=1;
			}
		    else new_hover[4*i+j]=0;
		    if(new_hover[4*i+j]!=hover_state[4*i+j]){		
		       setcolor(new_hover[4*i+j]?RED:YELLOW);
		       setlinestyle(0,0,3);
		       clrmous(MouseX, MouseY);
		       rectangle(14+j*156,120+i*120,14+144+j*156,120+48+i*120);   	 
		      }
		    hover_state[4*i+j]=new_hover[4*i+j];
		}  
   }
		 
   } 
   
   else if(time_state==1)// day
   {
   	  newmouse(&MouseX , &MouseY , &press); 
	  for( int i=0;i<5;i++){
	  	for(int j=0;j<6;j++){
	  		if(mouse_press(30+102*j,180+48*i,102+102*j,204+48*i)==1)
	  		{
				time_day=6*i+j+1;
				if(time_month==2&&(time_day==29||time_day==30))
				{
					clrmous(MouseX, MouseY);
                    setfillstyle(1, YELLOW);
                    bar(150, 160, 550, 300);
                    setcolor(RED);
                    setlinestyle(0, 0, 3);
                    rectangle(151, 161, 549, 299);
                    puthz(173, 180, "该日期不合法", 48, 48, BLUE);
                    puthz(173,180+55,"请重新选择",48,48,BLUE);
                    // 延时等待任意键/鼠标关闭提示
                    for (int i = 0; i < 500; i++)
                    {
                       delay(1);
                       if (kbhit()) bioskey(0);
                       newmouse(&MouseX, &MouseY, &press);
                   }
                    page351_draw_2();
                    continue;
				}
				page351_draw_3();
				time_state=2;
					
			}
		  }
	   }
	   
	   for( i=0;i<5;i++){
	  	for(int  j=0;j<6;j++)
	  	{
	  		newmouse(&MouseX , &MouseY , &press);
	  		if(check_mouse_click(30+102*j,180+48*i,102+102*j,204+48*i)==1)
			{
				new_hover[6*i+j]=1;
			}
		    else new_hover[6*i+j]=0;
		    if(new_hover[6*i+j]!=hover_state[6*i+j]){		
		       setcolor(new_hover[6*i+j]?RED:YELLOW);
		       setlinestyle(0,0,3);
		       clrmous(MouseX, MouseY);
		       rectangle(30+102*j,180+48*i,102+102*j,204+48*i);   	 
		      }
		    hover_state[6*i+j]=new_hover[6*i+j];
		}
	  } 
   }
  
   else if(time_state==2)// hour 
   {
   	 newmouse(&MouseX , &MouseY , &press);
	 for(int i=0;i<2;i++){
	 	for(int j=0;j<2;j++){
	 		if(mouse_press(50+j*300,140+i*96,290+j*300,188+i*96)==1)
	 		{
	 			time_hour=2*i+j+1;
	 			time_display(time_month,time_day,time_hour);
	 			l=1;
			 }
	  if((mouse_press(224,140+96*3-25,224+192,140+96*3+48-25)==1)&&(l==1))
	  {
		time_submmit(time_month,time_day,time_hour);
	  	return 35;
	  }
	  else if((mouse_press(224,140+96*3-25,224+192,140+96*3+48-25)==1)&&(l==0))
	  {
	  	clrmous(MouseX, MouseY);
        setfillstyle(1, YELLOW);
	    bar(150, 160, 550, 300);
	    setcolor(RED);
	    setlinestyle(0, 0, 3);
	    rectangle(151, 161, 549, 299);
	    puthz(173, 180, "请选择入校时段", 48, 48, BLUE);
	    // 延时等待任意键/鼠标关闭提示
	    for (int i = 0; i < 500; i++)
	    {
	      delay(1);
	      if (kbhit()) bioskey(0);
	      newmouse(&MouseX, &MouseY, &press);
         }
        page351_draw_3();
	  }
		 }
	 }
	 /**delay(20);
	 newmouse(&MouseX , &MouseY , &press);
	 if((mouse_press(224,140+96*3-25,224+192,140+96*3+48-25)==1)&&(l==1))
	  {
	  	puthz(250,250,"我爱你",48,48,BLUE);
		time_submmit(time_month,time_day,time_hour);
	  	return 35;
	  }
	  else if((mouse_press(224,140+96*3-25,224+192,140+96*3+48-25)==1)&&(l==0))
	  {
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
        page351_draw_3();
	  }*/
	 for(i=0;i<2;i++){
	 	for(int j=0;j<2;j++){
	 		newmouse(&MouseX , &MouseY , &press);
	  		if(check_mouse_click(50+j*300,140+i*96,290+j*300,188+i*96)==1)
			{
				new_hover[2*i+j]=1;
			}
		    else new_hover[2*i+j]=0;
		    if(new_hover[2*i+j]!=hover_state[2*i+j]){		
		       setcolor(new_hover[2*i+j]?RED:YELLOW);
		       setlinestyle(0,0,3);
		       clrmous(MouseX, MouseY);
		       rectangle(50+j*300,140+i*96,290+j*300,188+i*96);   	 
		      }
		    hover_state[2*i+j]=new_hover[2*i+j];
		 }
	 }
	 
		  
   }
  
  delay(20);
  }
}

void page351_draw_1()// month
{
   char month[14][15];
   strcpy(month[0],"一月份");
   strcpy(month[1],"二月份");
   strcpy(month[2],"三月份");
   strcpy(month[3],"四月份");
   strcpy(month[4],"五月份");
   strcpy(month[5],"六月份");
   strcpy(month[6],"七月份");
   strcpy(month[7],"八月份");
   strcpy(month[8],"九月份");
   strcpy(month[9],"十月份");
   strcpy(month[10],"十一月");
   strcpy(month[11],"十二月");
   clrmous(MouseX , MouseY);
   setbkcolor(WHITE);
   cleardevice();
   puthz(104,30,"请选择您的入校时间",48,48,RED);
   setfillstyle(SOLID_FILL,YELLOW);
   for(int i=0;i<3;i++) {
   	for(int j=0;j<4;j++) {
   		bar(14+j*156,120+i*120,14+144+j*156,120+48+i*120);
   		puthz(14+j*156+1,120+i*120+1,month[4*i+j],48,48,BLUE);
	   }
   }
   
   	
}
void page351_draw_2()// day
{  
   char day[32][15];
   strcpy(day[0],"零一号");strcpy(day[1],"零二号");strcpy(day[2],"零三号");strcpy(day[3],"零四号");strcpy(day[4],"零五号");
   strcpy(day[5],"零六号");strcpy(day[6],"零七号");strcpy(day[7],"零八号");strcpy(day[8],"零九号");strcpy(day[9],"零十号");
   strcpy(day[10],"十一号");strcpy(day[11],"十二号");strcpy(day[12],"十三号");strcpy(day[13],"十四号");strcpy(day[14],"十五号");
   strcpy(day[15],"十六号");strcpy(day[16],"十七号");strcpy(day[17],"十八号");strcpy(day[18],"十九号");strcpy(day[19],"二十号");
   strcpy(day[20],"二一号");strcpy(day[21],"二二号");strcpy(day[22],"二三号");strcpy(day[23],"二四号");strcpy(day[24],"二五号");
   strcpy(day[25],"二六号");strcpy(day[26],"二七号");strcpy(day[27],"二八号");strcpy(day[28],"二九号");strcpy(day[29],"三十号");
   clrmous(MouseX , MouseY);
   setbkcolor(WHITE);
   cleardevice();
   puthz(104,30,"请选择您的入校时间",48,48,RED);
   puthz(212,30+40+50,"请选择您的入校天数",24,24,BLUE);
   setfillstyle(SOLID_FILL,YELLOW);
   for(int i=0;i<5;i++){
   	for(int j=0;j<6;j++){
   		bar(30+102*j,180+48*i,102+102*j,204+48*i);
   		puthz(30+102*j,180+48*i,day[6*i+j],24,24,BLUE);
	   }
   }
}

void page351_draw_3()// hour
{
   char time[6][30];
   strcpy(time[0],"七点至九点");strcpy(time[1],"九点至十点");strcpy(time[2],"两点至四点");strcpy(time[3],"四点至六点");
   clrmous(MouseX , MouseY);
   setbkcolor(WHITE);
   cleardevice();
   setfillstyle(SOLID_FILL,YELLOW);
   puthz(104,30,"请选择您的入校时间",48,48,RED);
   puthz(212,30+40+25,"请选择您的入校时段",24,24,BLUE);
   for(int i=0;i<2;i++){
   	for(int j=0;j<2;j++)
   	{
   		bar(50+j*300,140+i*96,290+j*300,188+i*96);
   		puthz(50+j*300+1,140+i*96+1,time[i*2+j],48,48,RED);
	   }
   }
   puthz(26,140+96*2+12,"您的入校时间",24,24,BLUE);
   bar(26+144+5,140+96*2,26+288+5+300,140+96*2+48);
   bar(224,140+96*3-25,224+192,140+96*3+48-25);
   puthz(224+1,140+96*3+1-25,"确定申请",48,48,RED);
}
void time_display(int month,int day,int hour)
{
	setfillstyle(SOLID_FILL,YELLOW);
	bar(26+144+5,140+96*2,26+288+5+300,140+96*2+48);
	char time_hour[30];
	char time_month[20];
	char time_day[20];
	char buffer[50];
	switch(hour)
	{
		case 1:
			strcpy(time_hour,"七点至九点");
			break;
		case 2:
			strcpy(time_hour,"九点至十点");
			break;
		case 3:
			strcpy(time_hour,"两点至四点");
			break;
		case 4:
			strcpy(time_hour,"四点至六点");
			break;
	}
	settextstyle(0,0,3);
	setcolor(BLUE);
	sprintf(time_month,"%d",month);
	sprintf(time_day,"%d",day);
	sprintf(buffer,"日%s",time_hour);
	puthz(26+288+5+5-144,140+96*2+12,"二零二六年",24,24,BLUE);
	outtextxy(26+288+5+5+120+10-144,140+96*2+12+2,time_month);
	puthz(26+288+5+5+120+10+48+1-144,140+96*2+12,"月",24,24,BLUE);
	outtextxy(26+288+5+5+120+10+48+24+10-144,140+96*2+12+2,time_day);
	puthz(26+288+5+5+120+10+48+24+10+48+1-144,140+96*2+12,buffer,24,24,BLUE);
}

void time_submmit(int month,int day,int hour)
{
	char username[20];
	strcpy(username,Get_username());
	char path[50];
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%stime.txt",username);
	char time[100];
	char time_hour[30];
	switch(hour)
	{
		case 1:
			strcpy(time_hour,"七点至九点");
			break;
		case 2:
			strcpy(time_hour,"九点至十点");
			break;
		case 3:
			strcpy(time_hour,"两点至四点");
			break;
		case 4:
			strcpy(time_hour,"四点至六点");
			break;
	}
	sprintf(time,"二零二六年%d月%d日%s",month,day,time_hour);
	FILE *fp=fopen(path,"wt");
	if(!fp) {printf("fail to open the file");}
	fprintf(fp,"Time :%s\n",time);
	fprintf(fp,"Status :PENDING");
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

