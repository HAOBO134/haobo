#include "common.h"
#include "page1.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int p1(void)
{
	int page = 0;
	int i;
	int input_state;//����ģʽ
	char name[100]="";//�洢�û���
	char password[100]="";//�洢����
	char trash[1000]="";//�����̻���
	char empty[100]="";//��������ַ���
	char encrypted_passwords[100]="";//��������������ʾ��������
	char key;//�洢���µļ�ֵ
	int len;//��¼�ַ�������
	int encrypt=1;//�ж��Ƿ���Ҫ��������
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
	//���ض���
	page1_screen(encrypt);//����ҳ��
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	delay(100);
	
	while(page == 0)
	{
		while(input_state == 0)//δ������Ч�ַ�
		{
			newmouse(&MouseX,&MouseY,&press);
		
		    if(mouse_press(150, 320, 150+100, 320+30) == 1)//�����¼
		    {
			    loginuser(name , password, &page );//���õ�¼����
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//����û���
			    strcpy( password, empty );//�������
			    strcpy( encrypted_passwords, empty );//��ռ�������
		    }
		
		
		    else if(mouse_press(370, 320, 370+100, 320+30) == 1)//���ע��
		    {
			    page = 0;
			    registeruser(name, password );//����ע�ắ��
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//����û���
			    strcpy( password, empty );//�������
			    strcpy( encrypted_passwords, empty );//��ռ�������
		    }
		    
		    else if(mouse_press(100, 170, 180+260, 170+40) == 1)//����û��������
		    {
				input_state =1;//�л�Ϊ�û�������ģʽ
				clrmous( MouseX , MouseY );
		    	setcolor(RED);
		    	setlinestyle(0, 0, 3);
		    	rectangle(100+1, 170+1, 180+260-1, 170+40-1);//����û��������
		    }
		    
			else if(mouse_press(100, 170+40+40, 180+260, 170+40+40+40) == 1)//������������
		    {
		    	input_state =2;//�л�Ϊ��������ģʽ
		    	clrmous( MouseX , MouseY );
		    	setcolor(RED);
		    	setlinestyle(0, 0, 3);
		    	rectangle(100+1, 170+40+40+1, 180+260-1, 170+40+40+40-1);//������������
		    }
		    else if(mouse_press(460, 170+40+40+10, 460+20, 170+40+40+40-10) == 1)//����л�������ʾ
		    {
		    	encrypt++;
		    	encrypt=encrypt%2;
		    	clrmous( MouseX , MouseY );
		    	setcolor(WHITE);
		    	setfillstyle(SOLID_FILL, WHITE);
		    	bar(460, 170+40+40+10, 460+20, 170+40+40+40-10 );
		    	bar(100, 170+40+40, 180+260, 170+40+40+40);
		    	if (encrypt==0)//�жϴ�ʱ�����Ƿ����
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
		    if (kbhit()) //��⵽��������
			{
			    key = bioskey(0);//��key�洢���µļ�ֵ
				trash[0]=key;
			}
		}
		
		while(input_state == 1)//�����û���
		{
			setcolor(DARKGRAY);
			outtextxy(110, 180, name);//�û���ʵʱ��ʾ
			if (kbhit()) //��⵽��������
			{
			    key = bioskey(0);
			    if (key == '\b')//����˸��
			    {
			    	len=strlen( name );
				    name[len-1]='\0';//ɾ�����һ���ַ�
				    clrmous( MouseX , MouseY );
				    setfillstyle(SOLID_FILL, WHITE);
	                bar(100, 170, 180+260, 170+40);//��������
	                setcolor(RED);
					setlinestyle(0, 0, 3);
	                rectangle(100+1, 170+1, 180+260-1, 170+40-1);
	                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	                newmouse(&MouseX,&MouseY,&press);
			    }
			    else if (strlen(name)>=8)//��ⳤ���Ƿ񳬱�
				{
					clrmous( MouseX , MouseY );
					setfillstyle(1,YELLOW);
					bar(150,160,490,300 );
					setcolor(BLACK);
					setlinestyle(0, 0, 3);
					rectangle(150+1,160+1,490-1,300-1);
					puthz(173, 200, "�û����������𳬹���",24,30,BLACK);
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
			    else if ((key>='a'&&key<='z')||(key>='A'&&key<='Z')||(key>='0'&&key<='9')||key=='_')//����Ƿ�Ϊ�Ϸ��ַ�
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
					puthz(173, 200, "�������Сд��ĸ����",24,30,BLACK);
					puthz(248, 235, "�ֻ��»���",24,30,BLACK);
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
			if(mouse_press(150, 320, 150+100, 320+30) == 1)//�����¼
		    {
			    loginuser(name , password, &page );//���õ�¼����
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//����û���
			    strcpy( password, empty );//�������
			    strcpy( encrypted_passwords, empty );//��ռ�������
			    input_state=0;//�˳�����ģʽ
		    }
		
		
		    else if(mouse_press(370, 320, 370+100, 320+30) == 1)//���ע��
		    {
			    page = 0;
			    registeruser(name, password );//����ע�ắ��
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//����û���
			    strcpy( password, empty );//�������
			    strcpy( encrypted_passwords, empty );//��ռ�������
			    input_state=0;//�˳�����ģʽ
		    }
		    else if(mouse_press(460, 170+40+40+10, 460+20, 170+40+40+40-10) == 1)//����л�������ʾ
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
			else if ((mouse_press(0, 0, 639, 479)==1 ) && (mouse_press( 100, 170, 180+260, 170+40) !=1))//��������, ��¼��ע������ĵط�
			{
				clrmous( MouseX , MouseY );
				setfillstyle(SOLID_FILL, WHITE);
				bar(100, 170, 180+260, 170+40);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
				outtextxy(110, 180, name);
			    input_state=0;//�˳�����ģʽ
			}
		}
			
		
		while(input_state == 2)//��������
		{
			setcolor(DARKGRAY);
			if (encrypt )
			{
				outtextxy(110, 260, encrypted_passwords);
			}
			else
			{
				outtextxy(110, 260, password);
			}//ʵʱ��ʾ����
			if (kbhit())//��⵽��������
			{
				key = bioskey(0);
				if (key=='\b')//����˸��
				{
					len=strlen(password);
					password[len-1]='\0';//ɾ�����һ���ַ�
					encrypted_passwords[len-1]='\0';//ɾ�����һ�������ַ�
					clrmous( MouseX , MouseY );
					setfillstyle(SOLID_FILL, WHITE);
	                bar(100, 170+40+40, 180+260, 170+40+40+40);//��������
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
					puthz(173, 200, "���볤�����𳬹���ʮ",24,30,BLACK);
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
					puthz(173, 200, "�������Сд��ĸ����",24,30,BLACK);
					puthz(248, 235, "�ֻ��»���",24,30,BLACK);
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
			if(mouse_press(150, 320, 150+100, 320+30) == 1)//�����¼
		    {
			    loginuser(name , password, &page );//���õ�¼����
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//����û���
			    strcpy( password, empty );//�������
			    strcpy( encrypted_passwords, empty );//��ռ�������
			    input_state=0;//�˳�����ģʽ
		    }
		
		
		    else if(mouse_press(370, 320, 370+100, 320+30) == 1)//���ע��
		    {
			    page = 0;
			    registeruser(name, password );//����ע�ắ��
			    cleardevice();
			    page1_screen(encrypt);
			    strcpy( name, empty );//����û���
			    strcpy( password, empty );//�������
			    strcpy( encrypted_passwords, empty );//��ռ�������
			    input_state=0;//�˳�����ģʽ
		    }
		    else if(mouse_press(460, 170+40+40+10, 460+20, 170+40+40+40-10) == 1)//����л�������ʾ
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


void page1_screen(int encrypt)//��ҳ��
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
	puthz(40,40,"��ӭ�����ᵺ����ģ����",48,50,MAGENTA);
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
	puthz(10,176,"�û���",24,30,BLACK);
	puthz(25,256,"����",24,30,BLACK);
	puthz(500,256,"��ʾ����",24,30,BLACK);
	bar(150, 320, 150+100, 320+30);
	bar(370, 320, 370+100, 320+30);
	puthz(173,323,"��¼",24,30,BLACK);
	puthz(393,323,"ע��",24,30,BLACK);
}

void registeruser(char *name, char *password )//�û�ע��
{
	FILE *file;//�����ļ�ָ��
	int i=1;
	char path[100]="C:\\CODE\\SOURCE\\USER\\";//�������·��
	char suffix[100]=".txt";//�����ļ���׺
	strcat( path, name );//���û����Ƶ�·��ĩβ
	strcat( path, suffix );//���Ϻ�׺
	if (strlen( name)==0)//����û�������
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(218, 200, "�û�������Ϊ��",24,30,BLACK);
		for ( i=1;i<500;i++)//��ֹ�������
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);
	    return;
	}
	if (strlen( password)==0)//������볤��
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(233, 200, "���벻��Ϊ��",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);
	    return;
	}
	file = fopen(path, "rt");//��ֻ����һ���ı��ļ�
	if (file != NULL)//����򿪳ɹ���˵���û����ѱ�ռ��
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(203, 200, "���û����ѱ�ռ��",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);//�ر��ļ�
	    return;
	}
	file = fopen(path, "wt");//ֻд����һ���ı��ļ�
	if (file == NULL )
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(203, 200, "�޷����ļ�",24,30,BLACK);
	}
	fprintf(file, "%s", password);//������д����ļ�
	clrmous( MouseX , MouseY );
	setfillstyle(1,YELLOW);
	bar(150,160,490,300 );
	setcolor(BLACK);
	setlinestyle(0, 0, 3);
	rectangle(150+1,160+1,490-1,300-1);
	puthz(263, 200, "ע��ɹ�",24,30,BLACK);
	for ( i=1;i<500;i++)
	{
		newmouse(&MouseX,&MouseY,&press);
		delay( 1);
	}
	fclose(file);//�ر��ļ�
	return;
}

void loginuser(char *name, char *password , int *page )//�û���¼
{
	FILE *file;
	int i=1;
	char path[100]="C:\\CODE\\SOURCE\\USER\\";
	char suffix[100]=".txt";
	char filepassword[100];//�洢�ļ��ڵ�����
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
		puthz(218, 200, "�û�������Ϊ��",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);
	    return;
	}
	file = fopen(path , "rt");//ֻ�����ļ�
	if (file  == NULL )
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(188, 200, "�û�������򲻴���",24,30,BLACK);
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
		puthz(233, 200, "���벻��Ϊ��",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
	    fclose(file);
	    return;
	}
	fscanf(file, "%s", filepassword);//��ȡ�ļ��ڵ�����
	if (strcmp(password,filepassword)==0)//�Ƚ��ļ��ڵ���������������
	{
		clrmous( MouseX , MouseY );
		setfillstyle(1,YELLOW);
		bar(150,160,490,300 );
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(150+1,160+1,490-1,300-1);
		puthz(263, 200, "��¼�ɹ�",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
		*page = 1;//�ı�ҳ��ֵ������ҳ����ת
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
		puthz(263, 200, "�������",24,30,BLACK);
		for ( i=1;i<500;i++)
		{
			newmouse(&MouseX,&MouseY,&press);
			delay( 1);
		}
		fclose(file);
	    return;
	}
}
	