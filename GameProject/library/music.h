#pragma once
#ifndef LIBRARY_MUSIC
#define LIBRARY_MUSIC

#include <graphics.h>
#include <conio.h>
#include "function.h"
#include <mmsystem.h>  
#include <string>
#pragma comment(lib, "winmm.lib")

inline void music_error(const char* message, MCIERROR error) {
	print_error({"MCIERROR: ", message, std::to_string(error).c_str()});
}

inline MCIERROR music_init(const char* path, const char* folder = "music") {
	char* command = cat(cat("open \"./resource/", cat(folder, cat("/", path))), "\" alias _music");
	errno = mciSendString(command, nullptr, 0, nullptr);
	if(errno)
		music_error("initialize music", errno);
	return errno;
}

inline MCIERROR music_play() {
	errno = mciSendString("play _music", nullptr, 0, nullptr);
	if(errno)
		music_error("play music", errno);
	return errno;
}
 
inline MCIERROR music_stop() {
	const MCIERROR error = mciSendString("stop _music", nullptr, 0, nullptr);
	if(error) {
		music_error("stop music", error);
		return error;
	}
	return mciSendString("close _music", nullptr, 0, nullptr);
}

inline MCIERROR music_get_position(char** target) {
	char* result = (char*) calloc(128, sizeof(char));
	errno = mciSendString("status _music position", result, 127, nullptr);
	if(errno)
		music_error("get position", errno);
	*target = result;
	return errno;
}

inline MCIERROR music_pause() {
	errno = mciSendString("pause _music", nullptr, 127, nullptr);
	if(errno)
		music_error("pause music", errno);
	return errno;
}
#endif