#pragma once
#ifndef PAGE_GAME
#define PAGE_GAME
#include "../../library/control.h"
#include "result.h"

inline int show_game(GameMap* map, int difficulty = 0) {
	cleanup();
	put_background("loading.jpg");
	GameRound* round = game_event_loop(map, difficulty);
	//TODO: 游戏结束评分界面
	if(round == nullptr) {
		return 0;
	}
	return show_result(round);
}

#endif