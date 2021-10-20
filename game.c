#include "game.h"
#include "main.h"
#include <curses.h>
#include <zconf.h>


//const int grid_width = WINDOW_WIDTH - MENU_WIDTH - 2;
//const int grid_height = WINDOW_HEIGHT - 2;
//int grid[grid_height][grid_width]; // current
//int temp[grid_height][grid_width]; // temp
int run = 1;

void init_game() {

    is_pause = 0;
    generation = 0;
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {
            grid[row][col] = IS_NOT_LIFE;
        }
    }

    //
//    grid[2][0] = IS_LIFE;
//    grid[3][0] = IS_LIFE;
//    grid[4][0] = IS_LIFE;
    // Dual block
    grid[10][10] = IS_LIFE;
    grid[10][11] = IS_LIFE;
    grid[10][12] = IS_LIFE;
    grid[11][10] = IS_LIFE;
    grid[11][11] = IS_LIFE;
    grid[11][12] = IS_LIFE;
    grid[12][10] = IS_LIFE;
    grid[12][11] = IS_LIFE;
    grid[12][12] = IS_LIFE;

    grid[13][13] = IS_LIFE;
    grid[13][14] = IS_LIFE;
    grid[13][15] = IS_LIFE;
    grid[14][13] = IS_LIFE;
    grid[14][14] = IS_LIFE;
    grid[14][15] = IS_LIFE;
    grid[15][13] = IS_LIFE;
    grid[15][14] = IS_LIFE;
    grid[15][15] = IS_LIFE;
//    grid[3][3] = IS_LIFE;

    // vertical line
//    grid[2][10] = IS_LIFE;
//    grid[3][10] = IS_LIFE;
//    grid[4][10] = IS_LIFE;

    // random
    grid[49][49] = IS_LIFE;
//    grid[2][1] = IS_LIFE;
//    grid[3][1] = IS_LIFE;
//    grid[4][1] = IS_LIFE;
//    grid[2][3] = IS_LIFE;
//    grid[2][3] = IS_LIFE;

    // Glider
    grid[8][47] = IS_LIFE;
    grid[9][48] = IS_LIFE;
    grid[10][46] = IS_LIFE;
    grid[10][47] = IS_LIFE;
    grid[10][48] = IS_LIFE;

    print_generation();
};

int get_neighbours() {
    // TODO : fix algorithm
    int x, y, neighbours_counter = 0;
    for (y = -1; y < 2; y++) {
        for (x = -1; x < 2; x++) {
            /*
             * Check is point in grid. Not count neighbours
             */
            if (
                    0 <= (row + y) &&
                    (row + y) < grid_height &&
                    0 <= (col + x) &&
                    (col + x) < grid_width
                    ) {
                if ((x != 0 || y != 0) && grid[(row + y)][(col + x)] == 1) {
                    neighbours_counter++;
                }
            }
        }
    }
    return neighbours_counter;
}

/*
 * Main game cycle
 */
void run_game() {
    while (!is_pause) {
        render_grid();
    }
    nodelay(stdscr, false); // remove delay and waite input
    game_input();
}

/*
 * Entry game point
 */
void start_game() {
    init_game();
    run_game();
}

/*
 * Exit game
 */
int stop_game() {
    endwin();
    exit(0);
}

/*
 * Print generation counter
 */
void print_generation() {
    if (generation == 0) {
        // Remove old digits
        mvprintw(10, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "          Generation : %d                  ",
                 generation);
    }

    mvprintw(10, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "          Generation : %d", generation);
}

void render_pause() {
    mvprintw(14, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    ###############################");
    mvprintw(15, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    #            PAUSE            #");
    mvprintw(16, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    ###############################");
}

void render_no_pause() {
    mvprintw(14, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "                                   ");
    mvprintw(15, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "                                   ");
    mvprintw(16, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "                                   ");
}

/*
 * Handle user input
 *
 * if is_pause no delay mode
 */
void game_input() {
    int c = getch();
//    mvprintw(20, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "              key code:  %d ", c);
    if (c == KEY_N) {
        render_no_pause();
        nodelay(stdscr, true);
        start_game();

    } else if (c == KEY_SPACE && is_pause) {
        render_grid();
    } else if (c == ECS) {
        stop_game();
    } else if (c == KEY_P) {
        if (is_pause) {
            render_no_pause();
            is_pause = 0;
            nodelay(stdscr, true);  // no delay for getch
            run_game();
        } else {
            render_pause();
//            mvprintw(15, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "            ");
            nodelay(stdscr, false);  // no delay for getch
            is_pause = 1;
        }
    } else {
        if (is_pause) {
            game_input();
        }

    }
}


/*
 * Print game board
 */
void render_grid() {

    int neighbours;
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {
            temp[row][col] = IS_NOT_LIFE;
        }
    }
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {

            // get count neighbours
            neighbours = get_neighbours();

            // Life pint
            if (grid[row][col] == 1) {
                if (neighbours < 2 || neighbours > 3) {
                    temp[row][col] = IS_NOT_LIFE;
                } else {
                    temp[row][col] = IS_LIFE;
                }
                // No Life point
            } else if (grid[row][col] == 0) {
                if (neighbours == 3) {
                    temp[row][col] = IS_LIFE; // new life for 3 neighbours
                } else {
                    temp[row][col] = IS_NOT_LIFE;
                }
            }
//            mvprintw(row + 1, col + 1, "%d", temp[row][col]);
        }
    }

    // Render new grid
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {

            // render square as double char print
            if (grid[row][col]) {
                mvprintw(row + 1, (col + 1) * 2, IS_LIFE_SIMBOL);
                mvprintw(row + 1, (col + 1) * 2 + 1, IS_LIFE_SIMBOL);
            } else {
                mvprintw(row + 1, (col + 1) * 2, IS_NOT_LIFE__SIMBOL);
                mvprintw(row + 1, (col + 1) * 2 + 1, IS_NOT_LIFE__SIMBOL);
            }
            grid[row][col] = temp[row][col];
        }
    }
    generation++;
    print_generation();
    curs_set(0); // Hide cursor
    refresh();
//    if(!is_pause) {
//        usleep(500000);
//    }
    game_input();
}