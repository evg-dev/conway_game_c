#include "game.h"
#include "main.h"
#include <curses.h>


//const int grid_width = WINDOW_WIDTH - MENU_WIDTH - 2;
//const int grid_height = WINDOW_HEIGHT - 2;
//int grid[grid_height][grid_width]; // current
//int temp[grid_height][grid_width]; // temp

void init_game() {

    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {
            grid[row][col] = IS_NOT_LIFE;
        }
    }

    grid[2][10] = IS_LIFE;
    grid[3][10] = IS_LIFE;
    grid[4][10] = IS_LIFE;
//    grid[2][1] = IS_LIFE;
//    grid[3][1] = IS_LIFE;
//    grid[4][1] = IS_LIFE;
//    grid[2][3] = IS_LIFE;
//    grid[2][3] = IS_LIFE;

};


void start_game() {
    init_game();
    render_grid();
}

void render_grid() {

    int x;
    int y;
    int neighbours;
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {
            temp[row][col] = IS_NOT_LIFE;
        }
    }
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {

            // get count neighbours
            neighbours = 0;
            int c = 0;
            for (y = -1; y < 2; y++) {
                for (x = -1; x < 2; x++) {
                    // Check is point in grid
                    if (
                            0 <= (row + y) &&
                            (row + y) < grid_height &&
                            0 <= (col + x) &&
                            (col + x) < grid_width
                            ) {

                        if ((x != 0 || y != 0) && grid[(row + y)][(col + x)] == 1) {
                            c++;
                            neighbours++;
//                            mvprintw(row + 1, col + 1, "%d", x);
                        }
                    }
                }
            }


            // Life
//            mvprintw(row + 1, col + 1, "%d",c);
            if (grid[row][col] == 1) {
                if (neighbours < 2 || neighbours > 3) {
                    temp[row][col] = IS_NOT_LIFE;
//                    mvprintw(row + 1, col + 1, "1");
                } else {
                    temp[row][col] = IS_LIFE;
//                    mvprintw(row + 1, col + 1, "2");
                }

                // No Life
            } else if (grid[row][col] == 0) {
//                mvprintw(row + 1, col + 1, "%d", neighbours);
                if (neighbours == 3) {
                    temp[row][col] = IS_LIFE;
//                    mvprintw(row + 1, col + 1, "3");
                } else {
                    temp[row][col] = IS_NOT_LIFE;
//                    mvprintw(row + 1, col + 1, "4");
                }
            }
//            mvprintw(row + 1, col + 1, "%d", temp[row][col]);
        }
    }


    // Render new grid
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {
            grid[row][col] = temp[row][col];
//            getmaxyx(window, height_screen, width_screen);
//            attron(COLOR_PAIR(GREEN_CHAR_PAIR));

            if (temp[row][col]) {
//                attron(COLOR_PAIR(GREEN_BACKGROUND_CHAR_PAIR));
                mvprintw(row + 1, col + 2, IS_LIFE_SIMBOL);
//                mvaddwstr(row + 1, col + 2, BORDER_VERTICAL);
            } else {
//                attron(COLOR_PAIR(GREEN_CHAR_PAIR));
                mvprintw(row + 1, col + 2, IS_NOT_LIFE__SIMBOL);
//                mvaddwstr(row + 1, col + 2, BORDER_VERTICAL);
            }
//            mvprintw(row + 1, col + 2, "%d", ░);

//                mvprintw(10, 10, "%d, %d", grid_width, grid_height);
//            mvprintw(row + 1, col + 1, "%d", temp[row][col]);
        }
    }

    int c = getch();
    if (c == KEY_UP) {
        render_grid();
    }
}