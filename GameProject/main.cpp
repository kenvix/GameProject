#include <cstdio>
#include <graphics.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[]) {
	printf("Initializing graph %dx%d", WINDOW_WIDTH, WINDOW_HEIGHT);
#ifdef _DEBUG
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, SHOWCONSOLE);
#else 
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
#endif
	IMAGE global_background;
	loadimage(&global_background, "resource/background/global_background.jpg");
	putimage(0, 0, &global_background);
	getchar();
	return 0;
}
