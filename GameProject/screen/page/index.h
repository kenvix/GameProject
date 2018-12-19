#ifndef PAGE_FIRSTINDEX
#define PAGE_FIRSTINDEX
#include "../../library/global.h"
#include "../../library/view.h"

// 点击开始游戏返回 1；点击游戏记录返回 2；
inline int show_index() {
	put_background("index.jpg");
	draw_player_info();
	int result;
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();//获取一个鼠标的信息
		if (((Mouse.x >= 323 && Mouse.x <= 515) && (Mouse.y >= 372 && Mouse.y <= 562)) || ((Mouse.x >= 668 && Mouse.x <= 860) && (Mouse.y >= 372 && Mouse.y <= 562))) {
			if (Mouse.mkLButton) {
				result = 1;
				break;
			}
			//判断是否点击 开始游戏
		} else if ((Mouse.x >= 490 && Mouse.x <= 682) && (Mouse.y >= 202 && Mouse.y <= 392)) {
			if (Mouse.mkLButton) {
				result = 2;
				break;
			}
			//判断是否点击 游戏记录
		}
	}
	FlushMouseMsgBuffer();//消除鼠标信息
	return result;
}

#endif