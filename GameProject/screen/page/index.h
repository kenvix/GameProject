#ifndef PAGE_FIRSTINDEX
#define PAGE_FIRSTINDEX
#include "../../library/global.h"
#include "../../library/view.h"
// �����ʼ��Ϸ���� 1�������Ϸ��¼���� 2��
inline int index_first() {
	MOUSEMSG Mouse;
	while (true) {
	Mouse=GetMouseMsg();//��ȡһ��������Ϣ
	if ((Mouse.x >= 400 && Mouse.x <= 600) && (Mouse.y >= 250 && Mouse.y <= 310)) {
		if (Mouse.mkLButton == WM_LBUTTONDOWN)
			return 1;
		//�ж��Ƿ��� ��ʼ��Ϸ
	}
	if ((Mouse.x >= 400 && Mouse.x <= 600) && (Mouse.y >= 330 && Mouse.y <= 390)) {
		if (Mouse.mkLButton == WM_LBUTTONDOWN)
			return 2;
		//�ж��Ƿ��� ��Ϸ��¼
	}
	}
	FlushMouseMsgBuffer();//���������Ϣ
	cleanup();
	put_background("index.jpg");
}

#endif