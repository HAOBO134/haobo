#include "common.h"
#include "page32.h"

#define FILE_PATH "C:\\CODE\\SOURCE\\USER\\USER.txt"
//上牌功能页 

Button city[3];
char cityprefix[10];
int  state=0;
int  generated=0;
int  repeated=0;
int  current_page=1;
int  last_page=1;
char Plates[10][10];
char NewPlate[10];
 


int p32()
{
	FILE* fp;//jian cha na ge yong hu zai deng lu 
	FILE* fp1;//jian cha yong hu you mei you zhu ce che liang
    FILE* fp2;//yong lai ji lu chepai hao
    int hover_state[9]={0};
    int new_hover[9]={0};
	char buffer[20];
	char username[20];
	char path[40]="C:\\CODE\\SOURCE\\USER\\";
	
	fp=fopen(FILE_PATH,"rt");
	fgets(username,sizeof(username),fp);
	fclose(fp);
	strcat(path,username);
	strcat(path,".txt");
    fp1=fopen(path,"rt");
	for(int i=0;i<2;i++)
	{
		buffer[0]='\0'; 
		fgets(buffer,sizeof(buffer),fp1);
	}
	if(strlen(buffer)==0) 
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(203, 200, "您未注册车辆",24,30,BLACK);
        for(i=1;i<500;i++)
		   {
		   	 newmouse(&MouseX,&MouseY,&press);
		   	 delay(1);
			} 
		fclose(fp1);
		return 3; 
	}//检查是否有电动车 
	
    fp=fopen(path,"rt");
    for(i=0;i<4;i++)
       {
       	buffer[0]='\0';
       	fgets(buffer,sizeof(buffer),fp);
	   }
	if(strlen(buffer)!=0)
	 {
	 	clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490+50,300 );
		setcolor(RED);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1+50,300-1);
		puthz(203, 200, "您的车辆已经完成上牌",24,30,BLUE);
        for(i=1;i<500;i++)
		   {
		   	 newmouse(&MouseX,&MouseY,&press);
		   	 delay(1);
			} 
		fclose(fp);
		fclose(fp1);
		return 3; 
	 }//检查是否已有车牌号 
	 
	page3_draw();
	rectangle(0,120-1,80+1,168+1);
	  if(state==0)
	{
	  button_init();	
	  for(int i=0;i<3;i++) draw_button(city+i);
	  while(strlen(cityprefix)==0)
	  {
	  newmouse(&MouseX , &MouseY , &press);
	  if(press==1&&strlen(cityprefix)==0)
	  {
	   if(check_mouse_click(110,250,100+116,250+58)) strcpy(cityprefix,"京");
	   if(check_mouse_click(302,250,302+116,250+58)) strcpy(cityprefix,"鄂");
	   if(check_mouse_click(504,250,504+116,250+58)) strcpy(cityprefix,"沪");	
	  }
	  if(strlen(cityprefix)!=0) {
          fp2=fopen(path,"at+");
		  fprintf(fp2,"\n城市：%s",cityprefix);
		  fclose(fp2);	  	
		  state=1;
	  }
	  delay(20);
    }
    }
    
	 if(state==1)
	{  
	   setfillstyle(SOLID_FILL,WHITE);
	   bar(110-4,250-4,100+116+20,250+58+5);
	   bar(302-5,250-5,302+116+5,250+58+5);
	   bar(504-5,250-5,504+116+5,250+58+5);
	   srand((unsigned int)time(NULL));
	   clrmous(MouseX, MouseY);
       page32_draw();
       car_plate_generate();
       settextstyle(0,0,3);
       for(int i=0;i<3;i++){
		for(int j=0;j<3;j++) outtextxy(130+i*170+4,176+j*96+12,Plates[i*3+j]);
		} 
	   while(1)
	   {
	   	  newmouse(&MouseX , &MouseY , &press);
			for(int i=0;i<3;i++){
		      for(int j=0;j<3;j++) 
				{
					 if(check_mouse_click(130+i*170,176+j*96,130+i*170+120,176+j*96+48)==1)
				       	{
				       	    new_hover[3*i+j]=1;
						}
					 else new_hover[3*i+j]=0;
					 if(new_hover[3*i+j]!=hover_state[3*i+j]){		
					    setcolor(new_hover[3*i+j]?RED:YELLOW);
				        setlinestyle(0,0,3);
				        clrmous(MouseX, MouseY);
					    rectangle(130+i*170-3,176+j*96-3,130+i*170+120+3,176+j*96+48+3);   	 
				       }
				     hover_state[3*i+j]=new_hover[3*i+j];  
				}
			  }
	   	    if(press==1)
			 {
				 for(int i=0;i<3;i++){
		          for(int j=0;j<3;j++) 
				  {
				  if(check_mouse_click(130+i*170,176+j*96,130+i*170+120,176+j*96+48)==1) 
				    {
				    	fp2=fopen(path,"at+");
				        fprintf(fp2,"\n车牌号：%s",Plates[i*3+j]);
						fclose(fp2);
						clrmous( MouseX , MouseY );
						setfillstyle(1,YELLOW);
						bar(150,160,490,300 );
						setcolor(BLACK);
						setlinestyle(0, 0, 3);
						rectangle(150+1,160+1,490-1,300-1);
						puthz(203, 200, "成功选择车牌号",24,30,BLACK);
						
        				for(i=1;i<500;i++)
		 				  {
		   	 				newmouse(&MouseX,&MouseY,&press);
		   					delay(1);
							}
						fclose(fp1);
						fclose(fp);
						return 3; 
				       //xuan ze che pai hou yao cun ru	
					}
				  }
		        } 
			     if(check_mouse_click(288,424,288+144,424+48)==1) current_page++;	
			 } 	
		    if(current_page-last_page==1)
			{
			  update_Plates();	
			}// diao yong bian huan ye mian han shu
			last_page=current_page;	  	
	  	    delay(20);
	}	
	
  }
}

