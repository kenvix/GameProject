#pragma once
#ifndef LIBRARY_CONTROL
#define LIBRARY_CONTROL
#include "function.h"
#include <wincrypt.h>
#include <synchapi.h>
#include <conio.h>
#include <set>
#include <map>

#define GRADE_PERFECT 0.1
#define GRADE_GOOD 0.2
#define GRADE_BAD 0.5

#define SCORE_PERFECT 100
#define SCORE_GOOD 50
#define SCORE_BAD 0
#define SCORE_MISS -10

const char game_valid_keys[] = {'A','S','D','J','K','L','a','s','d','j','k','l'};
const char game_keys[] = {'a','s','d','j','k','l'};

inline bool is_valid_key(int key) {
	for (char valid_key : game_valid_keys) {
		if(valid_key == key)
			return true;
	}
	return false;
}

inline std::vector<GameControl*> game_read_control(GameMap* map) {
	FILE* fs;
	errno = fopen_s(&fs, cat(cat("resource/map/", map->path),"/control.txt"), "r");
	fseek(fs, 0L, SEEK_END);
	unsigned size = ftell(fs);
	fseek(fs, 0L, SEEK_SET);
	std::vector<GameControl*> result;
	for (unsigned i = 0; feof(fs) != 1; i++) {
		int minute = -1;
		double second;
		char key;
		fscanf_s(fs, "%d:%lf %c\n", &minute, &second, &key);
		if(minute != -1) {
			GameControl* control = (GameControl*) calloc(1, sizeof(GameMap));
			control->key = key;
			control->time = (double) minute * 60 + second;
			result.insert(result.begin(), control);
		}
	}
	return result;
}

/**
 * 判定是否击中以及击打等级，并增加分数。（界限Y=406）
 * @param control 当前的控制数据
 * @param round 当前回合
 * @param time 击打时的相对播放时间
 * @return 击打等级，1=BAD 2=GOOD 3=PERFECT 0=INVALID
 */
inline unsigned int game_check_key(GameControl* control, GameRound* round, double time, char key) {
	double pressed_time = control->time - time;
	if(pressed_time > -GRADE_PERFECT && pressed_time < GRADE_PERFECT) {
		round->score += SCORE_PERFECT;
		
		return 3;
	} else if(pressed_time > -GRADE_GOOD && pressed_time < GRADE_GOOD) {
		round->score += SCORE_GOOD;

		return 2;
	} else if(pressed_time > -GRADE_BAD && pressed_time < GRADE_BAD) {
		round->score += SCORE_BAD;

		return 1;
	}
	return 0;
}

/**
 * TODO: 绘制条子
 */
inline void draw_game_stick(GameControl* control) {
	
}

/**
 * 播放游戏背景音乐，并阻塞线程直到开始播放
 */
inline void game_play_music(GameMap* map) {
	music_stop();
	music_play(map->path, "map", true);
}

/**
 * 游戏事件循环
 * @param map 地图对象
 * @param control 控制向量
 */
inline GameRound* game_event_loop(GameMap* map, std::vector<GameControl*> control) {
	GameRound* round = (GameRound*) calloc(1, sizeof(GameRound));
	std::map<char, std::vector<GameControl*>> accepting_keys;
	for (const char game_key : game_keys)
		accepting_keys[game_key] = std::vector<GameControl*>();

	game_play_music(map);
	//ready to start timer
	for (unsigned time = 0; time < map->time; time += 0.015) {
		unsigned control_size = control.size();
		if(control_size > 0) {
			GameControl* head_control = control[control_size-1];
			if(head_control->time >= time) {
				control.pop_back();
				draw_game_stick(head_control);
				std::vector<GameControl*> target = accepting_keys[head_control->key];
				target.insert(target.begin(), head_control);
			}
		}
		for (const char game_key : game_keys) {
			std::vector<GameControl*> querying_accepting_keys = accepting_keys[game_key];
			if(!querying_accepting_keys.empty()) {
				if(time - querying_accepting_keys[querying_accepting_keys.size()-1]->time > GRADE_BAD) {
					querying_accepting_keys.pop_back();
					//TODO: STATUS MISS
					round->score += SCORE_MISS;
				}
			}
		}
		if(_kbhit() != 0) {
			int key = _getch();
			if(is_valid_key(key)) {
				key = get_game_key(key);
				if(!accepting_keys[key].empty()) {
					GameControl* current_control = accepting_keys[key][accepting_keys[key].size()-1];
					if(abs(time - current_control->time) < GRADE_BAD) {
						game_check_key(current_control, round, time, key); //TODO: Play efforts for bad/good/perfect
					}
				}
			}
		}
		Sleep(15);
	}
	return round;
}
#endif