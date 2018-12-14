#include <cstdio>
#include <graphics.h>

#include "library/view.h"
#include "library/global.h"
#include "library/function.h"
#include <cstring>

extern GamePlayer* player;
extern GameRound* rounds;

int main(int argc, char* argv[]) {
	create_window();
	put_background();
	if(!dir_exists("data"))
		create_directory("data");
	FILE* file_player = nullptr;
	db_init("data/player.dat", &file_player);
	FILE* file_rounds = nullptr;
	db_init("data/file_rounds.dat", &file_rounds);
	
	getchar();
	return 0;
}