void page3_draw()
{
	clrmous( MouseX , MouseY );
	cleardevice();
	setbkcolor(WHITE);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	setlinestyle(0,0,3);
	bar(0,24,80,72);
	bar(0,120,80,168);
	bar(0,216,80,264);
	bar(0,312,80,360);
	bar(0,408,80,456);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(100,0,110,480);
	setcolor(RED);
	puthz(1,36,"注册",24,24,BLACK);
	puthz(1,132,"上牌",24,24,BLACK);
	puthz(1,228,"年审",24,24,BLACK);
	puthz(1,324,"入校",24,24,BLACK);
	puthz(1,420,"报废",24,24,BLACK);
	puthz(192,10,"自行车上牌系统",48,48,BLUE);
}
void page32_draw()
{
	setcolor(RED);
	puthz(169,109,"请选择您的车牌号",48,48,RED);
	setfillstyle(SOLID_FILL,YELLOW);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			bar(130+i*170,176+j*96,130+i*170+120,176+j*96+48);
		}
	 } 
    setfillstyle(SOLID_FILL,BLUE);
	bar(288,424,288+144,424+48);
	puthz(288+1,424,"换一页",48,48,RED);	
}
void button_init()
{
	city[0].x=110;
	city[0].y=250;
	strcpy(city[0].text,"北京");
	city[0].width=116;
	city[0].height=58;
	
	city[1].x=302;
	city[1].y=250;
	strcpy(city[1].text,"武汉");
	city[1].width=116;
	city[1].height=58; 
	
	city[2].x=504;
	city[2].y=250;
	strcpy(city[2].text,"上海");
	city[2].width=116;
	city[2].height=58;
}
void draw_button(Button *button)
{   
    setcolor(RED);
    rectangle(button->x-1,button->y-1,button->x+button->width+1,button->y+button->height+1);
	setfillstyle(SOLID_FILL,GREEN);
	bar(button->x,button->y,button->x+button->width,button->y+button->height);
	setcolor(BLUE);
	puthz(button->x+3,button->y+3,button->text,48,48,BLUE);
	
}
void car_plate_generate()
{
	generated=0;
	NewPlate[0]='\0';
	for(int k=0;k<9;k++)
	{
	  Plates[generated][0]='\0';	
	}
	
	while(generated<9){
	
		for(int j=0;j<5;j++)
		 {
		 	int choice=rand()%36;
		 	if(choice<10) NewPlate[j]='0'+choice;  
			else NewPlate[j]='A'+(choice-10);	
		 }
		 NewPlate[5]='\0';
		 
		for(int i=0;i<generated;i++)
		{
			if(strcmp(NewPlate,Plates[i])==0) repeated=1;	
		} 
		if(!repeated)
		{
			strcpy(Plates[generated],NewPlate);
			generated++;
		}	
	}
}		
void update_Plates()
{
	car_plate_generate();
	setfillstyle(SOLID_FILL,YELLOW);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			bar(130+i*170,176+j*96,130+i*170+120,176+j*96+48);
			setcolor(RED); 
			outtextxy(130+i*170+4,176+j*96+12,Plates[i*3+j]);
		}
	 } 

}

