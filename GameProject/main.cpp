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

void show_init_error(LPCTSTR msg, int code = 1) {
	RECT rect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	drawtext(msg, &rect, DT_SINGLELINE | DT_CENTER);
	_getch();
	exit(code);
}

void play_background_music() {
	music_init("background.mp3");
	music_play();
}

int main(int argc, char* argv[]) {
	create_window();
	if(!dir_exists("data"))
		create_directory("data");
	int flag_database_error = 0;
	db_init("data/player.dat", &file_player);
	if(errno) flag_database_error = 1;
	db_init("data/rounds.dat", &file_rounds_basic);
	if(errno) flag_database_error = 2;
	db_init("data/rounds_index.dat", &file_rounds_index);
	if(errno) flag_database_error = 3;
	if(flag_database_error > 0)
		show_init_error("FATAL: Unable to open database file: File inaccessible or locked. ", 2);
	rounds_basic = db_read_round(file_rounds_basic, file_rounds_index, &rounds_num);
	player = db_read_player(file_player);
	DWORD player_name_length;
	GetUserName(player->name, &player_name_length);
	player->name_length = player_name_length;
	play_background_music();
	INDEX_NODE:
	int selection = show_index();
	int selected_map = -1;
	std::vector<std::string> maps = get_map_list();
	switch (selection) {
	case 1:
		MAP_NODE:
		int difficulty;
		selected_map = show_map(maps, &difficulty);
		if (selected_map == 0) {
			goto INDEX_NODE;
		}
		else {
			int game_result = show_game(get_map_info(maps[selected_map - 1].c_str()), difficulty);
			play_background_music();
			if (game_result == 1) {
				show_record();
				goto INDEX_NODE;
			}
			else {
				goto MAP_NODE;
			}
		}
		break;

	case 2:
		show_record();
		goto INDEX_NODE;
		break;

	case 3:
		show_help();
		goto INDEX_NODE;
		break;
	}
	fclose(file_player);
	fclose(file_rounds_index);
	fclose(file_rounds_basic);
	return 0;
}
