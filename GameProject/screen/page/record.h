#pragma once
#ifndef PAGE_FIRSTGAME
#define PAGE_FIRSTGAME
#include "../../library/global.h"
#include "../../library/view.h"

inline void show_record(GamePlayer* player) {
	cleanup();
	put_background("record.jpg");
	draw_player_info();
	int role;
	RECT rect = { 233,15,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Max Combo"), &rect, DT_SINGLELINE);
	rect = { 233,35,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("666666"), &rect, DT_SINGLELINE);

	rect = { 484,15,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Max Score"), &rect, DT_SINGLELINE);
	rect = { 484,35,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("8888888"), &rect, DT_SINGLELINE);

	rect = { 783,15,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Experience"), &rect, DT_SINGLELINE);
	rect = { 183,116,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("peng"), &rect, DT_SINGLELINE);
	rect = { 183,224,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("lu"), &rect, DT_SINGLELINE);
	rect = { 183,338,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Rui"), &rect, DT_SINGLELINE);
	rect = { 183,448,WINDOW_WIDTH,WINDOW_HEIGHT };
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
}
#endif