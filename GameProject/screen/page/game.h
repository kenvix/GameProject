#pragma once
#ifndef PAGE_GAME
#define PAGE_GAME
#include "../../library/control.h"

inline void show_game(GameMap* map) {
	put_background("game-hard.jpg");
	const std::vector<GameControl*> controls = game_read_control(map);
	GameRound* round = game_event_loop(map, controls);
	//TODO: 游戏结束评分界面
}

#endif