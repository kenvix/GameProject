#pragma once
#ifndef LIBRARY_CONTROL
#define LIBRARY_CONTROL
#include "function.h"
#include <wincrypt.h>
#include <synchapi.h>
#include <conio.h>
#include <set>
#include <map>
#include <unordered_map>

#define GRADE_PERFECT 0.1
#define GRADE_GOOD 0.2
#define GRADE_BAD 0.5

#define SCORE_PERFECT 100
#define SCORE_GOOD 50
#define SCORE_BAD 0
#define SCORE_MISS -10

//条子起始位置
#define STICK_INIT_POSITION 20
//条子步进长度
#define STICK_STEP_LENGTH 5.1
//条子提前绘制时间
#define STICK_ADVANCE_TIME 3
//条子步进时间
#define STICK_STEP_TIME 0.015L 

#define STICK_WIDTH 67
#define STICK_HEIGHT 38

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
			GameControl* control = (GameControl*) calloc(1, sizeof(GameControl));
			control->key = key;
			control->time = (double) minute * 60 + second;
			control->position = -1;
			control->image = nullptr;
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

inline int get_stick_x_position(GameControl* control) {
	switch (control->key) {
		case 'a':
			return 20;
			break;
		
		case 's':
			return 120;
			break;
		
		case 'd':
			return 220;
			break;
		
		case 'j':
			return 320;
			break;
		
		case 'k':
			return 420;
			break;
		
		case 'l':
			return 520;
			break;
	}
	return 0;
}

/**
 * TODO: 绘制条子
 */
inline void draw_game_stick(GameControl* control, IMAGE* image, IMAGE* cache) {
	int y = control->position;
	int x = get_stick_x_position(control);
	if(control->position == -1) {
		control->position = STICK_INIT_POSITION;
		loadimage(image, "resource/image/stick.jpg", STICK_WIDTH, STICK_HEIGHT, true);
		getimage(cache, x, y, STICK_WIDTH, STICK_HEIGHT);
	} else {
		putimage(x, y, cache);
	}
	y = control->position += STICK_STEP_LENGTH;
	getimage(cache, x, y, STICK_WIDTH, STICK_HEIGHT);
	putimage(x, y, image);
}

inline void hide_game_stick(GameControl* control, IMAGE* cache) {
	int y = control->position;
	int x = get_stick_x_position(control);
	putimage(x, y, cache);
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
inline GameRound* game_event_loop(GameMap* map, std::vector<GameControl*>* control) {
	GameRound* round = (GameRound*) calloc(1, sizeof(GameRound));
	std::map<char, std::vector<GameControl*>> accepting_keys;
	std::unordered_map<GameControl*, IMAGE> images;
	std::unordered_map<GameControl*, IMAGE> old_images;
	for (const char game_key : game_keys)
		accepting_keys[game_key] = std::vector<GameControl*>();

	game_play_music(map);
	//ready to start timer
	RECT common_rect = {WINDOW_WIDTH - 230, WINDOW_HEIGHT - 40, WINDOW_WIDTH, WINDOW_HEIGHT};
	RECT timer_rect = {WINDOW_WIDTH - 230, WINDOW_HEIGHT - 20, WINDOW_WIDTH, WINDOW_HEIGHT};
	char* timer_buffer = (char*) calloc(100, sizeof(char));
	settextstyle(18, 0, _T("Consolas"));
	drawtext(_T(map->name), &common_rect, DT_SINGLELINE);
	for (double time = 0; time < map->time; time += STICK_STEP_TIME) {
		unsigned control_size = control->size();
		if(control_size > 0) {
			GameControl* head_control = (*control)[control_size-1];
			if(head_control->time >= (time - STICK_ADVANCE_TIME)) {
				control->pop_back();
				IMAGE image;
				IMAGE cache;
				draw_game_stick(head_control, &image, &cache);
				images[head_control] = image;
				old_images[head_control] = cache;
				std::vector<GameControl*>* target = &accepting_keys[head_control->key];
				target->insert(target->begin(), head_control);
			}
		}
		for (const char game_key : game_keys) {
			std::vector<GameControl*>* querying_accepting_keys = &accepting_keys[game_key];
			if(!querying_accepting_keys->empty()) {
				GameControl* object = (*querying_accepting_keys)[querying_accepting_keys->size()-1];
				if(time - object->time > GRADE_BAD) {
					querying_accepting_keys->pop_back();
					//TODO: STATUS MISS
					round->score += SCORE_MISS;
					images[object] = NULL;  //destroy invalid images
					hide_game_stick(object, &old_images[object]);
					old_images[object] = NULL;
				} else {
					draw_game_stick(object, &images[object], &old_images[object]);
				}
			}
		}
		sprintf_s(timer_buffer, 100, "Time: %8.3lf / %7.2lf", time, map->time);
		drawtext(_T(timer_buffer), &timer_rect, DT_SINGLELINE);
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