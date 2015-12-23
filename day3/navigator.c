#include <stdio.h>
#include <stdlib.h>

typedef struct house house;
struct house {
    int x;
    int y;
    house* next;
};

void arrow_to_coords(char, int*);
void house_free(house*);
house* house_init(int, int);
int house_add(house*, int, int);
house* house_find(house*, int, int);
house* house_last(house*);
int house_count(house*);

int main()
{

    int count = 1; // houses visited
    char c; // character read from stdin
    int m[2]; // movement coords
    house* h = house_init(0, 0);
    house* l; // current house I'm at aka last house

    printf("init %d:%d #%d\n", h->x, h->y, count);

    while ((c = fgetc(stdin)) != EOF) {
        arrow_to_coords(c, m);
        if (m[0] + m[1] == 0) // {0, 0} Wait
            continue;
        count += house_add(h, m[0], m[1]);
        l = house_last(h);
        printf("%c %d:%d #%d\n", c, l->x, l->y, count);
    }

    printf("house count: %d\n", count);

    house_free(h);

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

// unneeded because I use only stack memory so far
void house_free(house *first)
{
    house *curr, *head = first;
    while ((curr = head) != NULL) {
        head = head->next;
        free(curr);
    }
}

house* house_init(int x, int y)
{
    house *h = malloc(sizeof(house));

    h->next = NULL;
    h->x = x;
    h->y = y;

    return h;
}

/**
 * Adds a new house to the list of visited houses.
 * Expects a pointer to the first house in the list and the current
 * cooridinates.
 * Returns 1 if this house hasn't been visited before, otherwise 0.
 */
int house_add(house *f, int x, int y)
{
    int unique = 0;
    house *last = house_last(f);
    house *new = house_init(last->x + x, last->y + y);

    // check if it's already in the list
    if (!house_find(f, new->x, new->y))
        unique = 1;

    // add to the list
    last->next = new;

    return unique;
}

/**
 * Finds a house by cooridinates.
 * Expects a pointer to the first house in the list and integers for x
 * and y coordinates.
 * Returns a pointer to a house matching the provided coordinates or
 * NULL if not found.
 */
house* house_find(house *h, int x, int y)
{
    int c = 0;

    house *i = h;

    while (i != NULL) {
        if (i->x == x && i->y == y)
            return i;

        i = i->next;
        c++;
    }

    return NULL;
}

/**
 * Returns a pointer to the last house in a list of houses.
 * Expects a pointer to the start of a list of houses.
 */
house* house_last(house *h)
{
    house *i = h;

    while (i->next != NULL)
        i = i->next;

    return i;
}

/**
 * Counts the number of houses in a list of houses.
 * Expects a pointer to the first house in a list of houses.
 * Returns the number of unique houses.
 */
int house_count(house *h)
{
    house *i = h;
    int c = 1; // number of houses

    while (i->next != NULL) {
        i = i->next;
        c++;
    }

    return c;
}

// vim:tw=72
