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

inline int show_difficulty() {
	IMAGE cache;
	IMAGE pause;
	getimage(&cache, 193, 129, 616, 310);
	loadimage(&pause, "resource/image/difficulty.jpg", 616, 310, true);
	putimage(193, 129, &pause);
	int difficulty = -2;
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 20+193 && Mouse.x <= 202+193) && (Mouse.y >= 86+129 && Mouse.y < 294+129)) {
			if (Mouse.mkLButton) {
				difficulty = 0;
			}
		} else {
			if ((Mouse.x > 231+193 && Mouse.x <= 404+193) && (Mouse.y >= 86+129 && Mouse.y <294+129)) {
				if (Mouse.mkLButton) {
					difficulty = 1;
				}
			} else {
				if ((Mouse.x > 436+193 && Mouse.x <= 598+193) && (Mouse.y >= 86+129 && Mouse.y < 294+129)) {
					if (Mouse.mkLButton) {
						difficulty = 2;
					}
				} else {
					if ((Mouse.x >= 181 && Mouse.x <= 294) && (Mouse.y >= 116 && Mouse.y < 161)) {
						if (Mouse.mkLButton) {
							difficulty = -1;
						}
					}
				}
			}
		}
		if(difficulty >= -1)
			break;
	}
	putimage(193, 129, &cache);
	return difficulty;
}

/**
点击返回键 返回值为0
点击第一关 返回值为1
点击第二关 返回值为2
点击第三关 返回值为3
点击第四关 返回值为4
点击第五关 返回值为5
*/
inline int show_map(std::vector<std::string> maps, int* difficulty) {
	draw_map_common_info();
	FlushMouseMsgBuffer();
	SELECT_MAP:
	int conse = -1;
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
	if (conse != 0) {
		int selected_difficulty = show_difficulty();
		if (selected_difficulty == -1)
			goto SELECT_MAP;
		*difficulty = selected_difficulty;
	}
	else {
		*difficulty = -1;
	}
	return conse;
}
#endif