#pragma once
#ifndef LIBRARY_VIEW
#define LIBRARY_VIEW
#include <cstdio>
#include <graphics.h>
#include "function.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600


/**
 * 创建窗体
 */
inline HWND create_window() {
	printf("Initializing graph %dx%d", WINDOW_WIDTH, WINDOW_HEIGHT);
#ifdef _DEBUG
		HWND window = initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, SHOWCONSOLE);
#else 
		HWND window = initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
#endif
	SetWindowText(window, "kComposer");
	return window;
}

/**
 * 获取可用于绘制字的RECT
 */
inline RECT* get_rect() {
	RECT r = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	return &r;
}

/**
 * 初始化预设背景图
 */
inline IMAGE put_background(const char* path) {
	IMAGE background;
	loadimage(&background, cat("resource/background/", path));
	putimage(0, 0, &background);
	return background;
}

/**
 * 清除所有内容，在渲染新页前使用
 */
inline void cleanup() {
	cleardevice();
}

#endif