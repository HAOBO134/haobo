#include "common.h"
#include "page32.h"
#include "stdlib.h"
#include "page33.h"
#include "input.h"

#define FILE_PATH "C:\\CODE\\SOURCE\\USER\\USER.txt"
#define PATH      "C:\\CODE\\SOURCE\\USER\\"


Information information[3];
int page_state=0;
int i;
int judge;
char user_name[20];


int p33()
{
  int hover_state[10]={0};
  int new_hover[10]={0};
  int change_state=0;
  draw();//hua chu hua mian
  while(1)
  {
  	if(!page_state)
  	   {
  	   	newmouse(&MouseX,&MouseY,&press);
  	   	
			 for(int i=0;i<4;i++)
  	   	{
  	   		if(check_mouse_click(402-100,210-20-20+58*i,502+100,258-20-20+58*i)) new_hover[i]=1;
  	   		else new_hover[i]=0;
  	   		if(new_hover[i]!=hover_state[i])
				 {
				 	setcolor(new_hover[i]?RED:YELLOW);
				    setlinestyle(0,0,3);
				    clrmous(MouseX, MouseY);
					rectangle(402-100,210-20-20+58*i,502+100,258-20-20+58*i);
				 }		
		    hover_state[i]=new_hover[i];
		}
  	   	for(i=0;i<2;i++)
			 {
			 	if(check_mouse_click(271-100+i*264,420,375-100+i*264,420+48)) new_hover[4+i]=1;
			 	else new_hover[4+i]=0;
			 	if(new_hover[4+i]!=hover_state[4+i])
				 {
				 	setcolor(new_hover[4+i]?RED:YELLOW);
				    setlinestyle(0,0,3);
				    clrmous(MouseX, MouseY);
					rectangle(271-100+i*264,420,375-100+i*264,420+48);
				 }  
			 	 hover_state[4+i]=new_hover[4+i];  	     
			 }  
  	   	 
		if(mouse_press(271-100,420,375-100,420+48)==1)
		 {
		 	 change_state=has_pending(Get_username());
		 	 if(!change_state){
		 	 	review_handle();
		 	 	return 3;
			  } 
			 else if(change_state==1)
			 {
			 	page33_draw_N("正在审核您的年审");
			 	return 3;
			 }
			 else if(change_state==2)
			 {
			 	page33_draw_N("请确认您的年审");
			 	return 3;
			 }
			 
		 } 	   	
	    else if(mouse_press(435,420,539,420+48)==1) return 3;
	    else if(mouse_press(0,24,80,72)==1) return 31;
		else if(mouse_press(0,24+96,80,72+96)==1) return 32;
		else if(mouse_press(0,24+96*3,80,72+96*3)==1) return 35;
		else if(mouse_press(0,24+96*4,80,72+96*4)==1) return 34;
	    
	   }
	   

    delay(20);
	} 
  	return 3;
  }
  
  
void review_handle(){
	char username[50];
	strcpy(username,Get_username());
	FILE *fp;
	char path[50]="C:\\CODE\\SOURCE\\USER\\";
	sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sre.txt",username);
	fp=fopen(path,"wt");
	if(!fp) {printf("fail to open the file"); exit(1);}
	fprintf(fp,"Status: PENDING\n");
	fclose(fp);
	
}

