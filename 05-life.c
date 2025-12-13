#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define GRID_COLS 70
#define GRID_ROWS 40
#define GRID_CELLS (GRID_COLS*GRID_ROWS)
#define ALIVE '*'
#define DEAD '-'
#define SPEED_MS 500000

/* Translate the specified x,y grid point into the index in the linear array.
 * This function implements wrapping, so both negative and positive
 * coordinates that are out of the grid will wrap around. */
int coord2index(int x, int y) {
    if (x < 0) {
        x = (-x) % GRID_COLS;
        x = GRID_COLS - x;
    }
    if (y < 0) {
        y = (-y) % GRID_ROWS;
        y = GRID_ROWS - y;
    }
    if (x >= GRID_COLS) x = x % GRID_COLS;
    if (y >= GRID_ROWS) y = y % GRID_ROWS;

    return y * GRID_COLS + x;
}

/* The function sets the specified cell at x,y to the specifie state. */
void set_cell(char *grid, int x, int y, char state) {
    grid[coord2index(x, y)] = state;
}

/* The function returns the state of the grid at x,y */
char get_cell(char *grid, int x, int y) {
    return grid[coord2index(x, y)];
}

/* Show the grid on the screen, clearing the terminal using the
 * required VT100 escape sequence. */
void print_grid(char *grid) {
    printf("\033[3J\033[H\033[2J"); // Clear screen
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            printf("%c ", get_cell(grid, x, y));
        }
        printf("\n");
    }
}

/* Set all the grid cels to the specified state */
void set_grid(char *grid, char state) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            set_cell(grid, x, y, state);
        }
    }
}

/* Return the number of living cells neighbors of x,y. */
int count_living_neighbors(char *grid, int x, int y) {
    int alive = 0;
    for (int yo = -1; yo < 2; yo++) {
        for (int xo = -1; xo < 2; xo++) {
            if (xo == 0 && yo == 0) continue;
            if (get_cell(grid, x+xo, y+yo) == ALIVE) alive++;
        }
    }
    return alive;
}

/* Compute the new state of Game of Life according to its rules. */
void compute_new_state(char *old, char *new) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            int n_alive = count_living_neighbors(old, x, y);
            int new_state;
            if (get_cell(old, x, y) == ALIVE) {
                new_state = (n_alive == 2 || n_alive == 3) ? ALIVE : DEAD;
            } else {
                new_state = (n_alive == 3) ? ALIVE : DEAD;
            }
            set_cell(new, x, y, new_state);
        }
    }
}

/* Place a glider at position x,y as upper left corner */
void place_glider(char *grid, int x, int y) {
    set_cell(grid, x+2, y  , ALIVE);
    set_cell(grid, x  , y+1, ALIVE);
    set_cell(grid, x+2, y+1, ALIVE);
    set_cell(grid, x+1, y+2, ALIVE);
    set_cell(grid, x+2, y+2, ALIVE);
}

/* Get a random cell state */
char random_state() {
    int r = (rand() % 100) > 70;
    if (r == 1) {
        return ALIVE;
    } else {
        return DEAD;
    }
}

/* Given a grid, set it to a random state in each cell */
void set_grid_random(char *grid) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            set_cell(grid, x, y, random_state());
        }
    }
}

/* Given two grids, copy the state of all cells from old_grid to new_grid */
void copy_grid(char *old_grid, char *new_grid) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            set_cell(new_grid, x, y, get_cell(old_grid, x, y));
        }
    }
}

int main(void) {
    srand(time(NULL));

    char old_grid[GRID_CELLS];
    char new_grid[GRID_CELLS];
    // set_grid(old_grid, DEAD);
    // set_grid(new_grid, DEAD);
    // print_grid(old_grid);
    // place_glider(old_grid, 5, 5);
    set_grid_random(old_grid);
    copy_grid(old_grid, new_grid);
    print_grid(old_grid);
    sleep(1);

    char *old = old_grid;
    char *new = new_grid;
    while(1) {
        compute_new_state(old, new);
        print_grid(new);
        usleep(SPEED_MS);

        // Swap pointers
        char *tmp = old;
        old = new;
        new = tmp;
    }

    return 0;
}
