#ifndef LIBRARY_VIEW
#define LIBRARY_VIEW
#include <cstdio>
#include <graphics.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

IMAGE global_background;
HWND global_window = nullptr;

/**
 * 创建窗体
 */
inline void create_window() {
	if(global_window == NULL) {
		printf("Initializing graph %dx%d", WINDOW_WIDTH, WINDOW_HEIGHT);
	#ifdef _DEBUG
		global_window = initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, SHOWCONSOLE);
	#else 
		global_window = initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
	#endif
	}
}

/**
 * 初始化预设背景图
 */
inline void put_background() {
	loadimage(&global_background, "resource/background/global_background.jpg");
	putimage(0, 0, &global_background);
}

#endif