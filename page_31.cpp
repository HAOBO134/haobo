#include "common.h"
#include "page31.h"

int p31()
{
	int i=1;
	int input_state=0;
	char car_name[20]="";
	int len;
	char key; 
	
	clrmous(MouseX,MouseY);
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
	rectangle(0,24-1,80+1,72+1);
	puthz(1,36,"注册",24,24,BLACK);
	puthz(1,132,"上牌",24,24,BLACK);
	puthz(1,228,"年审",24,24,BLACK);
	puthz(1,324,"入校",24,24,BLACK);
	puthz(1,420,"报废",24,24,BLACK);
	setcolor(BLUE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	
	FILE *file;
	char path[30]="C:\\CODE\\SOURCE\\USER\\USER.TXT";
    char user_name[30];	
    file=fopen(path,"rt");
    if(file == NULL)
    {
    	printf("无法打开文件");
    	for(i=1;i<500;i++)
    	{
    		delay(1);
		}
		exit(0);
		 
	}
    fscanf(file,"%s",user_name);
    fclose(file);
	puthz(189,5,"车辆注册",48,90,BLUE);
	puthz(160,132,"请输入车辆昵称：",24,45,BLUE);
    outtextxy(540,440,user_name);
    setcolor(YELLOW);
    bar(155,200,180+260+60+100,200+40);
    setfillstyle(SOLID_FILL,BLUE);
    bar(270,348,472,396);
    puthz(300,348,"注册",48,90,BLACK);
    
    while(1)
    	{
    	   while(input_state==0)
    		 {
    		 	newmouse(&MouseX,&MouseY,&press);
    		 	
			    if(mouse_press(155,200,180+260+60+100,200+40)==1)
    		    {
    		  	   setcolor(RED);
    		  	   rectangle(155-1,200-1,180+260+60+100+1,200+40+1);
    		  	   input_state=1;
			    }   //点击输入框 
				else if(mouse_press(270,348,472,396)==1)
				{
					car_zcjsqj(car_name,user_name);
					page_draw(user_name);	
				} 
				//点击注册 
				else if(mouse_press(0,120,80,168)==1) return 32;
				else if(mouse_press(0,216,80,264)==1) return 33;
				else if(mouse_press(0,312,80,360)==1) return 35;	
				else if(mouse_press(0,408,80,456)==1) return 34;
				
				 //切换界面的显示 
				if(mouse_press(270,348,472,396)==2)
				{
					setcolor(RED);
					rectangle(270-1,348-1,472+1,396+1);
				}
				else
				{
					setcolor(BLUE);
					rectangle(270-1,348-1,472+1,396+1);
				}
				
				if(mouse_press(0,120,80,168)==2)
				{
					setcolor(RED);
					rectangle(0+1,120+1,80+1,168+1);
				}
				else
				{
					setcolor(BLUE);
					rectangle(0+1,120+1,80+1,168+1);
				}
				
				if(mouse_press(0,216,80,264)==2)
				{
					setcolor(RED);
					rectangle(0+1,216+1,80+1,264+1);
				}
				else
				{
					setcolor(BLUE);
					rectangle(0+1,216+1,80+1,264+1);
				}
				
				if(mouse_press(0,312,80,360)==2)
				{
					setcolor(RED);
					rectangle(0+1,312+1,80+1,360+1);
				}
				else
				{
					setcolor(BLUE);
					rectangle(0+1,312+1,80+1,360+1);
				}
				
				if(mouse_press(0,408,80,456)==2)
				{
					setcolor(RED);
					rectangle(0+1,408+1,80+1,456+1);
				}
				else
				{
					setcolor(BLUE);
					rectangle(0+1,408+1,80+1,456+1);
				}
				//鼠标经过左侧选择框时变红 
            }
           while(input_state==1)
            {
            	setcolor(BLUE);
            	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            	outtextxy(165,210,car_name);
            	
            	newmouse(&MouseX,&MouseY,&press);
            	
				if(mouse_press(270,348,472,396)==1)
            	  {
            	  	car_zcjsqj(car_name,user_name);
            	  	page_draw(user_name);
            	  	input_state=0; 
				  }
				  
				else if(mouse_press(0,120,80,168)==1)  return 32; 
				else if(mouse_press(0,216,80,264)==1)  return 33;
				else if(mouse_press(0,312,80,360)==1)  return 35;	
				else if(mouse_press(0,408,80,456)==1)  return 34;
				//点击左侧栏目选择
				
				else if((mouse_press(0,0,639,479)==1)&&(mouse_press(155,200,180+260+60+100,200+40)!=1))
				{
					clrmous( MouseX , MouseY );
				    setfillstyle(SOLID_FILL, YELLOW);
				    bar(155,200,180+260+60+100,200+40);
				    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
				    outtextxy(165,210,car_name);
			        input_state=0;
					page_draw(user_name);					
				}
				
            	if(kbhit())
            	{
            		key=bioskey(0);
            		
            		if(key=='\b')
            		{
            			len=strlen(car_name);
            			car_name[len-1]='\0';
            			clrmous(MouseX,MouseY);
            			setfillstyle(SOLID_FILL,YELLOW);
            			bar(155,200,180+260+60+100,200+40);
            			setcolor(RED);
            			setlinestyle(0,0,3);
            			rectangle(155-1,200-1,180+260+60+100+1,200+40+1);
            			newmouse(&MouseX,&MouseY,&press);          			                                                           
					}
					//检验退格键 
					else if(strlen(car_name)>=12)
					{
						clrmous(MouseX,MouseY);
						setfillstyle(1,YELLOW);
						bar(150,160,490,300);
						setcolor(BLACK);
						setlinestyle(0,0,3);
						rectangle(150-1,160-1,490+1,300+1);
						puthz(173,200,"用户长度请勿超过十二",24,30,BLACK);
						
					for ( i=0;i<500;i++)
					{
						delay( 1);
						if ( kbhit( ))
						{
							key = bioskey(0);
						}
						newmouse(&MouseX,&MouseY,&press);
					}
					
					page_draw(user_name);
					settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
					setcolor(BLUE);
					outtextxy(165,210,car_name);
					
					setlinestyle(0,0,3);
					setcolor(RED);
					rectangle(155-1,200-1,180+260+60+100+1,200+40+1);
					break;					
					}
					//检验是否超过12个字母 
					else if((key>='a'&&key<='z')||(key>='A'&&key<='Z')||(key>='0'&&key<='9')||key=='_')
					{
						len=strlen(car_name);
						car_name[len]=key;
						car_name[len+1]='\0';
					}
					//输入了正确的键值 
					else
					{
					
						clrmous( MouseX , MouseY );
					    setfillstyle(1,YELLOW);
				     	bar(150,160,490,300 );
						setcolor(BLACK);
						setlinestyle(0, 0, 3);
						rectangle(150+1,160+1,490-1,300-1);
						puthz(173, 200, "请输入大小写字母、数",24,30,BLACK);
						puthz(248, 235, "字或下划线",24,30,BLACK);
						for ( i=0;i<500;i++)
						{
							delay( 1);
							if ( kbhit( ))
							{
								key = bioskey(0);
							}
							newmouse(&MouseX,&MouseY,&press);
						}
						page_draw(user_name);
						setcolor(BLUE);
						outtextxy(165,210,car_name);
					
						setcolor(RED);
						setlinestyle(0, 0, 3);
	               		rectangle(155-1,200-1,180+260+60+100+1,200+40+1);
					}
					 // 输入了其他键值
				}   
            	
				
        
            		
			}
    	}
    
    
    
	
	return 9;	
	
	
	
 } 
 void page_draw(char *user_name)
 {
 	clrmous(MouseX,MouseY);
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
	rectangle(0,24-1,80+1,72+1);
	puthz(1,36,"注册",24,24,BLACK);
	puthz(1,132,"上牌",24,24,BLACK);
	puthz(1,228,"变更",24,24,BLACK);
	puthz(1,324,"入校",24,24,BLACK);
	puthz(1,420,"报废",24,24,BLACK);
	setcolor(BLUE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	puthz(189,5,"车辆注册",48,90,BLUE);
	puthz(160,132,"请输入车辆昵称：",24,45,BLUE);
    outtextxy(540,440,user_name);
    setcolor(YELLOW);
    bar(155,200,180+260+60+100,200+40);
    setfillstyle(SOLID_FILL,BLUE);
    bar(270,348,472,396);
    puthz(300,348,"注册",48,90,BLACK);
 }
 void car_zcjsqj(char *car_name,char *user_name)
 {
 	FILE *file;
 	int i=1;
 	char path[30]="C:\\CODE\\SOURCE\\USER\\";
 	char suffix[20]=".txt";
 	char buffer[30];
 	
 	int line_count=0;
 	int text_has;
 	strcat(path,user_name);
 	strcat(path,suffix);
 	if(strlen(car_name)==0)
 	 {
 		clrmous(MouseX,MouseY);
 		setfillstyle(1,YELLOW);
 		bar(150,160,490,300);
 		setcolor(BLACK);
		setlinestyle(0,0,3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(218,200,"车辆名不能为空",24,30,BLUE);
		for(i=1;i<500;i++)
		   {
		   	 newmouse(&MouseX,&MouseY,&press);
		   	 delay(1);
			} 
		fclose(file);
		return;
	 }
 	
 
 	
 	file=fopen(path,"at+");
 	
 	if(file==NULL)
 	{
 	    clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(203, 200, "无法打开文件",24,30,BLACK);
		return ;
	 }
    while(fgets(buffer,sizeof(buffer),file)!=NULL) line_count++;
    if(line_count>=2) 
    {
    	clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLUE);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(203, 200, "您已注册车辆",24,30,BLUE);
		car_name[0]='\0';
        for(i=1;i<500;i++)
		   {
		   	 newmouse(&MouseX,&MouseY,&press);
		   	 delay(1);
			} 
		fclose(file);		
		return ;
	}
    
	fprintf(file,"\n%s",car_name);
    clrmous( MouseX , MouseY );
	setfillstyle(1,YELLOW);
	bar(150,160,490,300 );
	setcolor(BLUE);
	setlinestyle(0, 0, 3);
	rectangle(150+1,160+1,490-1,300-1);
	puthz(263, 200, "注册成功",24,30,BLUE);
	for ( i=1;i<500;i++)
	{
		newmouse(&MouseX,&MouseY,&press);
		delay( 1);
	}
	fclose(file);//关闭文件
	return;
 
 }
 
