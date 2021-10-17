#include <curses.h>
#include <ncursesw/ncurses.h>

#ifndef GAME_GAME_H
#define GAME_GAME_H
#define IS_LIFE 1;
#define IS_NOT_LIFE 0;
#define IS_LIFE_SIMBOL "▒" //▒
#define IS_NOT_LIFE__SIMBOL " "
#define _XOPEN_SOURCE_EXTENDED 1
#define _GNU_SOURCE

int row;
int col;

void init_game();
void start_game();

void render_grid();

int get_neighbours();

#endif //GAME_GAME_H
