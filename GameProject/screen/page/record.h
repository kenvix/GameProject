#pragma once
#ifndef PAGE_FIRSTGAME
#define PAGE_FIRSTGAME
#include "../../library/global.h"
#include "../../library/view.h"
#include <ctime>

extern GamePlayer* player;
extern GameRound* rounds_basic;
extern unsigned rounds_num;
extern FILE* file_player;

inline void show_record() {
	cleanup();
	put_background("record.jpg");
	draw_player_info();
	int role;
	char* strbuffer = (char*)calloc(133, sizeof(char));
	auto tm = (struct tm*) malloc(sizeof(struct tm));
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

	if(rounds_num >= 1) {
		GameRound current_round = rounds_basic[rounds_num - 1];
		GameMap* mapinfo = get_map_info(current_round.map);
		rect = { 183,124,WINDOW_WIDTH,WINDOW_HEIGHT };
		drawtext(_T(mapinfo->name), &rect, DT_SINGLELINE);
		rect = { 326,124,WINDOW_WIDTH,WINDOW_HEIGHT };
		drawtext(_T(mapinfo->description), &rect, DT_SINGLELINE);
		rect = { 430,124,WINDOW_WIDTH,WINDOW_HEIGHT };
		sprintf_s(strbuffer, 133, "%6u", current_round.max_combo);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
		rect = { 540,124,WINDOW_WIDTH,WINDOW_HEIGHT };
		sprintf_s(strbuffer, 133, "%6u", current_round.score);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
		rect = { 653,124,WINDOW_WIDTH,WINDOW_HEIGHT };
		localtime_s(tm, &current_round.time);
		strftime(strbuffer, 133, "%Y-%m-%d %H:%M:%S", tm);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
	}
	
	if(rounds_num >= 2) {
		GameRound current_round = rounds_basic[rounds_num - 2];
		GameMap* mapinfo = get_map_info(current_round.map);
		rect = { 183,229,WINDOW_WIDTH,WINDOW_HEIGHT };
		drawtext(_T(mapinfo->name), &rect, DT_SINGLELINE);
		rect = { 326,124,WINDOW_WIDTH,WINDOW_HEIGHT };
		drawtext(_T(mapinfo->description), &rect, DT_SINGLELINE);
		rect = { 430,229,WINDOW_WIDTH,WINDOW_HEIGHT };
		sprintf_s(strbuffer, 133, "%6u", current_round.max_combo);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
		rect = { 540,229,WINDOW_WIDTH,WINDOW_HEIGHT };
		sprintf_s(strbuffer, 133, "%6u", current_round.score);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
		rect = { 653,229,WINDOW_WIDTH,WINDOW_HEIGHT };
		localtime_s(tm, &current_round.time);
		strftime(strbuffer, 133, "%Y-%m-%d %H:%M:%S", tm);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
	}

	if(rounds_num >= 3) {
		GameRound current_round = rounds_basic[rounds_num - 1];
		GameMap* mapinfo = get_map_info(current_round.map);
		rect = { 183,341,WINDOW_WIDTH,WINDOW_HEIGHT };
		drawtext(_T(mapinfo->name), &rect, DT_SINGLELINE);
		rect = { 326 ,341,WINDOW_WIDTH,WINDOW_HEIGHT };
		drawtext(_T(mapinfo->description), &rect, DT_SINGLELINE);
		rect = { 395,341,WINDOW_WIDTH,WINDOW_HEIGHT };
		sprintf_s(strbuffer, 133, "%6u", current_round.max_combo);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
		rect = { 500,341,WINDOW_WIDTH,WINDOW_HEIGHT };
		sprintf_s(strbuffer, 133, "%6u", current_round.score);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
		rect = { 653,341,WINDOW_WIDTH,WINDOW_HEIGHT };
		localtime_s(tm, &current_round.time);
		strftime(strbuffer, 133, "%Y-%m-%d %H:%M:%S", tm);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
	}

	if(rounds_num >= 4) {
		GameRound current_round = rounds_basic[rounds_num - 1];
		GameMap* mapinfo = get_map_info(current_round.map);
		rect = { 183,448,WINDOW_WIDTH,WINDOW_HEIGHT };
		drawtext(_T(mapinfo->name), &rect, DT_SINGLELINE);
		rect = { 286,448,WINDOW_WIDTH,WINDOW_HEIGHT };
		drawtext(_T(mapinfo->description), &rect, DT_SINGLELINE);
		rect = { 395 ,448,WINDOW_WIDTH,WINDOW_HEIGHT };
		sprintf_s(strbuffer, 133, "%6u", current_round.max_combo);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
		rect = { 500,448,WINDOW_WIDTH,WINDOW_HEIGHT };
		sprintf_s(strbuffer, 133, "%6u", current_round.score);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
		rect = { 653,448,WINDOW_WIDTH,WINDOW_HEIGHT };
		localtime_s(tm, &current_round.time);
		strftime(strbuffer, 133, "%Y-%m-%d %H:%M:%S", tm);
		drawtext(_T(strbuffer), &rect, DT_SINGLELINE);
	}

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
	free(tm);
	free(strbuffer);
	FlushMouseMsgBuffer();
}

inline void show_rename() {
	char* name = (char*) calloc(512, sizeof(char));
	name[0] = '\0';
	InputBox(name, 511, "What's your name?", "Rename", player->name, 0, 0, false);
	if(strlen(name) > 1) {
		player->name_length = strlen(name);
		player->name = name;
		db_write_player(file_player, player);
	}
}

#endif