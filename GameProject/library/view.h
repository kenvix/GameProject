#pragma once
#ifndef LIBRARY_VIEW
#define LIBRARY_VIEW
#include <cstdio>
#include <graphics.h>
#include "function.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "kComposer"

extern GamePlayer* player;
extern GameRound* rounds_basic;
extern unsigned rounds_num;

/**
 * 初始化预设背景图
 */
inline IMAGE put_background(const char* path, int x = 0, int y = 0) {
	IMAGE background;
	loadimage(&background, cat("resource/background/", path));
	putimage(x, y, &background);
	setbkmode(TRANSPARENT);
	return background;
}

/**
 * 创建窗体
 */
inline HWND create_window() {
	printf("Initializing graph %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
#ifdef _DEBUG
		HWND window = initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, SHOWCONSOLE);
	    SetWindowText(window, cat(WINDOW_TITLE, " [Debug+Cheat]"));
#else 
		HWND window = initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
		SetWindowText(window, WINDOW_TITLE);
#endif
	RECT r = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

	if(dir_exists("resource/background")) {
		drawtext(_T("Loading resources ... (Check the accessibility of resources if there is no response)"), &r, DT_SINGLELINE);
	} else {
		drawtext(_T("Unable to load kComposer: resources not found."), &r, DT_SINGLELINE);
	}
	put_background("loading.jpg");
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
 * 清除所有内容，在渲染新页前使用
 */
inline void cleanup() {
	cleardevice();
}

/**
 * 绘制简要玩家信息
 */
inline void draw_player_info() {
	IMAGE img;
	loadimage(&img, _T("resource/image/player.jpg"));
	putimage(10, WINDOW_HEIGHT - 50, &img);
	RECT r1 = {60, WINDOW_HEIGHT - 50, WINDOW_WIDTH, WINDOW_HEIGHT};
	settextstyle(18, 0, _T("Consolas"));
	drawtext(_T(player->name), &r1, DT_SINGLELINE);
	RECT r2 = {60, WINDOW_HEIGHT - 30, WINDOW_WIDTH, WINDOW_HEIGHT};
	char info[300];
	sprintf_s(info, "Lv. %2u / Exp %llu", player->level, player->experience);
	drawtext(_T(info), &r2, DT_SINGLELINE);
}

#endif