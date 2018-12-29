#pragma once
#ifndef LIBRARY_FUNCTION
#define LIBRARY_FUNCTION

#include <cerrno>
#include <minwindef.h>
#include <io.h>
#include <cstdlib>
#include <cstdio>
#include <direct.h>
#include <xutility>
#include "global.h"
#include <vector>
#include<initializer_list> 
#include <iostream>
#include <string>
#define F_OK 0

//玩家升级到LV1所需经验
#define PLAYER_LV0_EXPERIENCE 10000

/**
 * 错误处理函数: 打印错误
 * @param errors 错误列表，需用大括号括起来
 */
template <typename T>
inline void bullshit(std::initializer_list<T> errors) {
	std::cerr << "----------------------Error Occured------------------------" << std::endl;
	for(T err : errors)
		std::cerr << err << std::endl;
}

/**
 * 连接字符串
 */
inline char* cat(const char* a, const char* b) {
	const unsigned buffer_size = (unsigned) sizeof(char) * (strlen(a) * strlen(b) + 2);
	char* buffer = (char*) malloc(buffer_size);
	strcpy_s(buffer, buffer_size, a);
	strcat_s(buffer, buffer_size, b);
	return buffer;
}

/**
 * 判断文件夹是否存在
 */
inline bool dir_exists(const char *pszDir) {
	if (pszDir == NULL)
		return false;
	return (_access(pszDir, 0) == 0);	// io.h
}

/**
 * 创建目录
 */
inline bool create_directory(const char* dir) {
	if (NULL == dir)
		return false;

	char path[MAX_PATH];
	int nPathLen = 0;

	strcpy_s(path, dir);
	if ((nPathLen = strlen(path)) < 1)
		return false;

	for (int i = 0; i < nPathLen; ++i){
		if (path[i] == '\\') {
			path[i] = '\0';
			_mkdir(path);	// <direct.h>
			path[i] = '\\';
		}
	}

	return (0 == _mkdir(path) || EEXIST == errno); // EEXIST => errno.h    errmo => stdlib.h
}

/**
 * 初始化数据库
 * @return bool is file exists
 */
inline bool db_init(const char* path, FILE** target) {
	errno_t err;
	FILE* stream = NULL;
	bool is_exist;
	if(_access(path, F_OK) == -1) {
		is_exist = false;
		err = fopen_s(&stream, path, "wb+");
	} else {
		is_exist = true;
		err = fopen_s(&stream, path, "rb+");
	}
	if(err) {
		errno = err;
		bullshit({"Failed to open database file: ", path, std::to_string(errno).c_str()});
	}
	*target = stream;
	return is_exist;
}

inline void db_write_rounds(FILE* file, FILE* index, GameRound* data, unsigned num) {
	fseek(file, 0L, SEEK_SET);
	fseek(index, 0L, SEEK_SET);
	fwrite(data, sizeof(GameRound), num, file);
	fprintf_s(index, "%d\n", num);
	for (unsigned i = 0; i < num; i++) {
		fwrite(data[i].map, data[i].map_length, 1, index);
	}
	fflush(file);
	fflush(index);
}

inline void db_write_player(FILE* file, GamePlayer* player) {
	fseek(file, 0L, SEEK_SET);
	fwrite(player, sizeof(GamePlayer), 1, file);
	fputs(player->name, file);
	fflush(file);
}

inline GameRound* db_read_round(FILE* file, FILE* index, unsigned* _num) {
	fseek(file, 0L, SEEK_END);
	const long size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	GameRound* buffer = (GameRound*) calloc(1, size);
	fread_s(buffer, size, size, 1, file);
	unsigned num = 0;
	fseek(index, 0L, SEEK_SET);
	fscanf_s(index, "%u\n", &num);
	for (unsigned i = 0; i < num; i++) {
		buffer[i].map = (char*) calloc(buffer[i].map_length + 2, sizeof(char));
		fread_s(buffer[i].map, buffer[i].map_length + 1, buffer[i].map_length, 1, index);
		buffer[i].map[buffer[i].map_length + 1] = '\0';
	}
	*_num = num;
	return buffer;
}

