#include <stdio.h>
#include "house.h"

void arrow_to_coords(char, int*);

int main() {

    char c; // character read from stdin
    int santas = 2; // number of people walking
    int s = 0; // current santa
    int m[santas]; // movement coords
    house* h[santas];
    h[0] = house_init(0, 0); // starting house
    h[1] = house_init(0, 0); // starting house

    while ((c = fgetc(stdin)) != EOF) {
        arrow_to_coords(c, m);
        if (m[0] + m[1] == 0) // {0, 0} Wait
            continue;
        printf("s%d %d:%d\n", s, m[0], m[1]);
        house_add(h[s], m[0], m[1]);

        // give each house to the next santa
        s++;
        if (s >= santas)
            s = 0;

        puts("---");

    }

    printf("house count: %d\n", house_count(h[0], h[1]));

    house_free(h[0]);
    house_free(h[1]);

    return 0;
}

/**
 * Maps arrow directions to matrix that can be added to house
 * coordinates.
 */
void arrow_to_coords(char direction, int *coords) {
    puts("move");
    switch (direction) {
        case '^': // North
            coords[0] = 0;
            coords[1] = 1;
            break;
        case 'v': // South
            coords[0] = 0;
            coords[1] = -1;
            break;
        case '<': // West
            coords[0] = -1;
            coords[1] = 0;
            break;
        case '>': // East
            coords[0] = 1;
            coords[1] = 0;
            break;
        default: // Wait
            coords[0] = 0;
            coords[1] = 0;
            break;
    }
}

// vim:tw=72
