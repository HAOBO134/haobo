#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include "mouse.h"


/**************************
MOUSE.c
UPDATER: dengshuumin
FUNCTION: mouse action
ABSTRACT:
		A.mread
		B.newmouse
VERSION: 3.0
***************************/
int MouseX;
int MouseY;
int MouseS;
int press;
void *buffer;
union REGS regs;
int flag=0;


void mouseinit()//初始化
{
	int retcode;
	int xmin,xmax,ymin,ymax,x_max=625,y_max=480;//x_max,y_max,可以直接显示出屏幕比例，而且增强了程序可维护性
	int size;

	xmin=2;
	xmax=x_max-1;
	ymin=8;
	ymax=y_max-2;
	regs.x.ax=0;
	int86(51,&regs,&regs);
	retcode=regs.x.ax;
	if(retcode==0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		delay(5000);
	}
	else
	{
		regs.x.ax=7;
		regs.x.cx=xmin;
		regs.x.dx=xmax;
		int86(51,&regs,&regs);
		regs.x.ax=8;
		regs.x.cx=ymin;
		regs.x.dx=ymax;
		int86(51,&regs,&regs);
	}     // 设置鼠标的水平和竖直的移动范围
	MouseS = 0;
	MouseX=320,MouseY=240;
	save_bk_mou(320,240);
	mouse(MouseX,MouseY);
	flag=1;
}

/*****************************
FUNCTION: mouse
DESCRIPTION: 画不同形态的鼠标
INPUT: x,y
RETURN: 无
******************************/
void mouse(int x,int y)
{
	
	switch(MouseS)
	{
		case 1:                                  //手势鼠标
		{
				setcolor(WHITE);
				setlinestyle(0,0,1);
				line(x-1,y+9,x-1,y+8);
				line(x,y+7,x,y+11);
				line(x+1,y+6,x+1,y+13);
				line(x+2,y+8,x+2,y+14);
				line(x+3,y-1,x+3,y+15);
				arc(x+4,y-1,0,180,1);
				line(x+4,y-2,x+4,y+15);
				line(x+5,y-1,x+5,y+16);
				arc(x+6,y+3,0,180,1);
				line(x+6,y+2,x+6,y+16);
				line(x+7,y+3,x+7,y+17);
				arc(x+8,y+5,0,180,1);
				line(x+8,y+4,x+8,y+17);
				line(x+9,y+5,x+9,y+16);
				arc(x+10,y+7,0,180,1);
				line(x+10,y+6,x+10,y+16);
				line(x+11,y+7,x+11,y+13);

				setcolor(DARKGRAY);
				line(x-1,y+9,x-1,y+8);
				line(x-1,y+8,x+1,y+6);
				line(x+1,y+6,x+3,y+10);
				line(x+3,y+10,x+3,y-1);
				arc(x+4,y-1,0,180,1);
				line(x+5,y-1,x+5,y+5);
				arc(x+6,y+3,0,180,1);
				line(x+7,y+3,x+7,y+7);
				arc(x+8,y+5,0,180,1);
				line(x+9,y+5,x+9,y+9);
				arc(x+10,y+7,0,180,1);
				line(x+11,y+7,x+11,y+13);
				arc(x+7,y+13,-90,0,4);
				line(x+7,y+17,x+3,y+15);
				line(x+3,y+15,x+1,y+13);
				line(x+1,y+13,x-1,y+9);
		}
			break;
		case 2:                        //垂直光标
		{
			setcolor(DARKGRAY);
			setlinestyle(0,0,1);
			line(x+1,y-1,x+9,y-1);
			line(x+1,y+15,x+9,y+15);
			line(x+5,y-1,x+5,y+15);
		}
			break;
		case 3:                        //十字
		{
			setcolor(WHITE);
			setlinestyle(0,0,1);
			line(x-1,y+7,x+11,y+7);
			line(x+5,y-1,x+5,y+15);
		}
			break;
		default:              //默认鼠标
		{
			setlinestyle(0,0,1);
			setcolor(WHITE);
			line(x,y,x,y+13);
			line(x+1,y+1,x+1,y+12);
			line(x+2,y+2,x+2,y+11);
			line(x+3,y+3,x+3,y+10);
			line(x+4,y+4,x+4,y+12);
			line(x+5,y+5,x+5,y+9);
			line(x+5,y+11,x+5,y+14);
			line(x+6,y+6,x+6,y+9);
			line(x+6,y+13,x+6,y+15);
			line(x+7,y+7,x+7,y+9);
			line(x+8,y+8,x+8,y+9);
			line(x+9,y+9,x+9,y+9);
			setcolor(DARKGRAY);
			line(x-1,y-1,x-1,y+14);
			line(x-1,y+14,x+3,y+11);
			line(x+3,y+11,x+3,y+12);
			line(x+3,y+12,x+4,y+13);
			line(x+4,y+13,x+4,y+14);
			line(x+4,y+14,x+7,y+17);
			line(x+7,y+17,x+7,y+13);
			line(x+7,y+13,x+6,y+12);
			line(x+6,y+12,x+6,y+11);
			line(x+6,y+11,x+5,y+10);
			line(x+5,y+10,x+11,y+10);
			line(x+11,y+10,x-1,y-2);
		}
		break;
	}
}

