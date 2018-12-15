#ifndef PAGE_FIRST
#define PAGE_FIRST
#include "../../library/global.h"
#include "../../library/view.h"

inline void show_first() {
	cleanup();
	put_background("global.jpg");
}
#endif