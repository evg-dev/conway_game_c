// for ncurses linking
#define _XOPEN_SOURCE_EXTENDED 1
#define _GNU_SOURCE

#include <stdio.h>
#include <curses.h>
#include <ncurses.h>
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


void render_border(WINDOW *window) {
    int width_screen, height_screen;
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
//    raw();
//    keypad(stdscr, TRUE);
    noecho();

//    for(int i = 0; i < 6; i++){
//        mvaddwstr(1, i, L"\u2550");
//    }
    clear();
    refresh();
    start_color();

    init_pair(GREEN_CHAR_PAIR, COLOR_GREEN, COLOR_BLACK);
//    printf("%ls", L"\u2563\n");
//    printf( "%ls", L"\u2563");
    render_border(stdscr);
    curs_set(0);


//    mvaddnwstr(0,0, star, -1);
//    mvwaddnwstr(stdscr, 1,1, star, 10);
//    add_wchstr(WACS_D_ULCORNER);
//    add_wchstr(WACS_D_WLINE);
//    add_wchstr(WACS_D_ULCORNER);
//    add_wchstr(WACS_D_ULCORNER);
//    add_wchstr(WACS_D_ULCORNER);
//    mvwadd_wchnstr(stdscr,0,2, WACS_D_HLINE,10);
//    mvaddwstr(0, 0, WACS_D_ULCORNER);
//    printw("h %d, w %d", height_screen, width_screen);
//    const wchar_t* star = L"\x2551";





//     should fill the left half of the
    // terminal window with filled block characters
//    int i, j;
//    for (i = 0; i < height_screen; i++) {
//
//        for (j = 0; j < width_screen; j++) {
//            attron(COLOR_PAIR(GREEN_CHAR_PAIR));
//            mvaddch(i, j, L'\u2550');
//        }
//    }

//    init_pair(2, COLOR_BLACK, COLOR_GREEN);

//    attron(COLOR_PAIR(1));
//    mvaddch(0, 0, '*');
//
//    wattron(stdscr, COLOR_PAIR(1));
//    mvwprintw(stdscr,1,1,"colored text");
//    printw("This should be printed in black with a red background!\n");

//    attron(COLOR_PAIR(2));
//    printw("And this in a green background!\n");
//    for(int i = 0; i < 10; i++){
//        mvaddch(0, i, L'\u2592');
//    }
//    mvaddch(0,0, L'\u2605');
//    printf(ANSI_COLOR_GREEN "\u2550\u2550\u2550\u2550\n");
//    const chtype * s =
//    border()
//    wborder(stdscr, WACS_D_ULCORNER, '#', '#', '#', '#', '#', '#', '#'); //Draw border
//    printw((const char *) L'\u2592');
//    printf("Hello МирЪ !!! 播 \n");
//    const wchar_t *wstr = L"<\u2550\u2550\u2550>";

//    mvwaddwstr(stdscr, 0, 0, wstr);
//    addchstr(L'\u2592');
//      234", "\u1234", "\u1234", "\u1234" );
    getch();
}


void do_resize(int dummy) {
    endwin();
    render_screen();

//    printf("dummy %d", dummy);
}

int main() {
    setlocale(LC_ALL, "");
    render_screen();
    signal(SIGWINCH, do_resize);
    getch();
    endwin();                  // close ncurses
    return 0;
}



//int main() {
//    setlocale(LC_ALL, ""); // must be caled before initscr
//    WINDOW *win = initscr();
//
//    int w, h;
//    getmaxyx(win, h, w);
//
//    // should fill the left half of the
//    // terminal window with filled block characters
//    int i, j;
//    for (i = 0; i < h; i++) {
//        for (j = 0; j < w/2; j++) {
//            mvaddch(i, j, L'\u2605');
//        }
//    }
//
//    refresh(); // show changes
//    getch();   // wait for user input
//    endwin();  // kill window
//
//    return 1;
//}