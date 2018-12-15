#pragma once
#ifndef LIBRARY_MUSIC
#define LIBRARY_MUSIC

#include <graphics.h>
#include <conio.h>
#include "function.h"
#include <mmsystem.h>  
#pragma comment(lib, "winmm.lib")

inline void music_play(const char* path) {
	char* command = cat(cat("open \"./resource/music/", path), "\" alias _music");
	mciSendString(command, nullptr, 0, nullptr);
	mciSendString("play _music", nullptr, 0, nullptr);
}

inline void music_stop() {
	mciSendString("stop _music", nullptr, 0, nullptr);
	mciSendString("close _music", nullptr, 0, nullptr);
}


#endif