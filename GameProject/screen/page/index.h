#pragma once
#ifndef PAGE_FIRST
#define PAGE_FIRST
#include "../../library/global.h"
#include "../../library/view.h"

/**
 * 显示主页
 * @return 0 for play game. 1 for records.
 */
inline int show_index() {
	cleanup();
	put_background("index.jpg");
	while(true) {
		while (!MouseHit())
			Sleep(16);
		MOUSEMSG msg = GetMouseMsg();
		if(msg.mkLButton) {
			
		}
		Sleep(16);
	}
}

#endif