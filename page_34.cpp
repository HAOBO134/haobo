#include "page34.h"//报废功能 
#include "page33.h"
#include "common.h"

Information information1[4];


int p34()
{
  int new_hover[8]={0};
  int hover_state[8]={0};
  int button_state[8]={0};
  int k=0;
  int reason;
  char username[30];
  strcpy(username,Get_username());
  information_get(information1); 
  
  page34_draw();
  
  while(1){
		newmouse(&MouseX , &MouseY , &press);	
		for( int i=0;i<2;i++){
		      for( int j=0;j<2;j++) {
		           if(mouse_press(120+i*260,176+j*96,120+i*260+250,176+j*96+48)==1)
						{
							for( k=0;k<8;k++) button_state[k]=0;
							button_state[2*i+j]=1;
						}
					if(button_state[2*i+j]==1)
					  {
					  	setcolor(RED);
					  	rectangle(120+i*260+3,176+j*96+3,120+i*260+250-3,176+j*96+48-3); 
					  }
				}
			}
			
		newmouse(&MouseX , &MouseY , &press);
		if(mouse_press(255,178+48*4,255+100,178+48*5)==1)
		{
		    k=0;
		    while(!button_state[k]) k++;
		    reason=k+1;
		    if(has_pending_request(username)==1&&reason!=0) 
		    {
		    	clrmous(MouseX, MouseY);
                setfillstyle(1, YELLOW);
                bar(150, 160, 550, 300);
                setcolor(BLACK);
                setlinestyle(0, 0, 3);
                rectangle(151, 161, 549, 299);
                puthz(173, 200, "你的申请正在被审核", 24, 30, BLUE);

                // 延时等待任意键/鼠标关闭提示
                for (int i = 0; i < 500; i++)
                {
                    delay(1);
                    if (kbhit()) bioskey(0);
                    newmouse(&MouseX, &MouseY, &press);
                }
                page34_draw();
                for(k=0;k<8;k++) button_state[k]=0;
                reason=0;
                
			}
			
			else if(has_pending_request(username)==2&&reason!=0) 
		    {
		    	clrmous(MouseX, MouseY);
                setfillstyle(1, YELLOW);
                bar(150, 160, 550, 300);
                setcolor(BLACK);
                setlinestyle(0, 0, 3);
                rectangle(151, 161, 549, 299);
                puthz(173, 200, "请确认您的申请", 24, 30, BLUE);

                // 延时等待任意键/鼠标关闭提示
                for (int i = 0; i < 500; i++)
                {
                    delay(1);
                    if (kbhit()) bioskey(0);
                    newmouse(&MouseX, &MouseY, &press);
                }
                page34_draw();
                for(k=0;k<8;k++) button_state[k]=0;
                reason=0;
                
			}
			
			
			else if(reason){
			create_scrap_request(username,reason);
			clrmous(MouseX, MouseY);
            setfillstyle(1, YELLOW);
            bar(150, 160, 550, 300);
            setcolor(BLACK);
            setlinestyle(0, 0, 3);
            rectangle(151, 161, 549, 299);
            puthz(173, 200, "报废申请成功", 24, 30, BLUE);

               // 延时等待任意键/鼠标关闭提示
            for (int i = 0; i < 500; i++)
            {
                delay(1);
                if (kbhit()) bioskey(0);
                newmouse(&MouseX, &MouseY, &press);
            }
            page34_draw();
            for(k=0;k<8;k++) button_state[k]=0;
            reason=0;
            return 3;
			}
		    
		}
		else if(mouse_press(255+100+40,178+48*4,255+100+40+100,178+48*5)==1) return 3;//回到主界面
	    else if(mouse_press(0,24,80,72)==1)   return 31;
		else if(mouse_press(0,120,80,168)==1) return 32;
		else if(mouse_press(0,216,80,264)==1) return 33;
		else if(mouse_press(0,312,80,360)==1) return 35;		
		
		newmouse(&MouseX , &MouseY , &press);
        for( i=0;i<2;i++){
		      for(int j=0;j<2;j++) 
				{
					if(button_state[2*i+j]==0){
					 if(check_mouse_click(120+i*260,176+j*96,120+i*260+250,176+j*96+48)==1)
				       	{
				       	    new_hover[2*i+j]=1;
						}
					 else new_hover[2*i+j]=0;
					 if(new_hover[2*i+j]!=hover_state[2*i+j]){		
					    setcolor(new_hover[2*i+j]?RED:YELLOW);
				        setlinestyle(0,0,3);
				        clrmous(MouseX, MouseY);
					    rectangle(120+i*260+3,176+j*96+3,120+i*260+250-3,176+j*96+48-3);   	 
				       }
				     hover_state[2*i+j]=new_hover[2*i+j];
				   }
				}
			  }
		
		for(i=0;i<2;i++)
		   {
		   	if(check_mouse_click(255+i*140,178+48*4,255+i*140+100,178+48*5)==1) new_hover[4+i]=1;
		   	else new_hover[4+i]=0;
		   	if(new_hover[4+i]!=hover_state[4+i]){		
				setcolor(new_hover[4+i]?RED:YELLOW);
				setlinestyle(0,0,3);
				clrmous(MouseX, MouseY);
				rectangle(255+i*140+3,178+48*4,255+i*140+100-3,178+48*5-3);   	 
				}
			hover_state[4+i]=new_hover[4+i]; 
		   }
		   
	
		
		
        delay(20);
   }
   
}


