#include "common.h"
#include "page1.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int p1(void)
{
	int page = 0;
	int i;
	int input_state;//输入模式
	char name[100]="";//存储用户名
	char password[100]="";//存储密码
	char trash[1000]="";//读键盘缓存
	char empty[100]="";//用于清空字符串
	char encrypted_passwords[100]="";//用于在密码栏显示加密密码
	char key;//存储当下的键值
	int len;//记录字符串长度
	int encrypt=1;//判断是否需要加密密码
	input_state = 0;
	setbkcolor( BLACK);
	clrmous(MouseX,MouseY);
	for ( i=0;i<20;i++)
	{
		delay( 5);
		setfillstyle(SOLID_FILL, YELLOW);
		bar( 0, i, 640, i+1);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		bar( 0, 480-2*i-1, 640, 480-2*i);
	}
	for ( i=20;i<130;i++)
	{
		delay( 5);
		setfillstyle(SOLID_FILL, YELLOW);
		bar( 0, i, 640, i+1);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		bar( 0, 480-i-21, 640, 480-i-20);
	}
	for ( i=130;i<200;i++)
	{
		delay( 10);
		setfillstyle(SOLID_FILL, YELLOW);
		bar( 0, i, 640, i+1);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		bar( 0, 480-i-21, 640, 480-i-20);
	}
	for ( i=200;i<230;i++)
	{
		delay( 15);
		setfillstyle(SOLID_FILL, YELLOW);
		bar( 0, i, 640, i+1);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		bar( 0, 480-i-21, 640, 480-i-20);
	}
	//加载动画
	page1_screen(encrypt);//绘制页面
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	delay(100);
	
	while(page == 0)
	{
		while(input_state == 0)//未输入有效字符
		{
			newmouse(&MouseX,&MouseY,&press);
		
		    if(mouse_press(150, 320, 150+100, 320+30) == 1)//点击登录
		    {
			    loginuser(name , password, &page );//调用登录函数
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//清空用户名
			    strcpy( password, empty );//清空密码
			    strcpy( encrypted_passwords, empty );//清空加密密码
		    }
		
		
		    else if(mouse_press(370, 320, 370+100, 320+30) == 1)//点击注册
		    {
			    page = 0;
			    registeruser(name, password );//调用注册函数
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//清空用户名
			    strcpy( password, empty );//清空密码
			    strcpy( encrypted_passwords, empty );//清空加密密码
		    }
		    
		    else if(mouse_press(100, 170, 180+260, 170+40) == 1)//点击用户名输入框
		    {
				input_state =1;//切换为用户名输入模式
				clrmous( MouseX , MouseY );
		    	setcolor(RED);
		    	setlinestyle(0, 0, 3);
		    	rectangle(100+1, 170+1, 180+260-1, 170+40-1);//标红用户名输入框
		    }
		    
			else if(mouse_press(100, 170+40+40, 180+260, 170+40+40+40) == 1)//点击密码输入框
		    {
		    	input_state =2;//切换为密码输入模式
		    	clrmous( MouseX , MouseY );
		    	setcolor(RED);
		    	setlinestyle(0, 0, 3);
		    	rectangle(100+1, 170+40+40+1, 180+260-1, 170+40+40+40-1);//标红密码输入框
		    }
		    else if(mouse_press(460, 170+40+40+10, 460+20, 170+40+40+40-10) == 1)//点击切换密码显示
		    {
		    	encrypt++;
		    	encrypt=encrypt%2;
		    	clrmous( MouseX , MouseY );
		    	setcolor(WHITE);
		    	setfillstyle(SOLID_FILL, WHITE);
		    	bar(460, 170+40+40+10, 460+20, 170+40+40+40-10 );
		    	bar(100, 170+40+40, 180+260, 170+40+40+40);
		    	if (encrypt==0)//判断此时密码是否加密
		    	{
		    		setcolor(BLACK);
					setlinestyle(0, 0, 3);
					line( 460, 270, 470, 280);
					line( 470, 280, 480, 260);
		    	}
		    	setcolor(DARKGRAY);
				if (encrypt )
				{
					outtextxy(110, 260, encrypted_passwords);
				}
				else
				{
					outtextxy(110, 260, password);
				}
				for ( i=0;i<500;i++)
				{
					delay( 1);
					newmouse(&MouseX,&MouseY,&press);
				}
		    }
			else if(mouse_press(600, 0, 639, 39) == 1)
		    {
		    	page = 100;
		    	break;
		    }
		    if (kbhit()) //检测到键盘输入
			{
			    key = bioskey(0);//用key存储当下的键值
				trash[0]=key;
			}
		}
		
		while(input_state == 1)//输入用户名
		{
			setcolor(DARKGRAY);
			outtextxy(110, 180, name);//用户名实时显示
			if (kbhit()) //检测到键盘输入
			{
			    key = bioskey(0);
			    if (key == '\b')//检测退格键
			    {
			    	len=strlen( name );
				    name[len-1]='\0';//删除最后一个字符
				    clrmous( MouseX , MouseY );
				    setfillstyle(SOLID_FILL, WHITE);
	                bar(100, 170, 180+260, 170+40);//清空输入框
	                setcolor(RED);
					setlinestyle(0, 0, 3);
	                rectangle(100+1, 170+1, 180+260-1, 170+40-1);
	                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	                newmouse(&MouseX,&MouseY,&press);
			    }
			    else if (strlen(name)>=8)//检测长度是否超标
				{
					clrmous( MouseX , MouseY );
					setfillstyle(1,YELLOW);
					bar(150,160,490,300 );
					setcolor(BLACK);
					setlinestyle(0, 0, 3);
					rectangle(150+1,160+1,490-1,300-1);
					puthz(173, 200, "用户名长度请勿超过八",24,30,BLACK);
					for ( i=0;i<500;i++)
					{
						delay( 1);
						if ( kbhit( ))
						{
							key = bioskey(0);
						}
						newmouse(&MouseX,&MouseY,&press);
					}
					page1_screen(encrypt);
					setcolor(DARKGRAY);
					outtextxy(110, 180, name);
					if (encrypt )
					{
						outtextxy(110, 260, encrypted_passwords);
					}
					else
					{
						outtextxy(110, 260, password);
					}
					setcolor(RED);
					setlinestyle(0, 0, 3);
	                rectangle(100+1, 170+1, 180+260-1, 170+40-1);
	                break;
				}
			    else if ((key>='a'&&key<='z')||(key>='A'&&key<='Z')||(key>='0'&&key<='9')||key=='_')//检测是否为合法字符
			    {
				    len=strlen( name );
				    name[len]=key;
				    name[len+1]='\0';
			    }
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
					page1_screen(encrypt);
					setcolor(DARKGRAY);
					outtextxy(110, 180, name);
					if (encrypt )
					{
						outtextxy(110, 260, encrypted_passwords);
					}
					else
					{
						outtextxy(110, 260, password);
					}
					setcolor(RED);
					setlinestyle(0, 0, 3);
	                rectangle(100+1, 170+1, 180+260-1, 170+40-1);
				}
			}
			newmouse(&MouseX,&MouseY,&press);
			if(mouse_press(150, 320, 150+100, 320+30) == 1)//点击登录
		    {
			    loginuser(name , password, &page );//调用登录函数
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//清空用户名
			    strcpy( password, empty );//清空密码
			    strcpy( encrypted_passwords, empty );//清空加密密码
			    input_state=0;//退出输入模式
		    }
		
		
		    else if(mouse_press(370, 320, 370+100, 320+30) == 1)//点击注册
		    {
			    page = 0;
			    registeruser(name, password );//调用注册函数
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//清空用户名
			    strcpy( password, empty );//清空密码
			    strcpy( encrypted_passwords, empty );//清空加密密码
			    input_state=0;//退出输入模式
		    }
		    else if(mouse_press(460, 170+40+40+10, 460+20, 170+40+40+40-10) == 1)//点击切换密码显示
		    {
		    	encrypt++;
		    	encrypt=encrypt%2;
		    	clrmous( MouseX , MouseY );
		    	setcolor(WHITE);
		    	setfillstyle(SOLID_FILL, WHITE);
		    	bar(460, 170+40+40+10, 460+20, 170+40+40+40-10 );
		    	bar(100, 170+40+40, 180+260, 170+40+40+40);
		    	if (encrypt==0)
		    	{
		    		setcolor(BLACK);
					setlinestyle(0, 0, 3);
					line( 460, 270, 470, 280);
					line( 470, 280, 480, 260);
		    	}
		    	setcolor(DARKGRAY);
				if (encrypt )
				{
					outtextxy(110, 260, encrypted_passwords);
				}
				else
				{
					outtextxy(110, 260, password);
				}
				for ( i=0;i<500;i++)
				{
					delay( 1);
					newmouse(&MouseX,&MouseY,&press);
				}
		    }
		    else if(mouse_press(600, 0, 639, 39) == 1)
		    {
		    	page = 100;
		    	break;
		    }
			else if ((mouse_press(0, 0, 639, 479)==1 ) && (mouse_press( 100, 170, 180+260, 170+40) !=1))//点击输入框, 登录及注册以外的地方
			{
				clrmous( MouseX , MouseY );
				setfillstyle(SOLID_FILL, WHITE);
				bar(100, 170, 180+260, 170+40);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
				outtextxy(110, 180, name);
			    input_state=0;//退出输入模式
			}
		}
			
		
		while(input_state == 2)//输入密码
		{
			setcolor(DARKGRAY);
			if (encrypt )
			{
				outtextxy(110, 260, encrypted_passwords);
			}
			else
			{
				outtextxy(110, 260, password);
			}//实时显示密码
			if (kbhit())//检测到键盘输入
			{
				key = bioskey(0);
				if (key=='\b')//检测退格键
				{
					len=strlen(password);
					password[len-1]='\0';//删除最后一个字符
					encrypted_passwords[len-1]='\0';//删除最后一个加密字符
					clrmous( MouseX , MouseY );
					setfillstyle(SOLID_FILL, WHITE);
	                bar(100, 170+40+40, 180+260, 170+40+40+40);//清空输入框
	                setcolor(RED);
					setlinestyle(0, 0, 3);
	                rectangle(100+1, 170+40+40+1, 180+260-1, 170+40+40+40-1);
	                newmouse(&MouseX,&MouseY,&press);
				}
				else if (strlen(password)>=20)
				{
					clrmous( MouseX , MouseY );
					setfillstyle(1,YELLOW);
					bar(150,160,490,300 );
					setcolor(BLACK);
					setlinestyle(0, 0, 3);
					rectangle(150+1,160+1,490-1,300-1);
					puthz(173, 200, "密码长度请勿超过二十",24,30,BLACK);
					for ( i=0;i<500;i++)
					{
						delay( 1);
						if ( kbhit( ))
						{
							key = bioskey(0);
						}
						newmouse(&MouseX,&MouseY,&press);
					}
					page1_screen(encrypt);
					setcolor(DARKGRAY);
					outtextxy(110, 180, name);
					if (encrypt )
					{
						outtextxy(110, 260, encrypted_passwords);
					}
					else
					{
						outtextxy(110, 260, password);
					}
					setcolor(RED);
					setlinestyle(0, 0, 3);
	                rectangle(100+1, 170+40+40+1, 180+260-1, 170+40+40+40-1);
	                break;
				}
				else if ((key>='a'&&key<='z')||(key>='A'&&key<='Z')||(key>='0'&&key<='9')||key=='_')
				{
					len=strlen(password);
					password[len]=key;
					password[len+1]='\0';
					encrypted_passwords[len]='*';
					encrypted_passwords[len+1]='\0';
				}
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
					page1_screen(encrypt);
					setcolor(DARKGRAY);
					outtextxy(110, 180, name);
					if (encrypt )
					{
						outtextxy(110, 260, encrypted_passwords);
					}
					else
					{
						outtextxy(110, 260, password);
					}
					setcolor(RED);
					setlinestyle(0, 0, 3);
	                rectangle(100+1, 170+40+40+1, 180+260-1, 170+40+40+40-1);
				}
			}
			newmouse(&MouseX,&MouseY,&press);
			if(mouse_press(150, 320, 150+100, 320+30) == 1)//点击登录
		    {
			    loginuser(name , password, &page );//调用登录函数
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//清空用户名
			    strcpy( password, empty );//清空密码
			    strcpy( encrypted_passwords, empty );//清空加密密码
			    input_state=0;//退出输入模式
		    }
		
		
		    else if(mouse_press(370, 320, 370+100, 320+30) == 1)//点击注册
		    {
			    page = 0;
			    registeruser(name, password );//调用注册函数
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//清空用户名
			    strcpy( password, empty );//清空密码
			    strcpy( encrypted_passwords, empty );//清空加密密码
			    input_state=0;//退出输入模式
		    }
		    else if(mouse_press(460, 170+40+40+10, 460+20, 170+40+40+40-10) == 1)//点击切换密码显示
		    {
		    	encrypt++;
		    	encrypt=encrypt%2;
		    	clrmous( MouseX , MouseY );
		    	setcolor(WHITE);
		    	setfillstyle(SOLID_FILL, WHITE);
		    	bar(460, 170+40+40+10, 460+20, 170+40+40+40-10 );
		    	bar(100, 170+40+40, 180+260, 170+40+40+40);
		    	if (encrypt==0)
		    	{
		    		setcolor(BLACK);
					setlinestyle(0, 0, 3);
					line( 460, 270, 470, 280);
					line( 470, 280, 480, 260);
		    	}
		    	setcolor(RED);
				setlinestyle(0, 0, 3);
				rectangle(100+1, 170+40+40+1, 180+260-1, 170+40+40+40-1);
		    	setcolor(DARKGRAY);
				if (encrypt )
				{
					outtextxy(110, 260, encrypted_passwords);
				}
				else
				{
					outtextxy(110, 260, password);
				}
				for ( i=0;i<500;i++)
				{
					delay( 1);
					newmouse(&MouseX,&MouseY,&press);
				}
		    }
		    else if(mouse_press(600, 0, 639, 39) == 1)
		    {
		    	page = 100;
		    	break;
		    }
			else if ((mouse_press(0, 0, 639, 479)==1 ) && (mouse_press( 100, 250, 180+260, 170+160) !=1))
			{
				clrmous( MouseX , MouseY );
				setfillstyle(SOLID_FILL, WHITE);
				bar(100, 170+40+40, 180+260, 170+40+40+40);
				if (encrypt )
				{
					outtextxy(110, 260, encrypted_passwords);
				}
				else
				{
					outtextxy(110, 260, password);
				}
			    input_state = 0;
			}
		}
	}
		
		
		
	return page;
}


