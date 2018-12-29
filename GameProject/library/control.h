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
#include <ctime>

#define GRADE_PERFECT 0.2
#define GRADE_GOOD 0.3
#define GRADE_BAD 0.5

#define SCORE_PERFECT 50
#define SCORE_GOOD 15
#define SCORE_BAD -10
#define SCORE_MISS -30

//允许作弊模式
#define CHEAT

//条子起始位置
#define STICK_INIT_POSITION 20
//条子步进长度
#define STICK_STEP_LENGTH 5.9
//条子提前绘制时间
#define STICK_ADVANCE_TIME 0.87
//条子步进时间
#define STICK_STEP_TIME 0.014L 

#define STICK_WIDTH 67
#define STICK_HEIGHT 38

const char game_valid_keys[] = {'A','S','D','J','K','L','a','s','d','j','k','l'};
const char game_keys_hard[] = {'a','s','d','j','k','l'};
const char game_keys_normal[] = {'a','s','k','l'};
const char game_keys_easy[] = {'a','l'};

inline bool is_valid_key(int key) {
	for (char valid_key : game_valid_keys) {
		if(valid_key == key)
			return true;
	}
	return false;
}

inline void get_game_difficulty_key(int difficulty, unsigned* game_key_num, char** game_keys_v) {
	*game_key_num = difficulty == 0 ? 2 : difficulty == 1 ? 4 : 6;
	char* game_keys = (char*) calloc(*game_key_num, sizeof(char));
	memcpy_s(game_keys, 6, difficulty == 0 ? game_keys_easy : difficulty == 1 ? game_keys_normal : game_keys_hard, 6);
	*game_keys_v = game_keys;
}

inline std::vector<GameControl*> game_read_control(GameMap* map, int difficulty, unsigned* num = nullptr) {
	FILE* fs;
	errno = fopen_s(&fs, cat(cat("resource/map/", map->path),"/control.txt"), "r");
	if(errno != 0)
		bullshit({"Failed to read control: file error ", std::to_string(errno).c_str()});
	fseek(fs, 0L, SEEK_END);
	unsigned size = ftell(fs);
	fseek(fs, 0L, SEEK_SET);
	unsigned game_key_num;
	char* game_keys = nullptr;
	get_game_difficulty_key(difficulty, &game_key_num, &game_keys);
	std::vector<GameControl*> result;
	result.reserve(4096);
	unsigned i = 0;
	for (; feof(fs) != 1; i++) {
		int minute = -1;
		double second;
		char key;
		fscanf_s(fs, "%d:%lf %c\n", &minute, &second, &key);
		if(minute != -1) {
			for (unsigned ik = 0; ik < game_key_num; ik++) {
				if(game_keys[ik] == key) {
					GameControl* control = (GameControl*) calloc(1, sizeof(GameControl));
					control->key = key;
					control->time = (double) minute * 60 + second;
					control->position = -1;
					control->image = nullptr;
					result.insert(result.begin(), control);
				}
			}
		}
	}
	if(num != nullptr)
		*num = i;
	return result;
}

/**
 * 判定是否击中以及击打等级，并增加分数。（界限Y=406）
 * @param control 当前的控制数据
 * @param round 当前回合
 * @param time 击打时的相对播放时间
 * @return 击打等级，1=BAD 2=GOOD 3=PERFECT 0=INVALID
 */
