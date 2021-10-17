/*
 * Leaks check $ valgrind --leak-check=full ./game
 */

// for ncurses linking
#define _XOPEN_SOURCE_EXTENDED 1
#define _GNU_SOURCE

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>
#include "main.h"

//#include <wchar.h>
//#include <ncurses.h>


void render_menu() {
    mvprintw(1, width_screen - 45, "S - start");
    mvprintw(2, width_screen - 45, "P - pause");
    mvprintw(3, width_screen - 45, "N - start new game");
    mvprintw(4, width_screen - 45, "ESC - exit");
};


void render_border(WINDOW *window) {
    start_color();
    init_pair(GREEN_CHAR_PAIR, COLOR_GREEN, COLOR_BLACK);
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
        mvaddwstr(y, width_screen - 49, BORDER_VERTICAL);
    }

    // menu top and bottom T-like border chars
    mvaddwstr(0, width_screen - 49, BORDER_TOP_T);
    mvaddwstr(height_screen - 1, width_screen - 49, BORDER_BOTTOM_T);

}

void render_screen() {
    stdscr = initscr();
    keypad(stdscr, TRUE);
    noecho();
    clear();
    refresh();
    render_border(stdscr);
    render_menu();
    curs_set(0);

    handle_input();
}

void handle_input() {
    while (run) {
        int c = getch();
        if (c == KEY_UP) {
//            int myIntValue = 20;
//            wchar_t m_reportFileName[256];
//
//            swprintf_s(m_reportFileName, L"%d", myIntValue);
//
//            wprintf(L"%s\n", m_reportFileName);
            mvprintw(x_cursor, y_cursor, "%d", 'a');
//            getch();
        }

        if (c == KEY_DOWN) {
            mvprintw(x_cursor, y_cursor, "%d", 'b');
        }

        if (c == KEY_LEFT) {
            mvprintw(x_cursor, y_cursor, "%d", 'c');
        }

        if (c == KEY_RIGHT) {
            mvprintw(x_cursor, y_cursor, "%d", 'd');
        } else {
            mvprintw(x_cursor, y_cursor, "%d", c);
        }

    }
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
    endwin();                  // close ncurses
    return 0;
}