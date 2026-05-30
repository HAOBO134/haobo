#include "common.h"
#include "page3.h"


int p3()
{   

	
	int hover_state[10];
	int new_hover[10];
	page3_draw_1();
	while(1)
	{
		
		
        newmouse(&MouseX , &MouseY , &press);
		for(int j=0;j<5;j++){
			if(mouse_press(0,24+96*j,80,72+96*j)==1)
			{
				return 31+j;
			}
			else if(mouse_press(600, 0, 639, 39)==1){
				delay(100);
				 newmouse(&MouseX , &MouseY , &press);
				 if(mouse_press(600, 0, 639, 39)==2) return 1;
			}
		}
		newmouse(&MouseX , &MouseY , &press);		
	    for(j=0;j<3;j++){
	    	if(mouse_press(226,120+96*j,226+288,120+96*j+48)==1){
				return 301+j;
			}
		}
		newmouse(&MouseX , &MouseY , &press);
	  	for(j=0;j<5;j++)
	  	{
	  		if(check_mouse_click(0,24+96*j,80,72+96*j)==1)
			{
				new_hover[j]=1;
			}
		    else new_hover[j]=0;
		    if(new_hover[j]!=hover_state[j]){		
		       setcolor(new_hover[j]?RED:YELLOW);
		       setlinestyle(0,0,3);
		       clrmous(MouseX, MouseY);
		       rectangle(0,24+96*j,80,72+96*j);   	 
		      }
		    hover_state[j]=new_hover[j];
		}  
		for(j=0;j<3;j++){
			if(check_mouse_click(226,120+96*j,226+288,120+96*j+48)==1)
			{
				new_hover[5+j]=1;
			}
		    else new_hover[5+j]=0;
		    if(new_hover[5+j]!=hover_state[5+j]){		
		       setcolor(new_hover[5+j]?RED:YELLOW);
		       setlinestyle(0,0,3);
		       clrmous(MouseX, MouseY);
		       rectangle(226,120+96*j,226+288,120+96*j+48);   	 
		      }
		    hover_state[5+j]=new_hover[5+j];
		}
		
	}
	
  /** 
	while(1)
      { 
        newmouse(&MouseX,&MouseY,&press);
        
        if(mouse_press(0,24,80,72)==2)
	   {
	  	setcolor(RED);
	  	rectangle(0,24-1,80+1,72+1);
	   } 
	   else 
	   {
	    setcolor(BLUE);
	  	rectangle(0,24-1,80+1,72+1);
	   }
	   if(mouse_press(0,120,80,168)==2)
	   {
	  	setcolor(RED);
	  	rectangle(0,120+1,80-1,168-1);
	   } 
	   else 
	   {
	    setcolor(BLUE);
	  	rectangle(0,120+1,80-1,168-1);
	   }
      	if(mouse_press(0,216,80,264)==2)
	   {
	  	setcolor(RED);
	  	rectangle(0,216+1,80-1,264-1);
	   } 
	   else 
	   {
	    setcolor(BLUE);
	  	rectangle(0,216+1,80-1,264-1);
	   }
	   if(mouse_press(0,312,80,360)==2)
	   {
	  	setcolor(RED);
	  	rectangle(0,312+1,80-1,360-1);
	   } 
	   else 
	   {
	    setcolor(BLUE);
	  	rectangle(0,312+1,80-1,360-1);
	   }
      	 if(mouse_press(0,408,80,456)==2)
	   {
	  	setcolor(RED);
	  	rectangle(0,408+1,80-1,456-1);
	   } 
	   else 
	   {
	    setcolor(BLUE);
	  	rectangle(0,408+1,80-1,456-1);
	   }
	   if(mouse_press(0,24,80,72)==1)
	   {
	   	 clrmous(MouseX,MouseY);
	   	 return 31;
	   }
	   if(mouse_press(0,120,80,168)==1)
	   {
	   	 clrmous(MouseX,MouseY);
	   	 return 32;
	   }
	   if(mouse_press(0,216,80,264)==1)
	   {
	   	 clrmous(MouseX,MouseY);
	   	 return 33;
	   }
	   if(mouse_press(0,312,80,360)==1)
	   {
	   	 clrmous(MouseX,MouseY);
	   	 return 35;
	   }
	   if(mouse_press(0,408,80,456)==1)
	   {
	   	 clrmous(MouseX,MouseY);
	   	 return 34;
	   }
	   if(mouse_press(600, 0, 639, 39)==1)
	   {
	   	 delay(100);
	   	 newmouse(&MouseX,&MouseY,&press);
	   	 if(mouse_press(600, 0, 639, 39)==2)
	   	 {
	   	 	return 1;
			}
	   }
	   
	   
	  }	
	**/
}


void page_draw()
{
	setbkcolor(WHITE);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	setlinestyle(0,0,3);
	
	bar(0,24,80,72);
	bar(0,120,80,168);
	bar(0,216,80,264);
	bar(0,312,80,360);
	bar(0,408,80,456);
	
	puthz(1,36,"注册",24,24,BLACK);
	puthz(1,132,"上牌",24,24,BLACK);
	puthz(1,228,"年审",24,24,BLACK);
	puthz(1,324,"入校",24,24,BLACK);
	puthz(1,420,"报废",24,24,BLACK);
	
	

}

void page3_draw_1(){
	char a[5][30];
	strcpy(a[0],"年审申请结果");strcpy(a[1],"报废申请结果");strcpy(a[2],"入校申请结果"); 
	clrmous(MouseX,MouseY);
    cleardevice(); 
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0, 639, 39);
    setcolor(RED);
    line(600, 0, 639, 39);
    line(600, 39, 639, 0);
	setbkcolor(WHITE);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	setlinestyle(0,0,3);
	bar(0,24,80,72);
	bar(0,120,80,168);
	bar(0,216,80,264);
	bar(0,312,80,360);
	bar(0,408,80,456);
	puthz(1,36,"注册",24,24,BLACK);
	puthz(1,132,"上牌",24,24,BLACK);
	puthz(1,228,"年审",24,24,BLACK);
	puthz(1,324,"报废",24,24,BLACK);
	puthz(1,420,"入校",24,24,BLACK);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(90,0,100,640);
	for(int i=0;i<3;i++){
		bar(226,120+96*i,226+288,120+96*i+48);
		puthz(226+1,120+96*i+1,a[i],48,48,BLUE);
	}
	
}