int has_pending(char *username)
{
	char filename[50];
	sprintf(filename,"C:\\CODE\\SOURCE\\USER\\%sre.txt",username);
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


void information_get(Information *information)
{
	if (information == NULL) {
        printf("错误：结构体指针为空！\n");
        return;
    }
	FILE *fp;
	char buffer[50];
	char path[100];
	fp=fopen(FILE_PATH,"rt");
	if (fp == NULL) {
        printf("错误：无法打开文件\n");
        return;
    }
	fgets(user_name,sizeof(user_name),fp);
	fclose(fp);
	strcpy(path,PATH);
	strcat(path,user_name);
	strcat(path,".txt");
	fp=fopen(path,"rt");
	if (fp == NULL) {
        printf("错误：无法打开文件\n");
        return;
    }
	
	for(int i=0;i<4;i++)
	{
		fgets(buffer,sizeof(buffer),fp);
		switch(i){
			case 0: strcpy(information->password,buffer);
			        trim_newline(information->password);
			        buffer[0]='\0';
			        break;
			case 1: strcpy(information->car_name,buffer);
			         trim_newline(information->car_name);
	                buffer[0]='\0';	
					break;	
			case 2: strcpy(information->city,buffer);
			        trim_newline(information->city);
					buffer[0]='\0';
			        break;
			case 3: strcpy(information->car_plate,buffer);
                    trim_newline(information->car_plate);
					buffer[0]='\0';
					break;    			
		}
	}
	fclose(fp);
}

void trim_newline(char *s)
{
	if(!s) return;
	size_t len=strlen(s);
	while(len>0&&(s[len-1]=='\n'||s[len-1]=='\r'))
	{
		s[len-1]='\0';
		len--;
	}
}
void draw()
{
  page3_draw();
  setfillstyle(SOLID_FILL,WHITE);
  bar(180,0,550,60);
  puthz(192,10,"自行车年审系统",48,48,BLUE);
  setcolor(RED);
  setfillstyle(SOLID_FILL,YELLOW);
  puthz(145,109-20,"请核对您的个人信息",48,48,RED);
  puthz(210-100,210-20-20,"密码名：",48,48,BLUE);
  puthz(210-100,268-20-20,"车辆名：",48,48,BLUE);
  puthz(210-100,326-20-20,"城市名：",48,48,BLUE);
  puthz(210-100,384-20-20,"车牌号：",48,48,BLUE);
  bar(402-100,210-20-20,502+100,258-20-20);
  bar(402-100,210+58-20-20,502+100,210+48+58-20-20);
  bar(402-100,210+58+58-20-20,502+100,210+58+58+48-20-20);
  bar(402-100,210+58+58+58-20-20,502+100,210+58+58+58+48-20-20);
  setfillstyle(SOLID_FILL,GREEN);
  bar(271-100,420,375-100,420+48);
  bar(435,420,539,420+48);
  puthz(272-100,421,"确认",48,48,RED);
  puthz(436,421,"取消",48,48,RED);	 
  information_get(information);
  setcolor(RED);
  settextstyle(0,0,3);
  outtextxy(402-100+15,210-20-20+15,information->password);
  outtextxy(402-100+15,210+58-20-20+15,information->car_name);
  puthz(402-100,210+58+58-20-20,information->city+6,48,48,RED);
  outtextxy(402-100+15,210+58+58+58-20-20+15,information->car_plate+8);	
}
void page33_draw_N(char *wenben){
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
   	 
 /**void change_draw(int judge)
    {
    	clrmous(MouseX,MouseY);
		setbkcolor(WHITE);
		setfillstyle(1,GREEN);
    	bar(100+40,117-24,100+540-30,117+246+30);
    	setfillstyle(1,YELLOW);
    	for(int i=0;i<3;i++) bar(296,117+6+72*i,296+300,117+48+72*i);
    	bar(170,291+12+12+12,270+104-100,291+48+36);
    	bar(470,291+12+12+12,370+104+100,291+48+36);
    	if(judge==0)//修改密码 
    	  {
    	  	puthz(100+48,117+6,"原密码",48,48,BLUE);
    	  	puthz(100+48,117+6+72,"新密码",48,48,BLUE);
    	  	puthz(100+48,117+6+144,"新密码",48,48,BLUE);
		  }
		else if(judge==1)
		{
			puthz(100+48,117+6,"原车名",48,48,BLUE);
    	  	puthz(100+48,117+6+72,"新车名",48,48,BLUE);
    	  	puthz(100+48,117+6+144,"新车名",48,48,BLUE);
		}
		puthz(170+1,291+1+12+12+12,"取消",48,48,BLUE);
		puthz(470+1,291+1+12+12+12,"确认",48,48,BLUE);
	}
**/
/**static void change_handle()
{
    change_state = 0;
    for (int k = 0; k < 3; ++k) output[k][0] = '\0';
    int focused = -1; // 0-based 行索引

    while (1) {
        newmouse(&MouseX, &MouseY, &press);

        // 取消按钮
        if (mouse_press(170, 291 + 12 + 12 + 12, 270 + 104 - 100, 291 + 48 + 36) == 1) {
            change_state = 0;
            return;
        }
        // 确认按钮
        if (mouse_press(470, 291 + 12 + 12 + 12, 370 + 104 + 100, 291 + 48 + 36) == 1) {
            change_submit();
            draw();
            change_draw(judge);
            delay(20);
            
        }

        int did_enter_input = 0;  // 用 int 代替 bool
        for (int j = 0; j < 3; ++j) {
            int x1 = 296;
            int y1 = 117 + 6 + 72 * j;
            int x2 = 296 + 300;
            int y2 = 117 + 48 + 72 * j;

            if (mouse_press(x1, y1, x2, y2) == 1) {
                focused = j;
                change_state = j + 1;
                change_draw(judge);

                clrmous(MouseX, MouseY);
                setcolor(RED);
                setlinestyle(0, 0, 3);
                rectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1);

                if (input_text(x1 + 1, y1 + 1, output[focused], redraw_for_input)) {
                    change_state = 0;
                    focused = -1;
                    change_draw(judge);
                } else {
                    change_state = 0;
                    focused = -1;
                    change_draw(judge);
                }

                did_enter_input = 1;  // 用1表示true
                break;
            }
        }

        if (!did_enter_input) {
            delay(20);
        }
    }
}
/**static void change_handle()
{
    // 保持原语义：change_state 为 0 表示未编辑，1/2/3 表示正在编辑第 1/2/3 行
    change_state = 0;
    for (int k = 0; k < 3; ++k) output[k][0] = '\0';
    int focused = -1; // 0-based 行索引，-1 表示没有焦点

    // 主循环：等待用户点击三行中的一行，或取消/确认按钮
    while (1) {
        newmouse(&MouseX, &MouseY, &press);

        // 取消按钮（左）检查
        if (mouse_press(170, 291 + 12 + 12 + 12, 270 + 104 - 100, 291 + 48 + 36) == 1) {
            change_state = 0;
            return;
        }

        // 确认按钮（右）检查
        if (mouse_press(470, 291 + 12 + 12 + 12, 370 + 104 + 100, 291 + 48 + 36) == 1) {
            change_submit();
            draw();
            change_draw(judge);
            // 继续等待下一次操作
            delay(20);
            continue;
        }

        // 检查三行输入框的点击
        bool did_enter_input = false;
        for (int j = 0; j < 3; ++j) {
            int x1 = 296;
            int y1 = 117 + 6 + 72 * j;
            int x2 = 296 + 300;
            int y2 = 117 + 48 + 72 * j;

            if (mouse_press(x1, y1, x2, y2) == 1) {
                // 进入编辑该行
                focused = j;
                change_state = j + 1; // 保留 1-based 的 change_state 语义
                // 先重绘对话框，清除旧的红框或干扰痕迹
                change_draw(judge);

                // 绘制红色选中框作为视觉反馈
                clrmous(MouseX, MouseY);
                setcolor(RED);
                setlinestyle(0, 0, 3);
                rectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1);

                // 调用阻塞式输入函数（input_text 内部会使用 redraw 回调）
                // 传入 focused 作为 0-based output 索引
                if (input_text(x1 + 1, y1 + 1, output[focused], redraw_for_input)) {
                    // 输入完成（按回车）
                    change_state = 0;
                    focused = -1;
                    // 重新绘制对话框，显示刚刚输入的内容
                    change_draw(judge);
                } else {
                    // input_text 未按预期返回 1 的情形（保底处理）
                    change_state = 0;
                    focused = -1;
                    change_draw(judge);
                }

                did_enter_input = true;
                break; // 跳出 for 循环，回到外层循环继续处理
            }
        }

        if (!did_enter_input) {
            // 无点击事件进入输入时，少量延迟避免忙等
            delay(20);
        }
    }
}
**/
/**static void change_submit()//修改模式下点击确定，检验输入的新密码或者新车名是否合法，如果合法就写入information数组，并写入用户文件 ，否则返回不合法 
{
	char path[50];
	for(int i=0;i<3;i++)
	{
		if(strlen(output[i])==0)
		{
			    clrmous(MouseX, MouseY);
                setfillstyle(1, YELLOW);
                bar(150, 160, 490, 300);
                setcolor(BLACK);
                setlinestyle(0, 0, 3);
                rectangle(151, 161, 489, 299);
                puthz(173, 200, "输入区域不能为空！", 24, 30, BLACK);

                // 延时等待任意键/鼠标关闭提示
                for (int i = 0; i < 500; i++)
                {
                    delay(1);
                    if (kbhit()) bioskey(0);
                    newmouse(&MouseX, &MouseY, &press);
                }
                // 清空提示区域
                setfillstyle(SOLID_FILL, WHITE);
                bar(150, 160, 490, 300);
		}
	}
	if(strcmp(output[0],judge?information->car_name:information->password)!=0)
	     {
		clrmous(MouseX, MouseY);
        setfillstyle(1, YELLOW);
        bar(150, 160, 490, 300);
        setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(151, 161, 489, 299);
        puthz(173, 200, "您输入的密码错误！", 24, 30, BLACK);
        // 延时等待任意键/鼠标关闭提示
		for (int i = 0; i < 500; i++)
            {
                delay(1);
                if (kbhit()) bioskey(0);
                newmouse(&MouseX, &MouseY, &press);
            }
                // 清空提示区域
        setfillstyle(SOLID_FILL, WHITE);
        bar(150, 160, 490, 300);
	}
	else if(strcmp(output[1],output[2])!=0)
	    {
	     clrmous(MouseX, MouseY);
         setfillstyle(1, YELLOW);
         bar(150, 160, 490, 300);
         setcolor(BLACK);
		 setlinestyle(0, 0, 3);
		 rectangle(151, 161, 489, 299);
         puthz(173, 200, "您两次输入的名字不同！", 24, 30, BLACK);
         // 延时等待任意键/鼠标关闭提示
		 for (int i = 0; i < 500; i++)
            {
                delay(1);
                if (kbhit()) bioskey(0);
                newmouse(&MouseX, &MouseY, &press);
            }
                // 清空提示区域
         setfillstyle(SOLID_FILL, WHITE);
         bar(150, 160, 490, 300);
	    }	
		
    else
       {
       	 strcpy(judge?information->car_name:information->password,output[1]);
       	 page_state=0;
       	 clrmous(MouseX, MouseY);
         setfillstyle(1, YELLOW);
         bar(150, 160, 490, 300);
         setcolor(BLACK);
		 setlinestyle(0, 0, 3);
		 rectangle(151, 161, 489, 299);
         puthz(173, 200, "恭喜您！修改成功！", 24, 30, BLACK);
         // 延时等待任意键/鼠标关闭提示
		 for (int i = 0; i < 500; i++)
            {
                delay(1);
                if (kbhit()) bioskey(0);
                newmouse(&MouseX, &MouseY, &press);
            }
                // 清空提示区域
         setfillstyle(SOLID_FILL, WHITE);
         bar(150, 160, 490, 300);
         
         FILE *fp;
         strcpy(path,PATH);
         strcat(path,user_name);
         strcat(path,".txt");
         fp=fopen(path,"wt");
         if (fp == NULL) {
             printf("错误：无法打开文件\n");
             return;
              }
         fprintf(fp,"%s\n",information->password);
         fprintf(fp,"%s\n",information->car_name);
         fprintf(fp,"%s\n",information->city);
         fprintf(fp,"%s\n",information->car_plate);
         fclose(fp);
	   }
	   return;
}
static void change_limited()
{
	     clrmous(MouseX, MouseY);
         setfillstyle(1, YELLOW);
         bar(150, 160, 490, 300);
         setcolor(BLACK);
		 setlinestyle(0, 0, 3);
		 rectangle(151, 161, 489, 299);
         puthz(173, 200, "抱歉，您无权修改此项内容！", 24, 30, BLACK);
         // 延时等待任意键/鼠标关闭提示
		 for (int i = 0; i < 500; i++)
            {
                delay(1);
                if (kbhit()) bioskey(0);
                newmouse(&MouseX, &MouseY, &press);
            }
                // 清空提示区域
         setfillstyle(SOLID_FILL, WHITE);
         bar(150, 160, 490, 300);
         draw();
} **/

	/**if(page_state==1)//修改模式 
	    {
	  	newmouse(&MouseX,&MouseY,&press);
	  	setcolor(RED);
		setlinestyle(0,0,3);
		rectangle(435,420,539,420+48);
		
		newmouse(&MouseX,&MouseY,&press);
		for(int i=0;i<4;i++)
  	   	{
  	   		if(check_mouse_click(402-100,210-20-20+58*i,502+100,258-20-20+58*i)) new_hover[i]=1;
  	   		else new_hover[i]=0;
  	   		if(new_hover[i]!=hover_state[i])
				 {
				 	setcolor(new_hover[i]?RED:YELLOW);
				    setlinestyle(0,0,3);
				    clrmous(MouseX, MouseY);
					rectangle(402-100,210-20-20+58*i,502+100,258-20-20+58*i);
				 }		
		    hover_state[i]=new_hover[i];
		    //掠过按钮加红框  
		}
	newmouse(&MouseX,&MouseY,&press);
	if(mouse_press(402-100,210-20-20+58*0,502+100,258-20-20+58*0)==1)
     {
		judge=0;
        change_draw(judge);
        change_handle();
	 }
	 
	else if(mouse_press(402-100,210-20-20+58*1,502+100,258-20-20+58*1)==1)
	{
		judge=1;
        change_draw(judge);
        change_handle();	
	}
    else if((mouse_press(402-100,210-20-20+58*2,502+100,258-20-20+58*2)==1)||(mouse_press(402-100,210-20-20+58*3,502+100,258-20-20+58*3)==1))
    change_limited();
	/**	
		for(i=0;i<4;i++)
        {
    // 只检测是否按下，不修改 mouse_down
         if(mouse_press(402-100,210-20-20+58*i,502+100,258-20-20+58*i) == 1)
         {
              delay(50);
			  newmouse(&MouseX,&MouseY,&press);
			  if(mouse_press(402-100,210-20-20+58*i,502+100,258-20-20+58*i) == 0)        
                {
                 switch(i)
                   {
                	case 0:
                   	 	judge=0;
                  	  	change_draw(judge);
                    	change_handle();
                   	 	break;
                	case 1:
                    	judge=1;
                    	change_draw(judge);
                    	change_handle();
                    	break;
                	case 2:
                	case 3:
                    	change_limited();
                    	break;
            		}
            }
       }  
   }
**/
