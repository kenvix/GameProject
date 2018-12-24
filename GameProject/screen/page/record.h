#pragma once
#ifndef PAGE_FIRSTGAME
#define PAGE_FIRSTGAME
#include "../../library/global.h"
#include "../../library/view.h"

extern GamePlayer* player;
extern GameRound* rounds_basic;
extern unsigned rounds_num;
inline void show_record() {
	cleanup();
	put_background("record.jpg");
	draw_player_info();
	int role;
	char* strbuffer = (char*)calloc(133, sizeof(char));
	RECT rect = { 233,15,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Max Combo"), &rect, DT_SINGLELINE);
	rect = { 233,35,WINDOW_WIDTH,WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, " %6u", player->max_combo);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 484,15,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Max Score"), &rect, DT_SINGLELINE);
	rect = { 484,35,WINDOW_WIDTH,WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "%6u", player->max_score);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 740,15,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("Experience"), &rect, DT_SINGLELINE);
	rect = { 740,35,WINDOW_WIDTH,WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "%6u", player->experience);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 183,124,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("FIRST"), &rect, DT_SINGLELINE);

	rect = { 183,229,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("SECOND"), &rect, DT_SINGLELINE);

	rect = { 183,341,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("THIRD"), &rect, DT_SINGLELINE);

	rect = { 183,448,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(_T("FORTH"), &rect, DT_SINGLELINE);
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 60 && Mouse.x <= 105) && (Mouse.y >= 200 && Mouse.x <= 315)) {
			if (Mouse.mkLButton) {
				role = 1;//打印左边的返回
				break;
			}
		} else {
			if ((Mouse.x >= 915 && Mouse.x <= 957) && (Mouse.y >= 200 && Mouse.y <= 315)) {
				if (Mouse.mkLButton) {
					role = 2;//打印右边的返回
					break;
				}
			}
		}
	}
	FlushMouseMsgBuffer();
}
#endif