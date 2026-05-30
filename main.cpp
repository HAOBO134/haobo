#include "common.h"
#include "main.h"
#include "mouse.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page301.h"
#include "page31.h" 
#include "page4.h"
#include "page32.h"
#include "page33.h"
#include "page34.h"
#include "page41.h"
#include "page44.h"
#include "page43.h" 
#include "page35.h"
#include "page351.h"
#include "page352.h"
#include "page353.h"
#include "page42.h"
#include "input.h"
#include "inform.h"



 
void main(void)
{
	int page=0,gd=VGA,gm=VGAHI,i;
	char username[20];
	
	initgraph(&gd,&gm,"C:\\BORLANDC\\BGI");
	mouseinit();


	while(1)
	{
		switch(page){
			case 0:
				page=p1();
				break;
			case 1:
				page=p2();
				break;
			case 3:
				page=p3();
				break;
			case 4:
				strcpy(username,p4());
				if(strcmp(username,"111")==0) page=1;
				else page=41;
				break;
			case 41:
				page=p41(username);
				break;
			case 44:
				page=p44(username);
				break;
			case 31:
				page=p31();
				break;
			case 32:
			    page=p32();
			    break;
			case 33:
			    page=p33();
				break; 
			case 34:
				page=p34();
				break;
			case 35:
				page=p35();
				break;
			case 351:
				page=p351();
				break;
			case 352:
				page=p352();
				break;
			case 353:
				page=p353();
				break;
			case 42:
				page=p42(username);
				break;
			case 43:
				page=p43(username);
				break;
			case 301:
				page=p301();
				break;
			case 302:
				page=p302();
				break;
			case 303:
				page=p303();
				break;
			case 9:
				return ;
				
				
		}
	}
}

