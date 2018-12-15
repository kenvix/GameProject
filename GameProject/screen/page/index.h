#ifndef PAGE_FIRSTINDEX
#define PAGE_FIRSTINDEX
#include "../../library/global.h"
#include "../../library/view.h"

// 点击开始游戏返回 1；点击游戏记录返回 2；
inline int show_index() {
	cleanup();
	put_background("index.jpg");
	draw_player_info();
	int result;
	while (true) {
		const MOUSEMSG Mouse = GetMouseMsg();//获取一个鼠标的信息
		if ((Mouse.x >= 400 && Mouse.x <= 600) && (Mouse.y >= 250 && Mouse.y <= 310)) {
			if (Mouse.mkLButton) {
				result = 1;
				break;
			}
			//判断是否点击 开始游戏
		} else if ((Mouse.x >= 400 && Mouse.x <= 600) && (Mouse.y >= 330 && Mouse.y <= 390)) {
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