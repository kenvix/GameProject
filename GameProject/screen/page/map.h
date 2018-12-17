#pragma once
#pragma once
#ifndef PAGE_FIRSTMAP
#define PAGE_FIRSTMAP
#include "../../library/global.h"
#include "../../library/view.h"
/**
 *
 * 点击返回键 返回值为0
 * 点击第一关 返回值为1
 * 点击第二关 返回值为2
 * 点击第三关 返回值为3
 * 点击第四关 返回值为4
 * 点击第五关 返回值为5
 */
inline int show_map() {
	cleanup();
	put_background("map.jpg");
	draw_player_info();
	int conse;
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 939 && Mouse.x <= 1011) && (Mouse.y >= 547 && Mouse.y <= 600)) {
			if (Mouse.mkLButton) {
				conse= 0;
				break;
			}
		} else {
			if ((Mouse.x >= 482 && Mouse.x <= 542) && (Mouse.y >= 95 && Mouse.y <= 145)) {
				if (Mouse.mkLButton) {
					conse= 1;
					break;
				}
			} else {
				if ((Mouse.x >= 295 && Mouse.x <= 357) && (Mouse.y >= 235 && Mouse.y <= 283)) {
					if (Mouse.mkLButton) {
						conse= 2;
						break;
					}
				} else {
					if ((Mouse.x >= 366 && Mouse.x <= 423) && (Mouse.y >= 415 && Mouse.y <= 464)) {
						if (Mouse.mkLButton) {
							conse = 3;
							break;
						}
					} else {
						if ((Mouse.x >= 563 && Mouse.x <= 622) && (Mouse.y >= 415 && Mouse.y <= 464)) {
							if (Mouse.mkLButton) {
								conse = 4;
								break;
							}
						} else {
							if ((Mouse.x >= 660 && Mouse.x <= 719) && (Mouse.y >= 235 && Mouse.y <= 283)) {
								if (Mouse.mkLButton) {
									conse = 5;
									break;
								}
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
#endif
