#pragma once
#ifndef PAGE_FIRSTMAP
#define PAGE_FIRSTMAP
#include "../../library/global.h"
#include "../../library/view.h"

int flag_show_map_hover_status = -2;

inline void draw_map_common_info() {
	if(flag_show_map_hover_status != -1) {
		put_background("map.jpg");
		draw_player_info();
		flag_show_map_hover_status = -1;
	}
}

inline void draw_map_selection_info(std::vector<std::string> maps, int key) {
	if(maps.size() > (std::vector<std::string>::size_type) key) {
		const char* path = maps[key].c_str();
		if(flag_show_map_hover_status < 0) {
			put_background("map-hover.jpg");
			draw_player_info();
		} if(flag_show_map_hover_status != key) {
			flag_show_map_hover_status = key;
			GameMap* info = get_map_info(path);;
			settextstyle(19, 0, _T("Consolas"));
			RECT rect = {749, 26, WINDOW_WIDTH, WINDOW_HEIGHT};
			drawtext(_T(info->name), &rect, DT_SINGLELINE);
			rect = {749, 53, WINDOW_WIDTH, WINDOW_HEIGHT};
			drawtext(_T(info->description), &rect, DT_SINGLELINE);
			rect = {749, 100, WINDOW_WIDTH, WINDOW_HEIGHT};
			drawtext(_T(cat("Difficulty: ", get_difficulty(info->difficulty))), &rect, DT_SINGLELINE);
		}
	}
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
	draw_map_common_info();
	int conse = -1;
	FlushMouseMsgBuffer();
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 939 && Mouse.x <= 1011) && (Mouse.y >= 547 && Mouse.y <= 600)) {
			if (Mouse.mkLButton) {
				conse = 0;
			}
		} else {
			if ((Mouse.x >= 488 && Mouse.x <= 552) && (Mouse.y >= 100 && Mouse.y <= 160)) {
				if (Mouse.mkLButton) {
					conse = 1;
				} else if(Mouse.uMsg == WM_MOUSEMOVE) {
					draw_map_selection_info(maps, 0);
				}
			} else {
				if ((Mouse.x >= 676 && Mouse.x <= 738) && (Mouse.y >= 243 && Mouse.y <= 299)) {
					if (Mouse.mkLButton) {
						conse = 2;
					} else if(Mouse.uMsg == WM_MOUSEMOVE) {
						draw_map_selection_info(maps, 1);
					}
				} else {
					if ((Mouse.x >= 600 && Mouse.x <= 661) && (Mouse.y >= 424 && Mouse.y <= 481)) {
						if (Mouse.mkLButton) {
							conse = 3;
						}  else if(Mouse.uMsg == WM_MOUSEMOVE) {
							draw_map_selection_info(maps, 2);
						}
					} else {
						if ((Mouse.x >= 382 && Mouse.x <= 442) && (Mouse.y >= 424 && Mouse.y <= 481)) {
							if (Mouse.mkLButton) {
								conse = 4;
							}  else if(Mouse.uMsg == WM_MOUSEMOVE) {
								draw_map_selection_info(maps, 3);
							}
						} else {
							if ((Mouse.x >= 307 && Mouse.x <= 371) && (Mouse.y >= 243 && Mouse.y <= 299)) {
								if (Mouse.mkLButton) {
									conse = 5;
								}  else if(Mouse.uMsg == WM_MOUSEMOVE) {
									draw_map_selection_info(maps, 4);
								}
							} else {
								draw_map_common_info();
							}
						}
					}
				}
			}
		}
		if(conse >= 0 && maps.size() >= conse)
			break;
	}
	FlushMouseMsgBuffer();
	flag_show_map_hover_status = -2;
	return conse;
}
#endif