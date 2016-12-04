#include <stdio.h>
#include <stdlib.h>
#include "house.h"

void arrow_to_coords(char, int*);

int main(int argc, char *argv[]) {

    char c; // character read from stdin
    int santas; // number of people walking
    int s = 0; // current santa
    int m[2]; // movement coords
    house* h; // final combined list of houses

    // Get number of Santas from args or default to 1
    if (argc > 1) {
        santas = atoi(argv[1]);
    } else {
        santas = 1;
    }
    house* ha[santas]; // array of house lists

    for (int i = 0; i < santas; ++i)
        ha[i] = house_init(0, 0); // starting house

    while ((c = fgetc(stdin)) != EOF) {

        arrow_to_coords(c, m);
        if (m[0] + m[1] == 0) // {0, 0} Wait
            continue;
        house_add(ha[s], m[0], m[1]);

        // give each house to the next santa
        s++;
        if (s >= santas)
            s = 0;

    }

    h = house_join(ha, santas);
    house_uniq(h);

    printf("%d\n", house_count(h));

    for (int i = 0; i < santas; ++i)
        house_free(ha[i]);

    return 0;
}

/**
 * Maps arrow directions to matrix that can be added to house
 * coordinates.
 */
void arrow_to_coords(char direction, int *coords) {
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
