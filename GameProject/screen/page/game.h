#pragma once
#ifndef PAGE_FIRSTGAME
#define PAGE_FIRSTGAME
#include "../../library/global.h"
#include "../../library/view.h"

inline void draw_map_selection_info(std::string path) {
	GameMap* info = get_map_info(path.c_str());

}

inline void show_game() {
	cleanup();
	put_background("game.jpg");
	draw_player_info();
	int role;
	RECT rect = { 226,25,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Hellow"), &rect, DT_SINGLELINE);
	RECT rect = { 484,25,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("JIA"), &rect, DT_SINGLELINE);
	RECT rect = { 783,25,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Shuai"), &rect, DT_SINGLELINE);
	RECT rect = { 183,116,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("peng"), &rect, DT_SINGLELINE);
	RECT rect = { 183,224,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("lu"), &rect, DT_SINGLELINE);
	RECT rect = { 183,338,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Rui"), &rect, DT_SINGLELINE);
	RECT rect = { 183,448,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("feng"), &rect, DT_SINGLELINE);
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 60 && Mouse.x <= 105) && (Mouse.y >= 200 && Mouse.x <= 315)) {
			if (Mouse.mkLButton) {
				role = 1;//打印左边的返回
				break;
			}
			else {
				if ((Mouse.x >= 915 && Mouse.x <= 957) && (Mouse.y >= 200 && Mouse.y <= 315)) {
					if (Mouse.mkLButton) {
						role = 2;//打印右边的返回
						break;
					}
				}
			}
		}
	}
	FlushMouseMsgBuffer();
	return role;
}
#endif