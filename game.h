#include <curses.h>
#include <ncursesw/ncurses.h>

#ifndef GAME_GAME_H
#define GAME_GAME_H

#define _XOPEN_SOURCE_EXTENDED 1
#define _GNU_SOURCE
#define IS_LIFE 1;
#define IS_NOT_LIFE 0;
#define IS_LIFE_SIMBOL "▒" //▒
#define IS_NOT_LIFE__SIMBOL " "
#define  KEY_SPACE 32
#define  KEY_N 110
#define  KEY_S 32
#define  KEY_P 112
#define  ECS 27

int row, col;

void print_generation();

void init_game();

void start_game();

void game_input();

void render_grid();

int get_neighbours();

int stop_game();

void run_game();

void render_pause();

void render_no_pause();

#endif //GAME_GAME_H
