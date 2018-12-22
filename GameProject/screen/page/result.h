#pragma once
#ifndef PAGE_RESULT
#define PAGE_RESULT
#include "../../library/global.h"
#include "../../library/view.h"
#include<conio.h>

extern GamePlayer* player;
extern GameRound* rounds_basic;
extern unsigned rounds_num;

extern FILE* file_player;
extern FILE* file_rounds_basic;
extern FILE* file_rounds_index;

inline void apply_game_result(GameRound* round) {
	if(player->max_combo < round->max_combo)
		player->max_combo = round->max_combo;
	if(round->score > 0) {
		player->experience += round->score;
		if(player->max_score < round->score)
			player->max_score = round->score;
		if(get_level_experience(player->level + 1) <= player->experience)
			player->level++;
	}
	db_write_player(file_player, player);
	//db_write_rounds(file_rounds_basic, file_rounds_index, round, )
}

inline int show_result(GameRound* round) {
	int no;
	// 绘制游戏结束界面
	POINT pts[] = { {193,129},{802,129},{802,433},{193,433} };
	polygon(pts, 4);
	setfillcolor(BLACK);
	fillrectangle(193,129,802,433);
	POINT pot[] = { {221,365},{413,365},{413,406},{221,406} };
	polygon(pot, 4);
	POINT pet[] = { {576,365},{770,365},{770,406},{576,406} };
	polygon(pet, 4);
	circle(670, 227, 70);
	char* strbuffer = (char*) calloc(133, sizeof(char));

	apply_game_result(round);

	RECT rect = { 250,175, WINDOW_WIDTH, WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "Total Score: %15u", round->score);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 250,210, WINDOW_WIDTH, WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "Max Combo: %17u", round->max_combo);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 250,245, WINDOW_WIDTH, WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "Level: %21u", player->level);
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 250,280, WINDOW_WIDTH, WINDOW_HEIGHT };
	sprintf_s(strbuffer, 133, "Experience: %16llu", player->experience);;
	drawtext(_T(strbuffer), &rect, DT_SINGLELINE);

	rect = { 285,377, WINDOW_WIDTH, WINDOW_HEIGHT };
	drawtext(_T("RECORD"), &rect, DT_SINGLELINE);

	rect = { 640,377, WINDOW_WIDTH, WINDOW_HEIGHT };
	drawtext(_T("CONTINUE"), &rect, DT_SINGLELINE);
	// 捕捉鼠标信息
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 221 && Mouse.x <= 413) && (Mouse.y >= 365 && Mouse.y <= 406)) {
			if (Mouse.mkLButton) {
				no = 1;   //判断是否点击游戏记录 (RECORD)
				break;
			}
		}
		else {
			if ((Mouse.x >= 576 && Mouse.x <= 770) && (Mouse.y >= 365 && Mouse.y <= 406)) {
				if (Mouse.mkLButton) {
					no = 0;   //判断是否点击 继续游戏 (CONTINUE)
					break;
				}
			}
		}
	}
	FlushMouseMsgBuffer();
	return no;
}
#endif