inline bool db_insert_round(GameRound** source, unsigned* num, GameRound* data) {
	GameRound* new_ptr = (GameRound*) realloc(*source, sizeof(*source) + sizeof(GameRound) * sizeof(data));
	if(new_ptr != NULL) {
		*source = new_ptr;
		(*source)[*num].max_combo = data->max_combo;
		(*source)[*num].level = data->level;
		(*source)[*num].map = data->map;
		(*source)[*num].map_length = data->map_length;
		(*source)[*num].score = data->score;
		(*source)[*num].time = data->time;
		(*num)++;
		return true;
	} else {
		return false;
	}
	(*num)++;
	return true;
}

inline GamePlayer* db_read_player(FILE* file) {
	GamePlayer* buffer = (GamePlayer*) calloc(1, sizeof(GamePlayer));
	fread_s(buffer, sizeof(GamePlayer), sizeof(GamePlayer), 1, file);
	fseek(file, sizeof(GamePlayer), SEEK_SET);
	buffer->name = (char*) calloc(1, buffer->name_length + 2);
	if(buffer->name_length > 0)
		fgets(buffer->name, buffer->name_length+1, file);
	return buffer;
}

/**
 * 列出地图
 * @return int 地图数量
 */
inline std::vector<std::string> get_map_list() {
	std::vector<std::string> result;
	intptr_t handle = NULL;
    intptr_t handle_next = NULL;
    struct _finddata_t cfile = {0};
    handle = _findfirst("resource/map/*", &cfile); // 在当前目录下查找文件或子目录；[支持通配符]
    handle_next = handle;
    while (handle_next != -1) {
        if(strncmp(cfile.name, "..", 49) != 0 && strncmp(cfile.name, ".", 49) != 0) {
	        result.insert(result.begin(), cfile.name);
			printf("Scanned Map: %s\n", cfile.name);
        }
        handle_next = _findnext(handle, &cfile); // 继续查找下一个
    }
    _findclose(handle);
	return result;
}

/**
 * 获取地图信息
 * @param path 地图文件夹名称，位于map文件夹下
 */
inline GameMap* get_map_info(const char* path) {
	FILE* file = nullptr;
	const char* file_path = cat(cat("resource/map/", path), "/info.txt");
	errno = fopen_s(&file, file_path, "r");
	if(errno)
		bullshit({"Failed to open map info file: ", file_path, std::to_string(errno).c_str()});
	GameMap* data = (GameMap*) calloc(1, sizeof(GameMap));
	data->name = (char*) calloc(50, sizeof(char));
	data->description = (char*) calloc(100, sizeof(char));
	data->path = (char*) calloc(strlen(path) + 2, sizeof(char));
	strncpy_s(data->path, strlen(path)+1, path, strlen(path)+1);
	int minute;
	double second;
	fgets(data->name, 49, file);
	fscanf_s(file, "\n%d:%lf\n%hu\n", &minute, &second, &data->difficulty);
	data->time = (double) minute * 60 + second;
	fgets(data->description, 99, file);
	return data;
}

/**
 * 获取某个等级所需经验值
 * @param level 等级
 * @return 所需经验
 */
inline unsigned long long get_level_experience(unsigned level) {
	unsigned long long exp = PLAYER_LV0_EXPERIENCE;
	for (unsigned i = 0; i < level; i++) {
		exp *= 2;
	}
	return exp;
}

inline char* get_difficulty(unsigned short difficulty) {
	char* result = (char*) calloc(8, sizeof(char));
	switch (difficulty) { //等级评定 Easy=0 Normal=1 Hard=2 Chaos=3
		case 0:
			result = (char*) "Easy";
			break;

		case 1:
			result = (char*) "Normal";
			break;

		case 2:
			result = (char*) "Hard";
			break;

		case 3:
			result = (char*) "Chaos";
			break;
	}
	return result;
}

/**
 * 将可能的大写按键转换为小写按键以便匹配
 */
inline char get_game_key(char key) {
	switch (key) {
		case 'A':
		case 'a':
			return 'a';
			break;

		case 'S':
		case 's':
			return 's';
			break;

		case 'D':
		case 'd':
			return 'd';
			break;

		case 'J':
		case 'j':
			return 'j';
			break;

		case 'K':
		case 'k':
			return 'k';
			break;

		case 'L':
		case 'l':
			return 'l';
			break;
	}
	return '\0';
}

inline void get_level_description(unsigned level, char** target) {
	switch (level) {
		case 3:
			*target = (char*) "Perfect";
			break;
		
		case 2:
			*target = (char*) "Good";
			break;

		case 1:
			*target = (char*) "Bad";
			break;

		default:
			*target = (char*) "Miss";
			break;
	}
}

#endif