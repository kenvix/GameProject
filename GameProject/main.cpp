#include <cstdio>
#include <graphics.h>
#include<conio.h>
#include "library/view.h"
#include "library/global.h"
#include "library/function.h"
#include <cstring>
#include "screen/page/first.h"
#include "screen/page/map.h"
#include "library/music.h"
#include "screen/page/index.h"
#include "screen/page/record.h"
#include "screen/page/game.h"
#define DEFAULT_NAME (char*) "Unnamed Player"

GamePlayer* player = nullptr;
GameRound* rounds_basic = nullptr;
unsigned rounds_num = 0;

FILE* file_player = nullptr;
FILE* file_rounds_basic = nullptr;
FILE* file_rounds_index = nullptr;

int main(int argc, char* argv[]) {
	create_window();
	if(!dir_exists("data"))
		create_directory("data");
	db_init("data/player.dat", &file_player);
	db_init("data/rounds.dat", &file_rounds_basic);
	db_init("data/rounds_index.dat", &file_rounds_index);
	rounds_basic = db_read_round(file_rounds_basic, file_rounds_index, &rounds_num);
	player = db_read_player(file_player);
	music_init("background.mp3");
	music_play();
	if(strlen(player->name) < 1) {
		player->name = DEFAULT_NAME;
		player->name_length = strlen(DEFAULT_NAME);
		db_write_player(file_player, player);
	}
	INDEX_NODE:
	int selection = show_index();
	int selected_map = -1;
	std::vector<std::string> maps = get_map_list();
	switch (selection) {
		case 1:
			MAP_NODE:
			selected_map = show_map(maps);
			if(selected_map == 0) {
				goto INDEX_NODE;
			} else {
				if(show_game(get_map_info(maps[selected_map-1].c_str())) == 1) {
					show_record();
					goto INDEX_NODE;
				} else {
					goto MAP_NODE;
				}
			}
			break;

		case 2:
			show_record();
			goto INDEX_NODE;
			break;
	}
	fclose(file_player);
	fclose(file_rounds_index);
	fclose(file_rounds_basic);
	return 0;
}