inline unsigned int game_check_key(GameControl* control, GameRound* round, GameScoreStat* stat, double time, char key) {
	double pressed_time = control->time - time;
	stat->combo++;
	if(pressed_time > -GRADE_PERFECT && pressed_time < GRADE_PERFECT) {
		stat->score += SCORE_PERFECT * stat->combo;
		stat->perfect++;
		return 3;
	} else if(pressed_time > -GRADE_GOOD && pressed_time < GRADE_GOOD) {
		stat->score += SCORE_GOOD * stat->combo;
		stat->good++;
		return 2;
	} else if(pressed_time > -GRADE_BAD && pressed_time < GRADE_BAD) {
		stat->score += SCORE_BAD;
		stat->bad++;
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
 * 绘制条子
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
	music_init(cat(map->path, "/music.mp3"), "map");
	music_play();
}

/**
 * 绘制击打结果
 */
inline void draw_hit_result(GameControl* control, unsigned hit_level) {
	char* result = (char*) calloc(30, sizeof(char));
	RECT common_rect = {WINDOW_WIDTH - 230, WINDOW_HEIGHT - 60, WINDOW_WIDTH, WINDOW_HEIGHT};
	settextstyle(18, 0, _T("Consolas"));
	char* hit_level_description = (char*) calloc(10, sizeof(char));
	get_level_description(hit_level, &hit_level_description);
	sprintf_s(result, 30, "%s for %c at %3.2lf", hit_level_description, control->key, control->time);
	drawtext(_T(result), &common_rect, DT_SINGLELINE);
}

inline void test_and_draw_combo(unsigned hit_level, GameScoreStat* stat, unsigned* max_combo) {
	if(hit_level == 3 || hit_level == 2) {
		if(*max_combo < stat->combo)
			*max_combo = stat->combo;
	} else {
		stat->combo = 0;
	}
	char result[30];
	RECT combo_rect = {WINDOW_WIDTH - 230, 20, WINDOW_WIDTH, WINDOW_HEIGHT};
	settextstyle(18, 0, _T("Consolas"));
	sprintf_s(result, 30, "Combo %3u / Max Combo %3u", stat->combo, *max_combo);
	drawtext(_T(result), &combo_rect, DT_SINGLELINE);
}

/**
 * 游戏事件循环
 * @param map 地图对象
 * @param control 控制向量
 * @param difficulty 期望的难度
 */
inline GameRound* game_event_loop(GameMap* map, int difficulty) {
	std::vector<GameControl*> control_raw = game_read_control(map, difficulty);
	std::vector<GameControl*>* control = &control_raw;
	GameRound* round = (GameRound*) calloc(1, sizeof(GameRound));
	round->map = map->path;
	round->map_length = strlen(map->path);
	round->time = std::time(nullptr);
	GameScoreStat* stat = (GameScoreStat*) calloc(1, sizeof(GameScoreStat));
	std::map<char, std::vector<GameControl*>>* accepting_keys = new std::map<char, std::vector<GameControl*>>();
	std::unordered_map<GameControl*, IMAGE*>* images = new std::unordered_map<GameControl*, IMAGE*>();
	std::map<char, GameControl*>* last_control = new std::map<char, GameControl*>();
	std::unordered_map<GameControl*, IMAGE*>* old_images = new std::unordered_map<GameControl*, IMAGE*>();
	images->reserve(4096);
	old_images->reserve(4096);
	unsigned game_key_num;
	char* game_keys = nullptr;
	get_game_difficulty_key(difficulty, &game_key_num, &game_keys);
	//images.reserve(control->size() + 1);
	//old_images.reserve(control->size() + 1);
	unsigned max_combo = 0;
	unsigned combo = 0;
	for (unsigned i = 0; i < game_key_num/sizeof(char); i++) {
		const char game_key = game_keys[i];
		(*accepting_keys)[game_key] = std::vector<GameControl*>();
		(*last_control)[game_key] = nullptr;
	}
	bool cheat_mode = false;
	int cheat_key = 0;
	////////////////////////////
	/*for(auto c : *control) {
					IMAGE image;
					IMAGE cache;
					images[c] = image;
					old_images[c] = cache;
	}*/
	/////////////////////////////
	char* music_position_string = (char*) calloc(128, sizeof(char));
	game_play_music(map);
	//ready to start timer
	RECT common_rect = {WINDOW_WIDTH - 230, WINDOW_HEIGHT - 40, WINDOW_WIDTH, WINDOW_HEIGHT};
	RECT timer_rect = {WINDOW_WIDTH - 230, WINDOW_HEIGHT - 20, WINDOW_WIDTH, WINDOW_HEIGHT};
	RECT score_rect = {WINDOW_WIDTH - 230, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	RECT stat_rect = {7, WINDOW_HEIGHT - 20, WINDOW_WIDTH, WINDOW_HEIGHT};
	char* timer_buffer = (char*) calloc(256, sizeof(char));
	settextstyle(18, 0, _T("Consolas"));
	drawtext(_T(map->name), &common_rect, DT_SINGLELINE);
	for (double time = 0; time < map->time; time += STICK_STEP_TIME) {
		unsigned control_size = control->size();
		//校准时间到播放进度
		music_get_position(&music_position_string);
		double music_position = (double) atoi(music_position_string) / 1000;
		time = music_position;
		if(control_size > 0) {
			GameControl* head_control = (*control)[control_size-1];
			if(time >= (head_control->time - STICK_ADVANCE_TIME)) {
				control->pop_back();
				std::vector<GameControl*>* target = &(*accepting_keys)[head_control->key];
				if((*last_control)[head_control->key] == nullptr || time - ( (*last_control)[head_control->key]->time - STICK_ADVANCE_TIME ) > 0.34) {
					IMAGE* image = new IMAGE();
					IMAGE* cache = new IMAGE();
					draw_game_stick(head_control, image, cache);
					(*images)[head_control] = image;
					(*old_images)[head_control] = cache;
					target->insert(target->begin(), head_control);
					stat->total++;
				}
				(*last_control)[head_control->key] = head_control;
			}
		}
		for (unsigned ik = 0; ik < game_key_num; ik++) {
			const char game_key = game_keys[ik];
			std::vector<GameControl*>* querying_accepting_keys = &(*accepting_keys)[game_key];
			if(!querying_accepting_keys->empty()) {
				for(GameControl* object : *querying_accepting_keys) {
					if(time - object->time > GRADE_BAD) {
						querying_accepting_keys->pop_back();
						//TODO: STATUS MISS
						stat->score += SCORE_MISS;
						stat->miss++;
						hide_game_stick(object, (*old_images)[object]);
						draw_hit_result(object, 0);
						test_and_draw_combo(0, stat, &max_combo);
						delete (*images)[object];
						delete (*old_images)[object];
						images->erase(object);
						old_images->erase(object);
					} else {
						draw_game_stick(object, (*images)[object], (*old_images)[object]);
#ifdef CHEAT
						if(cheat_mode && abs(time - object->time) < GRADE_PERFECT) {
							cheat_key = object->key;
						}
#endif
					}
				}
			}
		}
		sprintf_s(timer_buffer, 100, "Time: %8.3lf / %7.2lf", time, map->time);
		drawtext(_T(timer_buffer), &timer_rect, DT_SINGLELINE);
		if(_kbhit() != 0 || cheat_key != 0) {
			int key;
			if(cheat_key != 0) {
				key = cheat_key;
				cheat_key = 0;
			} else {
				key = _getch();
			}
			if(is_valid_key(key)) {
				key = get_game_key(key);
				if(!(*accepting_keys)[key].empty()) {
					GameControl* current_control = (*accepting_keys)[key][(*accepting_keys)[key].size()-1];
					if(time - current_control->time < GRADE_BAD) {
						unsigned hit_level = game_check_key(current_control, round, stat, time, key);
						test_and_draw_combo(hit_level, stat, &max_combo);
						(*accepting_keys)[key].pop_back();
						hide_game_stick(current_control, (*old_images)[current_control]);
						//TODO: Play efforts for bad/good/perfect
						draw_hit_result(current_control, hit_level);
						delete (*images)[current_control];
						delete (*old_images)[current_control];
						images->erase(current_control);
						old_images->erase(current_control);
					}
				}
			} else if(key == 27) {
				//Pause game
				music_pause();
				IMAGE cache;
				IMAGE pause;
				getimage(&cache, 193, 129, 616, 310);
				loadimage(&pause, "resource/image/paused.jpg", 616, 310, true);
				putimage(193, 129, &pause);
				const char pause_key = _getch();
				if(pause_key == 'E' || pause_key == 'e') {
					return nullptr;
				}
				putimage(193, 129, &cache);
				music_play();
			} 
#ifdef CHEAT
			else if(key == 8) { //响应作弊键
				cheat_mode = cheat_mode ? false : true;
			}
#endif
		}
		sprintf_s(timer_buffer, 100, "Score: %6ld", stat->score);
		drawtext(_T(timer_buffer), &score_rect, DT_SINGLELINE);
		sprintf_s(timer_buffer, 100, "Total %4u / Perfect %3u / Good %3u / Bad %3u / Miss %3u", stat->total, stat->perfect, stat->good, stat->bad, stat->miss);
		drawtext(_T(timer_buffer), &stat_rect, DT_SINGLELINE);
		Sleep(STICK_STEP_TIME * 1000);
 	}
	round->max_combo = max_combo;
	round->score = stat->score < 0 ? 0 : stat->score;
	free(music_position_string);
	free(timer_buffer);
	for (GameControl* control_v : *control)
		free(control_v);
	return round;
}
#endif