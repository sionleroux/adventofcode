#include <stdio.h>
#include <string.h>

// constants
const int keypad[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
const int directions[4][2] = {
    {-1,0},  // U
    {0,1},  // R
    {1,0}, // D
    {0,-1}, // L
};
typedef enum direction { U, R, D, L } direction;

// globals
FILE *input; // input
int coords[2] = {1, 1}; // middle:5

// functions
direction ctod(char c);
void move(direction d);

int main(void) {
    char c; // char from input

    // open file
    input = fopen("input.txt", "r");
    if (input == NULL) {
        puts("Error opening file!");
        return 1;
    }

    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            printf("%d", keypad[coords[0]][coords[1]]);
        } else {
            move(ctod(c));
            /* printf("%c:%d,", c, keypad[coords[0]][coords[1]]); */
        }
    }

    putchar('\n');
    fclose(input);
    return 0;
}

// char to direction
direction ctod(char c) {
    if (c == 'U') return U;
    if (c == 'R') return R;
    if (c == 'D') return D;
    if (c == 'L') return L;
    return -1;
}

void move(direction d) {
    coords[0] += directions[d][0];
    coords[1] += directions[d][1];

    // reset if we moved off the keypad
    if (coords[0] > 2) coords[0] = 2;
    if (coords[1] > 2) coords[1] = 2;
    if (coords[0] < 0) coords[0] = 0;
    if (coords[1] < 0) coords[1] = 0;
}