void page1_screen(int encrypt)//画页面
{
	clrmous( MouseX , MouseY );
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, YELLOW);
	bar( 0, 0, 640, 230);
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar( 0, 231, 640, 480);
	setfillstyle(SOLID_FILL, LIGHTRED);
	bar( 600, 39, 639, 0);
	setcolor(RED);
	setlinestyle(0, 0, 3);
	line(600, 39, 639, 0);
	line(639, 39, 600, 0);
	puthz(40,40,"欢迎来到夺岛军演模拟器",48,50,MAGENTA);
	setfillstyle(SOLID_FILL, WHITE);
	bar(100, 170, 180+260, 170+40);
	setfillstyle(SOLID_FILL, WHITE);
	bar(100, 170+40+40, 180+260, 170+40+40+40);
	bar(460, 170+40+40+10, 460+20, 170+40+40+40-10);
	if (encrypt==0)
	{
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		line( 460, 270, 470, 280);
		line( 470, 280, 480, 260);
	}
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	puthz(10,176,"用户名",24,30,BLACK);
	puthz(25,256,"密码",24,30,BLACK);
	puthz(500,256,"显示密码",24,30,BLACK);
	bar(150, 320, 150+100, 320+30);
	bar(370, 320, 370+100, 320+30);
	puthz(173,323,"登录",24,30,BLACK);
	puthz(393,323,"注册",24,30,BLACK);
}

