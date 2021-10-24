/*
 * Leaks check $ valgrind --leak-check=full ./game
 */

// for ncurses linking
#define _XOPEN_SOURCE_EXTENDED 1
#define _GNU_SOURCE

#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>
#include "main.h"

void render_menu() {
    print_generation();

    mvprintw(2, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    ###############################");
    mvprintw(3, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    #    Conway's Game of Life    #");
    mvprintw(4, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    ###############################");


    mvprintw(30, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "            Cursor state");

    mvprintw(32, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "╳╳ - set IS_NOT_LIFE");
    mvprintw(33, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "╬╬ - set LIFE");

    mvprintw(35, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "               Controls");

    mvprintw(37, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "ENTER - change point state");

    mvprintw(39, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "↑ - cursor UP");
    mvprintw(40, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "← - cursor LEFT");
    mvprintw(41, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "→ - cursor RIGHT");
    mvprintw(42, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "↓ - cursor DOWN");

    mvprintw(44, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "S - start");
    mvprintw(45, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "P - pause");
    mvprintw(46, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "N - start new game");

    mvprintw(48, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "SPACE - next generation");
    mvprintw(49, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "ESC - exit");
};

void print_cursor(int cursor_x, int cursor_y) {
    if (grid[cursor_y - 1][cursor_x - 1]) {
        mvaddwstr(cursor_y, cursor_x * 2 - 1, DELETE_SYMBOL);
        mvaddwstr(cursor_y, cursor_x * 2, DELETE_SYMBOL);
    } else {
        mvaddwstr(cursor_y, cursor_x * 2 - 1, INSERT_SYMBOL);
        mvaddwstr(cursor_y, cursor_x * 2, INSERT_SYMBOL);
    }
}

void render_border(WINDOW *window) {
    start_color();
    init_pair(GREEN_CHAR_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(GREEN_BACKGROUND_CHAR_PAIR, COLOR_GREEN, COLOR_GREEN);
    getmaxyx(window, height_screen, width_screen);
    attron(COLOR_PAIR(GREEN_CHAR_PAIR));
    // Corners
    mvaddwstr(0, 0, BORDER_TOP_LEFT);
    mvaddwstr(0, width_screen - 1, BORDER_TOP_RIGHT);
    mvaddwstr(height_screen - 1, 0, BORDER_BOTTOM_LEFT);
    mvaddwstr(height_screen - 1, width_screen - 1, BORDER_BOTTOM_RIGHT);

    // Top and bottom
    for (int x = 1; x < width_screen - 1; x++) {
        mvaddwstr(0, x, BORDER_HORIZONTAL);
        mvaddwstr(height_screen - 1, x, BORDER_HORIZONTAL);
    }

    // Left and right vertical, right menu
    for (int y = 1; y < height_screen - 1; y++) {
        mvhline(y, 0, GREEN_CHAR_PAIR, COLS); // Black background
        mvaddwstr(y, 0, BORDER_VERTICAL);
        mvaddwstr(y, width_screen - 1, BORDER_VERTICAL);
        mvaddwstr(y, width_screen - MENU_WIDTH, BORDER_VERTICAL);
    }

    // menu top and bottom T-like border chars
    mvaddwstr(0, width_screen - MENU_WIDTH, BORDER_TOP_T);
    mvaddwstr(height_screen - 1, width_screen - MENU_WIDTH, BORDER_BOTTOM_T);

}

void render_screen() {
    stdscr = initscr();
    nodelay(stdscr, true);  // no delay for getch
    keypad(stdscr, TRUE);
    noecho();   // hide echo
    clear();
    refresh();
    render_border(stdscr);
    render_menu();
    start_game();
    curs_set(0);
}

void set_window_size() {
    // system call with params passing
    sprintf(string_buffer, "resize -s %d %d > nul", WINDOW_HEIGHT, WINDOW_WIDTH);
    system(string_buffer);
}

void do_resize(int dummy) {
    endwin();
    render_screen();
}

int main() {
    setlocale(LC_ALL, "");
    set_window_size();
    render_screen();
    signal(SIGWINCH, do_resize);

    getch();
    endwin(); // close ncurses
    return 0;
}