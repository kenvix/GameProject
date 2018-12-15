#pragma once
#ifndef LIBRARY_GLOBAL
#define LIBRARY_GLOBAL

/**
 * 玩家
 */
typedef struct {
	char* name;
	unsigned int name_length;
	unsigned long long experience;
	unsigned int level;
	unsigned int max_combo; //这辈子的最大连击次数
	unsigned int max_score; //单局游戏最大得分
} GamePlayer;

/**
 * 一个回合
 */
typedef struct {
	unsigned int max_combo; //这局最大连击次数
	unsigned int max_score; //这局得分
	unsigned int time; //何时开始的游戏（UNIX TIMESTAMP）
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
	unsigned short difficulty; //等级评定 Easy=0 Normal=1 Hard=2 Chaos=3
} GameMap;

#endif