void registeruser(char *name, char *password )//用户注册
{
	FILE *file;//定义文件指针
	int i=1;
	char path[100]="C:\\CODE\\SOURCE\\USER\\";//定义绝对路径
	char suffix[100]=".txt";//定义文件后缀
	strcat( path, name );//将用户名移到路径末尾
	strcat( path, suffix );//加上后缀
	if (strlen( name)==0)//检测用户名长度
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(218, 200, "用户名不能为空",24,30,BLACK);
		for ( i=1;i<500;i++)//防止连续点击
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);
	    return;
	}
	if (strlen( password)==0)//检测密码长度
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(233, 200, "密码不能为空",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);
	    return;
	}
	file = fopen(path, "rt");//以只读打开一个文本文件
	if (file != NULL)//如果打开成功，说明用户名已被占用
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(203, 200, "该用户名已被占用",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);//关闭文件
	    return;
	}
	file = fopen(path, "wt");//只写建立一个文本文件
	if (file == NULL )
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(203, 200, "无法打开文件",24,30,BLACK);
	}
	fprintf(file, "%s", password);//将密码写入该文件
	clrmous( MouseX , MouseY );
	setfillstyle(1,YELLOW);
	bar(150,160,490,300 );
	setcolor(BLACK);
	setlinestyle(0, 0, 3);
	rectangle(150+1,160+1,490-1,300-1);
	puthz(263, 200, "注册成功",24,30,BLACK);
	for ( i=1;i<500;i++)
	{
		newmouse(&MouseX,&MouseY,&press);
		delay( 1);
	}
	fclose(file);//关闭文件
	return;
}

void loginuser(char *name, char *password , int *page )//用户登录
{
	FILE *file;
	int i=1;
	char path[100]="C:\\CODE\\SOURCE\\USER\\";
	char suffix[100]=".txt";
	char filepassword[100];//存储文件内的密码
	strcat( path, name );
	strcat( path, suffix );
	if (strlen( name)==0)
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(218, 200, "用户名不能为空",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);
	    return;
	}
	file = fopen(path , "rt");//只读打开文件
	if (file  == NULL )
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(188, 200, "用户名错误或不存在",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
		fclose(file);
	    return;
	}
	if (strlen( password)==0)
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(233, 200, "密码不能为空",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);
	    return;
	}
	fscanf(file, "%s", filepassword);//读取文件内的密码
	if (strcmp(password,filepassword)==0)//比较文件内的密码和输入的密码
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(263, 200, "登录成功",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
		*page = 1;//改变页面值，进行页面跳转
		fclose(file);
		file = fopen("C:\\CODE\\SOURCE\\USER\\user.txt", "wt");
		fprintf(file, "%s", name);
		fclose(file);
	    return;
	}
	else
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(263, 200, "密码错误",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
		fclose(file);
	    return;
	}
}
	