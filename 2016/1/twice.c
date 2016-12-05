#include <stdio.h>
#include <stdlib.h>

#define VERBOSE 0 // 1 means print debug statement
#define GRIDSIZE 256 // maybe a bit bigger than needed, but don't care
/* #define GRIDSIZE 20 */ // big enough for short example input

// types/constants
typedef enum bearing { NORTH, EAST, SOUTH, WEST } bearing;
const int bearings[][2] = {
    {0,1},  // N
    {1,0},  // E
    {0,-1}, // S
    {-1,0}, // W
}; // didn't use this as much as I thought I would

// functions
void turn(int); // sets heading
int move(void); // steps forward
void measure(void); // actual work
int arrived(); // returns true when coord already visited
void init(int grid[][GRIDSIZE]); // sets whole grid to 0

// globals
FILE *input; // input
int coords[2] = {0, 0}; // you are here
int heading = NORTH; // start facing N, doesn't really matter
int grid[GRIDSIZE][GRIDSIZE]; // map of where you step

int main(void) {

    // open file
    input = fopen("input.txt", "r");
    if (input == NULL) {
        puts("Error opening file!");
        exit(1); // sometimes I rename this and forget
    }

    init(grid);

    // actual work
    measure();

#if VERBOSE == 1
    // debug draw
    for (int x = 0; x < GRIDSIZE; ++x) {
        for (int y = 0; y < GRIDSIZE; ++y) {
            printf("%d", grid[x][y]);
        }
        putchar('\n');
    }
#endif

    // final output
    printf("%d\n", abs(coords[0]) + abs(coords[1]));

    fclose(input);
    return 0;
}

// this function used to be called "main" lol but I put the set up stuff there
// and the actual work here
void measure() {
    char c; // char from input

    // Input looks like: R4, L8, L4
    // The following block finds the L/R letters, converts them to turns and
    // calls move.  Move will get the number and move forward by that many steps
    // until it arrives at the destination.  Other characters [, ] are ignored.

    // actual work
    do {
#if VERBOSE == 1
        puts("read");
#endif
        c = fgetc(input);
        if (c == 'R') {
            turn(1);
            if (move()) return; // stops if moving brought us to destination
            // I'm not sure why other ways of doing this weren't OK
        }
        if (c == 'L') {
            turn(-1);
            if (move()) return;
        }
    } while (c != EOF);

}

// returns true if the current coords on grid have already been visited
int arrived() {
#if VERBOSE == 1
    printf("accessing: x:%d(%d), y:%d(%d) :: ", coords[0], coords[0]+GRIDSIZE/2, coords[1], coords[1]+GRIDSIZE/2);
#endif
    int x = grid[coords[0] + GRIDSIZE/2][coords[1] + GRIDSIZE/2];
#if VERBOSE == 1
    printf("%d\n", x);
#endif
    return x;
}

// set heading by 90 degree turn left(-1) or right(1)
// basically incrementing with wrapping at 4
void turn(int direction) {
    heading += direction;
    if (heading > 3) heading = NORTH;
    if (heading < 0) heading = WEST;
}

// updates the coordinates by travelling forwards based on current heading
// used to be short multiplication, but now we need to draw a line, so it loops
// over distance scalar 1 by one to check in case we arrive at destination while
// moving forward
int move(void) {
    int distance;
    fscanf(input, "%d", &distance);
    for (int i = 0; i < distance; ++i) {
        // step forward
        coords[0] += bearings[heading][0];
        coords[1] += bearings[heading][1];
#if VERBOSE == 1
        puts("stepping...");
#endif

        // stop moving if we cross our own path
        if (arrived()) return 1;

#if VERBOSE == 1
        puts("step");
#endif
        // mark this coord as stepped on
        grid[coords[0] + GRIDSIZE/2][coords[1] + GRIDSIZE/2] = 1;
    }
    return 0;
}

// sets all grid values to 0 omfg you have no idea what bad things happen when
// you don't do this...
void init(int grid[][GRIDSIZE]) {
    for (int x = 0; x < GRIDSIZE; ++x) {
        for (int y = 0; y < GRIDSIZE; ++y) {
            grid[x][y] = 0;
        }
    }
}
