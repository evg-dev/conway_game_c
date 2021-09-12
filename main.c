#define _XOPEN_SOURCE_EXTENDED 1
//#define NCURSES_WIDECHAR 1
#define _XOPEN_SOURCE 400
#define _GNU_SOURCE

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <signal.h>
//#include <ncurses.h>
//#include <ncursesw/ncurses.h>
#include <locale.h>
//#include <ncurses.h>
#include <wchar.h>


//#include <ncursesw/ncurses.h>
//

//#define ANSI_COLOR_GREEN   "\x1b[32m"
//
//void mvwaddwstr(WINDOW *pSt, int i, int i1, const wchar_t *pInt);
//int mvwaddwstr(WINDOW *win, int y, int x, const wchar_t *wstr);

void render_screen() {
    initscr();

//    raw();
//    keypad(stdscr, TRUE);
    noecho();

//    for(int i = 0; i < 10; i++){
//        mvaddwstr(0, i, L"\u2550");
//    }
//    for(int i = 0; i < 6; i++){
//        mvaddwstr(1, i, L"\u2550");
//    }


    clear();
    refresh();


//    chtype x;
//    x='H';
//    addch(x);
//    for( int i=128 ; i<=255 ; i++ ) /*ASCII values ranges from 0-255*/
//    {

//        printf("ASCII value of character %c \n", i);
//    }
//    for(int i = 0; i < 10; i++){
//        mvaddch(0, i, L'\u2592');
//    }
//    mvaddch(100,100, L'\u2605');
//    printf(ANSI_COLOR_GREEN "\u2550\u2550\u2550\u2550\n");
//    const chtype * s =

    wborder(stdscr, L'\u2550', '#', '#', '#', '#', '#', '#', '#'); //Draw border
//    printw((const char *) L'\u2592');
//    printf("Hello МирЪ !!! 播 \n");
    const wchar_t *wstr = L"<\u2603\u26c4\U0001F638>";
    stdscr = initscr();
    mvwaddwstr(stdscr, 0, 0, wstr);
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