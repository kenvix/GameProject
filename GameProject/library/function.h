#ifndef LIBRARY_FUNCTION
#define LIBRARY_FUNCTION

#include <cerrno>
#include <minwindef.h>
#include <io.h>
#include <cstdlib>
#include <direct.h>
#include <xutility>
#include "global.h"
#define F_OK 0

/**
 * 判断文件夹是否存在
 */
inline bool dir_exists(const char *pszDir) {
	if (pszDir == NULL)
		return false;
	return (_access(pszDir, 0) == 0);	// io.h
}

// 创建目录
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
	if(err)
		errno = err;
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
	GameRound* buffer = (GameRound*) malloc(size);
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

inline GamePlayer* db_read_player(FILE* file) {
	GamePlayer* buffer = (GamePlayer*) malloc(sizeof(GamePlayer));
	fread_s(buffer, sizeof(GamePlayer), sizeof(GamePlayer), 1, file);
	fseek(file, sizeof(GamePlayer), SEEK_SET);
	buffer->name = (char*) malloc(buffer->name_length + 2);
	fgets(buffer->name, buffer->name_length, file);
	return buffer;
}

#endif