#pragma once
#pragma once
#ifndef PAGE_FIRSTMAP
#define PAGE_FIRSTMAP
#include "../../library/global.h"
#include "../../library/view.h"
/*
������ؼ� ����ֵΪ0
�����һ�� ����ֵΪ1
����ڶ��� ����ֵΪ2
��������� ����ֵΪ3
������Ĺ� ����ֵΪ4
�������� ����ֵΪ5

*/
inline int show_map() {
	cleanup();
	put_background("map.jpg");
	int conse;
	while (true)
	{
		const MOUSEMSG Mouse = GetMouseMsg();
		if ((Mouse.x >= 939 && Mouse.x <= 1011) && (Mouse.y >= 547 && Mouse.y <= 600)) {
			if (Mouse.mkLButton) {
				conse= 0;
				break;
			}
		}
		else
			if ((Mouse.x >= 482 && Mouse.x <= 542) && (Mouse.y >= 95 && Mousew.y <= 145)) {
				if (Mouse.mkLButton) {
					conse= 1;
					break;
				}
			}
			else
				if ((Mouse.x >= 295 && Mouse.x <= 357) && (Mouse.y >= 235 && Mousew.y <= 283)) {
					if (Mouse.mkLButton) {
						conse= 2;
						break;
					}
				}
				else
					if ((Mouse.x >= 366 && Mouse.x <= 423) && (Mouse.y >= 415 && Mousew.y <= 464)) {
						if (Mouse.mkLButton) {
							conse = 3;
							break;
						}
					}
					else
						if ((Mouse.x >= 563 && Mouse.x <= 622) && (Mouse.y >= 415 && Mousew.y <= 464)) {
							if (Mouse.mkLButton) {
								conse = 4;
								break;
							}
						}
						else
							if ((Mouse.x >= 660 && Mouse.x <= 719) && (Mouse.y >= 235 && Mousew.y <= 283)) {
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
