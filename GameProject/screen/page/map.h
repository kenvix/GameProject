#pragma once
#ifndef PAGE_FIRSTMAP
#define PAGE_FIRSTMAP
#include "../../library/global.h"
#include "../../library/view.h"

/*
点击第一个地图 返回1
点击第二个地图 返回2
点击第三个地图 返回3
点击第四个地图 返回4
点击返回键 返回5
*/
inline int show_map() {
	cleanup();
	put_background("map.jpg");
	draw_player_info();
	int conse;
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 45 && Mouse.x <= 715) && (Mouse.y >= 50 && Mouse.y <= 145) {
			if (Mouse.mkLButton) {
				conse=1;
				break;
			}
		}
		else if (Mouse.x >= 45 && Mouse.x <= 715) && (Mouse.y >= 145 && Mouse.y <= 240) {
			if (Mouse.mkLButton) {
				conse=2;
				break;
			}
		}
		else if (Mouse.x >= 45 && Mouse.x <= 715) && (Mouse.y >= 240 && Mouse.y <= 340) {
			if (Mouse.mkLButton) {
				conse = 3;
				break;
			}
		}
		else if (Mouse.x >= 45 && Mouse.x <= 715) && (Mouse.y >= 340 && Mouse.y <= 435) {
			if (Mouse.mkLButton) {
				conse = 4;
				break;
			}
		}
		else if (Mouse.x >= 45 && Mouse.x <= 715) && (Mouse.y >= 435 && Mouse.y <= 530) {
			if (Mouse.mkLButton) {
				conse = 5;
				break;
			}
		}
	}
	FlushMouseMsgBuffer();
	return conse;
}
#endif
