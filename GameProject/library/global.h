#pragma once
#ifndef LIBRARY_GLOBAL
#define LIBRARY_GLOBAL
#include <easyx.h>

/**
 * 击打等级
 */
typedef enum {
	Miss,
	Bad,
	Good,
	Perfect
} HitLevel;

/**
 * 玩家
 */
typedef struct {
	char* name;
	unsigned int name_length;
	unsigned long long experience;
	unsigned int level;
	unsigned int max_combo; //最大连击次数
	unsigned int max_score; //单局游戏最大得分
} GamePlayer;

/**
 * 一个回合
 */
typedef struct {
	unsigned int max_combo; //这局最大连击次数
	unsigned int score; //这局得分
	time_t time; //何时开始的游戏（UNIX TIMESTAMP）
	unsigned short level; //等级评定 S=0 A=1 B=2 C=3 D=4
	char* map; //Map Internal Path
	unsigned int map_length;
} GameRound;

/**
 * 地图文件
 */
typedef struct {
	char* path; //Map Internal Path
	char* name;
	char* description;
	double time; //地图时间长度 
	unsigned short difficulty; //等级评定 Easy=0 Normal=1 Hard=2 Chaos=3
} GameMap;

/**
 * 过程控制
 */
typedef struct {
	double time; //秒数，0.001即为1ms
	unsigned key; //按键ID
	int position; //Y Position
	IMAGE* image;
} GameControl;

typedef struct {
	long score;
	unsigned combo;
	unsigned total; //方块总数
	unsigned perfect;
	unsigned good;
	unsigned bad;
	unsigned miss;
} GameScoreStat;

extern GamePlayer* player;
extern GameRound* rounds_basic;
extern unsigned rounds_num;

inline GamePlayer* get_player() {
	return player;
}

inline GameRound* get_rounds_basic() {
	return rounds_basic;
}

inline unsigned get_rounds_num() {
	return rounds_num;
}

#endif