/*void mou_pos(int *nx,int *ny,int*nbuttons)//更改鼠标位置
{
	int x0=*nx,y0=*ny;

	mread(nx,ny,nbuttons);
	clrmous(x0,y0);
	save_bk_mou(*nx,*ny);
	drawmous(*nx,*ny);
}

void mread(int *nx,int *ny,int*nbuttons)//改坐标不画
{
	int x0=*nx,y0=*ny,buttons0=*nbuttons;
	int xnew,ynew,buttonsnew;

	do{
	regs.x.ax=3;
	int86(51,&regs,&regs);
	buttonsnew=regs.x.bx;
	delay(10);
	regs.x.ax=3;
	int86(51,&regs,&regs);
	if(regs.x.bx==buttonsnew)
		*nbuttons=regs.x.bx;
	else
		*nbuttons=buttons0;
	xnew=regs.x.cx;
	ynew=regs.x.dx;
	}while(xnew==x0&&ynew==y0&&*nbuttons==0);
	*nx=xnew;
	*ny=ynew;
}
*/

/***************************************
FUNCTION: mread
DESCRIPTION: 获取新的寄存器信息
INPUT: nx,ny,nbuttons
RETURN: 无
****************************************/
void mread(int *nx,int *ny,int *nbuttons)  
{
	regs.x.ax=3;
	int86(51,&regs,&regs);
	*nx = regs.x.cx;
	*ny = regs.x.dx;
	*nbuttons = regs.x.bx;
}

/*******************************************
FUNCTION: newmouse
DESCRIPTION: 鼠标状态发生变化则更新鼠标
INPUT: nx,ny,nbuttons
RETURN: 无
********************************************/
void newmouse(int *nx,int *ny,int *nbuttons)
{
	int xn,yn,buttonsn;
	int x0=*nx,y0=*ny,buttons0=*nbuttons;
	mread(&xn,&yn,&buttonsn);
	*nx = xn;
	*ny = yn;
	*nbuttons = buttonsn;
	if(buttons0 == *nbuttons)
		*nbuttons = 0;    //使得能连续按键
	if(xn == x0 && yn == y0 && buttonsn == buttons0)
		return;            //鼠标状态不变则直接返回S
	clrmous(x0,y0);        //说明鼠标状态发生了改变
	save_bk_mou(*nx,*ny);
	drawmous(*nx,*ny);
}

void save_bk_mou(int nx,int ny)//存鼠标背景
{
	int size;

	size=imagesize(nx-1,ny-2,nx+11,ny+17);
	buffer=malloc(size);
	if(buffer!=NULL)
		getimage(nx-1,ny-2,nx+11,ny+17,buffer);
	else
		printf("Error");
}

void clrmous(int nx,int ny)//清除鼠标
{
	if(flag==1)
	{
		//setwritemode(XOR_PUT); 
		//mouse(nx,ny);
		putimage(nx-1,ny-2,buffer,COPY_PUT);
		free(buffer);
		flag=0;
		//setwritemode(COPY_PUT);
	}
}
void drawmous(int nx,int ny)//画出鼠标
{
	if(flag==0)
	{
		setwritemode(COPY_PUT);
	    mouse(nx,ny);
		flag=1;
	}
}



//如果在框中点击，则返回1；在框中未点击，则返回2；不在框中则返回0
int mouse_press(int x1, int y1, int x2, int y2)
{
	//在框中点击，则返回1
	if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 1)
	{
		return 1;
	}
	
	//在框中未点击，则返回2
	else if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 0)
	{
		return 2;
	}
	
	//在框中点击右键，则返回3
	else if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 2)
	{
		return 3;
	}
	
	else
	{
		return 0;
	}
}

