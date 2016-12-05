#include <stdio.h>
#include <stdlib.h>

// I wrote more explanations in twice.c, it's basically the same but with quite
// a bit more complexity because it requires keeping track of where you step and
// this one doesn't

// types/constants
typedef enum bearing { NORTH, EAST, SOUTH, WEST } bearing;
const int bearings[][2] = {
    {0,1},  // N
    {1,0},  // E
    {0,-1}, // S
    {-1,0}, // W
};

// functions
void turn(int direction);
void move(void);

// globals
FILE *input; // input
int coords[2] = {0, 0};
int heading = NORTH;

int main(void) {
    char c; // char from input

    // open file
    input = fopen("input.txt", "r");
    if (input == NULL) {
        puts("Error opening file!");
        return 1;
    }

    // actual work
    do {
        c = fgetc(input);
        if (c == 'R') {
            turn(1);
            move();
        }
        if (c == 'L') {
            turn(-1);
            move();
        }
    } while (c != EOF);

    printf("%dx%d=%d\n", coords[0], coords[1], abs(coords[0]) + abs(coords[1]));

    fclose(input);
    return 0;
}

void turn(int direction) {
    heading += direction;
    if (heading > 3) heading = 0;
    if (heading < 0) heading = 3;
}

void move(void) {
    int distance;
    fscanf(input, "%d", &distance);
    coords[0] += bearings[heading][0] * distance;
    coords[1] += bearings[heading][1] * distance;
}
