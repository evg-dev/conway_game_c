/*
 * Leaks check $ valgrind --leak-check=full ./game
 * */

#ifndef GAME_MAIN_H
#define GAME_MAIN_H

// for ncurses linking
#define _XOPEN_SOURCE_EXTENDED 1
#define _GNU_SOURCE

#include <stdio.h>
#include <curses.h>
//#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>
#include <wchar.h>
#include "game.h"
// color pair
#define GREEN_CHAR_PAIR 1
// border symbols
#define  BORDER_TOP_LEFT L"\u2554"    // ╔
#define BORDER_TOP_RIGHT L"\u2557"    // ╗
#define BORDER_BOTTOM_RIGHT L"\u255D" // ╝
#define BORDER_BOTTOM_LEFT L"\u255A"  // ╚
#define BORDER_HORIZONTAL L"\u2550"   // ═
#define BORDER_VERTICAL L"\u2551"     // ║
#define BORDER_TOP_T L"\u2566"        // ╦
#define BORDER_BOTTOM_T L"\u2569"     // ╩
// window size
#define WINDOW_WIDTH 150
#define WINDOW_HEIGHT 50
#define MENU_WIDTH 49
#define MENU_WIDTH_IDENT 4

char string_buffer[32];
int width_screen, height_screen;
int x_cursor = 10, y_cursor = 10;
int run = 1;


void handle_input();

void render_screen();

void render_menu();

void do_resize(int dummy);

void set_window_size();

void render_border(WINDOW *window);

#endif //GAME_MAIN_H