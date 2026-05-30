#include "common.h"

#define MAX_USER_CNT 100
#define USER_PER_PAGE 4
#define FILE_PATH "C:\\CODE\\SOURCE\\USER\\total.txt"

int load_usernames();            
void draw_ui_once();             
void update_page_content(int cur_page); 
 

int g_user_total = 0;            
int g_total_page = 0;            
char g_usernames[MAX_USER_CNT][20] = {0}; 

char* p4() {
    
    
    setbkcolor(WHITE);
    clrmous(MouseX, MouseY);
    cleardevice();
    setcolor(BLACK);

    g_user_total = load_usernames();
    g_total_page = (g_user_total == 0) ? 1 : (g_user_total + 3) / 4;

    draw_ui_once();
    update_page_content(1);

    int cur_page = 1;
    int exit_flag = 0;
    int last_page = 1;
    int new_hover[4];
    int hover_state[4] = {0, 0, 0, 0};

    while (!exit_flag) {
        // ========== 关键修改：使用 newmouse 替代手动绘制 ==========
        // newmouse 内部会自动处理：清除旧光标->保存新背景->绘制新光标
        // 只有当鼠标真正移动时才会重绘，因此不会闪烁
        newmouse(&MouseX , &MouseY , &press);
        
        
        new_hover[0] = check_mouse_click(0, 0, 320, 120);
        new_hover[1] = check_mouse_click(0, 120, 320, 240);
        new_hover[2] = check_mouse_click(0, 240, 320, 360);
        new_hover[3] = check_mouse_click(0, 360, 320, 480);
        
        // 只重绘状态发生变化的框，减少闪烁
        for (int i = 0; i < 4; i++) {
            if (new_hover[i] != hover_state[i]) {
                int y1 = i * 120+3;
                int y2 = y1 + 120-3;
                
                // 重绘该框的边框
                clrmous(MouseX, MouseY);
                setcolor(new_hover[i] ? RED : YELLOW);
                setlinestyle(0, 0, 3);  // 保持3像素宽度一致
                rectangle(0, y1, 320, y2);
                
                hover_state[i] = new_hover[i];
            }
        } 
        
		// ========== 检测点击（无操作时不做任何事） ==========
        if (press == 1) {
            // 上一页按钮（344,46 → 446,76）
            if (check_mouse_click(344, 46, 446, 76) && cur_page > 1) {
                cur_page--;
                delay(100); 
            }
            // 下一页按钮（344,406 → 446,436）
            else if (check_mouse_click(344, 406, 446, 436) && cur_page < g_total_page) {
                cur_page++;
                delay(100);
            }
            // 退出按钮（600,0 → 639,39）
            else if (check_mouse_click(600, 0, 639, 39)) {
                return "111";
            }
            // 等待按键释放，防止连续触发
            else if(check_mouse_click(0, 0, 320, 120)){
            	return g_usernames[cur_page*4-4];
			}
			else if(check_mouse_click(0, 0+120, 320, 120+120)){
            	return g_usernames[cur_page*4-4+1];
			}
			else if(check_mouse_click(0, 0+120+120, 320, 120+120+120)){
            	return g_usernames[cur_page*4-4+2];
			}
			else if(check_mouse_click(0, 0+120+120+120, 320, 120+120+120+120)){
            	return g_usernames[cur_page*4-4+3];
			}
            while (press == 1) {
                newmouse(&MouseX , &MouseY , &press);
            }
        }

        // ========== 仅页码变化时更新内容 ==========
        if (cur_page != last_page) {
            // 翻页时先隐藏鼠标，避免绘制残影
            clrmous(MouseX, MouseY);
            update_page_content(cur_page);
            last_page = cur_page;
            
            // 翻页后恢复鼠标显示（如果需要的话，newmouse下次循环会自动处理）
        }

        delay(20);
    }

    return NULL;
}

int load_usernames() {
    FILE *fp = fopen(FILE_PATH, "rt");
    if (fp == NULL) return 0;

    char buffer[100] = {0};
    int count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && count < MAX_USER_CNT) {
        buffer[strcspn(buffer, "\n\r")] = '\0';
        if (strlen(buffer) > 0) {
            strncpy(g_usernames[count], buffer, 19);
            count++;
        }
        memset(buffer, 0, sizeof(buffer));
    }
    fclose(fp);
    return count;
}

void draw_ui_once() {
    setcolor(YELLOW);
    setlinestyle(0, 0, 3);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    for (int i = 0; i < USER_PER_PAGE; i++) {
        int y1 = i * 120;
        rectangle(0, y1, 320, y1 + 120);
        bar(1, y1 + 1, 319, y1 + 119); 
    }

    // 上一页按钮
    rectangle(344, 46, 446, 76);
    // 下一页按钮
    rectangle(344, 406, 446, 436);
    // 退出按钮
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(600, 0, 639, 39);
    setcolor(RED);
    line(600, 0, 639, 39);
    line(600, 39, 639, 0);

    
}

void update_page_content(int cur_page) {
    int start_idx = (cur_page - 1) * USER_PER_PAGE;

    // 清空4个显示框的文字区
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    for (int i = 0; i < USER_PER_PAGE; i++) {
        int y1 = i * 120;
        bar(5, y1 + 5, 315, y1 + 115); 
    }

    // 绘制当前页用户名
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    setcolor(BLACK);  // 修复：settextcolor -> setcolor
    for ( i = 0; i < USER_PER_PAGE; i++) {
        char text[20] = "";
        if (start_idx + i < g_user_total) {
            strcpy(text, g_usernames[start_idx + i]);
        }
        int y1 = i * 120;
        int x = 160 - textwidth(text)/2;
        int y = y1 + 60 - textheight(text)/2;
        outtextxy(x, y, text);
    }

    // 更新按钮状态
    // 上一页按钮
    setfillstyle(SOLID_FILL, cur_page == 1 ? DARKGRAY : GREEN);
    bar(345, 47, 445, 75);
    puthz(354, 50, "上一页", 24, 24, WHITE);
    
    // 下一页按钮
    setfillstyle(SOLID_FILL, cur_page == g_total_page ? DARKGRAY : GREEN);
    bar(345, 407, 445, 435);
    puthz(354, 410, "下一页", 24, 24, WHITE);

}


