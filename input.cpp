#include"common.h" 
#include "input.h"



//在(x,y)位置进行文本输入并显示，把最终结果拷贝到char *output中 
/**int input_text(int x, int y, char *output,draw_fn_t redraw)
{
    char buffer[20] = {0}; // 内部缓存，最多8个有效字符 + \0
    int key, len;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    while (1)
    {
        // 实时显示输入内容
        setcolor(BLUE);
        outtextxy(x, y, buffer);
        newmouse(&MouseX, &MouseY, &press);
        if (kbhit())
        {
            key = bioskey(0);
            char ch = key & 0xFF;
            // 按 ENTER 键确认输入，退出函数
            if (ch == '\r')
            {
                
                if (strlen(buffer) == 0)
              {
                clrmous(MouseX, MouseY);
                setfillstyle(1, YELLOW);
                bar(150, 160, 490, 300);
                setcolor(BLACK);
                setlinestyle(0, 0, 3);
                rectangle(151, 161, 489, 299);
                puthz(173, 200, "请输入您的用户名", 24, 30, BLACK);

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
                redraw();
              }
				else
				{strcpy(output, buffer);
				 redraw();   // 把结果复制到外部数组
                 return 1;}
            }
            
            
            
			// ================= 退格键 =================
            else if (ch == '\b')
            {
                len = strlen(buffer);
                if (len > 0)
                {
                    buffer[len - 1] = '\0';

                    // 清空输入框区域（黄色背景）
                    clrmous(MouseX, MouseY);
                    setfillstyle(SOLID_FILL, YELLOW);
                    bar(x, y, x + 300, y + 42);
                }
            }

            // ================= 超过8位提示 =================
            else if (strlen(buffer) >= 8)
            {
                clrmous(MouseX, MouseY);
                setfillstyle(1, YELLOW);
                bar(150, 160, 490, 300);
                setcolor(BLACK);
                setlinestyle(0, 0, 3);
                rectangle(151, 161, 489, 299);
                puthz(173, 200, "用户名长度请勿超过八", 24, 30, BLACK);

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
                redraw();
            }

            // ================= 合法字符 =================
            else if ((ch >= 'a' && ch <= 'z') ||
                     (ch >= 'A' && ch <= 'Z') ||
                     (ch >= '0' && ch <= '9') ||
                     (ch == '_'))
            {
                len = strlen(buffer);
                buffer[len] = ch;
                buffer[len + 1] = '\0';
            }

            // ================= 非法字符提示 =================
            else
            {
                clrmous(MouseX, MouseY);
                setfillstyle(1, YELLOW);
                bar(150, 160, 490, 300);
                setcolor(BLACK);
                setlinestyle(0, 0, 3);
                rectangle(151, 161, 489, 299);
                puthz(173, 200, "请输入大小写字母、数", 24, 30, BLACK);
                puthz(248, 235, "字或下划线", 24, 30, BLACK);

                // 延时等待关闭
                for (int i = 0; i < 500; i++)
                {
                    delay(1);
                    if (kbhit()) bioskey(0);
                    newmouse(&MouseX, &MouseY, &press);
                }

                // 清空提示
                setfillstyle(SOLID_FILL, WHITE);
                bar(150, 160, 490, 300);
                redraw();
            }

            
            
        }

        // 实时更新鼠标
        newmouse(&MouseX, &MouseY, &press);
        delay(20);
    }
}
**/
int input_text(int x, int y, char *output, draw_fn_t redraw)
{
    const int MAX_INPUT_LEN = 8;
    char buffer[MAX_INPUT_LEN + 1] = {0}; // 本地缓冲，最多 MAX_INPUT_LEN 个字符
    int key, len;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    // 不要无条件清空外部 output
    if (output && output[0] != '\0') {
        strncpy(buffer, output, MAX_INPUT_LEN);
        buffer[MAX_INPUT_LEN] = '\0';
    }

    // 初次显示已有内容
    setcolor(BLUE);
    outtextxy(x, y, buffer);

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        // 显示当前缓冲
        setcolor(BLUE);
        outtextxy(x, y, buffer);

        if (kbhit())
        {
            key = bioskey(0);
            char ch = key & 0xFF;

            if (ch == '\r') {
                if (strlen(buffer) == 0) {
                    // 提示不能为空（保持原有提示逻辑）
                    clrmous(MouseX, MouseY);
                    setfillstyle(1, YELLOW);
                    bar(150, 160, 490, 300);
                    setcolor(BLACK);
                    setlinestyle(0, 0, 3);
                    rectangle(151, 161, 489, 299);
                    puthz(173, 200, "请输入用户名", 24, 30, BLACK);
                    for (int i = 0; i < 500; i++) {
                        delay(1);
                        if (kbhit()) bioskey(0);
                        newmouse(&MouseX, &MouseY, &press);
                    }
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(150, 160, 490, 300);
                    if (redraw) redraw();
                } else {
                    // 成功：把本地 buffer 写回 output
                    if (output) {
                        strncpy(output, buffer, MAX_INPUT_LEN);
                        output[MAX_INPUT_LEN] = '\0';
                    }
                    return 1;
                }
            }
            else if (ch == '\b') {
                len = strlen(buffer);
                if (len > 0) {
                    buffer[len - 1] = '\0';
                    // 清除输入显示区域并重绘 buffer
                    clrmous(MouseX, MouseY);
                    setfillstyle(SOLID_FILL, YELLOW);
                    bar(x, y, x + 300, y + 42);
                    setcolor(BLUE);
                    outtextxy(x, y, buffer);
                }
            }
            else if (strlen(buffer) >= MAX_INPUT_LEN) {
                // 超长提示（保持原逻辑）
                clrmous(MouseX, MouseY);
                setfillstyle(1, YELLOW);
                bar(150, 160, 490, 300);
                setcolor(BLACK);
                setlinestyle(0, 0, 3);
                rectangle(151, 161, 489, 299);
                puthz(173, 200, "用户名不能超过8位", 24, 30, BLACK);
                for (int i = 0; i < 500; i++) {
                    delay(1);
                    if (kbhit()) bioskey(0);
                    newmouse(&MouseX, &MouseY, &press);
                }
                setfillstyle(SOLID_FILL, WHITE);
                bar(150, 160, 490, 300);
                if (redraw) redraw();
            }
            else if ((ch >= 'a' && ch <= 'z') ||
                     (ch >= 'A' && ch <= 'Z') ||
                     (ch >= '0' && ch <= '9') ||
                     (ch == '_')) {
                len = strlen(buffer);
                if (len < MAX_INPUT_LEN) {
                    buffer[len] = ch;
                    buffer[len + 1] = '\0';
                    setcolor(BLUE);
                    outtextxy(x, y, buffer);
                }
            }
            else {
                // 非法字符提示（不修改 output）
                clrmous(MouseX, MouseY);
                setfillstyle(1, YELLOW);
                bar(150, 160, 490, 300);
                setcolor(BLACK);
                setlinestyle(0, 0, 3);
                rectangle(151, 161, 489, 299);
                puthz(173, 200, "只允许字母、数字和下划线", 24, 30, BLACK);
                for (int i = 0; i < 500; i++) {
                    delay(1);
                    if (kbhit()) bioskey(0);
                    newmouse(&MouseX, &MouseY, &press);
                }
                setfillstyle(SOLID_FILL, WHITE);
                bar(150, 160, 490, 300);
                if (redraw) redraw();
            }
        }

        delay(20);
    }
}