/******
FUNC:Ditect mouse position in map 
DESCRIPTION:分块探测鼠标的位置在哪一格并侦测是否按下
INPUT:*x_6, x position of piece; *y_6, y position of piece
RETURN:1, press; 0, not at here; 2, not press; 3, right press
******/

int mouse_press_6(int *x_6, int *y_6)
{
	int cut_y = 0, y_p, x_t = MouseX, y_t = MouseY, tmp;
	float k;
	
	//判定地图外
	if(y_t < 20 || y_t > 450 || x_t < 170 || x_t > 620)
		return 0;
	
	
	while(!(y_t > 20 && y_t < 120)){
		y_t -= 100;
		cut_y++;
	}
	if (y_t < 40) {
		while(!(x_t >= 170 && x_t < 230))
			x_t -= 60;
		k = (x_t * 1.0 - 200) / (y_t - 20);
		if (-1.5 < k && k < 1.5)
			y_p = 0;
		else
			y_p = -1;
		
		tmp = y_p + cut_y * 2;
		if (tmp >= 0 && tmp <= 7)
			*x_6 = tmp;
		else
			return 0;
	}
	else if (y_t < 70) {
		tmp = cut_y * 2;
		if (tmp >= 0 && tmp <= 7)
			*x_6 = tmp;
		else
			return 0;
	}
	else if (y_t < 90) {
		while(!(x_t >= 170 && x_t < 230))
			x_t -= 60;
		k = (x_t * 1.0 - 200) / (90 - y_t);
		if (-1.5 < k && k < 1.5)
			y_p = 0;
		else
			y_p = 1;
		tmp = y_p + cut_y * 2;
		if (tmp >= 0 && tmp <= 7)
			*x_6 = tmp;
		else
			return 0;
	}
	else {
		tmp = cut_y * 2 + 1;
		if (tmp >= 0 && tmp <= 7)
			*x_6 = tmp;
		else
			return 0;
	}
	
	x_t = MouseX;
	if (*x_6 % 2) {
		tmp = (x_t - 200)/60; 
		if (tmp >= 0 && tmp <= 6)
			*y_6 = tmp;
		else
			return 0;
	}
	else {
		tmp = (x_t - 170)/60;
		if (tmp >= 0 && tmp <= 6)
			*y_6 = tmp;
		else
			return 0;
	}
	
	return press;
}

int check_mouse_click(int x1, int y1, int x2, int y2) {
    // 使用全局 MouseX/MouseY（已由 newmouse 更新）
    return (MouseX >= x1 && MouseX <= x2 && MouseY >= y1 && MouseY <= y2) ? 1 : 0;
}

// name=mouse_clicked_on_release.c
// 仿照 MOUSE.c 风格：检测“按下并在区域内释放”作为一次点击事件。
// 返回 1 表示在指定矩形区域内发生了完整的点击（按下->释放），否则返回 0。
int mouse_clicked_on_release(int x1, int y1, int x2, int y2)
{
    static int prevButtons = 0;     // 上一帧的按钮状态（0/1/2）
    static int pressedInside = 0;   // 标记：当前按下动作是否始于区域内
    int nx, ny, buttons;
    int clicked = 0;

    // 读取当前鼠标原始状态（不做鼠标绘制/清除）
    mread(&nx, &ny, &buttons);

    // 更新全局位置/按键状态（与程序其它部分保持一致）
    MouseX = nx;
    MouseY = ny;
    press = buttons;

    // 判断当前是否在区域内（包含边界）
    int inside = (MouseX >= x1 && MouseX <= x2 && MouseY >= y1 && MouseY <= y2) ? 1 : 0;

    // 如果当前为按下且按下发生在区域内，则记录
    if (press == 1 && inside) {
        pressedInside = 1;
    }

    // 如果此前按下来自区域内，且现在为释放（从1到0），并且释放时仍在区域内 -> 视为一次点击
    if (pressedInside && prevButtons == 1 && press == 0 && inside) {
        clicked = 1;
        pressedInside = 0; // 重置标志，避免重复触发
    }

    // 如果释放在区域外，清除 pressedInside（按下-移出-释放 不算）
    if (press == 0 && !inside) {
        pressedInside = 0;
    }

    // 保存本帧状态为上一帧供下次比较
    prevButtons = press;

    return clicked;
}

char * Get_username()
{
	FILE *fp;
	char username[30];
	fp=fopen("C:\\CODE\\SOURCE\\USER\\USER.txt","rt");
	if(!fp) printf("fail to open the file");
	fgets(username,sizeof(username),fp);
	fclose(fp);
	return username;
}
