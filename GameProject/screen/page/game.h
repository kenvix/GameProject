#pragma once
#ifndef PAGE_GAME
#define PAGE_GAME
#include "../../library/control.h"
#include "result.h"

inline int show_game(GameMap* map) {
	cleanup();
	put_background("game-hard.jpg");
	std::vector<GameControl*> controls = game_read_control(map);
	GameRound* round = game_event_loop(map, &controls);
	//TODO: 游戏结束评分界面
	if(round == nullptr) {
		return 0;
	}
	for (GameControl* control : controls)
		free(control);
	return show_result(round);
}

#endif