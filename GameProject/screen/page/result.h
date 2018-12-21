#pragma once
#ifndef PAGE_FIRSTRESULT
#define PAGE_FIRSTRESULT
#include "../../library/global.h"
#include "../../library/view.h"
#include<conio.h>

extern GamePlayer* player;

inline void show_result(GameRound* round) {
	int no;
	// 绘制游戏结束界面
	POINT pts[] = { {5,5},{611,5},{611,305},{5,305} };
	polygon(pts, 4);
	POINT pot[] = { {59,239},{59,270},{181,270},{181,239} };
	polygon(pot, 4);
	POINT pet[] = { {450,239},{450,270},{573,270},{573,239} };
	polygon(pet, 4);
	circle(450, 100, 70);
	char* strbuffer = (char*) calloc(133, sizeof(char));

	RECT rect = { 65,35, WINDOW_WIDTH, WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "Total Score: %15u", round->score);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 65,70, WINDOW_WIDTH, WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "Max Combo: %17u", round->max_combo);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 65,105, WINDOW_WIDTH, WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "Level: %21u", round->max_combo);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 65,140, WINDOW_WIDTH, WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "Experience: %16u", round->max_combo);;
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 80,248, WINDOW_WIDTH, WINDOW_HEIGHT };
	drawtext(_T("RECORD"), &rect, DT_SINGLELINE);

	rect = { 473,248, WINDOW_WIDTH, WINDOW_HEIGHT };
	drawtext(_T("CONTINUE"), &rect, DT_SINGLELINE);
	// 捕捉鼠标信息
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 59 && Mouse.x <= 181) && (Mouse.y >= 239 && Mouse.y <= 270)) {
			if (Mouse.mkLButton) {
				no = 1;   //判断是否点击游戏记录 (RECORD)
				break;
			}
		}
		else {
			if ((Mouse.x >= 450 && Mouse.x <= 573) && (Mouse.y >= 239 && Mouse.y <= 270)) {
				if (Mouse.mkLButton) {
					no = 2;   //判断是否点击 继续游戏 (CONTINUE)
					break;
				}
			}
		}
	}
	FlushMouseMsgBuffer();
	_getch();
	closegraph();
}
#endif
