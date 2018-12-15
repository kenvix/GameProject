#include <cstdio>
#include <graphics.h>

#include "library/view.h"
#include "library/global.h"
#include "library/function.h"
#include <cstring>
#include "screen/page/first.h"
#include "library/music.h"
#include "screen/page/index.h"
#define DEFAULT_NAME (char*) "Unnamed Player"

GamePlayer* player = nullptr;
GameRound* rounds_basic = nullptr;
unsigned rounds_num = 0;

int main(int argc, char* argv[]) {
	create_window();
	if(!dir_exists("data"))
		create_directory("data");
	FILE* file_player = nullptr;
	db_init("data/player.dat", &file_player);
	FILE* file_rounds_basic = nullptr;
	db_init("data/rounds.dat", &file_rounds_basic);
	FILE* file_rounds_index = nullptr;
	db_init("data/rounds_index.dat", &file_rounds_index);
	rounds_basic = db_read_round(file_rounds_basic, file_rounds_index, &rounds_num);
	player = db_read_player(file_player);
	music_play("background.mp3");
	if(strlen(player->name) < 1) {
		player->name = DEFAULT_NAME;
		player->name_length = strlen(DEFAULT_NAME);
		db_write_player(file_player, player);
	}
	show_index();
	draw_player_info();
	
	_getch();
	fclose(file_player);
	fclose(file_rounds_index);
	fclose(file_rounds_basic);
	return 0;
}