void page34_draw()
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
	rectangle(0,408-1,80+1,456+1);
	puthz(1,36,"注册",24,24,BLACK);
	puthz(1,132,"上牌",24,24,BLACK);
	puthz(1,228,"年审",24,24,BLACK);
	puthz(1,324,"入校",24,24,BLACK);
	puthz(1,420,"报废",24,24,BLACK);
	puthz(208,10,"自行车报废界面",48,48,BLUE);
	puthz(208,82,"请选择报废理由",48,48,BLUE);
	bar(120,178,120+250,178+48);
	bar(120+250+10,178,120+250+10+250,178+48);
	bar(120,178+48+48,120+250,178+48+48+48);
	bar(120+250+10,178+48+48,120+250+10+250,178+48+48+48);
	bar(255,178+48*4,255+100,178+48*5);
	bar(255+100+40,178+48*4,255+100+40+100,178+48*5);
	puthz(120+5,178,"电动车老旧",48,48,BLUE);
	puthz(120+260+5,178,"电动车损毁",48,48,BLUE);
	puthz(120+5,178+96,"电动车车祸",48,48,BLUE);
	puthz(120+260+5,178+96,"电动车泡水",48,48,BLUE);
	puthz(255+4,178+48*4,"确定",48,48,RED);
	puthz(255+4+140,178+48*4,"取消",48,48,RED);
	
}

void create_scrap_request(char *username,int reason)
{
	char user_name[50];
	strcpy(user_name,username);
	FILE *fp;
	char path[50]="C:\\CODE\\SOURCE\\USER\\";
	strcat(user_name,"scrap");//the username has been changed
	strcat(path,user_name);
	strcat(path,".txt");
	fp=fopen(path,"wt");
	if(!fp) {printf("fail to open the file"); exit(1);}
	fprintf(fp,"Username:%s\n",username);
	fprintf(fp,"Car Name:%s\n",information1->car_name);
	fprintf(fp,"Reason Code: %d\n",reason);
	fprintf(fp,"Status: PENDING\n");
	fclose(fp);
		
}

int has_pending_request(char *username)
{
	char filename[50];
	sprintf(filename,"C:\\CODE\\SOURCE\\USER\\%sscrap.txt",username);
	FILE *fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	
	char line[256];
	int has_pending=0;
	
	while(fgets(line,sizeof(line),fp)){
		if(strstr(line,"PENDING")){
			has_pending=1;
			break;
		}
		if(strstr(line,"REJECTED")||strstr(line,"APPROVE"))
		{
			has_pending=2;
			break;
		}
	} 
	
	fclose(fp);
	return has_pending;
		
}

