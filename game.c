#include "game.h"
#include "main.h"
#include <curses.h>
#include <zconf.h>

int cursor_x = 25, cursor_y = 25;

void print_symbol(int coord_x, int coord_y, char *symbol) {
    mvprintw(coord_y, coord_x * 2 - 1, symbol);
    mvprintw(coord_y, coord_x * 2, symbol);
}

void init_game() {

    is_pause = 1;
    print_no_pause();
    generation = 0;
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {
            grid[row][col] = IS_NOT_LIFE;
        }
    }
    // TODO: first render and set cursor
    input_grid_points();

/*
    Examples

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

    // vertical line
    grid[2][10] = IS_LIFE;
    grid[3][10] = IS_LIFE;
    grid[4][10] = IS_LIFE;

    // random
    grid[49][49] = IS_LIFE;
    grid[2][1] = IS_LIFE;
    grid[3][1] = IS_LIFE;
    grid[4][1] = IS_LIFE;
    grid[2][3] = IS_LIFE;
    grid[2][3] = IS_LIFE;

    // Glider
    grid[8][47] = IS_LIFE;
    grid[9][48] = IS_LIFE;
    grid[10][46] = IS_LIFE;
    grid[10][47] = IS_LIFE;
    grid[10][48] = IS_LIFE;
    */

    print_generation();
}

void input_grid_points() {
    print_pause();
    print_actual_grid(false);
    print_cursor(cursor_x, cursor_y);
}

int get_neighbours() {
    int x, y, neighbours_counter = 0;
    for (y = -1; y < 2; y++) {
        for (x = -1; x < 2; x++) {
            /*
             * Check is point in grid. Not count neighbours out of grid
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
    nodelay(stdscr, false); // remove delay and await input
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

void print_pause() {
    mvprintw(14, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    ###############################");
    mvprintw(15, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    #            PAUSE            #");
    mvprintw(16, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), "    ###############################");

    print_cursor(cursor_x, cursor_y);
}

void print_no_pause() {
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
    if (c == KEY_N) {
        print_no_pause();
        nodelay(stdscr, true); // no delay again
        start_game();

    } else if (c == KEY_SPACE && is_pause) {
        render_grid(); // manual render
    } else if (c == ECS) {
        stop_game(); // exit
    } else if (c == KEY_P) {
        print_actual_grid(false);
        if (is_pause) {
            print_no_pause();
            is_pause = 0;
            nodelay(stdscr, true);  // no delay and continue game cycle
            run_game();
        } else {
            print_pause();
            nodelay(stdscr, false);  // no delay for getch
            is_pause = 1;
        }
        // cursor handle
    } else if (c == KEY_UP) {
        // print new cursor re render
        if (cursor_y > 1) {
            cursor_y--; // revers y coordinate
        }
        print_actual_grid(false);
        print_cursor(cursor_x, cursor_y);
        curs_set(0);
        game_input();
    } else if (c == KEY_LEFT) {
        if (cursor_x > 1) {
            cursor_x--;
        }
        print_actual_grid(false);
        print_cursor(cursor_x, cursor_y);
        curs_set(0);
        game_input();
    } else if (c == KEY_RIGHT) {
        if (cursor_x < 51) {
            cursor_x++;
        }
        print_actual_grid(false);
        print_cursor(cursor_x, cursor_y);
        curs_set(0);
        game_input();
    } else if (c == KEY_DOWN) {
        if (cursor_y < 51) {
            cursor_y++; // revers y coordinate
        }
        print_actual_grid(false);
        print_cursor(cursor_x, cursor_y);
        curs_set(0);
        game_input();
    } else if (c == KEY_ENT) {
        if (grid[cursor_y - 1][cursor_x - 1]) {
            grid[cursor_y - 1][cursor_x - 1] = IS_NOT_LIFE
        } else {
            grid[cursor_y - 1][cursor_x - 1] = IS_LIFE
        }
        print_actual_grid(false);
        print_cursor(cursor_x, cursor_y);
        curs_set(0);
        game_input();
    } else {

        mvprintw(12, width_screen - (MENU_WIDTH - MENU_WIDTH_IDENT), " %d ", c);
        // await input on pause
        if (is_pause) {
            game_input();
        }
    }
    // this no delay true
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

            // Life point
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
        }
    }

    // Render new grid
    print_actual_grid(true);
    generation++;
    print_generation();
    curs_set(0); // Hide cursor
    refresh();
    if (!is_pause) {
        usleep(500000);
    }
    game_input();
}

void print_actual_grid(bool set_temp) {
    for (row = 0; row < grid_height; row++) {
        for (col = 0; col < grid_width; col++) {

            if (set_temp == true) {
                grid[row][col] = temp[row][col];
            }
            // render square as double char print
            if (grid[row][col]) {
                print_symbol(col + 1, row + 1, IS_LIFE_SIMBOL);
            } else {
                print_symbol(col + 1, row + 1, IS_NOT_LIFE__SIMBOL);
            }
        }
    }
}