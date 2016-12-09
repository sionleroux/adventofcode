#include <stdio.h>
#include <string.h>

// constants
const char keypad[7][7] = {
	"0000000",
	"0001000",
	"0023400",
	"0567890",
	"00ABC00",
	"000D000",
	"0000000"
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
int coords[2] = {3, 1}; // middle:5 Y,X

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

    /* printf("%c start!\n", keypad[coords[0]][coords[1]]); */

    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            printf("%c", keypad[coords[0]][coords[1]]);
            /* printf("%c done!\n", keypad[coords[0]][coords[1]]); */
        } else {
            move(ctod(c));
            /* printf("%c:%c,", c, keypad[coords[0]][coords[1]]); */
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
    // save current coords in case of reset
    int prev[2] = {coords[0], coords[1]};

    // move using directions matrix
    coords[0] += directions[d][0];
    coords[1] += directions[d][1];

    // reset if we moved off the keypad
    if (keypad[coords[0]][coords[1]] == '0') {
        coords[0] = prev[0];
        coords[1] = prev[1];
    }
}
