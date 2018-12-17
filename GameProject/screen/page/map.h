#pragma once
#ifndef PAGE_FIRSTMAP
#define PAGE_FIRSTMAP
#include "../../library/global.h"
#include "../../library/view.h"

inline void draw_map_selection_info(std::string path) {
	GameMap* info = get_map_info(path.c_str());
	
} 

/*
点击返回键 返回值为0
点击第一关 返回值为1
点击第二关 返回值为2
点击第三关 返回值为3
点击第四关 返回值为4
点击第五关 返回值为5
*/
inline int show_map(std::vector<std::string> maps) {
	cleanup();
	put_background("map.jpg");
	draw_player_info();
	int conse = 0;
	bool hover = false;
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 939 && Mouse.x <= 1011) && (Mouse.y >= 547 && Mouse.y <= 600)) {
			if (Mouse.mkLButton) {
				conse = 0;
				break;
			}
		} else {
			if ((Mouse.x >= 488 && Mouse.x <= 552) && (Mouse.y >= 100 && Mouse.y <= 160)) {
				if (Mouse.mkLButton) {
					conse = 1;
					break;
				} else if(Mouse.uMsg == WM_MOUSEMOVE) {
					hover = true;
					draw_map_selection_info(maps[0]);
				}
			} else {
				if ((Mouse.x >= 676 && Mouse.x <= 738) && (Mouse.y >= 243 && Mouse.y <= 299)) {
					if (Mouse.mkLButton) {
						conse = 2;
						break;
					} else if(Mouse.uMsg == WM_MOUSEMOVE) {
						hover = true;
						draw_map_selection_info(maps[1]);
					}
				} else {
					if ((Mouse.x >= 600 && Mouse.x <= 661) && (Mouse.y >= 424 && Mouse.y <= 481)) {
						if (Mouse.mkLButton) {
							conse = 3;
							break;
						}  else if(Mouse.uMsg == WM_MOUSEMOVE) {
							hover = true;
							draw_map_selection_info(maps[2]);
						}
					} else {
						if ((Mouse.x >= 382 && Mouse.x <= 442) && (Mouse.y >= 424 && Mouse.y <= 481)) {
							if (Mouse.mkLButton) {
								conse = 4;
								break;
							}  else if(Mouse.uMsg == WM_MOUSEMOVE) {
								hover = true;
								draw_map_selection_info(maps[3]);
							}
						} else {
							if ((Mouse.x >= 307 && Mouse.x <= 371) && (Mouse.y >= 243 && Mouse.y <= 299)) {
								if (Mouse.mkLButton) {
									conse = 5;
									break;
								}  else if(Mouse.uMsg == WM_MOUSEMOVE) {
									hover = true;
									draw_map_selection_info(maps[4]);
								}
							}
						}
					}
				}
			}
		}
		FlushMouseMsgBuffer();
		return conse;
	}
}
#endif