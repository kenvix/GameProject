#pragma once
#ifndef PAGE_FIRSTRESULT
#define PAGE_FIRSTRESULT
#include "../../library/global.h"
#include "../../library/view.h"
#include<conio.h>
inline void show_result(GameRound* round,GamePlayer* player) {
	int no;
	// 绘制游戏结束界面
	initgraph(616, 310);
	POINT pts[] = { {5,5},{611,5},{611,305},{5,305} };
	polygon(pts, 4);
	POINT pot[] = { {59,239},{59,270},{181,270},{181,239} };
	polygon(pot, 4);
	POINT pet[] = { {450,239},{450,270},{573,270},{573,239} };
	polygon(pet, 4);
	circle(450, 100, 70);
	RECT rect = { 65,35,616,310 };
	drawtext(_T("Total Score:"), &rect, DT_SINGLELINE);
	rect = { 150,35,616,310 };
	drawtext(_T(round->score), &rect, DT_SINGLELINE);

	rect = { 65,70,616,310 };
	drawtext(_T("Max Combo:"), &rect, DT_SINGLELINE);
	rect = { 150,70,616,310 };
	drawtext(_T(round->max_combo), &rect, DT_SINGLELINE);

	rect = { 65,105,616,310 };
	drawtext(_T("Level:"), &rect, DT_SINGLELINE);
	rect = { 150,105,616,310 };
	drawtext(_T(player->level), &rect, DT_SINGLELINE);

	rect = { 65,140,616,310 };
	drawtext(_T("Experince:"), &rect, DT_SINGLELINE);
	rect = { 150,140,616,310 };
	drawtext(_T(player->experience), &rect, DT_SINGLELINE);

	rect = { 80,248,616,310 };
	drawtext(_T("RECORD"), &rect, DT_SINGLELINE);

	rect = { 473,248,616,310 };
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
