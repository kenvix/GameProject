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
			if ((Mouse.x >= 488 && Mouse.x <= 552) && (Mouse.y >= 100 && Mousew.y <= 160)) {
				if (Mouse.mkLButton) {
					conse= 1;
					break;
				}
			}
			else
				if ((Mouse.x >= 676 && Mouse.x <= 738) && (Mouse.y >= 243 && Mousew.y <= 299)) {
					if (Mouse.mkLButton) {
						conse= 2;
						break;
					}
				}
				else
					if ((Mouse.x >= 600 && Mouse.x <= 661) && (Mouse.y >= 424 && Mousew.y <= 481)) {
						if (Mouse.mkLButton) {
							conse = 3;
							break;
						}
					}
					else
						if ((Mouse.x >= 382 && Mouse.x <= 442) && (Mouse.y >= 424 && Mousew.y <= 481)) {
							if (Mouse.mkLButton) {
								conse = 4;
								break;
							}
						}
						else
							if ((Mouse.x >= 307 && Mouse.x <= 371) && (Mouse.y >= 243 && Mousew.y <= 299)) {
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
