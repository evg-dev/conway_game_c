/*
 * Leaks check $ valgrind --leak-check=full ./game
 * */

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

// color pair
#define GREEN_CHAR_PAIR 1
// border symbols
#define  BORDER_TOP_LEFT L"\u2554"    // ╔
#define BORDER_TOP_RIGHT L"\u2557"    // ╗
#define BORDER_BOTTOM_RIGHT L"\u255D" // ╝
#define BORDER_BOTTOM_LEFT L"\u255A"  // ╚
#define BORDER_HORIZONTAL L"\u2550"   // ═
#define BORDER_VERTICAL L"\u2551"     // ║


int width_screen, height_screen;
int x_cursor = 10, y_cursor = 10;
int run = 1;

void handle_input();

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
    for (int i = 1; i < width_screen - 1; i++) {
        mvaddwstr(0, i, BORDER_HORIZONTAL);
        mvaddwstr(height_screen - 1, i, BORDER_HORIZONTAL);
    }

    // Left and right vertical
    for (int i = 1; i < height_screen - 1; i++) {
        mvaddwstr(i, 0, BORDER_VERTICAL);
        mvaddwstr(i, width_screen - 1, BORDER_VERTICAL);
    }
}

void render_screen() {
    stdscr = initscr();
    keypad(stdscr, TRUE);
    noecho();
    clear();
    refresh();
    render_border(stdscr);
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


void do_resize(int dummy) {
    endwin();
    render_screen();
}

int main() {
    setlocale(LC_ALL, "");

    render_screen();
    signal(SIGWINCH, do_resize);

    getch();
    endwin();                  // close ncurses
    return 0;
}