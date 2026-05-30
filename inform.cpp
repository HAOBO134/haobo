#include "common.h"
#include "inform.h"
#include <ctype.h>

void user_information_get(User_information *information,char *username)
{
	if (information == NULL) {
        printf("错误：结构体指针为空！\n");
        return;
    }
	FILE *fp;
	char buffer[50];
	char path[100]="C:\\CODE\\SOURCE\\USER\\";
	strcat(path,username);
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
			        trim_newline1(information->password);
			        buffer[0]='\0';
			        break;
			case 1: strcpy(information->car_name,buffer);
			         trim_newline1(information->car_name);
	                buffer[0]='\0';	
					break;	
			case 2: strcpy(information->city,buffer+6);
			        trim_newline1(information->city);
					buffer[0]='\0';
			        break;
			case 3: strcpy(information->car_plate,buffer+8);
                    trim_newline1(information->car_plate);
					buffer[0]='\0';
					break;    			
		}
	}
	fclose(fp);
}

int scrap_information_get(Scrap_information *information,char *username)
{
	if (information == NULL) {
        printf("错误：结构体指针为空！\n");
        return 3;
    }
    char path[60];
    char buffer[50];
    sprintf(path,"C:\\CODE\\SOURCE\\USER\\%sscrap.txt",username);
    FILE *fp=fopen(path,"rt");
    if(!fp) return 0;
    for(int i=0;i<4;i++)
	{
		fgets(buffer,sizeof(buffer),fp);
		switch(i){
			case 0: strcpy(information->username,buffer+9);
			        trim_newline1(information->username);
			        buffer[0]='\0';
			        break;
			case 1: strcpy(information->car_name,buffer+9);
			         trim_newline1(information->car_name);
	                buffer[0]='\0';	
					break;	
			case 2: strcpy(information->reason_code,buffer+12);
			        trim_newline1(information->reason_code);
					buffer[0]='\0';
			        break;
			case 3: strcpy(information->status,buffer+7);
                    trim_newline1(information->status);
					buffer[0]='\0';
					break;    			
		}
	}
	fclose(fp);
	return 1;
    
}

int admission_information_get(char *username,char *time,char *location,char *park,char *status,int *month,int *day)
{
	FILE *fp0,*fp1,*fp2;
	char path[4][50];
	char buffer[50];
	sprintf(path[0],"C:\\CODE\\SOURCE\\USER\\%stime.txt",username);
	sprintf(path[1],"C:\\CODE\\SOURCE\\USER\\%slocat.txt",username);
	sprintf(path[2],"C:\\CODE\\SOURCE\\USER\\%spark.txt",username);
	fp0=fopen(path[0],"rt");fp1=fopen(path[1],"rt");fp2=fopen(path[2],"rt");
	if(!fp0||!fp1||!fp2) return 0;//入校信息不完善 
	fgets(buffer,sizeof(buffer),fp0);
	strcpy(time,buffer+6);
	buffer[0]='\0';
	fgets(buffer,sizeof(buffer),fp0);
	strcpy(status,buffer+7);
	buffer[0]='\0';
	fgets(buffer,sizeof(buffer),fp1);
	strcpy(location,buffer+10);
	buffer[0]='\0';
	fgets(buffer,sizeof(buffer),fp2);
	strcpy(park,buffer+6);
	buffer[0]='\0';
	fclose(fp0);fclose(fp1);fclose(fp2);
	time_handle(time,month,day);
	fclose(fp0);fclose(fp1);fclose(fp2);
	return 1;
	
}

void trim_newline1(char *s)
{
	if(!s) return;
	size_t len=strlen(s);
	while(len>0&&(s[len-1]=='\n'||s[len-1]=='\r'))
	{
		s[len-1]='\0';
		len--;
	}
}




void time_handle(char *time, int *month, int *day)
{
    *month = 0;
    *day = 0;
    char *p;

    // 找“年”
    p = strstr(time, "年");
    if (!p) return;
    p += 2;   // GBK中文占2字节
    // 解析月份
    while (*p && strncmp(p, "月", 2) != 0) {
        if (isdigit((unsigned char)*p)) {
            *month = *month * 10 + (*p - '0');
        }
        p++;
    }
    if (!*p) return;
    p += 2;
    // 解析日期
    while (*p && strncmp(p, "日", 2) != 0) {
        if (isdigit((unsigned char)*p)) {
            *day = *day * 10 + (*p - '0');
        }
        p++;
    }
}
	


	

