#pragma once
#ifndef LIBRARY_MUSIC
#define LIBRARY_MUSIC

#include <graphics.h>
#include <conio.h>
#include "function.h"
#include <mmsystem.h>  
#pragma comment(lib, "winmm.lib")

inline MCIERROR music_play(const char* path) {
	char* command = cat(cat("open \"./resource/music/", path), "\" alias _music");
	const MCIERROR error = mciSendString(command, nullptr, 0, nullptr);
	if(error) return error;
	return mciSendString("play _music", nullptr, 0, nullptr);
}
 
inline MCIERROR music_stop() {
	const MCIERROR error = mciSendString("stop _music", nullptr, 0, nullptr);
	if(error) return error;
	return mciSendString("close _music", nullptr, 0, nullptr);
}


#endif