#ifndef PAGE_FIRSTINDEX
#define PAGE_FIRSTINDEX
#include "../../library/global.h"
#include "../../library/view.h"
// 点击开始游戏返回 1；点击游戏记录返回 2；
inline int index_first() {
	MOUSEMSG Mouse;
	while (true) {
	Mouse=GetMouseMsg();//获取一个鼠标的信息
	if ((Mouse.x >= 400 && Mouse.x <= 600) && (Mouse.y >= 250 && Mouse.y <= 310)) {
		if (Mouse.mkLButton == WM_LBUTTONDOWN)
			return 1;
		//判断是否点击 开始游戏
	}
	if ((Mouse.x >= 400 && Mouse.x <= 600) && (Mouse.y >= 330 && Mouse.y <= 390)) {
		if (Mouse.mkLButton == WM_LBUTTONDOWN)
			return 2;
		//判断是否点击 游戏记录
	}
	}
	FlushMouseMsgBuffer();//消除鼠标信息
	cleanup();
	put_background("index.jpg");
}

#endif